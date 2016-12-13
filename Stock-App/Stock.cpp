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
  this->maxMade = 0;
  
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
  this->maxMade = 0;
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
  
  if (previousW1.size() > 0) {
    this->previousW1.erase(previousW1.begin());
    this->previousW1.push_back(this->w1);
  }
  
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
    this->percentageMade = this->moneyMade / this->buyPrice;
    
    if (this->percentageMade > this->maxMade) {
      this->maxMade = this->percentageMade;
    }
    
    this->isSell = false;
    this->isBought = false;
    
    if (this->moneyMade / this->buyPrice < -0.02) {
      this->maxLossTaken = true;
    }
    
    //if (this->maxMade > this->percentageMade + .01f) {
    //  this->maxLossTaken = true;
    //}
    
    this->numberOfTrades++;
    return;
  }
  
  float averagePrice = currentCandle.getAveragePrice();
  if ((averagePrice >= this->buyPrice + stockModel.getMaxGain() || averagePrice <= this->buyPrice - stockModel.getMaxLoss()) && this->isBought) {
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

void Stock::supertrendAlgorithm() {
  static float previousTrend = 0;
  static float previousTrendUp = 0;
  static float previousTrendDown = 0;
  
  float averageTrueRange = this->averageTrueRange();
  if (averageTrueRange == -100000) {
    return;
  }
  
  const Candle& candle = this->candles[this->candles.size() - 1];
  float highlow2 = (candle.getHigh() + candle.getLow()) / 2.0f;
  float factorAdjusted = this->stockModel.getFactor() * averageTrueRange;
  
  float up = highlow2 - factorAdjusted;
  float down = highlow2 + factorAdjusted;
  
  float trendUp = candle.getClose() > previousTrendUp ? fmaxf(up, previousTrendUp) : up;
  float trendDown = candle.getClose() < previousTrendDown ? fminf(down, previousTrendDown) : down;
  
  float trend = 0;
  if (candle.getClose() > previousTrendDown) {
    std::cout << "1" << std::endl;
    trend = 1;
  }
  else {
    if (candle.getClose() < previousTrendUp) {
      std::cout << "2" << std::endl;
      trend = -1;
    }
    else {
      if (isnan(previousTrend)) {
        std::cout << "3" << std::endl;
        trend = 1;
      }
      else {
        std::cout << "4" << std::endl;
        trend = previousTrend;
      }
    }
  }
  
  this->waveTrendComplete = true;
  //float tsl = trend == 1 ? trendUp : trendDown;
  std::cout << "TREND: " << trend << std::endl;
  if (trend == 1) {
    this->isBuy = true;
    //std::cout << "BUY: " << candle.getClose() << std::endl;
  }
  else {
    this->isSell = true;
    //std::cout << "SELL: " << candle.getClose() << std::endl;
  }

  previousTrend = trend;
  previousTrendUp = trendUp;
  previousTrendDown = trendDown;
  
  /*
   TrendUp=close[1]>TrendUp[1]? max(Up,TrendUp[1]) : Up
   TrendDown=close[1]<TrendDown[1]? min(Dn,TrendDown[1]) : Dn
   
   Trend = close > TrendDown[1] ? 1: close< TrendUp[1]? -1: nz(Trend[1],1)
   Tsl = Trend==1? TrendUp: TrendDown
   
   linecolor = Trend == 1 ? green : red
   
   plotarrow(Trend == 1 and Trend[1] == -1 ? Trend : na, title="Up Entry Arrow", colorup=lime, maxheight=60, minheight=50, transp=0)
   plotarrow(Trend == -1 and Trend[1] == 1 ? Trend : na, title="Down Entry Arrow", colordown=red, maxheight=60, minheight=50, transp=0)
   
   */
}

float Stock::averageTrueRange() const {
  if (this->candles.size() < this->stockModel.getPd() + 1) {
    return -100000;
  }
  
  float averageTrueRange = 0.0f;
  for (unsigned int i = (unsigned int)this->candles.size() - 1; i > this->candles.size() - this->stockModel.getPd(); i--) {
    const Candle& current = this->candles[i];
    const Candle& previous = this->candles[i - 1];
    float trueRange = fmaxf(current.getHigh() - current.getLow(), fabsf(current.getHigh() - previous.getClose()));
    trueRange = fmaxf(trueRange, fabsf(current.getLow() - previous.getClose()));
    averageTrueRange += trueRange;
  }
  
  averageTrueRange /= this->stockModel.getPd();
  return averageTrueRange;
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
