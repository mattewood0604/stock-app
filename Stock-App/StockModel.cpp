//
//  StockModel.cpp
//  Stock-App
//
//  Created by Matt Wood on 10/21/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#include "StockModel.hpp"

StockModel::StockModel(const std::string& _symbol) {
  if (_symbol.compare("JNUG") == 0) {
    // 68 40 48000
    this->shortTimePeriods = 37;
    this->longTimePeriods = 40;
    this->wTimePeriods = 4;
    this->maxCandleTime = 60000;
    this->maxGain = 0.10f;
    this->maxLoss = 0.10f;
    
    this->factor = 3;
    this->pd = 7;
  }
  else if (_symbol.compare("DUST") == 0) {
    this->shortTimePeriods = 26;
    this->longTimePeriods = 58;
    this->wTimePeriods = 4;
    this->maxCandleTime = 45000;
    this->maxGain = 0.10f;
    this->maxLoss = 0.10f;
    
    this->factor = 3;
    this->pd = 7;
  }
  else if (_symbol.compare("LABU") == 0) {
    this->shortTimePeriods = 49;
    this->longTimePeriods = 23;
    this->wTimePeriods = 4;
    this->maxCandleTime = 134000;
    this->maxGain = 1.003f;
    this->maxLoss = 0.992f;
    
    this->factor = 3;
    this->pd = 7;
  }
  else if (_symbol.compare("LABD") == 0) {
    this->shortTimePeriods = 20;
    this->longTimePeriods = 22;
    this->wTimePeriods = 4;
    this->maxCandleTime = 39000;
    this->maxGain = 0.10f;
    this->maxLoss = 0.10f;
    
    this->factor = 3;
    this->pd = 7;
  }
  else if (_symbol.compare("NUGT") == 0) {
    this->shortTimePeriods = 35;
    this->longTimePeriods = 42;
    this->wTimePeriods = 4;
    this->maxCandleTime = 18000;
    this->maxGain = 0.10f;
    this->maxLoss = 0.10f;
    
    this->factor = 3;
    this->pd = 7;
  }
  else if (_symbol.compare("JDST") == 0) {
    // (this->open + this->close) / 2.0f; 30 46 127 .25%
    
    this->shortTimePeriods = 46;//21;
    this->longTimePeriods = 30;//22;
    this->wTimePeriods = 4;
    this->maxCandleTime = 127000;//75000;//64000;
    this->maxGain = 0.10f;
    this->maxLoss = 0.10f;
    
    this->factor = 3;
    this->pd = 7;
    
    this->minutesSpan = 55;
    this->buyQuoteNumber[0] = 2550;
    this->buyQuoteNumber[1] = 0;

    //         2         1      0.95        50        16        24
    this->multiplier = 1;
    this->bollingerBandLength = 5;
    this->standardDevHigh = 5;

    this->lowestPercentile = 1.00;
    this->highestPercentile = 0.95;
    this->lookBackPeriod = 50;
    
    this->shiftedMovingAverageLength = 7;
    this->movingAverageLength = 15;
    this->shiftLength = 0;
    
    //this->minutesSpan = 45;
    //this->buyQuoteNumber[0] = 3450;
    //this->buyQuoteNumber[1] = 0;
    
    //this->minutesSpan = 20;
    //this->buyQuoteNumber[0] = 14;
    //this->buyQuoteNumber[1] = 0;
    //this->buyQuoteNumber[1] = 2705;
    //this->buyQuoteNumber[2] = 0;
    
    unsigned int timeSpan = this->minutesSpan * 60 / 2;
    this->sellQuoteNumber[0] = this->buyQuoteNumber[0] + timeSpan;
    this->sellQuoteNumber[1] = 0;
    //this->sellQuoteNumber[1] = this->buyQuoteNumber[1] + timeSpan;
    //this->sellQuoteNumber[2] = 0;
  }
  else if (_symbol.compare("GDXJ") == 0) {
    this->shortTimePeriods = 37;
    this->longTimePeriods = 24;
    this->wTimePeriods = 4;
    this->maxCandleTime = 26000;
    this->maxGain = 0.10f;
    this->maxLoss = 0.10f;
    
    this->factor = 3;
    this->pd = 7;
  }
  else if (_symbol.compare("TWLO") == 0) {
    this->shortTimePeriods = 20;
    this->longTimePeriods = 20;
    this->wTimePeriods = 4;
    this->maxCandleTime = 15000;
    this->maxGain = 0.10f;
    this->maxLoss = 0.10f;
    
    this->factor = 3;
    this->pd = 7;
    
    this->minutesSpan = 23;
    this->buyQuoteNumber[0] = 836;
    this->buyQuoteNumber[1] = 3706;
    this->buyQuoteNumber[2] = 5637;
    this->buyQuoteNumber[3] = 6643;
    this->buyQuoteNumber[4] = 7449;
    this->buyQuoteNumber[5] = 0;
    
    //this->minutesSpan = 60;
    //this->buyQuoteNumber[0] = 2;
    //this->buyQuoteNumber[1] = 0;
    
    unsigned int timeSpan = this->minutesSpan * 30;
    this->sellQuoteNumber[0] = this->buyQuoteNumber[0] + timeSpan;
    this->sellQuoteNumber[1] = this->buyQuoteNumber[1] + timeSpan;
    this->sellQuoteNumber[2] = this->buyQuoteNumber[2] + timeSpan;
    this->sellQuoteNumber[3] = this->buyQuoteNumber[3] + timeSpan;
    this->sellQuoteNumber[4] = this->buyQuoteNumber[4] + timeSpan;
    this->sellQuoteNumber[5] = 0;
  }
  else {
    this->shortTimePeriods = 20;
    this->longTimePeriods = 20;
    this->wTimePeriods = 4;
    this->maxCandleTime = 15000;
    this->maxGain = 0.10f;
    this->maxLoss = 0.10f;
    
    this->factor = 3;
    this->pd = 7;
  }
  
}

