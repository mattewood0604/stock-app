//
//  Candle.cpp
//  Stock-App
//
//  Created by Matt Wood on 10/21/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#include "Candle.hpp"
#include "StockModel.hpp"

Candle::Candle(const unsigned int& _maxTime) {
  this->lastTime = 0;
  this->totalTime = 0;
  this->high = 0;
  this->low = INT64_MAX;
  this->close = 0;
  this->open = 0;
  
  this->maxTime = _maxTime;
}

void Candle::setLastTime(const uint64_t& _lastTime) {
  this->lastTime = _lastTime;
}

void Candle::addTimeQuote(const TimeQuote& _timeQuote) {
  if (this->lastTime != 0) {
    this->totalTime += _timeQuote.dayTime - this->lastTime;
  }
  else {
    this->open = _timeQuote.price;
  }
  
  if (this->high < _timeQuote.price) {
    this->high = _timeQuote.price;
  }
  
  if (this->low > _timeQuote.price) {
    this->low = _timeQuote.price;
  }
  
  if (this->totalTime > this->maxTime) {
    this->close = _timeQuote.price;
  }
  
  this->lastTime = _timeQuote.dayTime;
}

float Candle::getAveragePrice() const {
  return (this->high + this->low + this->close) / 3.0f;
}

unsigned int Candle::getTotalTime() const {
  return this->totalTime;
}

float Candle::getOpen() const {
  return this->open;
}

float Candle::getClose() const {
  return this->close;
}
