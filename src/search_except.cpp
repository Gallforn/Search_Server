//
// Created by Maxim on 31.03.2022.
//
#include <exception>
#include "search_except.h"

const char* se::EmptyConfig::what() const noexcept
{
    return "Config file is empty!";
}

const char* se::InvalidVersion::what() const noexcept
{
    return "config.json has incorrect file version!";
}

const char* se::NoExistFile::what() const noexcept
{
    return "File no exist!";
}

