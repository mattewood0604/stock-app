//
//  StockModel.hpp
//  Stock-App
//
//  Created by Matt Wood on 10/21/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#ifndef StockModel_hpp
#define StockModel_hpp

#include <stdio.h>
#include <string>

class StockModel {
  public:
    StockModel(const std::string& _symbol);
  
    void reset();
  
    const unsigned int& getShortTimePeriods() const;
    const unsigned int& getLongTimePeriods() const;
    const unsigned int& getMaxCandleTime() const;
    const unsigned int& getWTimePeriods() const;
    const float& getMaxGain() const;
    const float& getMaxLoss() const;
  
    const unsigned int& getFactor() const;
    const unsigned int& getPd() const;
  
    const unsigned int& getStandardDevHigh() const;
    const unsigned int& getBollingerBandLength() const;
    const unsigned int& getLookBackPeriod() const;
    const float& getHighestPercentile() const;
    const float& getLowestPercentile() const;
  
    const unsigned int& getBuyQuoteNumber(const unsigned int& _index) const;
    const unsigned int& getSellQuoteNumber(const unsigned int& _index) const;
  
    void incrementShortTimePeriods();
    void incrementLongTimePeriods();
    void incrementMaxCandleTime();
    void incrementWTimePeriods();
  
    void resetMaxCandleTime();
    void resetShortTimePeriods();
    void resetLongTimePeriods();
    void resetWTimePeriods();

    unsigned int standardDevHigh;
    unsigned int bollingerBandLength;
    unsigned int lookBackPeriod;
    float highestPercentile;
    float lowestPercentile;
    unsigned int multiplier;
  
    unsigned int shiftedMovingAverageLength;
    unsigned int movingAverageLength;
    unsigned int shiftLength;
  
  private:
    unsigned int shortTimePeriods;
    unsigned int longTimePeriods;
    unsigned int wTimePeriods;
    unsigned int maxCandleTime;
  
    float maxGain;
    float maxLoss;
  
    unsigned int factor;
    unsigned int pd;
  
    unsigned int minutesSpan;
    unsigned int buyQuoteNumber[10];
    unsigned int sellQuoteNumber[10];
};

#endif /* StockModel_hpp */
