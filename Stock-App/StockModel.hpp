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

class StockModel {
  public:
    StockModel();
  
    void reset();
  
    const unsigned int& getShortTimePeriods() const;
    const unsigned int& getLongTimePeriods() const;
    const unsigned int& getMaxCandleTime() const;
    const unsigned int& getWTimePeriods() const;
    const float& getMaxGain() const;
    const float& getMaxLoss() const;
  
    void incrementShortTimePeriods();
    void incrementLongTimePeriods();
    void incrementMaxCandleTime();
  
    void resetMaxCandleTime();
    void resetShortTimePeriods();
  
  private:
    unsigned int shortTimePeriods;
    unsigned int longTimePeriods;
  
    unsigned int wTimePeriods;
  
    unsigned int maxCandleTime;
  
    float maxGain;
    float maxLoss;
};

#endif /* StockModel_hpp */
