//
//  BuySell.cpp
//  Stock-App
//
//  Created by Matt Wood on 12/29/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#include <iostream>

#include "RestCall.hpp"
#include "BuySell.hpp"
#include "Model.hpp"
#include "StockModel.hpp"

void BuySell::buyOrSell(Stock& _stock) {
  if (!_stock.waveTrendComplete) {
    return;
  }
  
  const Candle& currentCandle = _stock.candles[_stock.candles.size() - 1];
  if (currentCandle.getClose() == 0) {
    return;
  }
  
  if (_stock.maxLossTaken) {
    return;
  }
  
  /*
  const unsigned int longSmaLength = 30;
  const unsigned int smaLength = 15;
  float smaSlope = 0;
  float longSmaSlope = 0;
  if (_stock.getNumberOfCandles() >= longSmaLength + 1) {
    float previousSmaSlope = 0;
    for (unsigned int i = 0; i < longSmaLength; i++) {
      float averagePrice = _stock.candles[_stock.candles.size() - i - 1].getAveragePrice();
      if (i < smaLength) {
        smaSlope += averagePrice;
      }
      longSmaSlope += averagePrice;
    }
    smaSlope /= smaLength;
    longSmaSlope /= longSmaLength;
  }
   */
  
  //
  //float slope = currentCandle.getAveragePrice() - _stock.candles[_stock.candles.size() - 2].getAveragePrice();
  //float bidMoreAsk =
  if (_stock.isBuy && Model::getPurchasedStockSymbol().compare("") == 0 && (!Model::isStopBuying() || _stock.numberOfTrades == 0)) {
    //RestCall::order(_stock, "buy", 1, _stock.currentQuote.price + 1);
    //std::cout << "BUY \t(" << _stock.numberOfQuotes << ")(" << _stock.w1 << ", " << _stock.w2 << ") :\t" << _stock.currentQuote.price << std::endl;
    if (_stock.numberOfTrades == 0) {
      Model::setStopBuying(false);
    }
    
    _stock.isBought = true;
    _stock.isBuy = false;
    _stock.buyPrice = _stock.currentQuote.price + .01; //currentCandle.getOpen();
    //_stock.numberOfTrades++;
    Model::setPurchasedStockSymbol(_stock.symbol);
    return;
  }
  else if (_stock.isSell && _stock.isBought) {
    //RestCall::order(_stock, "sell", 1, _stock.currentQuote.price - 1);
    //std::cout << "SELL\t(" << _stock.numberOfQuotes << ")(" << _stock.w1 << ", " << _stock.w2 << ") :\t" << _stock.currentQuote.price << std::endl;
    //std::cout << "------------------------" << std::endl;
    _stock.moneyMade += (_stock.currentQuote.price - .01) - _stock.buyPrice; //currentCandle.getOpen() - _stock.buyPrice;
    //std::cout << (_stock.currentQuote.price - .01) - _stock.buyPrice << std::endl;
    _stock.percentageMade = _stock.moneyMade / _stock.buyPrice;
    
    if (_stock.percentageMade > _stock.maxMade) { 
      _stock.maxMade = _stock.percentageMade;
    }
    
    _stock.isSell = false;
    _stock.isBought = false;
    
    if (_stock.moneyMade / _stock.buyPrice < -0.02) {
      Model::setStopBuying(true);
      _stock.maxLossTaken = true;
    }
    
    Model::setPurchasedStockSymbol("");
    
    _stock.numberOfTrades++;
    if (_stock.currentQuote.price - _stock.buyPrice < 0) {
      _stock.negativeTrades++;
    }
    
    return;
  }
  
  float averagePrice = currentCandle.getAveragePrice();
  if ((averagePrice >= _stock.buyPrice * _stock.getStockModel().getMaxGain() || averagePrice <= _stock.buyPrice * _stock.getStockModel().getMaxLoss()) && _stock.isBought) {
    _stock.isBuy = false;
    _stock.isSell = true;
    return;
  }
  
  if (_stock.w1 >= _stock.w2 && !_stock.isBought) {
    //std::cout << "BUY \t" << "(" << _stock.w1 << ", " << _stock.w2 << ")" << std::endl;
    _stock.isBuy = true;
  }
  else if (_stock.w1 <= _stock.w2 && _stock.isBought) {
    //std::cout << "SELL\t" << "(" << _stock.w1 << ", " << _stock.w2 << ")" << std::endl;
    _stock.isSell = true;
  }
}

void BuySell::buyOrSellTimeSpan(Stock &_stock) {
  float moneyMade = _stock.buyPrice ? _stock.currentQuote.price - _stock.buyPrice : 0;
  float percentageMade = moneyMade ? (moneyMade / _stock.buyPrice) * 100 : 0;

  if (_stock.getStockModel().getBuyQuoteNumber(_stock.numberOfTrades) == _stock.numberOfQuotes) {
    //RestCall::order(_stock, "buy", 10, _stock.currentQuote.price + 1);
    std::cout << "BUY \t" << _stock.symbol << ":\t" << _stock.currentQuote.price << std::endl;
    
    _stock.isBought = true;
    _stock.buyPrice = _stock.currentQuote.price; //currentCandle.getOpen();
  }
  else if ((_stock.getStockModel().getSellQuoteNumber(_stock.numberOfTrades) == _stock.numberOfQuotes || percentageMade <= -2.0) && _stock.isBought) {
    //RestCall::order(_stock, "sell", 10, _stock.currentQuote.price - 1);
    std::cout << "SELL\t" << _stock.symbol << ":\t" << _stock.currentQuote.price << std::endl;
    std::cout << "------------------------" << std::endl;
    _stock.moneyMade += _stock.currentQuote.price - _stock.buyPrice; //currentCandle.getOpen() - _stock.buyPrice;
    std::cout << "Money Made = " << moneyMade << std::endl;
    _stock.percentageMade = moneyMade / _stock.buyPrice;
    std::cout << "Percentage Made = " << percentageMade << std::endl;
    
    _stock.numberOfTrades++;
    _stock.isBought = false;
  }
}
