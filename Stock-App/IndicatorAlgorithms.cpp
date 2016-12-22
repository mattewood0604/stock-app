//
//  IndicatorAlgorithms.cpp
//  Stock-App
//
//  Created by Matt Wood on 12/18/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#include <cmath>

#include "IndicatorAlgorithms.hpp"

////////////////////////////////////////////////////////////////////////////////////
// WAVE TREND ALGORITHM
////////////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////////////
// SUPER TREND ALGORITHM
////////////////////////////////////////////////////////////////////////////////////
void IndicatorAlgorithms::supertrendAlgorithm(Stock& _stock) {
  static float previousTrend = 0;
  static float previousTrendUp = 0;
  static float previousTrendDown = 0;
  
  float avgTrueRange = averageTrueRange(_stock);
  if (avgTrueRange == -100000) {
    return;
  }
  
  const Candle& candle = _stock.getLastCandle();
  float highlow2 = (candle.getHigh() + candle.getLow()) / 2.0f;
  float factorAdjusted = _stock.getStockModel().getFactor() * avgTrueRange;
  
  float up = highlow2 - factorAdjusted;
  float down = highlow2 + factorAdjusted;
  
  float trendUp = candle.getClose() > previousTrendUp ? fmaxf(up, previousTrendUp) : up;
  float trendDown = candle.getClose() < previousTrendDown ? fminf(down, previousTrendDown) : down;
  
  float trend = 0;
  if (candle.getClose() > previousTrendDown) {
    trend = 1;
  }
  else {
    if (candle.getClose() < previousTrendUp) {
      trend = -1;
    }
    else {
      if (isnan(previousTrend)) {
        trend = 1;
      }
      else {
        trend = previousTrend;
      }
    }
  }
  
  //this->waveTrendComplete = true;
  //float tsl = trend == 1 ? trendUp : trendDown;
  //std::cout << "TREND: " << trend << std::endl;
  if (trend == 1) {
    //this->isBuy = true;
    //std::cout << "BUY: " << candle.getClose() << std::endl;
  }
  else {
    //this->isSell = true;
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

float IndicatorAlgorithms::averageTrueRange(Stock& _stock) {
  if (_stock.getNumberOfCandles() < _stock.getStockModel().getPd() + 1) {
    return -100000;
  }
  
  float averageTrueRange = 0.0f;
  for (unsigned int i = (unsigned int)_stock.getNumberOfCandles() - 1; i > _stock.getNumberOfCandles() - _stock.getStockModel().getPd(); i--) {
    const Candle& current = _stock.getCandleAtIndex(i);
    const Candle& previous = _stock.getCandleAtIndex(i - 1);
    float trueRange = fmaxf(current.getHigh() - current.getLow(), fabsf(current.getHigh() - previous.getClose()));
    trueRange = fmaxf(trueRange, fabsf(current.getLow() - previous.getClose()));
    averageTrueRange += trueRange;
  }
  
  averageTrueRange /= _stock.getStockModel().getPd();
  return averageTrueRange;
}
