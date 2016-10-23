//
//  Quotes.cpp
//  Stock-App
//
//  Created by Matt Wood on 10/16/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#include "Quotes.hpp"

#include <iostream>

Quotes::Quotes() {
  this->timeQuotes = std::vector<TimeQuote>();
}

void Quotes::addTimeQuote(const std::string &_quote) {
  TimeQuote quote = TimeQuote(_quote);
  
  for (unsigned int i = 0; i < timeQuotes.size(); i++) {
    TimeQuote& stockQuote = timeQuotes[i];
    if (stockQuote.getSymbol() == quote.getSymbol()) {
      stockQuote = quote;
      return;
    }
  }
  
  timeQuotes.push_back(quote);
}

void Quotes::addTimeQuoteFromCSV(const std::string& _quote) {
  TimeQuote quote = TimeQuote(_quote, true);
  timeQuotes.push_back(quote);
}

void Quotes::resetTimeQuotes() {
  timeQuotes.clear();
}

unsigned int Quotes::totalTimeQuotes() {
  return (unsigned int)timeQuotes.size();
}

const TimeQuote& Quotes::getTimeQuote(const unsigned int& _index) {
  return timeQuotes[_index];
}

void Quotes::log() {
  for (unsigned int i = 0; i < timeQuotes.size(); i++) {
    const TimeQuote& stockQuote = timeQuotes[i];
    stockQuote.log();
  }
}
