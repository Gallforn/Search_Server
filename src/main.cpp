#include <iostream>
#include <chrono>
#include "ConvertJson.h"
#include "InvertedIndex.h"
#include "SearchServer.h"
#include "gtest/gtest.h"

#define TESTS

#ifdef TESTS
TEST(sample_test_case, sample_test)
{
    EXPECT_EQ(1, 1);
}

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

TEST(TestCaseInvertedIndex, TestBasic) {
    const std::vector<std::string> docs = {
            "../../data_base/testCJ_1/file001.txt",
            "../../data_base/testCJ_1/file002.txt"
    };
    const std::vector<std::string> requests = {"london", "the"};
    const std::vector<std::vector<se::Entry>> expected = {
            {
                    {0, 1}
            }, {
                    {0, 1}, {1, 3}
            }
    };
    TestInvertedIndexFunctionality(docs, requests, expected);
}
TEST(TestCaseInvertedIndex, TestBasic2) {
    const std::vector<std::string> docs = {
            "../../data_base/testCJ_2/file001.txt",
            "../../data_base/testCJ_2/file002.txt",
            "../../data_base/testCJ_2/file003.txt",
            "../../data_base/testCJ_2/file004.txt"
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
TEST(TestCaseInvertedIndex, TestInvertedIndexMissingWord) {
    const std::vector<std::string> docs = {
            "../../data_base/testCJ_3/file001.txt",
            "../../data_base/testCJ_3/file002.txt"
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

TEST(TestCaseSearchServer, TestSimple) {
    const std::vector<std::string> docs = {
            "../../data_base/test_sS_1/file001.txt",
            "../../data_base/test_sS_1/file002.txt",
            "../../data_base/test_sS_1/file003.txt",
            "../../data_base/test_sS_1/file004.txt"
    };
    const std::vector<std::string> request = {"milk water", "sugar"};
    const std::vector<std::vector<se::RelativeIndex>> expected = {
            {
                    {2, 1},
                    {0, 0.7},
                    {1, 0.3}
            },
            {
                    {}
            }
    };
    se::SearchServer srv(docs);
    std::vector<std::vector<se::RelativeIndex>> result = srv.search(request);

    ASSERT_EQ(result, expected);
}

TEST(TestCaseSearchServer, TestTop5) {
    const std::vector<std::string> docs = {
            "../../data_base/test_sS_2/file001.txt",
            "../../data_base/test_sS_2/file002.txt",
            "../../data_base/test_sS_2/file003.txt",
            "../../data_base/test_sS_2/file004.txt",
            "../../data_base/test_sS_2/file005.txt",
            "../../data_base/test_sS_2/file006.txt",
            "../../data_base/test_sS_2/file007.txt",
            "../../data_base/test_sS_2/file008.txt",
            "../../data_base/test_sS_2/file009.txt",
            "../../data_base/test_sS_2/file010.txt",
            "../../data_base/test_sS_2/file011.txt",
            "../../data_base/test_sS_2/file012.txt",
            "../../data_base/test_sS_2/file013.txt",
            "../../data_base/test_sS_2/file014.txt",
            "../../data_base/test_sS_2/file015.txt",
            "../../data_base/test_sS_2/file016.txt",
            "../../data_base/test_sS_2/file017.txt",
            "../../data_base/test_sS_2/file018.txt",
            "../../data_base/test_sS_2/file019.txt",
            "../../data_base/test_sS_2/file020.txt",
            "../../data_base/test_sS_2/file021.txt",
            "../../data_base/test_sS_2/file022.txt",
    };
    const std::vector<std::string> request = {"moscow is the capital of russia"};
    const std::vector<std::vector<se::RelativeIndex>> expected = {
            {
                    {7, 1},
                    {14, 1},
                    {0, 0.666666687},
                    {1, 0.666666687},
                    {2, 0.666666687}
            }
    };
    se::SearchServer srv(docs);
    std::vector<std::vector<se::RelativeIndex>> result = srv.search(request);
    result[0].resize(5);

    ASSERT_EQ(result, expected);
}


#endif

#ifndef TESTS
int main()
{
    auto begin = std::chrono::steady_clock::now();
    try
    {
      se::ConvertJSON cJ;
      se::SearchServer sS(cJ.GetNamesDocuments());

      cJ.putAnswers(sS.search(cJ.GetRequests()));
    }
    catch(std::exception& exc)
    {
        std::cerr << exc.what() << std::endl;
        return 1;
    }
    auto end = std::chrono::steady_clock::now();

    auto res = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    std::cout << "Duration " << res.count() << " ms" << std::endl;

    return 0;
}
#endif

