//
//  Stock.cpp
//  Stock-App
//
//  Created by Matt Wood on 10/21/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#include <iostream>
#include <math.h>

#include "Stock.hpp"
#include "StockModel.hpp"

Stock::Stock() {
  this->init();
}

Stock::Stock(const std::string& _symbol) {
  this->init();
  this->symbol = _symbol;
}

void Stock::init() {
  this->waveTrendComplete = false;
  
  this->averagePriceEMA = -1;
  this->apESA = 0;
  this->apESACalculated = 0;
  this->ci = 0;
  this->ciCalculated = 0;
  this->previousW1 = std::vector<float>();
  
  this->isBought = false;
  this->isBuy = false;
  this->isSell = false;
  
  this->moneyMade = 0;
  this->buyPrice = 0;
  
  this->shortMultiplier = 2.0f / (this->stockModel.getShortTimePeriods() + 1);
  this->longMultiplier = 2.0f / (this->stockModel.getLongTimePeriods() + 1);
  
  this->candles = std::vector<Candle>();
  this->candles.push_back(Candle(this->stockModel.getMaxCandleTime()));
  this->testQuotes = std::vector<TimeQuote>();
  
  this->maxLossTaken = false;
  
  this->numberOfTrades = 0;
}

void Stock::reset() {
  this->waveTrendComplete = false;
  
  this->averagePriceEMA = -1;
  this->apESA = 0;
  this->apESACalculated = 0;
  this->ci = 0;
  this->ciCalculated = 0;
  this->previousW1 = std::vector<float>();
  
  this->isBought = false;
  this->isBuy = false;
  this->isSell = false;
  
  this->moneyMade = 0;
  this->buyPrice = 0;
  
  this->shortMultiplier = 2.0f / (this->stockModel.getShortTimePeriods() + 1);
  this->longMultiplier = 2.0f / (this->stockModel.getLongTimePeriods() + 1);
  
  this->candles = std::vector<Candle>();
  this->candles.push_back(Candle(this->stockModel.getMaxCandleTime()));
  
  this->maxLossTaken = false;
}

void Stock::addTimeToCandles(const TimeQuote& _timeQuote) {
  const unsigned int& maxCandleTime = this->stockModel.getMaxCandleTime();
  
  Candle& candle = this->candles[this->candles.size() - 1];
  if (candle.getTotalTime() >= maxCandleTime) {
    this->calculateWaveTrend();
    
    Candle nextCandle = Candle(maxCandleTime);
    nextCandle.addTimeQuote(_timeQuote);
    this->candles.push_back(nextCandle);
  }
  else {
    candle.addTimeQuote(_timeQuote);
  }
}

void Stock::addQuoteToTestData(const TimeQuote& _timeQuote) {
  this->testQuotes.push_back(_timeQuote);
}

void Stock::calculateWaveTrend() {
  const Candle& currentCandle = this->candles[this->candles.size() - 1];
  if (this->candles.size() < this->stockModel.getShortTimePeriods()) {
    return;
  }
  
  if (this->averagePriceEMA == -1) {
    this->averagePriceEMA = 0;
    for (unsigned int i = 0; i < this->candles.size() - 1; i++) {
      const Candle& candle = this->candles[i];
      float averagePrice = candle.getAveragePrice();
      this->averagePriceEMA += averagePrice;
    }
    this->averagePriceEMA /= this->stockModel.getShortTimePeriods();
  }
  
  float averagePrice = currentCandle.getAveragePrice();
  float esa = this->ema(averagePrice, this->averagePriceEMA, this->shortMultiplier);
  this->averagePriceEMA = esa;
  if (this->apESACalculated < this->stockModel.getShortTimePeriods()) {
    this->apESA += fabs(averagePrice - esa);
    this->apESACalculated++;
    return;
  }
  else if (this->apESACalculated == this->stockModel.getShortTimePeriods()) {
    this->apESA /= this->stockModel.getShortTimePeriods();
    this->apESACalculated++;
  }
  
  float apMinusESA = fabs(averagePrice - esa);
  float d = this->ema(apMinusESA, this->apESA, this->shortMultiplier);
  this->apESA = d;
  float c = (averagePrice - esa) / (0.015 * d);
  
  if (this->ciCalculated < this->stockModel.getLongTimePeriods()) {
    this->ci += c;
    this->ciCalculated++;
    return;
  }
  else if (this->ciCalculated == this->stockModel.getLongTimePeriods()) {
    this->ci /= this->stockModel.getLongTimePeriods();
    this->ciCalculated++;
  }
  
  float tci = this->ema(c, this->ci, this->longMultiplier);
  this->ci = tci;
  
  this->w1 = tci;
  if (this->previousW1.size() < this->stockModel.getWTimePeriods()) {
    this->previousW1.push_back(this->w1);
    return;
  }
  
  this->w2 = 0;
  for (unsigned int i = 0; i < this->stockModel.getWTimePeriods(); i++) {
    float previousW1 = this->previousW1[i];
    this->w2 += previousW1;
  }
  this->w2 /= this->stockModel.getWTimePeriods();
  
  this->previousW1.erase(previousW1.begin());
  this->previousW1.push_back(this->w1);
  
  this->waveTrendComplete = true;
}

float Stock::ema(const float& _price, const float& _previousEMA, const float& _multiplier) const {
  return (_price - _previousEMA) * _multiplier + _previousEMA;
}

void Stock::buyOrSell() {
  if (!this->waveTrendComplete) {
    return;
  }
  
  const Candle& currentCandle = this->candles[this->candles.size() - 1];
  if (currentCandle.getClose() == 0) {
    return;
  }
  
  if (this->maxLossTaken) {
    return;
  }
  
  if (this->isBuy) {
    //std::cout << "BUY \t" << this->symbol << ":\t" << currentCandle.getOpen() << std::endl;
    this->isBought = true;
    this->isBuy = false;
    this->buyPrice = currentCandle.getOpen();
    this->numberOfTrades++;
    return;
  }
  else if (this->isSell) {
    //std::cout << "SELL\t" << this->symbol << ":\t" << currentCandle.getOpen() << std::endl;
    //std::cout << "------------------------" << std::endl;
    this->moneyMade += currentCandle.getOpen() - this->buyPrice;
    this->isSell = false;
    this->isBought = false;
    if (this->moneyMade / this->buyPrice < -0.02) {
      this->maxLossTaken = true;
    }
    this->numberOfTrades++;
    return;
  }
  
  float averagePrice = currentCandle.getAveragePrice();
  if ((averagePrice >= this->buyPrice + .1 || averagePrice <= this->buyPrice - .1) && this->isBought) {
    this->isBuy = false;
    this->isSell = true;
    return;
  }
  
  if (this->w1 >= this->w2 && !this->isBought) {
    this->isBuy = true;
  }
  else if (this->w1 <= this->w2 && this->isBought) {
    this->isSell = true;
  }
}

void Stock::logMoneyMade() const {
  std::string holding = this->isBought ? "holding" : "not holding";
  std::cout << this->symbol << "\t"
            << this->moneyMade << "\t"
            << this->moneyMade / this->buyPrice << "\t"
            << holding << "\t"
            << this->numberOfTrades << std::endl << std::endl;
}

StockModel& Stock::getStockModel() {
  return this->stockModel;
}

float Stock::getPercentageMade() const {
  return (this->moneyMade) / this->buyPrice;
}
