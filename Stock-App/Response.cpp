//
//  Response.cpp
//  Stock-App
//
//  Created by Matt Wood on 10/15/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#include <iostream>

#include "Model.hpp"
#include "Quotes.hpp"
#include "Response.hpp"

void Response::init() {
  this->memory = (char*)malloc(1);
  this->size = 0;
}

void Response::log() const {
  if (!Model::loggingEnabled) {
    return;
  }
  
  for (unsigned int i = 0; i < this->size; i++) {
    std::cout << this->memory[i];
  }
  
  std::cout << std::endl;
}

std::string Response::parseMarketStatus(const std::string& _json) const {
  static std::string status = "\"status\":";
  int statusIndex = (int)_json.find(status);
  int tooltipIndex = (int)_json.find(",", statusIndex);
  std::string marketStatus = _json.substr(statusIndex + status.size() + 1, tooltipIndex - statusIndex - status.size() - 2); // +1 and -2 for removing quotes
  return marketStatus;
}

void Response::parseQuotes(const std::string& _json) const {
  static std::string quotes = "\"quotes\":[";
  
  int quotesIndex = (int)_json.find(quotes);
  int closingBracketIndex = (int)_json.find("]", quotesIndex);
  std::string quotesString = _json.substr(quotesIndex + quotes.size(), closingBracketIndex - quotesIndex - quotes.size());
  
  int openCurlyIndex = (int)quotesString.find("{");
  int closeCurlyIndex = (int)quotesString.find("}");
  while (openCurlyIndex >= 0 && closeCurlyIndex >= 0) {
    std::string quote = quotesString.substr(openCurlyIndex, closeCurlyIndex - openCurlyIndex + 1);
    
    Model::addTimeQuote(quote);
    
    openCurlyIndex = (int)quotesString.find("{", closeCurlyIndex);
    closeCurlyIndex = (int)quotesString.find("}", openCurlyIndex);
  }
}

void Response::marketStatus() const {
  std::string jsonString = std::string(this->memory);
  Model::setMarketStatus(parseMarketStatus(jsonString));
}

void Response::parseQuotes() const {
  //if (!Model::isMarketOpen()) {
  //  return;
  //}
  
  std::string jsonString = std::string(this->memory);
  parseQuotes(jsonString);
}
