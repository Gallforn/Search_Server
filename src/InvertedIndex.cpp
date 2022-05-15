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

void se::InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs)
{
    std::cout << "Start update document base..." << std::endl;

    freq_dictionary.clear();

    std::recursive_mutex                access_locker;
    size_t                              input_docs_index{0};
    size_t                              input_docs_size{input_docs.size()};
    std::thread*                        th{nullptr};
    std::atomic<int>                    thread_counter{0};

    std::function<void(std::string, size_t)> text_extract = [&access_locker, &thread_counter, this]
                      (std::string path, size_t index){
        ++thread_counter;

        std::ifstream file(path, std::ios::app);

        if(!file.is_open() || file.fail() || file.bad())
        {
            access_locker.lock();
            std::cerr << "Error opening " << path << " file!" << std::endl;
            access_locker.unlock();
            return;
        }

        std::string              file_buffer; //текст из файла
        std::string              word;        //буфер для слов из file_buffer

        std::getline(file, file_buffer, '\0');

        file.close();

        for(auto& fBufIt : file_buffer)
        {
            if(fBufIt >= 'a' && fBufIt <= 'z')
            {
                word += fBufIt;
            }
            else if(fBufIt >= 'A' && fBufIt <= 'Z') //Приводим все заглавные буквы к прописным, только для ASCII
            {
                fBufIt += 32;
                word += fBufIt;
            }
            else if(!word.empty())
            {
                access_locker.lock();
                if (freq_dictionary.find(word) == freq_dictionary.end() || freq_dictionary[word][index].doc_id != index)
                {
                    freq_dictionary[word].push_back({index, 1});
                }
                else
                {
                    ++freq_dictionary[word][index].count;
                }
                access_locker.unlock();

                word.clear();
            }
        }
        --thread_counter;
    };

    for(; input_docs_index < input_docs_size; ++input_docs_index)
    {

        try
        {
            th = new std::thread(text_extract, input_docs[input_docs_index], input_docs_index);
        }
        catch(std::exception& exc)
        {
            std::cerr << exc.what() << std::endl;
            --input_docs_index;
        }

        if(th->joinable())
        {
            th->detach();
        }

    }

    while(thread_counter > 0)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    delete th;

    std::cout << "Update document base is over." << std::endl;
}

std::vector <se::Entry> se::InvertedIndex::GetWordCount(const std::string &word)
{
     return freq_dictionary[word];
}

