//
// Created by Maxim on 01.04.2022.
//
#include <fstream>
#include <iostream>
#include "InvertedIndex.h"
#include "ConvertJson.h"

void se::InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs)
{
    docs.clear();
    freq_dictionary.clear();

    std::string buffer;

    for(std::vector<std::string>::size_type iBeg{0}, iEnd{input_docs.size()}; iBeg < iEnd; ++iBeg)
    {
        std::ifstream file(input_docs[iBeg], std::ios::app);

        getline(file, buffer, '\0');

        docs.push_back(buffer);

        file.close();
    }

    indexing();
}

void se::InvertedIndex::indexing()
{
    std::stringstream ss;
    std::string buffer;
    for(std::vector<std::string>::size_type iBeg{0}, iEnd{docs.size()}; iBeg < iEnd; ++iBeg)
    {
        ss.clear();
        ss << docs[iBeg];
        while(ss >> buffer)
        {
            if(!freq_dictionary.contains(buffer) || freq_dictionary[buffer][iBeg].doc_id != iBeg)
            {
                freq_dictionary[buffer].push_back({iBeg, 1});
            }
            else
            {
                ++freq_dictionary[buffer][iBeg].count;
            }
        }
    }
}

std::vector <se::Entry> se::InvertedIndex::GetWordCount(const std::string &word)
{
    std::vector<Entry> result;

    for(size_t iBeg{0}, iEnd{freq_dictionary[word].size()}; iBeg < iEnd; ++iBeg)
    {
        result.push_back(freq_dictionary[word][iBeg]);
    }

    return result;
}

