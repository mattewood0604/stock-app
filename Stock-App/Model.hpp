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

#include "Quotes.hpp"
#include "TimeQuote.hpp"

class Model {
  public:
    static bool isMarketOpen(void);
    static void setMarketStatus(const std::string& _status);
  
    static void addTimeQuote(const std::string& _timeQuote);
    static void resetTimeQuotes();
  
    static unsigned int totalTimeQuotes();
    static const TimeQuote& getTimeQuote(const unsigned int& _index);
    static void logQuotes();
  
    static void addTestQuote();
  
    static const bool loggingEnabled;
  
    static const std::string quotesDirectory;
  
  private:
    static const std::string open;
    static const std::string closed;
  
    static std::string marketStatus;
  
    static Quotes timeQuotes;
};

#endif /* Model_hpp */
