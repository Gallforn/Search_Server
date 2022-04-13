//
// Created by Maxim on 02.04.2022.
//

#ifndef SEARCH_ENGINE_SEARCH_SERVER_H
#define SEARCH_ENGINE_SEARCH_SERVER_H

#include "InvertedIndex.h"

namespace se {
    struct RelativeIndex {
        int    doc_id_;
        float  rank_;
    };

    class SearchServer {
    public:
        SearchServer(InvertedIndex &idx) : index_(idx) {};

        std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input);
    private:
        InvertedIndex& index_;
    };
}

#endif //SEARCH_ENGINE_SEARCH_SERVER_H
