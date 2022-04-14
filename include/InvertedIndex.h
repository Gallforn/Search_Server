//
// Created by Maxim on 01.04.2022.
//

#ifndef SEARCH_ENGINE_INVERTEDINDEX_H
#define SEARCH_ENGINE_INVERTEDINDEX_H

#include <vector>
#include <map>
#include <string>

namespace se {
    struct Entry {
        size_t doc_id;
        size_t count;
    };

    class InvertedIndex {
    public:
        InvertedIndex() = default;

        void UpdateDocumentBase(std::vector<std::string> input_docs);

        std::vector <Entry> GetWordCount(const std::string &word);

    private:
        std::vector <std::string> docs;
        std::map <std::string, std::vector<Entry>> freq_dictionary;
    };
}

#endif //SEARCH_ENGINE_INVERTEDINDEX_H
