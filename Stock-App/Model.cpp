//
//  Model.cpp
//  Stock-App
//
//  Created by Matt Wood on 10/17/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#include "Model.hpp"
#include "Quotes.hpp"

const std::string Model::open = "OPEN";
const std::string Model::closed = "CLOSED";

std::vector<TimeQuote> Model::timeQuotes = std::vector<TimeQuote>();

const bool Model::loggingEnabled = true;
std::string Model::marketStatus = Model::open;

bool Model::isMarketOpen(void) {
  return marketStatus == open;
}

void Model::setMarketStatus(const std::string& _status) {
  marketStatus = _status;
}

void Model::addTimeQuote(const std::string& _timeQuote) {
  Quotes::addTimeQuote(_timeQuote);
}

void Model::logQuotes() {
  Quotes::log();
}
