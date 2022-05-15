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
    std::thread*                        th_1{nullptr};
    std::thread*                        th_2{nullptr};
    std::thread*                        th_3{nullptr};
    auto* th_1_ready =                  new std::atomic<bool>(true);
    auto* th_2_ready =                  new std::atomic<bool>(true);
    auto* th_3_ready =                  new std::atomic<bool>(true);

    std::function<void(std::string, size_t, std::atomic<bool>*)> text_extract = [&access_locker, this]
                      (std::string path, size_t index, std::atomic<bool>* is_ready){

        *is_ready = false;

        std::ifstream file(path, std::ios::app);

        if(!file.is_open() || file.fail() || file.bad())
        {
            *is_ready = true;
            access_locker.lock();
            std::cerr << "Error opening " << path << " file!" << std::endl;
            access_locker.unlock();
            return;
        }

        std::string        file_buffer;

        std::getline(file, file_buffer, '\0');

        file.close();

        std::string              word;
        std::vector<std::string> words;

        for(auto& fBufIt : file_buffer) //извлечение слов из буфера
        {
            if((fBufIt >= 'A' && fBufIt <= 'Z') || (fBufIt >= 'a' && fBufIt <= 'z'))
            {
                word += fBufIt;
            }
            else if(!word.empty())
            {
                words.push_back(word);
                word.clear();
            }
        }

        for(auto& wordsIt : words)
        {
                for (auto &wordsItIt: wordsIt) { //Приводим все заглавные буквы к прописным, только для ASCII
                    if (wordsItIt >= 'A' && wordsItIt <= 'Z') {
                        wordsItIt += 32;
                    }
                }

                access_locker.lock();
                if (freq_dictionary.find(wordsIt) == freq_dictionary.end() ||
                    freq_dictionary[wordsIt][index].doc_id != index) {
                    freq_dictionary[wordsIt].push_back({index, 1});
                } else {
                    ++freq_dictionary[wordsIt][index].count;
                }
                access_locker.unlock();
        }

        *is_ready = true;
    };

    do
    {
        if(input_docs_index < input_docs_size && *th_1_ready)
        {
            try
            {
                th_1 = new std::thread(text_extract, input_docs[input_docs_index], input_docs_index, th_1_ready);
                ++input_docs_index;
            }
            catch(std::exception& exc)
            {
                std::cerr << exc.what() << std::endl;
                --input_docs_index;
            }
        }

        if(input_docs_index < input_docs_size && *th_2_ready)
        {
            try
            {
                th_2 = new std::thread(text_extract, input_docs[input_docs_index], input_docs_index, th_2_ready);
                ++input_docs_index;
            }
            catch(std::exception& exc)
            {
                std::cerr << exc.what() << std::endl;
                --input_docs_index;
            }
        }

        if(input_docs_index < input_docs_size && *th_3_ready)
        {
            try
            {
                th_3 = new std::thread(text_extract, input_docs[input_docs_index], input_docs_index, th_3_ready);
                ++input_docs_index;
            }
            catch(std::exception& exc)
            {
                std::cerr << exc.what() << std::endl;
                --input_docs_index;
            }
        }

        if(th_1 != nullptr && th_1->joinable() && *th_1_ready)
        {
            th_1->join();
        }
        if(th_2 != nullptr && th_2->joinable() && *th_2_ready)
        {
            th_2->join();
        }
        if(th_3 != nullptr && th_3->joinable() && *th_3_ready)
        {
            th_3->join();
        }

    }while(input_docs_index < input_docs_size || !*th_1_ready || !*th_2_ready || !*th_3_ready);

    delete th_1_ready;
    delete th_2_ready;
    delete th_3_ready;

    delete th_1;
    delete th_2;
    delete th_3;

    std::cout << "Update document base is over." << std::endl;
}

std::vector <se::Entry> se::InvertedIndex::GetWordCount(const std::string &word)
{
     return freq_dictionary[word];
}

