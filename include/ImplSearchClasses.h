//
// Created by Maxim on 01.07.2022.
//

#ifndef SEARCH_ENGINE_IMPLSEARCHCLASSES_H
#define SEARCH_ENGINE_IMPLSEARCHCLASSES_H

#include "SearchServer.h"
#include "ConvertJson.h"
#include "InvertedIndex.h"

struct Impl
{
    Impl();
    ~Impl();

    se::SearchServer* sS;
    se::ConvertJSON*  cJ;
};

#endif //SEARCH_ENGINE_IMPLSEARCHCLASSES_H
