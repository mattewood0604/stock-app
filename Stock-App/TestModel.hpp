//
//  TestModel.hpp
//  Stock-App
//
//  Created by Matt Wood on 10/20/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#ifndef TestModel_hpp
#define TestModel_hpp

#include <map>

#include "Quotes.hpp"
#include "Stock.hpp"
#include "TimeQuote.hpp"

class TestModel {
  public:
    static void initialize();

    static Stock& getTestingStock();
    //static Stock& stockForSymbol(const std::string& _symbol);
  
    static unsigned int totalTimeQuotes();
    static const TimeQuote& getTestQuote(unsigned int _index);
  
    static std::string quotesDirectory();
    static void setDate(const std::string& _date);
  
    static void resetTestData();
    static void resetStockData();
  
    static void logMoneyMade();
  
    static const bool loggingEnabled;
  
    static const std::string stockSymbol;
    static std::vector<std::string> dates;
  
  private:
    static Stock testingStock;
    //static std::map<std::string, Stock> stocks;
  
    static std::string runDate;
};

#endif /* TestModel_hpp */
