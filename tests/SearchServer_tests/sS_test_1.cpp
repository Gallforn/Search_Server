#include "InvertedIndex.h"
#include "SearchServer.h"
#include "gtest/gtest.h"

TEST(TestCaseSearchServer, TestSimple) {
const std::vector<std::string> docs = {
        "../../../data_base/test_sS_1/file001.txt",
        "../../../data_base/test_sS_1/file002.txt",
        "../../../data_base/test_sS_1/file003.txt",
        "../../../data_base/test_sS_1/file004.txt"
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