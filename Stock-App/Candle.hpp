//
//  Candle.hpp
//  Stock-App
//
//  Created by Matt Wood on 10/21/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#ifndef Candle_hpp
#define Candle_hpp

#include <stdint.h>

#include "TimeQuote.hpp"

class Candle {
  public:
    Candle(const unsigned int& _maxTime);
  
    void setLastTime(const uint64_t& _lastTime);
    void addTimeQuote(const TimeQuote& _timeQuote);
  
    float getAveragePrice() const;
    unsigned int getTotalTime() const;
  
    float getOpen() const;
    float getClose() const;
  
  private:
    uint64_t lastTime;
    unsigned int totalTime;
    float high;
    float low;
    float close;
    float open;
  
    unsigned int maxTime;
};

#endif /* Candle_hpp */
