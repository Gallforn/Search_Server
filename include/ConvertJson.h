//
// Created by Maxim on 31.03.2022.
//

#ifndef SEARCH_ENGINE_JSON_CLASS_H
#define SEARCH_ENGINE_JSON_CLASS_H

#include "nlohmann/json.hpp"
#include "SearchServer.h"

namespace se
{
class ConvertJSON
{
public:
    ConvertJSON();

    std::vector <std::string> GetTextDocuments();

    int GetResponsesLimit();

    std::vector <std::string> GetRequests();

    void putAnswers(std::vector<std::vector<se::RelativeIndex>> answers);

private:
    nlohmann::json config;
    nlohmann::json requests;
    nlohmann::json answers;
};

}

#endif //SEARCH_ENGINE_JSON_CLASS_H
