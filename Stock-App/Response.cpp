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
#include "TestModel.hpp"

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

std::string Response::parseUrlForStock() const {
  std::string id = "\"id\":\"";
  
  std::string jsonString = std::string(this->memory);
  int idIndex = (int)jsonString.find(id);
  if (idIndex < 0) {
    std::cout << "Unable to parse id from response for stock" << std::endl;
    return "";
  }
  
  int commaIndex = (int)jsonString.find("\",", idIndex);
  if (commaIndex < idIndex) {
    std::cout << "Unable to parse id from response for stock" << std::endl;
    return "";
  }
  
  return jsonString.substr(idIndex + id.size(), commaIndex - (idIndex + id.size()));
}

unsigned int Response::parseAverageVolume() const {
  std::string averageVolume = "\"average_volume\":\"";
  
  std::string jsonString = std::string(this->memory);
  int averageVolumeIndex = (int)jsonString.find(averageVolume);
  if (averageVolumeIndex < 0) {
    return 0;
  }
  
  int commaIndex = (int)jsonString.find("\",", averageVolumeIndex);
  if (commaIndex < averageVolumeIndex) {
    return 0;
  }
  
  std::string averageVolumeString = jsonString.substr(averageVolumeIndex + averageVolume.size(), commaIndex - (averageVolumeIndex + averageVolume.size()));
  return atoi(averageVolumeString.c_str());
}

std::string Response::nextUrlForInstruments() const {
  std::string next = "\"next\":\"";
  
  std::string jsonString = std::string(this->memory);
  int nextIndex = (int)jsonString.find(next);
  if (nextIndex < 0) {
    std::cout << "Unable to parse next url from response for instruments" << std::endl;
    return "";
  }
  
  int quoteIndex = (int)jsonString.find("\"}", nextIndex);
  if (quoteIndex < nextIndex) {
    std::cout << "Unable to parse next url from response for instruments" << std::endl;
    return "";
  }
  
  return jsonString.substr(nextIndex + next.size(), quoteIndex - (nextIndex + next.size()));
}

std::vector<std::string> Response::getAllSymbolsFromInstruments() const {
  std::string symbol = "\"symbol\":\"";
  
  std::vector<std::string> symbols = std::vector<std::string>();
  
  std::string jsonString = std::string(this->memory);
  int symbolIndex = (int)jsonString.find(symbol);
  while (symbolIndex > 0) {
    int commaIndex = (int)jsonString.find("\",", symbolIndex);
    if (commaIndex < symbolIndex) {
      break;
    }
    
    std::string stockSymbol = jsonString.substr(symbolIndex + symbol.size(), commaIndex - (symbolIndex + symbol.size()));
    symbols.push_back(stockSymbol);
    symbolIndex = (int)jsonString.find(symbol, commaIndex);
  }
  
  return symbols;
}

void Response::tradingInformationFromInstruments() const {
  std::string symbol = "\"symbol\":\"";
  std::string dayTradeRatio = "\"day_trade_ratio\":\"";
  std::string maintenanceRatio = "\"maintenance_ratio\":\"";
  std::string marginInitialRatio = "\"margin_initial_ratio\":\"";
  std::string tradeable = "\"tradeable\":";
  
  std::string jsonString = std::string(this->memory);
  int symbolIndex = (int)jsonString.find(symbol);
  int dayTradeRatioIndex = (int)jsonString.find(dayTradeRatio);
  int maintenanceRatioIndex = (int)jsonString.find(maintenanceRatio);
  int marginInitialRatioIndex = (int)jsonString.find(marginInitialRatio);
  int tradeableIndex = (int)jsonString.find(tradeable);
  
  while (symbolIndex > 0) {
    int commaIndex = (int)jsonString.find("\",", symbolIndex);
    std::string stockSymbol = jsonString.substr(symbolIndex + symbol.size(), commaIndex - (symbolIndex + symbol.size()));
    
    commaIndex = (int)jsonString.find("\",", dayTradeRatioIndex);
    std::string dayTradeRatioString = jsonString.substr(dayTradeRatioIndex + dayTradeRatio.size(), commaIndex - (dayTradeRatioIndex + dayTradeRatio.size()));
    
    commaIndex = (int)jsonString.find("\",", maintenanceRatioIndex);
    std::string maintenanceRatioString = jsonString.substr(maintenanceRatioIndex + maintenanceRatio.size(), commaIndex - (maintenanceRatioIndex + maintenanceRatio.size()));
    
    commaIndex = (int)jsonString.find("\",", marginInitialRatioIndex);
    std::string marginInitialRatioString = jsonString.substr(marginInitialRatioIndex + marginInitialRatio.size(), commaIndex - (marginInitialRatioIndex + marginInitialRatio.size()));
    
    commaIndex = (int)jsonString.find(",\"", tradeableIndex);
    std::string tradeableString = jsonString.substr(tradeableIndex + tradeable.size(), commaIndex - (tradeableIndex + tradeable.size()));
    
    if (tradeableString.size() < 5 && stockIsValid(stockSymbol)) {
      std::cout << stockSymbol << std::endl;
      /*std::cout << "STOCK: " << stockSymbol << std::endl;
      std::cout << "--------------" << std::endl;
      std::cout << "DTR: " << dayTradeRatioString << std::endl;
      std::cout << "MR : " << maintenanceRatioString << std::endl;
      std::cout << "MIR: " << marginInitialRatioString << std::endl;
      std::cout << "TRADEABLE: " << tradeableString << std::endl;
      std::cout << std::endl;*/
    }
    
    
    symbolIndex = (int)jsonString.find(symbol, commaIndex);
    dayTradeRatioIndex = (int)jsonString.find(dayTradeRatio, commaIndex);
    maintenanceRatioIndex = (int)jsonString.find(maintenanceRatio, commaIndex);
    marginInitialRatioIndex = (int)jsonString.find(marginInitialRatio, commaIndex);
    tradeableIndex = (int)jsonString.find(tradeable, commaIndex);
  }
}

bool Response::stockIsValid(const std::string& _stockSymbol) const {
  for (unsigned int i = 0; i < TestModel::getTestStockSymbolCount(); i++) {
    if (TestModel::getTestStockSymbol(i).compare(_stockSymbol) == 0) {
      return true;
    }
  }
  
  return false;
}
