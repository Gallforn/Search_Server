//
// Created by Maxim on 31.03.2022.
//
#include <exception>
#include "search_except.h"

const char* se::EmptyConfig::what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW
{
    return "Config file is empty!";
}

const char* se::InvalidVersion::what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW
{
    return "config.json has incorrect file version!";
}

const char* se::NoExistFile::what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW
{
    return "File no exist!";
}

