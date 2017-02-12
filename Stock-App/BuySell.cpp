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
  
  //
  if (_stock.isBuy && Model::getPurchasedStockSymbol().compare("") == 0 && (!Model::isStopBuying() || _stock.numberOfTrades == 0)) {
    //RestCall::order(_stock, "buy", 1, _stock.currentQuote->price + 1);
    //std::cout << "BUY \t" << _stock.symbol << ":\t" << _stock.currentQuote->price << std::endl;
    if (_stock.numberOfTrades == 0) {
      Model::setStopBuying(false);
    }
    
    _stock.isBought = true;
    _stock.isBuy = false;
    _stock.buyPrice = _stock.currentQuote->price; //currentCandle.getOpen();
    _stock.numberOfTrades++;
    Model::setPurchasedStockSymbol(_stock.symbol);
    return;
  }
  else if (_stock.isSell) {
    //RestCall::order(_stock, "sell", 1, _stock.currentQuote->price - 1);
    //std::cout << "SELL\t" << _stock.symbol << ":\t" << _stock.currentQuote->price << std::endl;
    //std::cout << "------------------------" << std::endl;
    _stock.moneyMade += _stock.currentQuote->price - _stock.buyPrice; //currentCandle.getOpen() - _stock.buyPrice;
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
    return;
  }
  
  float averagePrice = currentCandle.getAveragePrice();
  if ((averagePrice >= _stock.buyPrice + _stock.getStockModel().getMaxGain() || averagePrice <= _stock.buyPrice - _stock.getStockModel().getMaxLoss()) && _stock.isBought) {
    _stock.isBuy = false;
    _stock.isSell = true;
    return;
  }
  
  if (_stock.w1 >= _stock.w2 && !_stock.isBought) {
    _stock.isBuy = true;
  }
  else if (_stock.w1 <= _stock.w2 && _stock.isBought) {
    _stock.isSell = true;
  }
}

void BuySell::buyOrSellTimeSpan(Stock &_stock) {
  if (_stock.getStockModel().getBuyQuoteNumber() == _stock.numberOfQuotes) {
    //RestCall::order(_stock, "buy", 1, _stock.currentQuote->price + 1);
    std::cout << "BUY \t" << _stock.symbol << ":\t" << _stock.currentQuote->price << std::endl;
    if (_stock.numberOfTrades == 0) {
      Model::setStopBuying(false);
    }
    
    _stock.buyPrice = _stock.currentQuote->price; //currentCandle.getOpen();
    _stock.numberOfTrades++;
    return;
  }
  else if (_stock.getStockModel().getSellQuoteNumber() == _stock.numberOfQuotes) {
    //RestCall::order(_stock, "sell", 1, _stock.currentQuote->price - 1);
    std::cout << "SELL\t" << _stock.symbol << ":\t" << _stock.currentQuote->price << std::endl;
    std::cout << "------------------------" << std::endl;
    _stock.moneyMade += _stock.currentQuote->price - _stock.buyPrice; //currentCandle.getOpen() - _stock.buyPrice;
    std::cout << "Money Made = " << _stock.moneyMade << std::endl;
    _stock.percentageMade = _stock.moneyMade / _stock.buyPrice;
    
    _stock.numberOfTrades++;
    return;
  }
}
