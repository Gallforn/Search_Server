//
// Created by Maxim on 31.03.2022.
//

#ifndef SEARCH_ENGINE_JSON_CLASS_H
#define SEARCH_ENGINE_JSON_CLASS_H

#include "json.hpp"
#include "SearchServer.h"

namespace se
{
class ConvertJSON
{
public:
    ConvertJSON();                                                        //Конструктор

    std::vector <std::string> GetNamesDocuments();                        //Возвращает вектор строк, c путями до файлов

    int GetResponsesLimit();                                              //Возвращает лимит ответов для каждого запроса

    std::vector <std::string> GetRequests();                              //Возвращает запросы из файла requests.json

    void putAnswers(std::vector<std::vector<se::RelativeIndex>> answers); //Запысывает результат поиска в answers.json

private:
    nlohmann::json config;                                                //Хранение содержимого config.json
    nlohmann::json requests;                                              //Хранение содержимого requests.json
    nlohmann::json answers;                                               //Хранит результат поиска для записи в
                                                                          // answers.json
};

}

#endif //SEARCH_ENGINE_JSON_CLASS_H
