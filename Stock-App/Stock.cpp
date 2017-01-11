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
#include "RestCall.hpp"
#include "Stock.hpp"
#include "StockModel.hpp"
#include "IndicatorAlgorithms.hpp"

Stock::Stock() : stockModel("") {
  this->testQuotes = std::vector<TimeQuote>();
  
  this->reset();
}

Stock::Stock(const std::string& _symbol) : stockModel(_symbol) {
  this->symbol = _symbol;
  this->instrumentUrl = RestCall::urlForStockSymbol(_symbol);
  
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
  
  Candle& candle = this->getLastCandle();
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

const TimeQuote& Stock::getTestQuote(const unsigned int& _marketTime) const {
  return this->testQuotes[_marketTime];
}
