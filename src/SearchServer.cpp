//
// Created by Maxim on 02.04.2022.
//
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "SearchServer.h"

se::SearchServer::SearchServer(std::vector<std::string> docs_names) : index_(se::InvertedIndex())
{
    index_.UpdateDocumentBase(std::move(docs_names));
}


std::vector<std::vector<se::RelativeIndex>> se::SearchServer::search(const std::vector<std::string>& queries_input)
{
    std::cout << "Starting search..." << std::endl;

    std::vector<std::vector<se::RelativeIndex>>  result { }; //результат, возвращаемый из метода
    std::stringstream ss                                { }; //строковый поток для извлечения отдельных слов из запроса
    std::map<size_t, float> rank                        { }; //класс для хранения абс. релевантности для каждого док-та
                                                             //обрабатываемого запроса
    std::string buffer                                  { }; //строка буффер для извлечения слов запроса из ss
    size_t req_id                                       {0}; //номер запроса

    result.resize(queries_input.size());

    for(auto bIt{queries_input.begin()}, eIt{queries_input.end()}; bIt != eIt; ++bIt, ++req_id)
    {
        rank.clear();
        float maxR{0.0f};
        ss.clear();
        ss << *bIt;

        while(ss >> buffer)
        {
            for(size_t buf_idx{0}, buf_size{buffer.size()}; buf_idx < buf_size; ++buf_idx)
            { //Приводим все заглавные буквы к прописным
                if(buffer[buf_idx] >= 'A' && buffer[buf_idx] <= 'Z')
                {
                    buffer[buf_idx] += 32;
                }
            }

            std::vector<se::Entry> entry_word = index_.GetWordCount(buffer);

            if(!entry_word.empty())
            {
                for(auto &i : entry_word)
                {
                    rank[i.doc_id] += static_cast<float>(i.count);
                    if(rank[i.doc_id] > maxR)
                    {
                        maxR = rank[i.doc_id];
                    }
                }
            }
        }

        std::vector<std::pair<size_t, float>> sort_rank; //вектор для сортировки пар из класса rank

        for(auto &i : rank)
        {
            i.second /= maxR;
            sort_rank.emplace_back(i);
        }

        std::sort(sort_rank.begin(), sort_rank.end(), [](std::pair<size_t, float> &a, std::pair<size_t, float> &b)
        {
            if(a.second == b.second)
            {
                return a.first < b.first;
            }
            else return a.second > b.second;
        });

        if(sort_rank.empty())
        {
            result[req_id].push_back({});
        }
        else
        {
            for(auto &i : sort_rank)
            {
                result[req_id].push_back({static_cast<int>(i.first), i.second});
            }
        }
    }

    std::cout << "Search is over." << std::endl;

    return result;
}


