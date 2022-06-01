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

TEST(TestCaseInvertedIndex, TestInvertedIndexMissingWord) {
const std::vector<std::string> docs = {
        "../../../../data_base/test_iI_3/file001.txt",
        "../../../../data_base/test_iI_3/file002.txt"
};
const std::vector<std::string> requests = {"m", "statement"};
const std::vector<std::vector<se::Entry>> expected = {
        {

        }, {
                {1, 1}
        }
};
TestInvertedIndexFunctionality(docs, requests, expected);
}
