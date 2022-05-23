//
// Created by Maxim on 01.04.2022.
//

#ifndef SEARCH_ENGINE_INVERTEDINDEX_H
#define SEARCH_ENGINE_INVERTEDINDEX_H

#include <vector>
#include <map>
#include <string>
#include <atomic>

namespace se {
    struct Entry {                                                    //Структура для хранения номера документа
        size_t doc_id;                                                //(нумерация с 0) и количество вхождений слова
        size_t count;                                                 //к которому она прикреплена

        // Данный оператор необходим для проведения тестовых сценариев
        bool operator == (const se::Entry& other) const {
            return (doc_id == other.doc_id && count == other.count);
        }
        };

    class InvertedIndex {
    public:
        InvertedIndex() = default;                                    //Конструктор по умолчанию

        void UpdateDocumentBase(std::vector<std::string> docsNames);  //Метод, осуществляющий многопоточный поиск,
                                                                      //1 поток - 1 файл
        std::vector <Entry> GetWordCount(const std::string &word);    //Возвращает все вхождения слова word во все
                                                                      //документы
    public:
        std::map <std::string, std::vector<Entry>> freq_dictionary;   //Частотный словарь, для каждого слова хранит
    };                                                                //id документа и количество данных слов в нем

    void textExtract(std::string, size_t, std::atomic<int>*, se::InvertedIndex*);    //Функция для выполнения в потоках
}

#endif //SEARCH_ENGINE_INVERTEDINDEX_H
