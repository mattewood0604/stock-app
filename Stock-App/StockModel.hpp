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
