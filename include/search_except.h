//
// Created by Maxim on 31.03.2022.
//

#ifndef SEARCH_ENGINE_EXEPTIONS_H
#define SEARCH_ENGINE_EXEPTIONS_H

namespace se
{
    class EmptyConfig : public std::exception
    {
    public:
        EmptyConfig() = default;
        const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
    };

    class InvalidVersion : public std::exception
    {
    public:
        InvalidVersion() = default;
        const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
    };

    class NoExistFile : public std::exception
    {
    public:
        NoExistFile() = default;
        const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
    };

}

#endif //SEARCH_ENGINE_EXEPTIONS_H
