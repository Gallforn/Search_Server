//
// Created by Maxim on 31.03.2022.
//
#include <fstream>
#include <vector>
#include <iostream>
#include "json.hpp"
#include "ConvertJson.h"
#include "search_except.h"
#include "SearchServer.h"

se::ConvertJSON::ConvertJSON()
{
    std::ifstream file("../../.json/config.json", std::ios::app);

    if(file.fail() || !file.is_open()) throw se::NoExistFile();

    file >> config;

    file.close();

    if(config["config"].empty()) throw se::EmptyConfig();

    if(config["config"]["version"] != "0.4") throw se::InvalidVersion();

    if(config["config"]["max_responses"] == 0) config["config"]["max_responses"] = 5;

    file.open("../../.json/requests.json", std::ios::app);

    if(file.fail()) throw se::NoExistFile();

    file >> requests;

    file.close();

    std::cout << "Starting " << config["config"]["name"] << " ver. " << config["config"]["version"] << std::endl;
}

std::vector<std::string> se::ConvertJSON::GetNamesDocuments()
{
    std::vector<std::string> result;

    std::string prefix = config["config"]["data_base_dir"];
    //prefix.erase(prefix.size() - 1);

    for(auto& it : config["files"])
    {
        result.push_back(prefix + "/" += it);
    }
    return result;
}

int se::ConvertJSON::GetResponsesLimit()
{
    return config["config"]["max_responses"];
}

std::vector<std::string> se::ConvertJSON::GetRequests()
{
    return requests["requests"];
}

void se::ConvertJSON::putAnswers(std::vector<std::vector<se::RelativeIndex>> ans)
{
    std::ofstream file("../../.json/answers.json");

    int number{1};
    int responses_limit{GetResponsesLimit()};

    for(size_t iBeg{0}, iEnd{ans.size()}; iBeg < iEnd; ++iBeg, ++number)
    {
        for(size_t jBeg{0}, jEnd{ans[iBeg].size()}; jBeg < jEnd && jBeg <= responses_limit; ++jBeg)
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

    file << answers.dump(4);

    file.close();
}

