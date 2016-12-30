//
//  Response.cpp
//  Stock-App
//
//  Created by Matt Wood on 10/15/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#include <iostream>

#include "Model.hpp"
#include "Response.hpp"

void Response::init() {
  this->memory = NULL;
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

void Response::parseQuotes() const {
  static std::string quotes = "\"results\":[";
  
  std::string jsonString = std::string(this->memory);
  
  int quotesIndex = (int)jsonString.find(quotes);
  if (quotesIndex < 0) {
    return;
  }
  
  int closingBracketIndex = (int)jsonString.find("]", quotesIndex);
  if (closingBracketIndex < 0) {
    return;
  }
  std::string quotesString = jsonString.substr(quotesIndex + quotes.size(), closingBracketIndex - quotesIndex - quotes.size());
  if (quotesString.size() <= 0) {
    return;
  }
  
  int openCurlyIndex = (int)quotesString.find("{");
  int closeCurlyIndex = (int)quotesString.find("}");
  while (openCurlyIndex >= 0 && closeCurlyIndex >= 0) {
    std::string quote = quotesString.substr(openCurlyIndex, closeCurlyIndex - openCurlyIndex + 1);
    
    TimeQuote timeQuote = TimeQuote(quote);
    timeQuote.writeToFile();
    Model::addTimeQuote(timeQuote);
    
    openCurlyIndex = (int)quotesString.find("{", closeCurlyIndex);
    closeCurlyIndex = (int)quotesString.find("}", openCurlyIndex);
  }
}
