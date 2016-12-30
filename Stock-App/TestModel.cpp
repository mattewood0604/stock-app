//
//  TestModel.cpp
//  Stock-App
//
//  Created by Matt Wood on 10/20/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#include "TestModel.hpp"

const unsigned int TestModel::maximumLongTimePeriods = 80;
const unsigned int TestModel::maximumShortTimePeriods = 50;
const unsigned int TestModel::maximumCandleTime = 60000;
const unsigned int TestModel::maximumWTimePeriods = 7;

const bool TestModel::loggingEnabled = true;

std::string TestModel::runDate = "";
//std::string TestModel::stockSymbol = "JNUG";

std::vector<std::string> TestModel::testStockSymbols;
std::vector<Stock> TestModel::testStocks;

std::vector<std::string> TestModel::dates;

//Stock TestModel::testingStock;

void TestModel::initialize() {
  createListOfDates();
  
  testStockSymbols.push_back("JNUG");
  testStockSymbols.push_back("DUST");
  for (unsigned int i = 0; i < testStockSymbols.size(); i++) {
    testStocks.push_back(Stock(testStockSymbols[i]));
  }
}

void TestModel::createListOfDates() {
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
  dates.push_back("10_27_2016");
  dates.push_back("10_28_2016");
  dates.push_back("10_31_2016");
  dates.push_back("11_01_2016");
  dates.push_back("11_02_2016");
  dates.push_back("11_03_2016");
  dates.push_back("11_04_2016");
  dates.push_back("11_07_2016");
  dates.push_back("11_09_2016");
  dates.push_back("11_10_2016");
  dates.push_back("11_11_2016");
  dates.push_back("11_21_2016");
  dates.push_back("11_28_2016");
  dates.push_back("11_29_2016");
  dates.push_back("11_30_2016");
  dates.push_back("12_01_2016");
  dates.push_back("12_02_2016");
  dates.push_back("12_05_2016");
  dates.push_back("12_06_2016");
  dates.push_back("12_07_2016");
  dates.push_back("12_08_2016");
  dates.push_back("12_09_2016");
  dates.push_back("12_12_2016");
  dates.push_back("12_13_2016");
  dates.push_back("12_14_2016");
  dates.push_back("12_15_2016");
  dates.push_back("12_16_2016");
  dates.push_back("12_19_2016");
  dates.push_back("12_20_2016");
  dates.push_back("12_21_2016");
  dates.push_back("12_22_2016");
  dates.push_back("12_23_2016");
  dates.push_back("12_27_2016");
}

// 2391

unsigned int TestModel::getTestStockSymbolCount() {
  return (unsigned int)testStockSymbols.size();
}

const std::string& TestModel::getTestStockSymbol(const unsigned int& _index) {
  return testStockSymbols[_index];
}

unsigned int TestModel::getTestStockCount() {
  return (unsigned int)testStocks.size();
}

Stock& TestModel::getTestStock(const unsigned int& _index) {
  return testStocks[_index];
}

std::string TestModel::createQuotesDirectory(const std::string& _symbol) {
  return "/Users/Matt/Desktop/symbol_data/" + runDate + "/" + _symbol + ".csv";
}

unsigned int TestModel::totalTimeQuotes(const unsigned int& _index) {
  return (unsigned int)testStocks[_index].testQuotes.size();
}

void TestModel::setDate(const std::string& _date) {
  runDate = _date;
}

void TestModel::resetStockData() {
  for (unsigned int i = 0; i < testStocks.size(); i++) {
    testStocks[i].reset();
  }
}

void TestModel::hardResetStock() {
  testStocks.clear();
  for (unsigned int i = 0; i < testStockSymbols.size(); i++) {
    testStocks.push_back(Stock(testStockSymbols[i]));
  }
}

void TestModel::logMoneyMade() {
  for (unsigned int i = 0; i < testStocks.size(); i++) {
    testStocks[i].logMoneyMade();
  }
}

unsigned int TestModel::getNumberOfDates() {
  return (unsigned int)dates.size();
}

const std::string& TestModel::getDateAtIndex(const unsigned int& _index) {
  return dates[_index];
}
