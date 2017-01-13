//
//  TimeQuote.cpp
//  Stock-App
//
//  Created by Matt Wood on 10/15/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#include <ctime>
#include <sstream>
#include <iostream>

#include "FileManager.hpp"
#include "Model.hpp"
#include "TestModel.hpp"
#include "TimeQuote.hpp"

std::string TimeQuote::bidKey = "\"bid_price\":";
std::string TimeQuote::bidQtyKey = "\"bid_size\":";
std::string TimeQuote::offerKey = "\"ask_price\":";
std::string TimeQuote::offerQtyKey = "\"ask_size\":";
std::string TimeQuote::timeKey = "\"time\":";
std::string TimeQuote::percentKey = "\"percent\":";
std::string TimeQuote::changeKey = "\"change\":";
std::string TimeQuote::priceKey = "\"last_trade_price\":";
std::string TimeQuote::symbolKey = "\"symbol\":";

TimeQuote::TimeQuote(const std::string& _json, FROM _from, const std::string& _symbol) {
  if (_from == CSV) {
    this->fromCSV(_symbol, _json);
    return;
  }
  
  this->json = _json;
  
  this->dayTime = (uint64_t)time(0) * 1000;
  this->symbol = parseString(symbolKey);
  //this->price = parseFloat(priceKey);
  this->percent = 0;//parseFloat(percentKey);
  this->change = 0;//parseFloat(changeKey);
  this->bid = parseFloat(bidKey);
  this->bidQty = parseInt(bidQtyKey);
  this->offer = parseFloat(offerKey);
  this->offerQty = parseInt(offerQtyKey);
}

void TimeQuote::fromCSV(const std::string& _symbol, const std::string& _quote) {
  if (_quote.length() == 0) {
    return;
  }
  
  if (_quote[0] == 't') {
    return;
  }
  
  this->symbol = _symbol;
  
  int lastCommaIndex = -1;
  int commaIndex = (int)_quote.find(',');
  
  std::string value = _quote.substr(lastCommaIndex + 1, commaIndex - lastCommaIndex - 1);
  this->dayTime = stoll(value);
  lastCommaIndex = commaIndex;
  
  commaIndex = (int)_quote.find(',', lastCommaIndex + 1);
  value = _quote.substr(lastCommaIndex + 1, commaIndex - lastCommaIndex);
  //this->price = stof(value);
  lastCommaIndex = commaIndex;
  
  commaIndex = (int)_quote.find(',', lastCommaIndex + 1);
  value = _quote.substr(lastCommaIndex + 1, commaIndex - lastCommaIndex);
  this->bid = stof(value);
  lastCommaIndex = commaIndex;
  
  commaIndex = (int)_quote.find(',', lastCommaIndex + 1);
  value = _quote.substr(lastCommaIndex + 1, commaIndex - lastCommaIndex);
  this->bidQty = stoi(value);
  lastCommaIndex = commaIndex;
  
  commaIndex = (int)_quote.find(',', lastCommaIndex + 1);
  value = _quote.substr(lastCommaIndex + 1, commaIndex - lastCommaIndex);
  this->offer = stof(value);
  lastCommaIndex = commaIndex;
  
  commaIndex = (int)_quote.find(',', lastCommaIndex + 1);
  value = _quote.substr(lastCommaIndex + 1, commaIndex - lastCommaIndex);
  this->offerQty = stoi(value);
  lastCommaIndex = commaIndex;
  
  commaIndex = (int)_quote.find(',', lastCommaIndex + 1);
  value = _quote.substr(lastCommaIndex + 1, commaIndex - lastCommaIndex);
  this->percent = stof(value);
  lastCommaIndex = commaIndex;
  
  commaIndex = (int)_quote.find(',', lastCommaIndex + 1);
  value = _quote.substr(lastCommaIndex + 1, commaIndex - lastCommaIndex);
  this->change = stof(value);
}

void TimeQuote::writeToFile() const {
  FileManager::writeQuoteToFile(*this);
}

void TimeQuote::log() const {
  std::cout << this->symbol << " = {" << std::endl;
  std::cout << "\t" << timeKey << " " << this->dayTime << std::endl;
  //std::cout << "\t" << priceKey << " " << this->price << std::endl;
  //std::cout << "\t" << percentKey << " " << this->percent << std::endl;
  //std::cout << "\t" << changeKey << " " << this->change << std::endl;
  std::cout << "\t" << bidKey << " " << this->bid << std::endl;
  std::cout << "\t" << bidQtyKey << " " << this->bidQty << std::endl;
  std::cout << "\t" << offerKey << " " << this->offer << std::endl;
  std::cout << "\t" << offerQtyKey << " " << this->offerQty << std::endl;
  std::cout << "}" << std::endl;
}

std::string TimeQuote::toCSV() const {
  std::string csv;
  
  csv.append(std::to_string(dayTime));
  csv.append(",");
  //csv.append(std::to_string(price));
  //csv.append(",");
  csv.append(std::to_string(bid));
  csv.append(",");
  csv.append(std::to_string(bidQty));
  csv.append(",");
  csv.append(std::to_string(offer));
  csv.append(",");
  csv.append(std::to_string(offerQty));
  csv.append(",");
  csv.append(std::to_string(percent));
  csv.append(",");
  csv.append(std::to_string(change));
  csv.append("\n");
  
  return csv;
}

const std::string& TimeQuote::getSymbol() const {
  return this->symbol;
}

int TimeQuote::parseInt(const std::string& _key) const {
  int bidIndex = (int)this->json.find(_key);
  int commaIndex = (int)this->json.find(",", bidIndex);
  std::string bidString = this->json.substr(bidIndex + _key.size(), commaIndex - bidIndex - _key.size());
  return atoi(bidString.c_str());
}

float TimeQuote::parseFloat(const std::string& _key) const {
  int keyIndex = (int)this->json.find(_key);
  int commaIndex = (int)this->json.find(",", keyIndex);
  std::string floatString = this->json.substr(keyIndex + _key.size(), commaIndex - keyIndex - _key.size());
  floatString.erase(floatString.begin());
  floatString.pop_back();
  return atof(floatString.c_str());
}

std::string TimeQuote::parseString(const std::string& _key) const {
  int keyIndex = (int)this->json.find(_key);
  int commaIndex = (int)this->json.find(",", keyIndex);
  return this->json.substr(keyIndex + _key.size() + 1, commaIndex - keyIndex - _key.size() - 2); // +1 and -2 for removing quotes
}

uint64_t TimeQuote::parseTime() const {
  uint64_t timeNumber;
  
  int keyIndex = (int)this->json.find(timeKey);
  int commaIndex = (int)this->json.find(",", keyIndex);
  
  std::string timeString = this->json.substr(keyIndex + timeKey.size(), commaIndex - keyIndex - timeKey.size());
  std::stringstream convert(timeString);
  convert >> timeNumber;
  
  return timeNumber;
}
