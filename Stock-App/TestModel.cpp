//
//  TestModel.cpp
//  Stock-App
//
//  Created by Matt Wood on 10/20/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#include "FileManager.hpp"
#include "TestModel.hpp"

const unsigned int TestModel::maximumLongTimePeriods = 80;
const unsigned int TestModel::maximumShortTimePeriods = 50;
const unsigned int TestModel::maximumCandleTime = 120000; //120000;
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
  
  // All At Once
  // 85%
  // 
  
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
  
  //testStockSymbols.push_back("THLD");
  //testStockSymbols.push_back("JNUG"); // 66%
  //testStockSymbols.push_back("NUGT"); // 51%
  
  //testStockSymbols.push_back("DUST"); // 53%
  //testStockSymbols.push_back("JDST"); // 70%
  
  //testStockSymbols.push_back("LABD"); // 22	20	39
  //testStockSymbols.push_back("LABU"); // 78	24	42
  
  //.testStockSymbols.push_back("CLF");
  //testStockSymbols.push_back("SPY");
  //testStockSymbols.push_back("NVDA");
  //testStockSymbols.push_back("GRPN");
  //testStockSymbols.push_back("JCP");
  //testStockSymbols.push_back("JNUG");
  testStockSymbols.push_back("JDST");
  //testStockSymbols.push_back("LABU");
  //testStockSymbols.push_back("NUGT");
  //testStockSymbols.push_back("TWLO");
  //testStockSymbols.push_back("DUST");
  //testStockSymbols.push_back("VALE");
  //testStockSymbols.push_back("P");
  
  //testStockSymbols.push_back("SVXY");
  
  /*
  testStockSymbols.push_back("AA");
  testStockSymbols.push_back("AG");
  testStockSymbols.push_back("AKS");
  testStockSymbols.push_back("ASTI");
  testStockSymbols.push_back("AUY");
  testStockSymbols.push_back("CDE");
  testStockSymbols.push_back("CIE");
  testStockSymbols.push_back("CLF");
  testStockSymbols.push_back("CNDT");
  testStockSymbols.push_back("CSX");
  testStockSymbols.push_back("CX");
  testStockSymbols.push_back("DGAZ");
  testStockSymbols.push_back("DUST");
  testStockSymbols.push_back("EGO");
  testStockSymbols.push_back("ENDP");
  testStockSymbols.push_back("ETE");
  testStockSymbols.push_back("EWZ");
  testStockSymbols.push_back("FCAU");
  testStockSymbols.push_back("FTR");
  testStockSymbols.push_back("GDX");
  testStockSymbols.push_back("GDXJ");
  testStockSymbols.push_back("GG");
  testStockSymbols.push_back("GGB");
  testStockSymbols.push_back("GRPN");
  testStockSymbols.push_back("GSAT");
  testStockSymbols.push_back("HL");
  testStockSymbols.push_back("IAG");
  testStockSymbols.push_back("JCP");
  testStockSymbols.push_back("JDST");
  testStockSymbols.push_back("JNUG");
  testStockSymbols.push_back("KGC");
  testStockSymbols.push_back("LABD");
  testStockSymbols.push_back("LABU");
  testStockSymbols.push_back("LC");
  testStockSymbols.push_back("MNKD");
  testStockSymbols.push_back("MSTX");
  testStockSymbols.push_back("NGD");
  testStockSymbols.push_back("NUGT");
  testStockSymbols.push_back("NVAX");
  testStockSymbols.push_back("NVDA");
  testStockSymbols.push_back("P");
  testStockSymbols.push_back("RAD");
  testStockSymbols.push_back("SUNEQ");
  testStockSymbols.push_back("SVXY");
  testStockSymbols.push_back("TVIX");
  testStockSymbols.push_back("TWLO");
  testStockSymbols.push_back("TZA");
  testStockSymbols.push_back("UNG");
  testStockSymbols.push_back("UVXY");
  testStockSymbols.push_back("VALE");
  testStockSymbols.push_back("WFT");
  testStockSymbols.push_back("WPX");
  testStockSymbols.push_back("ZNGA");
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
  dates.push_back("01_10_2017");
  dates.push_back("01_11_2017");
  dates.push_back("01_13_2017");
  dates.push_back("01_17_2017");
  dates.push_back("01_18_2017");
  dates.push_back("01_19_2017");
  dates.push_back("01_20_2017");
  dates.push_back("01_23_2017");
  dates.push_back("01_24_2017");
  dates.push_back("01_25_2017");
  dates.push_back("01_26_2017");
  dates.push_back("01_27_2017");
  dates.push_back("01_30_2017");
  dates.push_back("01_31_2017");
  dates.push_back("02_01_2017");
  dates.push_back("02_02_2017");
  dates.push_back("02_03_2017");
  dates.push_back("02_07_2017");
  dates.push_back("02_08_2017");
  dates.push_back("02_09_2017");
  dates.push_back("02_10_2017");
  dates.push_back("02_13_2017");
  dates.push_back("02_14_2017");
  dates.push_back("02_15_2017");
  dates.push_back("02_16_2017");
  dates.push_back("02_17_2017");
  dates.push_back("02_21_2017");
  dates.push_back("02_22_2017");
  dates.push_back("02_23_2017");
  dates.push_back("02_24_2017");
  dates.push_back("02_27_2017");
  dates.push_back("02_28_2017");
  dates.push_back("03_01_2017");
  dates.push_back("03_02_2017");
}

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
  return FileManager::mainDirectory + "/" + runDate + "/" + _symbol + ".csv";
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
