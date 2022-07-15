//
// Created by Maxim on 02.04.2022.
//
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "SearchServer.h"
#include "MainWindow.h"
#include "ui_UI.h"

void se::SearchServer::search(const std::string& queries_input, Ui::MainWindow* mW)
{
    if(queries_input.empty())
    {
        MainWindow::logger("Specify empty query!", mW);
        return;
    }

    MainWindow::logger("Starting search...", mW);

    std::map<std::string, float>    rank{ };                 //класс для хранения абс. релевантности для каждого док-та
                                                             //обрабатываемого запроса
    float                           maxR{0.0f};

    if(index_.empty())
    {
        MainWindow::logger("Frequency dictionary is empty! Search impossible!", mW);
        MainWindow::logger("Please check file config.json -> fields: \"data_base_dir\" & \"files\" for correctness.)", mW);

        return;
    }

    std::vector<std::string> queries_words; //Слова из запроса
    std::string              buffer{ }; //строка буффер для извлечения слов запроса

    for(size_t begin{0}, end{queries_input.size()}; begin <= end; ++begin) //Цикл извлечения отдельных слов запроса
    {
        if(((queries_input[begin] >= 'a' && queries_input[begin] <= 'z') ||
        (queries_input[begin] >= 'A' && queries_input[begin] <= 'Z')) && begin != end)
        {
            buffer += queries_input[begin];

            if(buffer[buffer.size() - 1] >= 'A' && buffer[buffer.size() - 1] <= 'Z')
            {
                buffer[buffer.size() - 1] += 32;
            }
        }
        else
        {
            if(!buffer.empty()) queries_words.push_back(buffer);
            buffer.clear();
        }
    }

     for(auto&& itQW : queries_words)
     {
         std::vector<se::Entry> entry_word = index_.GetWordCount(itQW);

         if(!entry_word.empty())
         {
             for(auto &i : entry_word)
             {
                 rank[i.filePath] += static_cast<float>(i.count);
                 if(rank[i.filePath] > maxR)
                 {
                     maxR = rank[i.filePath];
                 }
             }
         }
     }

     std::vector<std::pair<std::string, float>> sort_rank; //вектор для сортировки пар из класса rank

     for(auto &i : rank)
     {
         i.second /= maxR;
         sort_rank.emplace_back(i);
     }

     std::sort(sort_rank.begin(), sort_rank.end(), [](std::pair<std::string, float> &a, std::pair<std::string, float> &b)
     {
         if(a.second == b.second)
         {
             return a.first < b.first;
         }
         else return a.second > b.second;
     });

     if(!sort_rank.empty())
     {
         for(auto &i : sort_rank)
         {
             search_result.push_back({i.first, i.second});
         }
     }

    MainWindow::logger("Search is over.", mW);
}

void se::SearchServer::updateInvertedIndex(const std::vector<std::string>& docsNames, Ui::MainWindow* ui)
{
    index_.UpdateDocumentBase(docsNames, ui);
}


