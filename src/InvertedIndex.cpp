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
    docs.clear();
    freq_dictionary.clear();
    docs.resize(input_docs.size());

    __gnu_cxx::__recursive_mutex        docs_locker;
    std::vector<std::string>::size_type iBeg{0};
    std::vector<std::string>::size_type iEnd{input_docs.size()};
    std::thread*                        th_1;
    std::thread*                        th_2;
    std::thread*                        th_3;

    std::function<void(size_t)> text_extract = [&input_docs, &docs_locker, this](size_t index){

        std::ifstream file(input_docs[index], std::ios::app);
        std::string   buffer;

        std::getline(file, buffer, '\0');

        file.close();

        auto it = docs.begin();

        std::advance(it, index);

        docs_locker.lock();
        docs.emplace(it, buffer);
        docs_locker.unlock();

        std::stringstream ss;


        ss << docs[index];


        while(ss >> buffer)
        {
            docs_locker.lock();
            if(freq_dictionary.find(buffer) == freq_dictionary.end() || freq_dictionary[buffer][index].doc_id != index)
            {
                freq_dictionary[buffer].push_back({index, 1});
            }
            else
            {
                ++freq_dictionary[buffer][index].count;
            }
            docs_locker.unlock();
        }
    };

    do
    {
        if(iBeg < iEnd)
        {
            th_1 = new std::thread(text_extract, iBeg);
            ++iBeg;
        }
        if(iBeg < iEnd)
        {
            th_2 = new std::thread(text_extract, iBeg);
            ++iBeg;
        }
        if(iBeg < iEnd)
        {
            th_3 = new std::thread(text_extract, iBeg);
            ++iBeg;
        }
        if(th_1->joinable())
        {
            th_1->join();
        }

        if(th_2->joinable())
        {
            th_2->join();
        }

        if(th_3->joinable())
        {
            th_3->join();
        }

    }while(iBeg < iEnd || th_1->joinable() || th_2->joinable() || th_3->joinable());
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

