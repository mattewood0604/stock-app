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

#include "TimeQuote.hpp"

class Model {
  public:
    static bool isMarketOpen(void);
    static void setMarketStatus(const std::string& _status);
  
    static void addTimeQuote(const std::string& _timeQuote);
    static void logQuotes();
  
    static const bool loggingEnabled;
  
  private:
    static const std::string open;
    static const std::string closed;
  
    static std::string marketStatus;
  
    static std::vector<TimeQuote> timeQuotes;
};

#endif /* Model_hpp */
