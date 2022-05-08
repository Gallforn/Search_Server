#include <iostream>
#include "ConvertJson.h"
#include "InvertedIndex.h"
#include "SearchServer.h"

int main()
{
    try
    {
      se::ConvertJSON cJ;
      se::SearchServer sS(cJ.GetTextDocuments());

      cJ.putAnswers(sS.search(cJ.GetRequests()));
    }
    catch(std::exception& exc)
    {
        std::cerr << exc.what() << std::endl;
        return 1;
    }

    return 0;
}