// JNUG
// Long: 68 Short: 42 Time: 50000 44% (Start) 11/21 52% 12_05_2016 60.86%
// 70	41	50 12_07_2016 54%
// 74	39	50 12_07_2016 54%
// 76	38	50 12_07_2016 53%
// 67	43	50 52%
// 69	42	50 52%
// 78	37	50 52%
//

// CLF
// Long: 53	Short: 28	Time: 22000 16% (Found: 12_02_2016)

void StockModel::reset() {
  this->maxCandleTime = 100000;
  this->shortTimePeriods = 15;
  this->longTimePeriods = 15;
  this->wTimePeriods = 4;
}

const unsigned int& StockModel::getShortTimePeriods() const {
  return this->shortTimePeriods;
}

const unsigned int& StockModel::getLongTimePeriods() const {
  return this->longTimePeriods;
}

const unsigned int& StockModel::getMaxCandleTime() const {
  return this->maxCandleTime;
}

const unsigned int& StockModel::getWTimePeriods() const {
  return this->wTimePeriods;
}

const float& StockModel::getMaxGain() const {
  return this->maxGain;
}

const float& StockModel::getMaxLoss() const {
  return this->maxLoss;
}

const unsigned int& StockModel::getFactor() const {
  return this->factor;
}

const unsigned int& StockModel::getPd() const {
  return this->pd;
}

const unsigned int& StockModel::getStandardDevHigh() const {
  return this->standardDevHigh;
}

const unsigned int& StockModel::getBollingerBandLength() const {
  return this->bollingerBandLength;
}

const unsigned int& StockModel::getLookBackPeriod() const {
  return this->lookBackPeriod;
}

const float& StockModel::getHighestPercentile() const {
  return this->highestPercentile;
}

const float& StockModel::getLowestPercentile() const {
  return this->lowestPercentile;
}

void StockModel::incrementShortTimePeriods() {
  this->shortTimePeriods++;
}

void StockModel::incrementLongTimePeriods() {
  this->longTimePeriods++;
}

void StockModel::incrementMaxCandleTime() {
  this->maxCandleTime += 1000;
}

void StockModel::incrementWTimePeriods() {
  this->wTimePeriods++;
}

void StockModel::resetMaxCandleTime() {
  this->maxCandleTime = 100000;
}

void StockModel::resetShortTimePeriods() {
  this->shortTimePeriods = 15;
}

void StockModel::resetLongTimePeriods() {
  this->longTimePeriods = 15;
}

void StockModel::resetWTimePeriods() {
  this->wTimePeriods = 4;
}

const unsigned int& StockModel::getBuyQuoteNumber(const unsigned int& _index) const {
  return this->buyQuoteNumber[_index];
}

const unsigned int& StockModel::getSellQuoteNumber(const unsigned int& _index) const {
  return this->sellQuoteNumber[_index];
}
