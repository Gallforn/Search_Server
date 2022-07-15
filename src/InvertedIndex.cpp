//
// Created by Maxim on 01.04.2022.
//
#include <fstream>
#include <iostream>
#include <mutex>
#include <thread>
#include <exception>
#include <atomic>
#include <functional>
#include <QString>
#include "InvertedIndex.h"
#include "MainWindow.h"
#include "ui_UI.h"

void se::InvertedIndex::UpdateDocumentBase(std::vector<std::string> docsNames, Ui::MainWindow* mW)
{
    MainWindow::logger("Start update document base...", mW);

    freq_dictionary.clear();

    std::mutex accessLocker;                                        //ограничение доступа к freq_dictionary

    auto threadIsOver = std::make_unique<std::atomic<bool>>(false); //атомарный флаг завершения потоков

    std::function<void(std::string, size_t, size_t)> textExt = [this, &threadIsOver, &accessLocker, mW]
            (std::string&& path, size_t index, size_t docNamesCount){

        std::ifstream file(path, std::ios::in);

        if(!file.is_open() || file.fail() || file.bad())
        {
            accessLocker.lock();
            MainWindow::logger("Error opening file: " + static_cast<QString>(path.c_str()), mW);
            accessLocker.unlock();

            if(index == docNamesCount)
            {
                *threadIsOver = true;
            }

            return;
        }

        std::string              fileBuffer;      //текст из файла
        std::string              word;            //буфер для слов из file_buffer

        std::getline(file, fileBuffer, '\0');

        file.close();

        for(auto fBufIt{fileBuffer.begin()}, fBufEnd{fileBuffer.end()}; fBufIt != fBufEnd; ++fBufIt)
        {
            if(*fBufIt >= 'a' && *fBufIt <= 'z')      //Цикл получает слова из fileBuffer без "примесей"
            {                                         //лишних символов
                word += *fBufIt;
            }
            else if(*fBufIt >= 'A' && *fBufIt <= 'Z') //Приводим все заглавные буквы к прописным, только для ASCII
            {
                *fBufIt += 32;
                word += *fBufIt;
            }
            if((!word.empty() && (!(*fBufIt >= 'a' && *fBufIt <= 'z') && !(*fBufIt >= 'A' && *fBufIt <= 'Z'))) ||
               (!word.empty() && fBufIt == fBufEnd - 1))
            {
                std::lock_guard<std::mutex> accessGuard(accessLocker);
                if (freq_dictionary.find(word) == freq_dictionary.end() || freq_dictionary[word][index].filePath != path)
                {
                    freq_dictionary[word].push_back({path, 1});
                }
                else
                {
                    ++freq_dictionary[word][index].count;
                }
                word.clear();
            }
        }

        if(index == docNamesCount)
        {
            *threadIsOver = true;
        }
    };

    for(size_t input_docs_index{0}, input_docs_size{docsNames.size()}; input_docs_index < input_docs_size; ++input_docs_index)
    {
        std::thread th(textExt, std::move(docsNames[input_docs_index]), input_docs_index, input_docs_size - 1);

        th.detach();
    }

    while(!*threadIsOver)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    MainWindow::logger("Update document base is over.", mW);

}

std::vector <se::Entry> se::InvertedIndex::GetWordCount(const std::string &word)
{
    return freq_dictionary[word];
}

bool se::InvertedIndex::empty()
{
    return freq_dictionary.empty();
}

