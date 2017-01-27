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

#include "Stock.hpp"
#include "TimeQuote.hpp"

class Model {
  public:
    static void init();
  
    static bool isMarketOpen(void);
  
    static void addTimeQuote(TimeQuote _timeQuote);
    static void addTestQuote();
  
    static void setPurchasedStockSymbol(const std::string& _symbol);
    static const std::string& getPurchasedStockSymbol();
  
    static void setStopBuying(bool _stopBuying);
    static bool isStopBuying();
  
    static bool loggingEnabled;
  
    static Stock& getStockForSymbol(const std::string& _symbol);
  
    static float getBuyingPower();
    static void setBuyingPower(const float& _buyingPower);
  
  private:
    static const std::string open;
    static const std::string closed;
  
    static float buyingPower;
  
    static std::string purchasedStockSymbol;
  
    static bool stopBuying;
  
    static std::map<std::string, Stock> stocks;
};

#endif /* Model_hpp */
