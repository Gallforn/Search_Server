//
// Created by Maxim on 01.04.2022.
//
#include <fstream>
#include <iostream>
#include <mutex>
#include <thread>
#include "InvertedIndex.h"
#include "ConvertJson.h"

void se::InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs)
{
    std::cout << "Start update document base..." << std::endl;

    docs.clear();
    freq_dictionary.clear();
    docs.resize(input_docs.size());

    std::recursive_mutex                access_locker;
    size_t                              input_docs_index{0};
    size_t                              input_docs_size{input_docs.size()};
    std::thread*                        th_1;
    std::thread*                        th_2;
    std::thread*                        th_3;
    bool* th_1_ready =                  new bool(true);
    bool* th_2_ready =                  new bool(true);
    bool* th_3_ready =                  new bool(true);

    std::function<void(size_t, bool*)> text_extract = [&input_docs, &access_locker, this](size_t index, bool* is_ready){
        access_locker.lock();
        *is_ready = false;
        access_locker.unlock();

        access_locker.lock();
        std::ifstream file(input_docs[index], std::ios::app);
        access_locker.unlock();

        std::string       buffer;
        std::stringstream ss;

        std::getline(file, buffer, '\0');

        file.close();

        access_locker.lock();
        auto it = docs.begin();
        std::advance(it, index);
        docs.emplace(it, buffer);
        ss << docs[index];
        access_locker.unlock();


        while(ss >> buffer)
        {
            for(size_t buf_idx{0}, buf_size{buffer.size()}; buf_idx < buf_size; ++buf_idx)
            { //Приводим все заглавные буквы к прописным
                if(buffer[buf_idx] >= 'A' && buffer[buf_idx] <= 'Z')
                {
                    buffer[buf_idx] += 32;
                }
            }
            access_locker.lock();
            if(freq_dictionary.find(buffer) == freq_dictionary.end() || freq_dictionary[buffer][index].doc_id != index)
            {
                freq_dictionary[buffer].push_back({index, 1});
            }
            else
            {
                ++freq_dictionary[buffer][index].count;
            }
            access_locker.unlock();
        }
        access_locker.lock();
        *is_ready = true;
        access_locker.unlock();
    };

    do
    {
        if(input_docs_index < input_docs_size && *th_1_ready)
        {
            th_1 = new std::thread(text_extract, input_docs_index, th_1_ready);
            ++input_docs_index;
        }
        if(input_docs_index < input_docs_size && *th_2_ready)
        {
            th_2 = new std::thread(text_extract, input_docs_index, th_2_ready);
            ++input_docs_index;
        }
        if(input_docs_index < input_docs_size && *th_3_ready)
        {
            th_3 = new std::thread(text_extract, input_docs_index, th_3_ready);
            ++input_docs_index;
        }
        if(th_1->joinable() && *th_1_ready)
        {
            th_1->join();
        }

        if(th_2->joinable() && *th_2_ready)
        {
            th_2->join();
        }

        if(th_3->joinable() && *th_3_ready)
        {
            th_3->join();
        }

    }while(input_docs_index < input_docs_size || th_1->joinable() || th_2->joinable() || th_3->joinable());

    delete th_1_ready;
    delete th_2_ready;
    delete th_3_ready;

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

