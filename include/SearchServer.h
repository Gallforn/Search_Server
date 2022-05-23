//
// Created by Maxim on 02.04.2022.
//

#ifndef SEARCH_ENGINE_SEARCH_SERVER_H
#define SEARCH_ENGINE_SEARCH_SERVER_H

#include "InvertedIndex.h"

namespace se {
    struct RelativeIndex {                                    //Структура для хранения релевантности поиска для каждого
        int    doc_id_;                                       //запроса из requests.json к каждому документу
        float  rank_;

        bool operator ==(const RelativeIndex& other) const    //для тестирования
        {
            return (doc_id_ == other.doc_id_ && rank_ == other.rank_);
        }
    };

    class SearchServer {
    public:
        SearchServer(std::vector<std::string> docs_names);    //конструктор, создает объект InvertedIndex, принимает
                                                              //вектор с именами документов для вызова метода
                                                              //se::InvertedIndex::UpdateDocumentBase

        std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input);
        //search() - метод для поиска по запросам из requests.json
    private:
        InvertedIndex index_;                                 //объукт класса InvertedIndex
    };
}

#endif //SEARCH_ENGINE_SEARCH_SERVER_H
