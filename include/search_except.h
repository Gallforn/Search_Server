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
        [[nodiscard]] const char* what()  const noexcept override;
    };

    class InvalidVersion : public std::exception
    {
    public:
        InvalidVersion() = default;
        [[nodiscard]] const char* what() const noexcept override;
    };

    class NoExistFile : public std::exception
    {
    public:
        NoExistFile() = default;
        [[nodiscard]] const char* what() const noexcept override;
    };

}

#endif //SEARCH_ENGINE_EXEPTIONS_H
