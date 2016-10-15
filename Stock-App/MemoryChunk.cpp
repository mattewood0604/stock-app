//
//  MemoryChunk.cpp
//  Stock-App
//
//  Created by Matt Wood on 10/15/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#include <string>
#include <iostream>

#include "constants.hpp"
#include "MemoryChunk.hpp"

class TimeQuote {
  public:
  
  private:
  
};

void MemoryChunk::log() const {
  if (!loggingEnabled) {
    return;
  }
  
  for (unsigned int i = 0; i < this->size; i++) {
    printf("%c", (char)this->memory[i]);
  }
  
  printf("\n");
}

std::string parseMarketStatus(const std::string& _json) {
  static std::string status = "\"status\":";
  int statusIndex = (int)_json.find(status);
  int tooltipIndex = (int)_json.find(",", statusIndex);
  std::string marketStatus = _json.substr(statusIndex + status.size() + 1, tooltipIndex - statusIndex - status.size() - 2); // +1 and -2 for removing quotes
  return marketStatus;
}

int parseInt(const std::string& _quote, const std::string& _key) {
  int bidIndex = (int)_quote.find(_key);
  int commaIndex = (int)_quote.find(",", bidIndex);
  std::string bidString = _quote.substr(bidIndex + _key.size(), commaIndex - bidIndex - _key.size());
  int bidNumber = atoi(bidString.c_str());
  std::cout << bidNumber << std::endl << std::endl;
  return bidNumber;
}

float parseFloat(const std::string& _quote, const std::string& _key) {
  int keyIndex = (int)_quote.find(_key);
  int commaIndex = (int)_quote.find(",", keyIndex);
  std::string bidString = _quote.substr(keyIndex + _key.size(), commaIndex - keyIndex - _key.size());
  float bidNumber = atof(bidString.c_str());
  return bidNumber;
}

std::string parseString(const std::string& _quote, const std::string& _key) {
  int keyIndex = (int)_quote.find(_key);
  int commaIndex = (int)_quote.find(",", keyIndex);
  return _quote.substr(keyIndex + _key.size() + 1, commaIndex - keyIndex - _key.size() - 2); // +1 and -2 for removing quotes
}

void parseQuotes(const std::string& _json) {
  static std::string quotes = "\"quotes\":[";
  static std::string bid = "\"bid\":";
  static std::string bidQty = "\"bidQty\":";
  static std::string offer = "\"offer\":";
  static std::string offerQty = "\"offerQty\":";
  static std::string time = "\"time\":";
  static std::string percent = "\"percent\":";
  static std::string change = "\"change\":";
  static std::string price = "\"price\":";
  static std::string symbol = "\"symbol\":";
  
  int quotesIndex = (int)_json.find(quotes);
  int closingBracketIndex = (int)_json.find("]", quotesIndex);
  std::string quotesString = _json.substr(quotesIndex + quotes.size(), closingBracketIndex - quotesIndex - quotes.size());
  
  std::cout << quotesString << std::endl << std::endl;
  
  int openCurlyIndex = (int)quotesString.find("{");
  int closeCurlyIndex = (int)quotesString.find("}");
  
  while (openCurlyIndex >= 0 && closeCurlyIndex >= 0) {
    std::string quote = quotesString.substr(openCurlyIndex, closeCurlyIndex - openCurlyIndex + 1);
    
    std::string symbolName = parseString(quote, symbol);
    std::cout << symbolName << std::endl;
    
    float priceNumber = parseFloat(quote, price);
    std::cout << priceNumber << std::endl;
    
    float percentNumber = parseFloat(quote, percent);
    std::cout << percentNumber << std::endl;
    
    float changeNumber = parseFloat(quote, change);
    std::cout << changeNumber << std::endl;
    
    float bidNumber = parseFloat(quote, bid);
    std::cout << bidNumber << std::endl;
    
    int bidQtyNumber = parseInt(quote, bidQty);
    std::cout << bidQtyNumber << std::endl;
    
    float offerNumber = parseFloat(quote, offer);
    std::cout << offerNumber << std::endl;
    
    int offerQtyNumber = parseInt(quote, offerQty);
    
    
    std::cout << std::endl;
    
    openCurlyIndex = (int)quotesString.find("{", closeCurlyIndex);
    closeCurlyIndex = (int)quotesString.find("}", openCurlyIndex);
  }
}

void MemoryChunk::parse() const {
  std::string jsonString = std::string(this->memory);
  
  std::string marketStatus = parseMarketStatus(jsonString);
  parseQuotes(jsonString);
}
