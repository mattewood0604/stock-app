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

Stock::Stock() : currentQuote(), stockModel("") {
  this->testQuotes = std::vector<TimeQuote>();
  
  this->reset();
}

Stock::Stock(const std::string& _symbol) : currentQuote(), stockModel(_symbol) {
  this->symbol = _symbol;
  std::string url = RestCall::urlForStockSymbol(_symbol);
  if (url.length() == 0) {
    std::cout << _symbol << std::endl;
  }
  this->instrumentUrl = url.length() ? url : "";

  std::cout << this->instrumentUrl << std::endl;
  
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
  
  this->numberOfQuotes = 0;
}

void Stock::addTimeToCandles(TimeQuote& _timeQuote) {
  this->currentQuote = _timeQuote;
  
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

void Stock::addQuoteToTestData(TimeQuote& _timeQuote) {
  this->testQuotes.push_back(_timeQuote);
}

void Stock::setWaveTrendComplete(const bool& _complete) {
  this->waveTrendComplete = _complete;
}

float Stock::ema(const float& _price, const float& _previousEMA, const float& _multiplier) const {
  return (_price - _previousEMA) * _multiplier + _previousEMA;
}

void Stock::logMoneyMade() const {
  std::string holding = this->isBought ? "holding" : "not holding";
  float percentage = (this->buyPrice == 0) ? 0 : (this->moneyMade / this->buyPrice);
  std::cout << this->symbol << "\t"
            << this->moneyMade << "\t"
            << percentage * 100 << "\t"
            << holding << "\t"
            << this->numberOfTrades
            << std::endl << std::endl;
}

StockModel& Stock::getStockModel() {
  return this->stockModel;
}

float Stock::getPercentageMade() const {
  if (this->buyPrice == 0) {
    return 0.0;
  }
  
  return (this->moneyMade) / this->buyPrice;
}

const float& Stock::getShortMultiplier() const {
  return this->shortMultiplier;
}

const float& Stock::getLongMultiplier() const {
  return this->longMultiplier;
}

TimeQuote& Stock::getTestQuote(const unsigned int& _marketTime) {
  return this->testQuotes[_marketTime];
}
