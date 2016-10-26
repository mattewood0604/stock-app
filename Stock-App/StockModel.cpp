//
//  StockModel.cpp
//  Stock-App
//
//  Created by Matt Wood on 10/21/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#include "StockModel.hpp"

StockModel::StockModel() {
  this->shortTimePeriods = 20;
  this->longTimePeriods = 40;
  this->wTimePeriods = 4;
  this->maxCandleTime = 30000;
  this->maxGain = 0.10f;
  this->maxLoss = 0.10f;
}

void StockModel::reset() {
  this->maxCandleTime = 0;
  this->shortTimePeriods = 0;
  this->longTimePeriods = 0;
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

void StockModel::incrementShortTimePeriods() {
  this->shortTimePeriods++;
}

void StockModel::incrementLongTimePeriods() {
  this->longTimePeriods++;
}

void StockModel::incrementMaxCandleTime() {
  this->maxCandleTime += 1000;
}

void StockModel::resetMaxCandleTime() {
  this->maxCandleTime = 0;
}

void StockModel::resetShortTimePeriods() {
  this->shortTimePeriods = 0;
}
