//
// Created by Maxim on 01.07.2022.
//

#include "ImplSearchClasses.h"
#include "SearchServer.h"
#include "ConvertJson.h"

Impl::Impl() : sS(new se::SearchServer()), cJ(new se::ConvertJSON()){};

Impl::~Impl()
{
    delete sS;
    delete cJ;
}

