#include <iostream>
#include <windows.h>
#include "ConvertJson.h"
#include "InvertedIndex.h"
#include "SearchServer.h"

int main()
{
    try
    {
      se::ConvertJSON cJ;
      se::InvertedIndex iI;
      se::SearchServer sS(iI);

      iI.UpdateDocumentBase(cJ.GetTextDocuments());
      cJ.putAnswers(sS.search(cJ.GetRequests()));
    }
    catch(std::exception& exc)
    {
        std::cerr << exc.what() << std::endl;
        return 1;
    }

    return 0;
}

