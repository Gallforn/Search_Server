#include "InvertedIndex.h"
#include "SearchServer.h"
#include "gtest/gtest.h"

TEST(TestCaseSearchServer, TestTop5) {
const std::vector<std::string> docs = {
        "../../../data_base/test_sS_2/file001.txt",
        "../../../data_base/test_sS_2/file002.txt",
        "../../../data_base/test_sS_2/file003.txt",
        "../../../data_base/test_sS_2/file004.txt",
        "../../../data_base/test_sS_2/file005.txt",
        "../../../data_base/test_sS_2/file006.txt",
        "../../../data_base/test_sS_2/file007.txt",
        "../../../data_base/test_sS_2/file008.txt",
        "../../../data_base/test_sS_2/file009.txt",
        "../../../data_base/test_sS_2/file010.txt",
        "../../../data_base/test_sS_2/file011.txt",
        "../../../data_base/test_sS_2/file012.txt",
        "../../../data_base/test_sS_2/file013.txt",
        "../../../data_base/test_sS_2/file014.txt",
        "../../../data_base/test_sS_2/file015.txt",
        "../../../data_base/test_sS_2/file016.txt",
        "../../../data_base/test_sS_2/file017.txt",
        "../../../data_base/test_sS_2/file018.txt",
        "../../../data_base/test_sS_2/file019.txt",
        "../../../data_base/test_sS_2/file020.txt",
        "../../../data_base/test_sS_2/file021.txt",
        "../../../data_base/test_sS_2/file022.txt",
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

    std::cout << "Press Enter to continue..." << std::endl;
    std::cin.get();
}
