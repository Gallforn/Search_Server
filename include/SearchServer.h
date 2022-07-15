//
// Created by Maxim on 02.04.2022.
//

#ifndef SEARCH_ENGINE_SEARCH_SERVER_H
#define SEARCH_ENGINE_SEARCH_SERVER_H

#include <QString>
#include "InvertedIndex.h"
#include "ui_UI.h"

namespace se {
    struct RelativeIndex {                                    //Структура для хранения релевантности поиска для каждого
        std::string filePath;                                       //запроса из requests.json к каждому документу
        float       rank_;
    };

    class SearchServer {
    public: //public methods
        SearchServer() : index_(se::InvertedIndex()){};    //конструктор, создает объект InvertedIndex, принимает
                                                           //вектор с именами документов для вызова метода
                                                           //se::InvertedIndex::UpdateDocumentBase

        void search(const std::string&, Ui::MainWindow*); //search() - метод для поиска по запросам из requests.json

        void updateInvertedIndex(const std::vector<std::string>&, Ui::MainWindow*);

    public: //public fields
        std::vector<se::RelativeIndex> search_result;         //Хранит результат поиска

    private: //private fields
         InvertedIndex index_;                                 //объект класса InvertedIndex
    };
}

#endif //SEARCH_ENGINE_SEARCH_SERVER_H
