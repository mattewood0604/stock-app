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
std::string TestModel::stockSymbol = "JNUG";
std::vector<std::string> TestModel::dates;

Stock TestModel::testingStock = Stock(stockSymbol);

void TestModel::initialize() {
  //dates.push_back("10_5_2016");
  /*dates.push_back("10_6_2016");
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
  dates.push_back("11_21_2016");*/
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
}

Stock& TestModel::getTestingStock() {
  return testingStock;
}

void TestModel::setTestingStock(const std::string& _stock) {
  stockSymbol = _stock;
  testingStock = Stock(_stock);
}

std::string TestModel::quotesDirectory() {
  return "/Users/Matt/Desktop/symbol_data/" + runDate + "/" + stockSymbol + ".csv";
}

unsigned int TestModel::totalTimeQuotes() {
  return (unsigned int)testingStock.testQuotes.size();
}

const TimeQuote& TestModel::getTestQuote(unsigned int _index) {
  return testingStock.testQuotes[_index];
}

void TestModel::setDate(const std::string& _date) {
  runDate = _date;
}

void TestModel::resetTestData() {
  //stocks.clear();
}

void TestModel::resetStockData() {
  testingStock.reset();
}

void TestModel::hardResetStock() {
  testingStock = Stock(stockSymbol);
}

void TestModel::logMoneyMade() {
  testingStock.logMoneyMade();
}

unsigned int TestModel::getNumberOfDates() {
  return (unsigned int)dates.size();
}

const std::string& TestModel::getDateAtIndex(const unsigned int& _index) {
  return dates[_index];
}
