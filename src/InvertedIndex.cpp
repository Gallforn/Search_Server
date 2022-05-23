//
// Created by Maxim on 01.04.2022.
//
#include <fstream>
#include <iostream>
#include <mutex>
#include <thread>
#include <exception>
#include <atomic>
#include "InvertedIndex.h"
#include "ConvertJson.h"

std::mutex access_locker;

void se::textExtract(std::string path, size_t index, std::atomic<int>* thread_counter, se::InvertedIndex* iI)
{
    access_locker.lock();
    std::cout << "Thread " << index << std::endl;
    access_locker.unlock();
    ++*thread_counter;

    std::ifstream file(path, std::ios::app);

    if(!file.is_open() || file.fail() || file.bad())
    {
        access_locker.lock();
        std::cerr << "Error opening " << path << " file!" << std::endl;
        access_locker.unlock();
        return;
    }

    std::string              fileBuffer;      //текст из файла
    std::string              word;            //буфер для слов из file_buffer

    std::getline(file, fileBuffer, '\0');

    file.close();

    for(auto fBufIt{fileBuffer.begin()}, fBufEnd{fileBuffer.end()}; fBufIt != fBufEnd; ++fBufIt)
    {
        if(*fBufIt >= 'a' && *fBufIt <= 'z')      //Цикл получает слова из fileBuffer без "примесей"
        {                                         //лишних символов
            word += *fBufIt;
        }
        else if(*fBufIt >= 'A' && *fBufIt <= 'Z') //Приводим все заглавные буквы к прописным, только для ASCII
        {
            *fBufIt += 32;
            word += *fBufIt;
        }
        if((!word.empty() && (!(*fBufIt >= 'a' && *fBufIt <= 'z') && !(*fBufIt >= 'A' && *fBufIt <= 'Z'))) ||
          (!word.empty() && fBufIt == fBufEnd - 1))
        {
            std::lock_guard<std::mutex> accessGuard(access_locker);
            if (iI->freq_dictionary.find(word) == iI->freq_dictionary.end() || iI->freq_dictionary[word][index].doc_id != index)
            {
                iI->freq_dictionary[word].push_back({index, 1});
            }
            else
            {
                ++iI->freq_dictionary[word][index].count;
            }
            word.clear();
        }
    }

    access_locker.lock();
    std::cout << "Thread end " << index << std::endl;
    access_locker.unlock();

    --*thread_counter;
}

void se::InvertedIndex::UpdateDocumentBase(std::vector<std::string> docsNames)
{
    std::cout << "Start update document base..." << std::endl;

    freq_dictionary.clear();

    auto* thread_counter = new std::atomic<int>{0};  //Подсчитывает количество потоков, используется чтобы
                                                       // не дать выйти из метода UpdateDocumentBase если оно не 0
    for(size_t input_docs_index{0}, input_docs_size{docsNames.size()}; input_docs_index < input_docs_size; ++input_docs_index)
    {
#ifdef TESTS1
        try
        {
            std::thread th(textExtract, docsNames[input_docs_index], input_docs_index, thread_counter, this);

            th.join();
        }
        catch(std::exception& exc)
        {
            std::cerr << exc.what() << std::endl;
            --input_docs_index;
        }
#endif
        textExtract(docsNames[input_docs_index], input_docs_index, thread_counter, this);
    }

    while(*thread_counter > 0)
    {
        std::cout << thread_counter << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    std::cout << "Update document base is over." << std::endl;
}

std::vector <se::Entry> se::InvertedIndex::GetWordCount(const std::string &word)
{
    std::vector<Entry> result;

    for(size_t iBeg{0}, iEnd{freq_dictionary[word].size()}; iBeg < iEnd; ++iBeg)
    {
        result.push_back(freq_dictionary[word][iBeg]);
    }

    return result;
}

