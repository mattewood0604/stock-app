//
//  Model.cpp
//  Stock-App
//
//  Created by Matt Wood on 10/17/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#include "Model.hpp"
#include "Quotes.hpp"

std::map<std::string, Stock> Model::stocks = std::map<std::string, Stock>();

Quotes Model::timeQuotes;

const bool Model::loggingEnabled = false;

const std::string Model::quotesDirectory = "/Users/mwood212/Desktop/10_25_2016/";

const std::string Model::open = "OPEN";
const std::string Model::closed = "CLOSED";

std::string Model::marketStatus = Model::open;

bool Model::isMarketOpen(void) {
  return marketStatus == open;
}

void Model::setMarketStatus(const std::string& _status) {
  marketStatus = _status;
}

void Model::addTimeQuote(const TimeQuote _timeQuote) {
  Stock& stock = stocks[_timeQuote.getSymbol()]; //TestModel::stockForSymbol(quote.getSymbol());
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
