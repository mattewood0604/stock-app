//
//  Model.cpp
//  Stock-App
//
//  Created by Matt Wood on 10/17/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#include "Model.hpp"
#include "Quotes.hpp"

Quotes Model::timeQuotes;

const bool Model::loggingEnabled = true;

const std::string Model::quotesDirectory = "/Users/Matt/Desktop/10_20_2016/";

const std::string Model::open = "OPEN";
const std::string Model::closed = "CLOSED";

std::string Model::marketStatus = Model::open;

bool Model::isMarketOpen(void) {
  return marketStatus == open;
}

void Model::setMarketStatus(const std::string& _status) {
  marketStatus = _status;
}

void Model::addTimeQuote(const std::string& _timeQuote) {
  timeQuotes.addTimeQuote(_timeQuote);
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
