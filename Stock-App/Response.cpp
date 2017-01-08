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

std::string Response::parseAuthentication() const {
  std::string jsonString = std::string(this->memory);
  
  std::string tokenString = "{\"token\":\"";
  std::string curlyString = "\"}";
  int tokenStartIndex = (int)jsonString.find(tokenString.c_str()) + tokenString.size();
  int tokenEndIndex = (int)jsonString.size() - curlyString.size();
  
  if (tokenStartIndex < 0 || tokenEndIndex < 0) {
    return "";
  }
  else if (tokenEndIndex < tokenStartIndex) {
    return "";
  }
  
  return jsonString.substr(tokenStartIndex, tokenEndIndex - tokenStartIndex);
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

bool Response::parseOpenDays() const {
  std::string isOpen = "\"is_open\":";
  
  std::string jsonString = std::string(this->memory);
  int isOpenIndex = (int)jsonString.find(isOpen);
  if (isOpenIndex < 0) {
    return false;
  }
  
  int commaIndex = (int)jsonString.find(",", isOpenIndex);
  if (commaIndex < isOpenIndex) {
    return false;
  }
  
  std::string isOpenBool = jsonString.substr(isOpenIndex + isOpen.size(), commaIndex - (isOpenIndex + isOpen.size()));
  return isOpenBool.size() == 4;
}

float Response::parseBuyingPower() const {
  std::string buyingPower = "\"buying_power\":\"";
  
  std::string jsonString = std::string(this->memory);
  int buyingPowerIndex = (int)jsonString.find(buyingPower);
  if (buyingPowerIndex < 0) {
    std::cout << "Unable to parse buying power from response" << std::endl;
    return 0;
  }
  
  int commaIndex = (int)jsonString.find("\",", buyingPowerIndex);
  if (commaIndex < buyingPowerIndex) {
    std::cout << "Unable to parse buying power from response" << std::endl;
    return 0;
  }
  
  std::string buyingPowerValue = jsonString.substr(buyingPowerIndex + buyingPower.size(), commaIndex - (buyingPowerIndex + buyingPower.size()));
  return atof(buyingPowerValue.c_str());
}

std::string Response::parseIdForStock() const {
  std::string id = "\"id\":\"";
  
  std::string jsonString = std::string(this->memory);
  int idIndex = (int)jsonString.find(id);
  if (idIndex < 0) {
    std::cout << "Unable to parse id from response for stock" << std::endl;
    return "";
  }
  
  int commaIndex = (int)jsonString.find("\",", idIndex);
  if (commaIndex < idIndex) {
    std::cout << "Unable to parse id power from response for stock" << std::endl;
    return "";
  }
  
  return jsonString.substr(idIndex + id.size(), commaIndex - (idIndex + id.size()));
}
