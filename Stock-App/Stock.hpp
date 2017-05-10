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
  
    void addTimeToCandles(TimeQuote& _timeQuote);
    void addQuoteToTestData(TimeQuote& _timeQuote);
    TimeQuote& getTestQuote(const unsigned int& _marketTime);
  
    Candle& getLastCandle();
    unsigned int getNumberOfCandles() const;
    const Candle& getCandleAtIndex(const unsigned int& _index) const;
  
    StockModel& getStockModel();

    //void buyOrSell();
  
    float ema(const float& _price, const float& _previousEMA, const float& _multiplier) const;
  
    void setWaveTrendComplete(const bool& _complete);
  
    void logMoneyMade() const;
    float getPercentageMade() const;
  
    const float& getShortMultiplier() const;
    const float& getLongMultiplier() const;
  
    std::string symbol;
    std::string instrumentUrl;
  
    std::vector<TimeQuote> testQuotes;
  
    TimeQuote currentQuote;
  
    float averagePriceEMA;
    float apESA;
    unsigned int apESACalculated;
    float ci;
    unsigned int ciCalculated;
    std::vector<float> previousW1;
    
    float w1;
    float w2;
  
    unsigned int numberOfTrades;
    unsigned int negativeTrades;
  
    unsigned int numberOfQuotes;
  
    bool canStartBuying;

    unsigned int buyCandleNumber;
  
  private:
    friend class BuySell;
    friend class IndicatorAlgorithms;
  
    void supertrendAlgorithm();
    float averageTrueRange() const;
  
    bool waveTrendComplete;
    bool williamsVixValid;
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
  
    StockModel stockModel;
  
    std::vector<Candle> candles;
};

#endif /* Stock_hpp */
