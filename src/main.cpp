#include <iostream>
#include "ConvertJson.h"
#include "InvertedIndex.h"
#include "SearchServer.h"

template<class T, class U>
void test(T& class1, U& class2)
{
    std::vector<std::vector<se::RelativeIndex>> expect = class1.search(class2.GetRequests());

    for(auto& i : expect)
    {
        std::cout << "answer:" << std::endl;
        for(auto& j : i)
        {
            std::cout << j.doc_id_ << " " << j.rank_ << std::endl;
        }
    }
}

int main()
{
    try
    {
      se::ConvertJSON cJ;
      se::InvertedIndex iI;
      se::SearchServer sS(iI);

      std::cout << "Testing:" << std::endl;

      std::cout << "Test of SearchServer:" << std::endl;

      std::cout << "Test of SearchServer::search()" << std::endl;

      iI.UpdateDocumentBase(cJ.GetTextDocuments());
      test(sS, cJ);

      std::cout << "Test is over." << std::endl;

      cJ.putAnswers(sS.search(cJ.GetRequests()));
    }
    catch(std::exception& exc)
    {
        std::cerr << exc.what() << std::endl;
        return 1;
    }

    return 0;
}
