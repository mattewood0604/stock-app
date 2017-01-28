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
  
  //testStockSymbols.push_back("THLD");
  //testStockSymbols.push_back("JNUG"); // 66%
  //testStockSymbols.push_back("NUGT"); // 51%
  
  //testStockSymbols.push_back("DUST"); // 53%
  //testStockSymbols.push_back("JDST"); // 70%
  
  //testStockSymbols.push_back("LABD"); // 22	20	39
  //testStockSymbols.push_back("LABU"); // 78	24	42
  
  /*testStockSymbols.push_back("CNDT");
testStockSymbols.push_back("ARNC");
testStockSymbols.push_back("AA");
testStockSymbols.push_back("YUMC");
testStockSymbols.push_back("JCI");
testStockSymbols.push_back("TWLO");
testStockSymbols.push_back("HTZ");
testStockSymbols.push_back("UA");
testStockSymbols.push_back("HPE");
testStockSymbols.push_back("PYPL");
testStockSymbols.push_back("FIT");
testStockSymbols.push_back("LC");
testStockSymbols.push_back("FCAU");
testStockSymbols.push_back("VER");
testStockSymbols.push_back("NLY");
testStockSymbols.push_back("HST");
testStockSymbols.push_back("SRC");
testStockSymbols.push_back("CFG");
testStockSymbols.push_back("BABA");
testStockSymbols.push_back("SYF");
testStockSymbols.push_back("VALE");
testStockSymbols.push_back("JD");
testStockSymbols.push_back("PBR");
testStockSymbols.push_back("QRE");
testStockSymbols.push_back("SAN");
testStockSymbols.push_back("HMIN");
testStockSymbols.push_back("NOK");
testStockSymbols.push_back("LRE");
testStockSymbols.push_back("VIPS");
testStockSymbols.push_back("CX");
testStockSymbols.push_back("HMY");
testStockSymbols.push_back("ITUB");
testStockSymbols.push_back("BP");
testStockSymbols.push_back("TEVA");
testStockSymbols.push_back("RRMS");
testStockSymbols.push_back("IBN");
testStockSymbols.push_back("PWRD");
testStockSymbols.push_back("TSM");
testStockSymbols.push_back("QEPM");
testStockSymbols.push_back("NGLS");
testStockSymbols.push_back("LYG");
testStockSymbols.push_back("EPB");
testStockSymbols.push_back("EPD");
testStockSymbols.push_back("GGB");
testStockSymbols.push_back("ETE");
testStockSymbols.push_back("ERIC");
testStockSymbols.push_back("GFI");
testStockSymbols.push_back("BBD");
testStockSymbols.push_back("AZN");
testStockSymbols.push_back("ABEV");
testStockSymbols.push_back("BCS");
testStockSymbols.push_back("GPRO");
testStockSymbols.push_back("VPCO");
testStockSymbols.push_back("T");
testStockSymbols.push_back("MTG");
testStockSymbols.push_back("CDE");
testStockSymbols.push_back("FREEF");
testStockSymbols.push_back("DVN");
testStockSymbols.push_back("EFA");
testStockSymbols.push_back("GPS");
testStockSymbols.push_back("VXX");
testStockSymbols.push_back("TECK");
testStockSymbols.push_back("JPM");
testStockSymbols.push_back("KR");
testStockSymbols.push_back("KO");
testStockSymbols.push_back("NVDA");
testStockSymbols.push_back("P");
testStockSymbols.push_back("XOOM");
testStockSymbols.push_back("UAL");
testStockSymbols.push_back("NKE");
testStockSymbols.push_back("WMB");
testStockSymbols.push_back("KRE");
testStockSymbols.push_back("NUGT");
testStockSymbols.push_back("PHM");
testStockSymbols.push_back("IAU");
testStockSymbols.push_back("IAG");
testStockSymbols.push_back("UCO");
testStockSymbols.push_back("TLT");
testStockSymbols.push_back("GRPN");
testStockSymbols.push_back("BSJE");
testStockSymbols.push_back("BSJF");
testStockSymbols.push_back("BSJG");
testStockSymbols.push_back("DXJ");
testStockSymbols.push_back("PFE");
testStockSymbols.push_back("CNX");
testStockSymbols.push_back("XLV");
testStockSymbols.push_back("ODP");
testStockSymbols.push_back("C");
testStockSymbols.push_back("ARIA");
testStockSymbols.push_back("NRG");
testStockSymbols.push_back("ESV");
testStockSymbols.push_back("HL");
testStockSymbols.push_back("RGRC");
testStockSymbols.push_back("RGRE");
testStockSymbols.push_back("SQQQ");
testStockSymbols.push_back("YHOO");
testStockSymbols.push_back("HD");
testStockSymbols.push_back("HPQ");
testStockSymbols.push_back("AMAT");
testStockSymbols.push_back("AAPL");
testStockSymbols.push_back("CHK");
testStockSymbols.push_back("FXI");
testStockSymbols.push_back("FORX");
testStockSymbols.push_back("VLO");
testStockSymbols.push_back("GM");
testStockSymbols.push_back("AGLS");
testStockSymbols.push_back("GE");
testStockSymbols.push_back("GG");
testStockSymbols.push_back("XBI");
testStockSymbols.push_back("VRX");
testStockSymbols.push_back("GMCR");
testStockSymbols.push_back("MDLZ");
testStockSymbols.push_back("EWZ");
testStockSymbols.push_back("EWG");
testStockSymbols.push_back("EWJ");*/
testStockSymbols.push_back("JCP");
testStockSymbols.push_back("S");
testStockSymbols.push_back("GLD");
testStockSymbols.push_back("MCGC");
testStockSymbols.push_back("TZA");
testStockSymbols.push_back("CSX");
testStockSymbols.push_back("ABX");
testStockSymbols.push_back("ABT");
testStockSymbols.push_back("DGAZ");
testStockSymbols.push_back("MSFT");
testStockSymbols.push_back("FB");
testStockSymbols.push_back("FTR");
testStockSymbols.push_back("TXN");
testStockSymbols.push_back("EBAY");
testStockSymbols.push_back("NCFT");
testStockSymbols.push_back("MYL");
testStockSymbols.push_back("BRCD");
testStockSymbols.push_back("QLTB");
testStockSymbols.push_back("BRCM");
testStockSymbols.push_back("EXEL");
testStockSymbols.push_back("IWM");
testStockSymbols.push_back("WPX");
testStockSymbols.push_back("CODE");
testStockSymbols.push_back("XLP");
testStockSymbols.push_back("XLS");
testStockSymbols.push_back("XLU");
testStockSymbols.push_back("XLY");
testStockSymbols.push_back("XLB");
testStockSymbols.push_back("XLE");
testStockSymbols.push_back("XLF");
testStockSymbols.push_back("XLI");
testStockSymbols.push_back("XLK");
testStockSymbols.push_back("FOXA");
testStockSymbols.push_back("USO");
testStockSymbols.push_back("USB");
testStockSymbols.push_back("FEYE");
testStockSymbols.push_back("HAL");
testStockSymbols.push_back("RIG");
testStockSymbols.push_back("INTC");
testStockSymbols.push_back("ATVI");
testStockSymbols.push_back("DB");
testStockSymbols.push_back("UVXY");
testStockSymbols.push_back("AMD");
testStockSymbols.push_back("DNR");
testStockSymbols.push_back("NBR");
testStockSymbols.push_back("JBLU");
testStockSymbols.push_back("NVAX");
testStockSymbols.push_back("TGT");
testStockSymbols.push_back("WMT");
testStockSymbols.push_back("VZ");
testStockSymbols.push_back("TWTR");
testStockSymbols.push_back("ZNGA");
testStockSymbols.push_back("CY");
testStockSymbols.push_back("CF");
testStockSymbols.push_back("SWN");
testStockSymbols.push_back("OAS");
testStockSymbols.push_back("POT");
testStockSymbols.push_back("CYT");
testStockSymbols.push_back("BBY");
testStockSymbols.push_back("ECA");
testStockSymbols.push_back("ASTI");
testStockSymbols.push_back("V");
testStockSymbols.push_back("MNKD");
testStockSymbols.push_back("ENDP");
testStockSymbols.push_back("ABBV");
testStockSymbols.push_back("ORCL");
testStockSymbols.push_back("NEWLF");
testStockSymbols.push_back("MSZ");
testStockSymbols.push_back("UAA");
testStockSymbols.push_back("EEM");
testStockSymbols.push_back("BK");
testStockSymbols.push_back("IYR");
testStockSymbols.push_back("CMCSA");
testStockSymbols.push_back("CMCSK");
testStockSymbols.push_back("QCOM");
testStockSymbols.push_back("SIRO");
testStockSymbols.push_back("QCOR");
testStockSymbols.push_back("SIRI");
testStockSymbols.push_back("SPLS");
testStockSymbols.push_back("IEMG");
testStockSymbols.push_back("SYMC");
testStockSymbols.push_back("RAI");
testStockSymbols.push_back("SFXEQ");
testStockSymbols.push_back("BXUB");
testStockSymbols.push_back("RAD");
testStockSymbols.push_back("EGO");
testStockSymbols.push_back("DUST");
testStockSymbols.push_back("WLL");
testStockSymbols.push_back("AUY");
testStockSymbols.push_back("AG");
testStockSymbols.push_back("GDXJ");
testStockSymbols.push_back("MS");
testStockSymbols.push_back("FITB");
testStockSymbols.push_back("NFLX");
testStockSymbols.push_back("BEAM");
testStockSymbols.push_back("CSCO");
testStockSymbols.push_back("CAT");
testStockSymbols.push_back("SE");
testStockSymbols.push_back("SO");
testStockSymbols.push_back("FCX");
testStockSymbols.push_back("FCS");
testStockSymbols.push_back("VWO");
testStockSymbols.push_back("MSTX");
testStockSymbols.push_back("SDS");
testStockSymbols.push_back("AIG");
testStockSymbols.push_back("WDC");
testStockSymbols.push_back("GNW");
testStockSymbols.push_back("COG");
testStockSymbols.push_back("COB");
testStockSymbols.push_back("COP");
testStockSymbols.push_back("CTSH");
testStockSymbols.push_back("ITLY");
testStockSymbols.push_back("TVIX");
testStockSymbols.push_back("WFT");
testStockSymbols.push_back("WFC");
testStockSymbols.push_back("WFM");
testStockSymbols.push_back("SVXY");
testStockSymbols.push_back("IDIX");
testStockSymbols.push_back("EMDR");
testStockSymbols.push_back("HBNK");
testStockSymbols.push_back("EMDI");
testStockSymbols.push_back("RF");
testStockSymbols.push_back("SUNEQ");
testStockSymbols.push_back("F");
testStockSymbols.push_back("BSX");
testStockSymbols.push_back("SCHW");
testStockSymbols.push_back("GLW");
testStockSymbols.push_back("AKS");
testStockSymbols.push_back("QQQ");
testStockSymbols.push_back("TWX");
testStockSymbols.push_back("TWQ");
testStockSymbols.push_back("SLB");
testStockSymbols.push_back("SLV");
testStockSymbols.push_back("CVS");
testStockSymbols.push_back("CVX");
testStockSymbols.push_back("BAGL");
testStockSymbols.push_back("EWCS");
testStockSymbols.push_back("KMI");
testStockSymbols.push_back("MOS");
testStockSymbols.push_back("HITT");
testStockSymbols.push_back("GSAT");
testStockSymbols.push_back("AEO");
testStockSymbols.push_back("AES");
testStockSymbols.push_back("OIH");
testStockSymbols.push_back("JNUG");
testStockSymbols.push_back("CTL");
testStockSymbols.push_back("DAL");
testStockSymbols.push_back("CIE");
testStockSymbols.push_back("SBUX");
testStockSymbols.push_back("ON");
testStockSymbols.push_back("PG");
testStockSymbols.push_back("CRM");
testStockSymbols.push_back("EXC");
testStockSymbols.push_back("MCD");
testStockSymbols.push_back("SLW");
testStockSymbols.push_back("CYBX");
testStockSymbols.push_back("AAL");
testStockSymbols.push_back("UNG");
testStockSymbols.push_back("XOM");
testStockSymbols.push_back("XOP");
testStockSymbols.push_back("AMLP");
testStockSymbols.push_back("KGC");
testStockSymbols.push_back("EZU");
testStockSymbols.push_back("MET");
testStockSymbols.push_back("GDX");
testStockSymbols.push_back("MEA");
testStockSymbols.push_back("GILD");
testStockSymbols.push_back("HYG");
testStockSymbols.push_back("XME");
testStockSymbols.push_back("AXP");
testStockSymbols.push_back("M");
testStockSymbols.push_back("KEY");
testStockSymbols.push_back("LUV");
testStockSymbols.push_back("MGM");
testStockSymbols.push_back("MGN");
testStockSymbols.push_back("BMY");
testStockSymbols.push_back("NGD");
testStockSymbols.push_back("RSX");
testStockSymbols.push_back("VEA");
testStockSymbols.push_back("SPXS");
testStockSymbols.push_back("SPXU");
testStockSymbols.push_back("NE");
testStockSymbols.push_back("DIS");
testStockSymbols.push_back("SDRL");
testStockSymbols.push_back("BRXX");
testStockSymbols.push_back("XIV");
testStockSymbols.push_back("HBAN");
testStockSymbols.push_back("NEM");
testStockSymbols.push_back("STX");
testStockSymbols.push_back("BAC");
testStockSymbols.push_back("BAX");
testStockSymbols.push_back("DOW");
testStockSymbols.push_back("MU");
testStockSymbols.push_back("BLOX");
testStockSymbols.push_back("MO");
testStockSymbols.push_back("MM");
testStockSymbols.push_back("RWG");
testStockSymbols.push_back("AVP");
testStockSymbols.push_back("MPOYQ");
testStockSymbols.push_back("MPC");
testStockSymbols.push_back("LOW");
testStockSymbols.push_back("XRX");
testStockSymbols.push_back("X");
testStockSymbols.push_back("MDT");
testStockSymbols.push_back("NOV");
testStockSymbols.push_back("JNK");
testStockSymbols.push_back("SPY");
testStockSymbols.push_back("CNP");
testStockSymbols.push_back("CNQ");
testStockSymbols.push_back("TSLA");
testStockSymbols.push_back("JDST");
testStockSymbols.push_back("LABU");
testStockSymbols.push_back("LABD");
testStockSymbols.push_back("CLF");
testStockSymbols.push_back("ONCE");
testStockSymbols.push_back("GUSH");
  
  for (unsigned int i = 0; i < testStockSymbols.size(); i++) {
    testStocks.push_back(Stock(testStockSymbols[i]));
  }
}

void TestModel::createListOfDates() {
  /*
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
  */
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
  return FileManager::mainDirectory + runDate + "/" + _symbol + ".csv";
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
