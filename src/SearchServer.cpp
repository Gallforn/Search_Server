//
// Created by Maxim on 02.04.2022.
//
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "SearchServer.h"


std::vector<std::vector<se::RelativeIndex>> se::SearchServer::search(const std::vector<std::string>& queries_input)
{
    std::vector<std::vector<se::RelativeIndex>>  result { };
    std::vector<size_t> rList                           { };
    std::stringstream ss                                { };
    std::map<size_t, float> rank                        { };
    std::string buffer                                  { };
    size_t req_id                                       {0};
    float maxR                                          { };

    result.resize(queries_input.size());

    for(auto bIt{queries_input.begin()}, eIt{queries_input.end()}; bIt != eIt; ++bIt, ++req_id)
    {
        rank.clear();
        maxR = 0;
        ss.clear();
        ss << *bIt;

        while(ss >> buffer)
        {
            std::vector<se::Entry> entry_word = index_.GetWordCount(buffer);

            if(!entry_word.empty())
            {
                for(auto &i : entry_word)
                {
                    rank[i.doc_id] += i.count;
                    if(rank[i.doc_id] > maxR)
                    {
                        maxR = rank[i.doc_id];
                    }
                }
            }
        }

        std::vector<std::pair<size_t, float>> sort_rank;

        for(auto &i : rank)
        {
            i.second /= maxR;
            sort_rank.emplace_back(i);
        }

        std::sort(sort_rank.begin(), sort_rank.end(), [](std::pair<size_t, float> &a, std::pair<size_t, float> &b)
        {
            return a.second > b.second;
        });

        if(sort_rank.empty())
        {
            result[req_id].push_back({0, 0});
        }
        else
        {
            for(auto &i : sort_rank)
            {
                result[req_id].push_back({(int)i.first, i.second});
            }
        }
    }
    return result;
}


