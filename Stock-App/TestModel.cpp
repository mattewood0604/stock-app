//
//  TestModel.cpp
//  Stock-App
//
//  Created by Matt Wood on 10/20/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#include "TestModel.hpp"

const unsigned int TestModel::maximumLongTimePeriods = 100;
const unsigned int TestModel::maximumShortTimePeriods = 50;
const unsigned int TestModel::maximumCandleTime = 60000;
const unsigned int TestModel::maximumWTimePeriods = 7;

const bool TestModel::loggingEnabled = true;

std::string TestModel::runDate = "";
const std::string TestModel::stockSymbol = "ADMP";
std::vector<std::string> TestModel::dates;

Stock TestModel::testingStock = Stock(stockSymbol);

void TestModel::initialize() {
  //dates.push_back("10_4_2016");
  dates.push_back("10_5_2016");
  dates.push_back("10_6_2016");
  dates.push_back("10_7_2016");
  dates.push_back("10_10_2016");
  dates.push_back("10_11_2016");
  dates.push_back("10_12_2016");
  dates.push_back("10_13_2016");
  dates.push_back("10_20_2016");
  dates.push_back("10_21_2016");
  dates.push_back("10_25_2016");
  dates.push_back("10_26_2016");
  //dates.push_back("10_27_2016");
  //dates.push_back("10_28_2016");
  //dates.push_back("10_31_2016");
}

Stock& TestModel::getTestingStock() {
  return testingStock;
}

/*
Stock& TestModel::stockForSymbol(const std::string& _symbol) {
  Stock stock = stocks[_symbol];
  if (stock.symbol.empty()) {
    stocks[_symbol] = Stock(_symbol);
  }
  return stocks[_symbol];
}
 */

unsigned int TestModel::totalTimeQuotes() {
  //const Stock& stock = stocks[stockSymbol];
  //return (unsigned int)stock.testQuotes.size();
  return (unsigned int)testingStock.testQuotes.size();
}

const TimeQuote& TestModel::getTestQuote(unsigned int _index) {
  //Stock stock = stocks[stockSymbol];
  //return stock.testQuotes[_index];
  return testingStock.testQuotes[_index];
}

void TestModel::setDate(const std::string& _date) {
  runDate = _date;
}

std::string TestModel::quotesDirectory() {
  return "/Users/Matt/Desktop/symbol_data/" + runDate + "/" + stockSymbol + ".csv";
}

void TestModel::resetTestData() {
  //stocks.clear();
}

void TestModel::resetStockData() {
  //Stock& stock = stocks[stockSymbol];
  //stock.reset();
  testingStock.reset();
}

void TestModel::hardResetStock() {
  testingStock = Stock(stockSymbol);
}

void TestModel::logMoneyMade() {
  //const Stock& stock = stocks[stockSymbol];
  //stock.logMoneyMade();
  testingStock.logMoneyMade();
}
