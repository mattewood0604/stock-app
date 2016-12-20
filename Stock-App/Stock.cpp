//
//  Stock.cpp
//  Stock-App
//
//  Created by Matt Wood on 10/21/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#include <iostream>
#include <math.h>

#include "Model.hpp"
#include "Stock.hpp"
#include "StockModel.hpp"
#include "IndicatorAlgorithms.hpp"

Stock::Stock() : stockModel("") {
  this->testQuotes = std::vector<TimeQuote>();
  
  this->reset();
}

Stock::Stock(const std::string& _symbol) : stockModel(_symbol) {
  this->symbol = _symbol;
  this->testQuotes = std::vector<TimeQuote>();
  
  this->reset();
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
  
  this->numberOfTrades = 0;
}

void Stock::addTimeToCandles(const TimeQuote& _timeQuote) {
  const unsigned int& maxCandleTime = this->stockModel.getMaxCandleTime();
  
  Candle& candle = this->candles[this->candles.size() - 1];
  if (candle.getTotalTime() >= maxCandleTime) {
    IndicatorAlgorithms::calculateWaveTrend(*this);
    
    Candle nextCandle = Candle(maxCandleTime);
    nextCandle.addTimeQuote(_timeQuote);
    this->candles.push_back(nextCandle);
  }
  else {
    candle.addTimeQuote(_timeQuote);
  }
}

Candle& Stock::getLastCandle() {
  return this->candles[this->candles.size() - 1];
}

unsigned int Stock::getNumberOfCandles() const {
  return (unsigned int)this->candles.size();
}

const Candle& Stock::getCandleAtIndex(const unsigned int& _index) const {
  return this->candles[_index];
}

void Stock::addQuoteToTestData(const TimeQuote& _timeQuote) {
  this->testQuotes.push_back(_timeQuote);
}

void Stock::setWaveTrendComplete(const bool& _complete) {
  this->waveTrendComplete = _complete;
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
  
  if (this->isBuy && Model::getPurchasedStockSymbol().compare("") == 0 && !Model::isStopBuying()) {
    //std::cout << "BUY \t" << this->symbol << ":\t" << currentCandle.getOpen() << std::endl;
    this->isBought = true;
    this->isBuy = false;
    this->buyPrice = currentCandle.getOpen();
    this->numberOfTrades++;
    Model::setPurchasedStockSymbol(this->symbol);
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
      Model::setStopBuying(true);
      this->maxLossTaken = true;
    }
    
    Model::setPurchasedStockSymbol("");

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

const float& Stock::getShortMultiplier() const {
  return this->shortMultiplier;
}

const float& Stock::getLongMultiplier() const {
  return this->longMultiplier;
}
