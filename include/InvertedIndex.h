//
// Created by Maxim on 01.04.2022.
//

#ifndef SEARCH_ENGINE_INVERTEDINDEX_H
#define SEARCH_ENGINE_INVERTEDINDEX_H

#include <vector>
#include <map>
#include <string>
#include <QString>
#include "ui_UI.h"

namespace se
{
    struct Entry
    {
        std::string filePath;
        size_t      count;
    };

    class InvertedIndex {
    public:
        InvertedIndex() = default;                                    //Конструктор по умолчанию

        void UpdateDocumentBase(std::vector<std::string>, Ui::MainWindow*);  //Метод, осуществляющий многопоточный поиск,
                                                                      //1 поток - 1 файл
        std::vector <Entry> GetWordCount(const std::string &word);    //Возвращает все вхождения слова word во все
                                                                      //документы
        bool empty();                                                 //Метод для проверки отсутствия элементов в freq_dictionary

    private:
        std::map <std::string, std::vector<Entry>> freq_dictionary;   //Частотный словарь, для каждого слова хранит
    };                                                                                 //id документа и количество данных слов в нем
}

#endif //SEARCH_ENGINE_INVERTEDINDEX_H
