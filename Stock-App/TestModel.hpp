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

#include "Stock.hpp"
#include "TimeQuote.hpp"

class TestModel {
  public:
    static void initialize();

    static unsigned int getTestStockSymbolCount();
    static const std::string& getTestStockSymbol(const unsigned int& _index);
  
    static unsigned int getTestStockCount();
    static Stock& getTestStock(const unsigned int& _index);
  
    static std::string createQuotesDirectory(const std::string& _symbol);
  
    static unsigned int totalTimeQuotes(const unsigned int& _index = 0);
  
    static std::string quotesDirectory();
    static void setDate(const std::string& _date);
  
    static void resetTestData();
    static void resetStockData();
    static void hardResetStock();
  
    static void logMoneyMade();
  
    static unsigned int getNumberOfDates();
    static const std::string& getDateAtIndex(const unsigned int& _index);
  
    static const bool loggingEnabled;
  
    //static std::string stockSymbol;
  
    static const unsigned int maximumLongTimePeriods;
    static const unsigned int maximumShortTimePeriods;
    static const unsigned int maximumCandleTime;
    static const unsigned int maximumWTimePeriods;
  
  private:
    //static Stock testingStock;
    //static std::map<std::string, Stock> stocks;
    static std::vector<std::string> testStockSymbols;
    static std::vector<Stock> testStocks;
  
    static std::vector<std::string> dates;
    static std::string runDate;
  
    static void createListOfDates();
};

#endif /* TestModel_hpp */
