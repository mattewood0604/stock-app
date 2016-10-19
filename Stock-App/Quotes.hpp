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
    static void addTimeQuote(const std::string& _quote);
    static void log();
  
  private:
    static std::vector<TimeQuote> timeQuotes;
};

#endif /* Quotes_hpp */
