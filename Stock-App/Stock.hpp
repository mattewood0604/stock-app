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
#include "StockModel.hpp"

class Stock {
  public:
    Stock();
    Stock(const std::string& _symbol);
  
    void reset();
  
    void addTimeToCandles(const TimeQuote& _timeQuote);
    void addQuoteToTestData(const TimeQuote& _timeQuote);
    const TimeQuote& getTestQuote(const unsigned int& _marketTime) const;
  
    Candle& getLastCandle();
    unsigned int getNumberOfCandles() const;
    const Candle& getCandleAtIndex(const unsigned int& _index) const;
  
    StockModel& getStockModel();

    void buyOrSell();
  
    float ema(const float& _price, const float& _previousEMA, const float& _multiplier) const;
  
    void setWaveTrendComplete(const bool& _complete);
  
    void logMoneyMade() const;
    float getPercentageMade() const;
  
    const float& getShortMultiplier() const;
    const float& getLongMultiplier() const;
  
    std::string symbol;
  
    std::vector<TimeQuote> testQuotes;
  
    float averagePriceEMA;
    float apESA;
    int apESACalculated;
    float ci;
    int ciCalculated;
    std::vector<float> previousW1;
    
    float w1;
    float w2;
  
  private:
    void supertrendAlgorithm();
    float averageTrueRange() const;
  
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
