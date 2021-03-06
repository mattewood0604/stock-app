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
    this->shortTimePeriods = 42;
    this->longTimePeriods = 68;
    this->wTimePeriods = 4;
    this->maxCandleTime = 50000;
    this->maxGain = 0.10f;
    this->maxLoss = 0.10f;
    
    this->factor = 3;
    this->pd = 7;
  }
  else if (_symbol.compare("DUST") == 0) {
    this->shortTimePeriods = 23;
    this->longTimePeriods = 42;
    this->wTimePeriods = 4;
    this->maxCandleTime = 53000;
    this->maxGain = 0.10f;
    this->maxLoss = 0.10f;
    
    this->factor = 3;
    this->pd = 7;
  }
  else if (_symbol.compare("LABU") == 0) {
    this->shortTimePeriods = 24;
    this->longTimePeriods = 78;
    this->wTimePeriods = 4;
    this->maxCandleTime = 42000;
    this->maxGain = 0.10f;
    this->maxLoss = 0.10f;
    
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
    this->shortTimePeriods = 44;
    this->longTimePeriods = 45;
    this->wTimePeriods = 4;
    this->maxCandleTime = 52000;
    this->maxGain = 0.10f;
    this->maxLoss = 0.10f;
    
    this->factor = 3;
    this->pd = 7;
  }
  else if (_symbol.compare("JDST") == 0) {
    this->shortTimePeriods = 41;
    this->longTimePeriods = 51;
    this->wTimePeriods = 4;
    this->maxCandleTime = 39000;
    this->maxGain = 0.10f;
    this->maxLoss = 0.10f;
    
    this->factor = 3;
    this->pd = 7;
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
  this->maxCandleTime = 15000;
  this->shortTimePeriods = 20;
  this->longTimePeriods = 20;
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
  this->maxCandleTime = 15000;
}

void StockModel::resetShortTimePeriods() {
  this->shortTimePeriods = 20;
}

void StockModel::resetLongTimePeriods() {
  this->longTimePeriods = 20;
}

void StockModel::resetWTimePeriods() {
  this->wTimePeriods = 4;
}
