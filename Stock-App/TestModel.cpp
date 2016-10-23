//
//  TestModel.cpp
//  Stock-App
//
//  Created by Matt Wood on 10/20/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#include "TestModel.hpp"

std::map<std::string, Stock> TestModel::stocks;

const bool TestModel::loggingEnabled = true;

std::string TestModel::runDate = "";
const std::string TestModel::stockSymbol = "JNUG";
std::vector<std::string> TestModel::dates = {"10_4_2016", "10_5_2016", "10_6_2016"};

Stock& TestModel::stockForSymbol(const std::string& _symbol) {
  Stock stock = stocks[_symbol];
  if (stock.symbol.empty()) {
    stocks[_symbol] = Stock(_symbol);
  }
  return stocks[_symbol];
}

unsigned int TestModel::totalTimeQuotes() {
  const Stock& stock = stocks[stockSymbol];
  return (unsigned int)stock.testQuotes.size();
}

const TimeQuote& TestModel::getTestQuote(unsigned int _index) {
  Stock stock = stocks[stockSymbol];
  return stock.testQuotes[_index];
}

void TestModel::setDate(const std::string& _date) {
  runDate = _date;
}

std::string TestModel::quotesDirectory() {
  return "/Users/Matt/Desktop/symbol_data/" + runDate + "/" + stockSymbol + ".csv";
}

void TestModel::resetTestData() {
  stocks.clear();
}

void TestModel::logMoneyMade() {
  const Stock& stock = stocks[stockSymbol];
  stock.logMoneyMade();
}
