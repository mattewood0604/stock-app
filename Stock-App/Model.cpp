//
//  Model.cpp
//  Stock-App
//
//  Created by Matt Wood on 10/17/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#include <iostream>

#include "FileManager.hpp"
#include "Model.hpp"

bool Model::stopBuying = false;

float Model::buyingPower = 0;

std::map<std::string, Stock> Model::stocks = std::map<std::string, Stock>();

bool Model::loggingEnabled = false;

const std::string Model::open = "OPEN";
const std::string Model::closed = "CLOSED";

std::string Model::purchasedStockSymbol = "";

bool Model::isMarketOpen() {
  time_t currentTime = time(0);
  struct tm* now = localtime(&currentTime);
  
  float timeAsFloat = now->tm_hour + (now->tm_min / 60.0f);
  if (timeAsFloat > 9.5f && timeAsFloat < 16.0f) {
    return true;
  }
  
  return false;
}

void Model::addTimeQuote(TimeQuote _timeQuote) {
  Stock& stock = stocks[_timeQuote.getSymbol()];
  if (stock.symbol.empty()) {
    stocks[_timeQuote.getSymbol()] = Stock(_timeQuote.getSymbol());
  }
  stock.addTimeToCandles(_timeQuote);
}

void Model::setPurchasedStockSymbol(const std::string& _symbol) {
  purchasedStockSymbol = _symbol;
}

const std::string& Model::getPurchasedStockSymbol() {
  return purchasedStockSymbol;
}

void Model::setStopBuying(bool _stopBuying) {
  stopBuying = _stopBuying;
}

bool Model::isStopBuying() {
  return stopBuying;
}

Stock& Model::getStockForSymbol(const std::string& _symbol) {
  return stocks[_symbol];
}

float Model::getBuyingPower() {
  return buyingPower;
}

void Model::setBuyingPower(const float& _buyingPower) {
  buyingPower = _buyingPower;
}
