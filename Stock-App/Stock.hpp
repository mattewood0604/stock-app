//
//  Stock.hpp
//  Stock-App
//
//  Created by Matt Wood on 10/21/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#ifndef Stock_hpp
#define Stock_hpp

#include <string>
#include <vector>

#include "Candle.hpp"
#include "Quotes.hpp"
#include "StockModel.hpp"

class Stock {
  public:
    Stock();
    Stock(const std::string& _symbol);
  
    void addTimeToCandles(const TimeQuote& _timeQuote);
    void addQuoteToTestData(const TimeQuote& _timeQuote);
  
    StockModel& getStockModel();
  
    void calculateWaveTrend();
    void buyOrSell();
  
    void reset();
  
    void logMoneyMade() const;
    float getPercentageMade() const;
  
    std::string symbol;
  
    std::vector<TimeQuote> testQuotes;
  
  private:
    void init();
  
    void supertrendAlgorithm();
    float averageTrueRange() const;
  
    float ema(const float& _price, const float& _previousEMA, const float& _multiplier) const;
  
    float averagePriceEMA;
    float apESA;
    int apESACalculated;
    float ci;
    int ciCalculated;
    std::vector<float> previousW1;
  
    float w1;
    float w2;
  
    bool waveTrendComplete;
    bool isBought;
    bool isBuy;
    bool isSell;
  
    float moneyMade;
    float buyPrice;
    float shortMultiplier;
    float longMultiplier;
  
    float maxMade;
    float percentageMade;
    bool maxLossTaken;
  
    unsigned int numberOfTrades;
  
    StockModel stockModel;
  
    std::vector<Candle> candles;
};

#endif /* Stock_hpp */
