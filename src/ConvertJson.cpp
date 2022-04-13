//
// Created by Maxim on 31.03.2022.
//
#include <fstream>
#include <vector>
#include <iostream>
#include "nlohmann/json.hpp"
#include "ConvertJson.h"
#include "search_except.h"
#include "SearchServer.h"

se::ConvertJSON::ConvertJSON()
{
    std::ifstream file(L"C:\\Users\\Maxim\\CLionProjects\\Search_Engine\\.json\\config.json", std::ios::app);

    if(file.fail()) throw se::NoExistFile();

    file >> config;

    file.close();

    if(config["config"].empty()) throw se::EmptyConfig();

    if(config["config"]["version"] != "0.1") throw se::InvalidVersion();

    if(config["config"]["max_responses"] == 0) config["config"]["max_responses"] = 5;

    file.open(L"C:\\Users\\Maxim\\CLionProjects\\Search_Engine\\.json\\requests.json", std::ios::app);

    if(file.fail()) throw se::NoExistFile();

    file >> requests;

    file.close();

}

std::vector<std::string> se::ConvertJSON::GetTextDocuments()
{
    std::vector<std::string> result;

    for(auto b{config["files"].begin()}, e{config["files"].end()}; b != e; ++b)
    {
        result.push_back(*b);
    }
    return result;
}

int se::ConvertJSON::GetResponsesLimit()
{
    return config["config"]["max_responses"];
}

std::vector<std::string> se::ConvertJSON::GetRequests()
{
    std::vector<std::string> result;

    for(auto bIt{requests["requests"].begin()}, eIt{requests["requests"].end()}; bIt != eIt; ++bIt)
    {
        result.push_back(*bIt);
    }

    return result;
}

void se::ConvertJSON::putAnswers(std::vector<std::vector<se::RelativeIndex>> ans)
{
    std::ofstream file(L"C:\\Users\\Maxim\\CLionProjects\\Search_Engine\\.json\\answers.json");

    int number{1};
    int responses_limit{GetResponsesLimit()};

    for(std::vector<std::vector<std::pair<int, float>>>::size_type iBeg{0}, iEnd{ans.size()}; iBeg < iEnd; ++iBeg, ++number)
    {
        for(std::vector<se::RelativeIndex>::size_type jBeg{0}, jEnd{ans[iBeg].size()}; jBeg < jEnd && jBeg <= responses_limit; ++jBeg)
        {
            if(ans[iBeg][jBeg].rank_ == 0.0f)
            {
                answers["answers"]["request" + std::to_string(number)]["result"] = false;
            }
            else
            {
                answers["answers"]["request" + std::to_string(number)]["result"] = true;

                if(ans[iBeg].size() > 1)
                {
                    answers["answers"]["request" + std::to_string(number)]["relevance"].push_back({ans[iBeg][jBeg].doc_id_, ans[iBeg][jBeg].rank_});
                }
                else
                {
                    answers["answers"]["request" + std::to_string(number)]["doc_id"] = ans[iBeg][jBeg].doc_id_;
                    answers["answers"]["request" + std::to_string(number)]["rank"] = ans[iBeg][jBeg].rank_;
                }
            }
        }

    }

    file << answers;

    file.close();
}

