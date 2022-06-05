#include <iostream>
#include <chrono>
#include "ConvertJson.h"
#include "InvertedIndex.h"
#include "SearchServer.h"

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
        system("pause");
        return 1;
    }
    auto end = std::chrono::steady_clock::now();

    auto res = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    std::cout << "Duration " << res.count() << " ms" << std::endl;

    system("pause");
    return 0;
}


