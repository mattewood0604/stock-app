//
//  IndicatorAlgorithms.cpp
//  Stock-App
//
//  Created by Matt Wood on 12/18/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#include <cmath>

#include "IndicatorAlgorithms.hpp"

void IndicatorAlgorithms::calculateWaveTrend(Stock& _stock) {
  const Candle& currentCandle = _stock.getLastCandle(); // stock.getLastCandle()
  if (_stock.getNumberOfCandles() < _stock.getStockModel().getShortTimePeriods()) { // stock.enoughCandlesToStart
    return;
  }
  
  if (_stock.averagePriceEMA == -1) {
    calculateAveragePriceEMA(_stock);
  }
  
  float averagePrice = currentCandle.getAveragePrice();
  float esa = _stock.ema(averagePrice, _stock.averagePriceEMA, _stock.getShortMultiplier());
  _stock.averagePriceEMA = esa;
  if (_stock.apESACalculated < _stock.getStockModel().getShortTimePeriods()) {
    _stock.apESA += fabs(averagePrice - esa);
    _stock.apESACalculated++;
    return;
  }
  else if (_stock.apESACalculated == _stock.getStockModel().getShortTimePeriods()) {
    _stock.apESA /= _stock.getStockModel().getShortTimePeriods();
    _stock.apESACalculated++;
  }
  
  float apMinusESA = fabs(averagePrice - esa);
  float d = _stock.ema(apMinusESA, _stock.apESA, _stock.getShortMultiplier());
  _stock.apESA = d;
  float c = (averagePrice - esa) / (0.015 * d);
  
  if (_stock.ciCalculated < _stock.getStockModel().getLongTimePeriods()) {
    _stock.ci += c;
    _stock.ciCalculated++;
    return;
  }
  else if (_stock.ciCalculated == _stock.getStockModel().getLongTimePeriods()) {
    _stock.ci /= _stock.getStockModel().getLongTimePeriods();
    _stock.ciCalculated++;
  }
  
  float tci = _stock.ema(c, _stock.ci, _stock.getLongMultiplier());
  _stock.ci = tci;
  _stock.w1 = tci;
  
  if (_stock.previousW1.size() < _stock.getStockModel().getWTimePeriods()) {
    _stock.previousW1.push_back(_stock.w1);
    return;
  }
  
  calculateWs(_stock);
  
  _stock.setWaveTrendComplete(true);
}

void IndicatorAlgorithms::calculateAveragePriceEMA(Stock& _stock) {
  _stock.averagePriceEMA = 0;
  for (unsigned int i = 0; i < _stock.getNumberOfCandles() - 1; i++) {
    const Candle& candle = _stock.getCandleAtIndex(i);
    float averagePrice = candle.getAveragePrice();
    _stock.averagePriceEMA += averagePrice;
  }
  _stock.averagePriceEMA /= _stock.getStockModel().getShortTimePeriods();
}

void IndicatorAlgorithms::calculateWs(Stock& _stock) {
  _stock.w2 = 0;
  for (unsigned int i = 0; i < _stock.getStockModel().getWTimePeriods(); i++) {
    float previousW1 = _stock.previousW1[i];
    _stock.w2 += previousW1;
  }
  _stock.w2 /= _stock.getStockModel().getWTimePeriods();
  
  if (_stock.previousW1.size() > 0) {
    _stock.previousW1.erase(_stock.previousW1.begin());
    _stock.previousW1.push_back(_stock.w1);
  }
}
