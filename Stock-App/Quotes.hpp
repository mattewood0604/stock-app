//
//  Quotes.hpp
//  Stock-App
//
//  Created by Matt Wood on 10/16/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#ifndef Quotes_hpp
#define Quotes_hpp

#include <vector>

#include "TimeQuote.hpp"

class Quotes {
  public:
    Quotes();
  
    void addTimeQuote(const std::string& _quote);
    void addTimeQuoteFromCSV(const std::string& _quote);
    void resetTimeQuotes();
  
    unsigned int totalTimeQuotes();
    const TimeQuote& getTimeQuote(const unsigned int& _index);
  
    void log();
  
  private:
    std::vector<TimeQuote> timeQuotes;
};

#endif /* Quotes_hpp */
