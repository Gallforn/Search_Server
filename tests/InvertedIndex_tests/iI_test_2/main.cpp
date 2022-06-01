#include "InvertedIndex.h"
#include "gtest/gtest.h"

void TestInvertedIndexFunctionality(const std::vector<std::string>& docs, const std::vector<std::string>& requests,
                                    const std::vector<std::vector<se::Entry>>& expected){
    std::vector<std::vector<se::Entry>> result;
    se::InvertedIndex idx;
    idx.UpdateDocumentBase(docs);

    for(auto& request : requests)
    {
        std::vector<se::Entry> word_count = idx.GetWordCount(request);
        result.push_back(word_count);
    }

    ASSERT_EQ(result, expected);
}

TEST(TestCaseInvertedIndex, TestBasic2) {
const std::vector<std::string> docs = {
        "../../../../data_base/test_iI_2/file001.txt",
        "../../../../data_base/test_iI_2/file002.txt",
        "../../../../data_base/test_iI_2/file003.txt",
        "../../../../data_base/test_iI_2/file004.txt"
};
const std::vector<std::string> requests = {"milk", "water", "cappuchino"};
const std::vector<std::vector<se::Entry>> expected = {
        {
                {0, 4}, {1, 1}, {2, 5}
        }, {
                {0, 3}, {1, 2}, {2, 5}
        }, {
                {3, 1}
        }
};
TestInvertedIndexFunctionality(docs, requests, expected);
}