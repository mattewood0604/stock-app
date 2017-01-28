//
//  BuySell.cpp
//  Stock-App
//
//  Created by Matt Wood on 12/29/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#include <iostream>

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
    //std::cout << "BUY \t" << _stock.symbol << ":\t" << currentCandle.getOpen() << std::endl;
    if (_stock.numberOfTrades == 0) {
      Model::setStopBuying(false);
    }
    
    _stock.isBought = true;
    _stock.isBuy = false;
    _stock.buyPrice = _stock.currentQuote->offer; //currentCandle.getOpen();
    _stock.numberOfTrades++;
    Model::setPurchasedStockSymbol(_stock.symbol);
    return;
  }
  else if (_stock.isSell) {
    //std::cout << "SELL\t" << _stock.symbol << ":\t" << currentCandle.getOpen() << std::endl;
    //std::cout << "------------------------" << std::endl;
    _stock.moneyMade += _stock.currentQuote->bid - _stock.buyPrice; //currentCandle.getOpen() - _stock.buyPrice;
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
