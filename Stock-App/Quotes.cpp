//
//  Quotes.cpp
//  Stock-App
//
//  Created by Matt Wood on 10/16/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#include "Quotes.hpp"

std::vector<TimeQuote> Quotes::timeQuotes = std::vector<TimeQuote>();

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

void Quotes::log() {
  for (unsigned int i = 0; i < timeQuotes.size(); i++) {
    const TimeQuote& stockQuote = timeQuotes[i];
    stockQuote.log();
  }
}
