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
#include "Quotes.hpp"

bool Model::stopBuying = false;

std::map<std::string, Stock> Model::stocks = std::map<std::string, Stock>();

Quotes Model::timeQuotes;

const bool Model::loggingEnabled = false;

const std::string Model::quotesDirectory = "/Users/mwood212/Desktop/11_28_2016/";

const std::string Model::stockSymbolsForQuotesDirectory = "/Users/mwood212/Desktop/Stock-App/StocksForQuotes.txt";

const std::string Model::open = "OPEN";
const std::string Model::closed = "CLOSED";

std::string Model::purchasedStockSymbol = "";

bool Model::isMarketOpen(void) {
  time_t currentTime = time(0);
  struct tm* now = localtime(&currentTime);
  
  float timeAsFloat = now->tm_hour + (now->tm_min / 60.0f);
  if (timeAsFloat > 9.5f && timeAsFloat < 16.0f) {
    return true;
  }
  
  return false;
}

void Model::addTimeQuote(const TimeQuote _timeQuote) {
  Stock& stock = stocks[_timeQuote.getSymbol()];
  if (stock.symbol.empty()) {
    stocks[_timeQuote.getSymbol()] = Stock(_timeQuote.getSymbol());
  }
  stock.addTimeToCandles(_timeQuote);
}

void Model::resetTimeQuotes() {
  timeQuotes.resetTimeQuotes();
}

unsigned int Model::totalTimeQuotes() {
  return timeQuotes.totalTimeQuotes();
}

const TimeQuote& Model::getTimeQuote(const unsigned int& _index) {
  return timeQuotes.getTimeQuote(_index);
}

void Model::logQuotes() {
  timeQuotes.log();
}

std::string Model::symbolsForQuotesAsCSV() {
  return FileManager::readStockSymbolsForQuotes();
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
