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
  
  // Removed 13 Missing Days
  // JNUG && DUST: 115%
  // JNUG && JDST: 118%
  
  // NUGT && DUST: 68%
  // NUGT && JDST: 84%
  
  // All Days
  // JNUG && DUST: 127%
  // JNUG && JDST: 123% (With 13 missing days)
  
  // NUGT && DUST: 67%
  // NUGT && JDST: 94%
  
  testStockSymbols.push_back("THLD");
  //testStockSymbols.push_back("JNUG"); // 66%
  //testStockSymbols.push_back("NUGT"); // 51%
  
  //testStockSymbols.push_back("DUST"); // 53%
  //testStockSymbols.push_back("JDST"); // 70%
  
  //testStockSymbols.push_back("LABD"); // 22	20	39
  //testStockSymbols.push_back("LABU"); // 78	24	42
  
  /*
  testStockSymbols.push_back("AMLP");
  testStockSymbols.push_back("DGAZ");
  testStockSymbols.push_back("DUST");
  testStockSymbols.push_back("DWTI");
  testStockSymbols.push_back("DXJ");
  testStockSymbols.push_back("EEM");
  testStockSymbols.push_back("EFA");
  testStockSymbols.push_back("EWJ");
  testStockSymbols.push_back("EWW");
  testStockSymbols.push_back("EWZ");
  testStockSymbols.push_back("FXI");
  testStockSymbols.push_back("GDX");
  testStockSymbols.push_back("GDXJ");
  testStockSymbols.push_back("GLD");
  testStockSymbols.push_back("HYG");
  testStockSymbols.push_back("IAU");
  testStockSymbols.push_back("IEMG");
  testStockSymbols.push_back("IWM");
  testStockSymbols.push_back("IYR");
  testStockSymbols.push_back("JDST");
  testStockSymbols.push_back("JNK");
  testStockSymbols.push_back("JNUG");
  testStockSymbols.push_back("KRE");
  testStockSymbols.push_back("LABU");
  testStockSymbols.push_back("LQD");
  testStockSymbols.push_back("NUGT");
  testStockSymbols.push_back("OIH");
  testStockSymbols.push_back("QQQ");
  testStockSymbols.push_back("RSX");
  testStockSymbols.push_back("SDS");
  testStockSymbols.push_back("SLV");
  testStockSymbols.push_back("SPXU");
  testStockSymbols.push_back("SPY");
  testStockSymbols.push_back("SQQQ");
  testStockSymbols.push_back("TLT");
  testStockSymbols.push_back("TVIX");
  testStockSymbols.push_back("TZA");
  testStockSymbols.push_back("UCO");
  testStockSymbols.push_back("UNG");
  testStockSymbols.push_back("USO");
  testStockSymbols.push_back("UVXY");
  testStockSymbols.push_back("UWTI");
  testStockSymbols.push_back("VEA");
  testStockSymbols.push_back("VNQ");
  testStockSymbols.push_back("VWO");
  testStockSymbols.push_back("VXX");
  testStockSymbols.push_back("XBI");
  testStockSymbols.push_back("XIV");
  testStockSymbols.push_back("XLB");
  testStockSymbols.push_back("XLE");
  testStockSymbols.push_back("XLF");
  testStockSymbols.push_back("XLI");
  testStockSymbols.push_back("XLK");
  testStockSymbols.push_back("XLP");
  testStockSymbols.push_back("XLU");
  testStockSymbols.push_back("XLV");
  testStockSymbols.push_back("XLY");
  testStockSymbols.push_back("XOP");
   */
  
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
  dates.push_back("12_30_2016");
  dates.push_back("1_3_2017");
  dates.push_back("1_4_2017");
  dates.push_back("1_5_2017");
  dates.push_back("01_09_2017");
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
