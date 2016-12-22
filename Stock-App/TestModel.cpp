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
  
  /*testStockSymbols.push_back("RARE");
  testStockSymbols.push_back("PRTA");
  testStockSymbols.push_back("BLUE");
  testStockSymbols.push_back("ONCE");
  testStockSymbols.push_back("AVXS");
  testStockSymbols.push_back("EGRX");
  testStockSymbols.push_back("AGIO");
  testStockSymbols.push_back("SGEN");
  testStockSymbols.push_back("HSKA");
  testStockSymbols.push_back("ANIP");
  testStockSymbols.push_back("TREE");
  testStockSymbols.push_back("RGLD");
  testStockSymbols.push_back("WRLD");
  testStockSymbols.push_back("INCY");
  testStockSymbols.push_back("DXCM");
  testStockSymbols.push_back("STRA");
  testStockSymbols.push_back("FPRX");
  testStockSymbols.push_back("USCR");
  testStockSymbols.push_back("JBSS");
  testStockSymbols.push_back("OLED");
  testStockSymbols.push_back("VRTX");
  testStockSymbols.push_back("ROLL");
  testStockSymbols.push_back("BMRN");
  testStockSymbols.push_back("SYNA");
  testStockSymbols.push_back("AMBA");
  testStockSymbols.push_back("SINA");
  testStockSymbols.push_back("AMSG");
  testStockSymbols.push_back("PATK");
  testStockSymbols.push_back("INGN");
  testStockSymbols.push_back("NVDA");
  testStockSymbols.push_back("ALKS");
  testStockSymbols.push_back("CAVM");
  testStockSymbols.push_back("NXST");
  testStockSymbols.push_back("PRGO");
  testStockSymbols.push_back("PLCE");
  testStockSymbols.push_back("CMPR");
  testStockSymbols.push_back("LPNT");
  testStockSymbols.push_back("DECK");
  testStockSymbols.push_back("PDCE");
  testStockSymbols.push_back("LOPE");
  testStockSymbols.push_back("TCBI");
  testStockSymbols.push_back("MGLN");
  testStockSymbols.push_back("CYBR");
  testStockSymbols.push_back("ZBRA");
  testStockSymbols.push_back("FANG");
  testStockSymbols.push_back("CPLA");
  testStockSymbols.push_back("IBTX");
  testStockSymbols.push_back("LOGM");
  testStockSymbols.push_back("AMCX");
  testStockSymbols.push_back("BLKB");
  testStockSymbols.push_back("UEIC");
  testStockSymbols.push_back("SFNC");
  testStockSymbols.push_back("CRUS");
  testStockSymbols.push_back("WYNN");
  testStockSymbols.push_back("HURN");
  testStockSymbols.push_back("IOSP");
  testStockSymbols.push_back("GOLD");
  testStockSymbols.push_back("ASTE");
  testStockSymbols.push_back("PNFP");
  testStockSymbols.push_back("PFPT");
  testStockSymbols.push_back("SAFM");
  testStockSymbols.push_back("BCPC");
  testStockSymbols.push_back("FTRPR");
  testStockSymbols.push_back("EBIX");
  testStockSymbols.push_back("IDCC");
  testStockSymbols.push_back("PRAH");
  testStockSymbols.push_back("CVGW");
  testStockSymbols.push_back("MDSO");
  testStockSymbols.push_back("LULU");
  testStockSymbols.push_back("TRIP");
  testStockSymbols.push_back("CGNX");
  testStockSymbols.push_back("QRVO");
  testStockSymbols.push_back("AMWD");
  testStockSymbols.push_back("LBRDK");
  testStockSymbols.push_back("OSIS");
  testStockSymbols.push_back("ALGN");
  testStockSymbols.push_back("SPLK");
  testStockSymbols.push_back("IRBT");
  testStockSymbols.push_back("TECD");
  testStockSymbols.push_back("MGEE");
  testStockSymbols.push_back("MNRO");
  testStockSymbols.push_back("CCMP");
  testStockSymbols.push_back("SWKS");
  testStockSymbols.push_back("PSMT");
  testStockSymbols.push_back("IBKC");
  testStockSymbols.push_back("XRAY");
  testStockSymbols.push_back("IART");
  testStockSymbols.push_back("NEOG");
  testStockSymbols.push_back("PRXL");
  testStockSymbols.push_back("RRGB");
  testStockSymbols.push_back("SFBS");
  testStockSymbols.push_back("NUVA");
  testStockSymbols.push_back("BOKF");
  testStockSymbols.push_back("ADSK");
  testStockSymbols.push_back("KALU");
  testStockSymbols.push_back("SAVE");
  testStockSymbols.push_back("WOOF");
  testStockSymbols.push_back("EGBN");
  testStockSymbols.push_back("VSAT");
  testStockSymbols.push_back("MATW");
  testStockSymbols.push_back("DUST");
  testStockSymbols.push_back("JNUG");
  testStockSymbols.push_back("NUGT");
  testStockSymbols.push_back("CLF");
  testStockSymbols.push_back("GUSH");
  testStockSymbols.push_back("FAS");
  testStockSymbols.push_back("TNA");
  testStockSymbols.push_back("ERX");
  testStockSymbols.push_back("TZA");
  testStockSymbols.push_back("SPXL");
  testStockSymbols.push_back("TMV");
  testStockSymbols.push_back("SPXS");*/
  
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
  //dates.push_back("12_19_2016");
  dates.push_back("12_20_2016");
  dates.push_back("12_21_2016");
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
  return "/Users/Matt/Desktop/symbol_data/" + runDate + "/" + _symbol + ".csv";
}

unsigned int TestModel::totalTimeQuotes() {
  return (unsigned int)testStocks[0].testQuotes.size();
}

const TimeQuote& TestModel::getTestQuote(const unsigned int& _index, const unsigned int& _marketTime) {
  return testStocks[_index].testQuotes[_marketTime];
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
