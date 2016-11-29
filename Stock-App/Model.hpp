//
//  Model.hpp
//  Stock-App
//
//  Created by Matt Wood on 10/17/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#ifndef Model_hpp
#define Model_hpp

#include <string>
#include <vector>
#include <map>

#include "Quotes.hpp"
#include "Stock.hpp"
#include "TimeQuote.hpp"

class Model {
  public:
    static bool isMarketOpen(void);
  
    static void addTimeQuote(const TimeQuote _timeQuote);
    static void resetTimeQuotes();
  
    static unsigned int totalTimeQuotes();
    static const TimeQuote& getTimeQuote(const unsigned int& _index);
    static void logQuotes();
  
    static void addTestQuote();
  
    static std::string symbolsForQuotesAsCSV();
  
    static const bool loggingEnabled;
  
    static const std::string quotesDirectory;
    static const std::string stockSymbolsForQuotesDirectory;
  
  private:
    static const std::string open;
    static const std::string closed;
  
    static std::map<std::string, Stock> stocks;
  
    static Quotes timeQuotes;
};

#endif /* Model_hpp */
