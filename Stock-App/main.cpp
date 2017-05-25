//
//  main.cpp
//  Stock-App
//
//  Created by Matt Wood on 10/13/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#include <unistd.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include <cstdlib>
#include <iomanip>

#include "BuySell.hpp"
#include "FileManager.hpp"
#include "Model.hpp"
#include "RestCall.hpp"
#include "StockModel.hpp"
#include "StockRunner.hpp"
#include "TestModel.hpp"

unsigned int* gNumberOfTrades;

float**** createProfitStorage() {
  const unsigned int wTimePeriods = TestModel::maximumWTimePeriods + 1;
  const unsigned int longTimePeriods = TestModel::maximumLongTimePeriods + 1;
  const unsigned int shortTimePeriods = TestModel::maximumShortTimePeriods + 1;
  const unsigned int candleTimes = TestModel::maximumCandleTime / 1000;
  
  float**** profitStorage = new float***[wTimePeriods];
  for (unsigned int w = 0; w < wTimePeriods; w++) {
    profitStorage[w] = new float**[longTimePeriods];
    for (unsigned int l = 0; l < longTimePeriods; l++) {
      profitStorage[w][l] = new float*[shortTimePeriods];
      for (unsigned int s = 0; s < shortTimePeriods; s++) {
        profitStorage[w][l][s] = new float[candleTimes];
        for (unsigned int c = 0; c < candleTimes; c++) {
          profitStorage[w][l][s][c] = 0.0f;
        }
      }
    }
  }
  
  gNumberOfTrades = new unsigned int[longTimePeriods * shortTimePeriods * candleTimes];
  for (unsigned int i = 0; i < longTimePeriods * shortTimePeriods * candleTimes; i++) {
    gNumberOfTrades[longTimePeriods * shortTimePeriods * candleTimes] = 0;
  }
  
  return profitStorage;
}

void resetProfitStorage(float**** _profitStorage, unsigned int _w, unsigned int _l, unsigned int _s, unsigned int _c) {
  //for (unsigned int w = 0; w < _w; w++) {
    for (unsigned int l = 10; l < _l; l++) {
      for (unsigned int s = 10; s < _s; s++) {
        for (unsigned int c = 15; c < _c; c++) {
          _profitStorage[_w][l][s][c] = 0.0f;
        }
      }
    }
  //}
  
  delete [] gNumberOfTrades;
}

void calculateProfits(Stock& _stock, const StockModel& _stockModel, float**** _profits, unsigned int _index) {
  //if (_stockModel.getShortTimePeriods() <= _stockModel.getLongTimePeriods()) {
    for (unsigned int marketTime = 0; marketTime < TestModel::totalTimeQuotes(_index); marketTime++) {
      RestCall::mockRestCall(_stock, marketTime);
      BuySell::buyOrSell(_stock);
    }
  //}
  
  if (!isnan(_stock.getPercentageMade())) {
    gNumberOfTrades[_stockModel.getLongTimePeriods() * _stockModel.getShortTimePeriods() * (_stockModel.getMaxCandleTime() / 1000)] += _stock.numberOfTrades;
    _profits[_stockModel.getWTimePeriods()][_stockModel.getLongTimePeriods()][_stockModel.getShortTimePeriods()][_stockModel.getMaxCandleTime() / 1000] += (_stock.getPercentageMade() * 10000);
  }
}

StockModel& resetAllModelsForStock(const unsigned int& _stockIndex) {
  TestModel::hardResetStock();
  Stock& stock = TestModel::getTestStock(_stockIndex);
  StockModel& stockModel = stock.getStockModel();
  stockModel.reset();
  return stockModel;
}

void calculateAndWriteProfits(float**** _profits, const unsigned int& _index) {
  std::string profitData;
  profitData.append("WTIME\tLONG\tSHORT\tCANDLE\tPROFIT\n");
  profitData.append("---------------------------\n");
  
  unsigned int totalForTheDay = 0;
  unsigned int totalPositive = 0;
  Stock& stock = TestModel::getTestStock(_index);
  StockModel& stockModel = stock.getStockModel();
  //for (unsigned int wTime = 2; wTime < wTimePeriods; wTime++) {
  for (unsigned int longTime = 10; longTime < TestModel::maximumLongTimePeriods; longTime++) {
    for (unsigned int shortTime = 10; shortTime < TestModel::maximumShortTimePeriods; shortTime++) {
      for (unsigned int candleTime = 15; candleTime < TestModel::maximumCandleTime / 1000; candleTime++) {
        float profit = _profits[stockModel.getWTimePeriods()][longTime][shortTime][candleTime] / 100;
        unsigned int numberOfTrades = gNumberOfTrades[longTime * shortTime * candleTime];
        totalForTheDay++;
        if (profit > TestModel::getNumberOfDates() && profit < 1000) {
          totalPositive++;
        }
        std::cout << longTime << "\t" << shortTime << "\t" << candleTime << "\t" << profit << std::endl;
        //std::cout << wTime << "\t" << longTime << "\t" << shortTime << "\t" << candleTime << "\t" << profit << std::endl;
        profitData.append(std::to_string(longTime));
        profitData.append("\t");
        profitData.append(std::to_string(shortTime));
        profitData.append("\t");
        profitData.append(std::to_string(candleTime));
        profitData.append("\t");
        profitData.append(std::to_string(profit));
        profitData.append("\n");
      }
    }
  }
  //}
  
  // 7.5 & 3.5
  
  profitData.append("--------------------");
  profitData.append("POSITIVE: ");
  profitData.append(std::to_string(totalPositive));
  profitData.append("--------------------");
  profitData.append("\n");
  profitData.append("TOTAL: ");
  profitData.append(std::to_string(totalForTheDay));
  profitData.append("--------------------");
  profitData.append("\n");
  
  FileManager::writeProfitsForSymbol(TestModel::getTestStockSymbol(_index), profitData);
}

void runProfitMaximizationForIndividualStocks() {
  float**** newProfits = createProfitStorage();
  
  //FileManager::init();
  TestModel::initialize();
  
  for (unsigned int j = 0; j < TestModel::getTestStockCount(); j++) {
    Stock& stock = TestModel::getTestStock(j);
    std::cout << "STOCK: " << stock.symbol << std::endl;
    
    unsigned int totalTime = 0;
    for (unsigned int i = 0; i < TestModel::getNumberOfDates(); i++) {
      StockModel& stockModel = resetAllModelsForStock(j);
      
      std::cout << "DATE: " << TestModel::getDateAtIndex(i) << std::endl;
      std::cout << "--------------------" << std::endl;
      
      TestModel::setDate(TestModel::getDateAtIndex(i));
      if(!FileManager::readQuoteAtStockIndex(j)) {
        continue;
      }
      
      uint64_t startTime = (uint64_t)time(0);
      
      while (stockModel.getLongTimePeriods() <= TestModel::maximumLongTimePeriods) {
        
        while (stockModel.getShortTimePeriods() <= TestModel::maximumShortTimePeriods) {
          
          while (stockModel.getMaxCandleTime() <= TestModel::maximumCandleTime) {
            calculateProfits(stock, stockModel, newProfits, j);
            
            TestModel::resetStockData();
            Model::setStopBuying(false);
            Model::setPurchasedStockSymbol("");
            stockModel.incrementMaxCandleTime();
          }
          
          stockModel.resetMaxCandleTime();
          stockModel.incrementShortTimePeriods();
        }
        
        stockModel.resetShortTimePeriods();
        stockModel.incrementLongTimePeriods();
      }
      
      stockModel.resetLongTimePeriods();
      
      uint64_t endTime = (uint64_t)time(0);
      totalTime += (endTime - startTime);
      std::cout << "TIME TAKEN: " << endTime - startTime << std::endl;
    }
    
    std::cout << "TOTAL TIME: " << totalTime << "\n\n" << std::endl;
    
    calculateAndWriteProfits(newProfits, j);
    
    resetProfitStorage(newProfits, 4, TestModel::maximumLongTimePeriods, TestModel::maximumShortTimePeriods, TestModel::maximumCandleTime / 1000);
  }
  
  /*
  for (unsigned int w = 0; w < wTimePeriods; w++) {
    for (unsigned int l = 0; l < longTimePeriods; l++) {
      for (unsigned int s = 0; s < shortTimePeriods; s++) {
        delete newProfits[w][l][s];
      }
      delete newProfits[w][l];
    }
    delete newProfits[w];
  }
  delete[] newProfits;
   */
}

const float g_defaultProfit = -1000000;
unsigned int g_lowestNumberOfQuotes = 0;
unsigned int g_totalDays = 0;

const unsigned int g_minMinuteSpan = 5;
unsigned int g_minuteSpan = g_minMinuteSpan;
unsigned int g_maxMinuteSpan = 60;

unsigned int g_stockIndex = 0;

std::string g_profitData = "";

void resetTimeSpanProfits(float* _profits) {
  for (unsigned int i = 0; i < g_lowestNumberOfQuotes; i++) {
    _profits[i] = g_defaultProfit;
  }
}

unsigned int getLowestNumberOfQuotes() {
  unsigned int lowestNumberOfQuotes = 1000000;
  for (unsigned int i = 0; i < TestModel::getNumberOfDates(); i++) {
    Stock& stock = TestModel::getTestStock(g_stockIndex);
    stock.testQuotes.clear();
    
    std::cout << TestModel::getDateAtIndex(i) << std::endl;
    TestModel::setDate(TestModel::getDateAtIndex(i));
    if(!FileManager::readQuoteAtStockIndex(g_stockIndex)) {
      continue;
    }

    if (stock.testQuotes.size() < lowestNumberOfQuotes && stock.testQuotes.size() > 0) {
      lowestNumberOfQuotes = (unsigned int)stock.testQuotes.size();
    }
  }
  
  return lowestNumberOfQuotes;
}

float testProfits = 0;

void calculateTimeSpanProfitsForDate(float* _profits, const unsigned int& _dateIndex) {
  Stock& stock = TestModel::getTestStock(g_stockIndex);
  stock.testQuotes.clear();
  
  TestModel::setDate(TestModel::getDateAtIndex(_dateIndex));
  if(!FileManager::readQuoteAtStockIndex(g_stockIndex)) {
    return;
  }
  
  g_totalDays++;
  
  unsigned int timeSpan = g_minuteSpan * 60 / 2;
  
  for (unsigned int i = 0; g_lowestNumberOfQuotes; i++) {
    if (i + timeSpan >= g_lowestNumberOfQuotes) {
      break;
    }
    
    float buyPrice = stock.testQuotes[i].price;
    float sellPrice = stock.testQuotes[i + timeSpan].price;
    float profit = sellPrice - buyPrice;
    
    //if (i == 602) {
    //  std::cout << "Buy Time:  " << i << std::endl;
    //  std::cout << "Sell Time: " << i + timeSpan << std::endl;
    //  testProfits += profit;
    //  std::cout << "Profit = " << profit << std::endl;
    //}
    
    if (_profits[i] == g_defaultProfit) {
      _profits[i] = 0;
    }
    
    _profits[i] += profit;
  }
}

void logTimeSpanProfits(const float* _profits) {
  float maxProfit = -100000;
  for (unsigned int i = 0; i < g_lowestNumberOfQuotes; i++) {
    if (_profits[i] != g_defaultProfit) {
      if (_profits[i] > maxProfit) {
        maxProfit = _profits[i];
        std::cout << "MAX PROFIT: " << maxProfit << std::endl;
        std::cout << "QUOTE NUMBER: " << i << std::endl;
      }
      
      std::cout << _profits[i] << std::endl;
      g_profitData.append(std::to_string(_profits[i]));
      g_profitData.append("\n");
    }
  }
  
  g_profitData.append("\n");
  g_profitData.append("Total Days: ");
  g_profitData.append(std::to_string(g_totalDays));
  g_profitData.append("\n");
}

void maximizeTimeSpan() {
  TestModel::initialize();
  
  while (g_stockIndex < TestModel::getTestStockCount()) {
    std::cout << TestModel::getTestStockSymbol(g_stockIndex) << std::endl;
    
    g_minuteSpan = g_minMinuteSpan;
    g_profitData = "";
    g_totalDays = 0;
    g_lowestNumberOfQuotes = getLowestNumberOfQuotes();
    float profits[g_lowestNumberOfQuotes];
    
    while (g_minuteSpan <= g_maxMinuteSpan) {
      g_profitData.append("Minute Span: ");
      g_profitData.append(std::to_string(g_minuteSpan));
      g_profitData.append("\n");
      
      g_totalDays = 0;
      
      std::cout << "Minute Span: " << g_minuteSpan << std::endl;
      std::cout << "----------------" << std::endl << std::endl;
      
      resetTimeSpanProfits(profits);
      for (unsigned int dateIndex = 0; dateIndex < TestModel::getNumberOfDates(); dateIndex++) {
        calculateTimeSpanProfitsForDate(profits, dateIndex);
      }
      logTimeSpanProfits(profits);
      g_minuteSpan++;
      
      std::cout << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl;
    }
    
    FileManager::writeTimeSpanProfitsForSymbol(TestModel::getTestStockSymbol(g_stockIndex), g_profitData);
    
    std::cout << "Total Days: " << g_totalDays << std::endl;
    
    g_stockIndex++;
  }
}

void testWilliamsVix() {
  TestModel::initialize();
  
  const unsigned int totalSums = 101 * 101 * 4;
  float* sums = new float[totalSums];
  unsigned int* bottoms = new unsigned int[totalSums];
  for (unsigned int i = 0;  i < totalSums; i++) {
    sums[totalSums] = 0;
    bottoms[totalSums] = 0;
  }
  
  for (unsigned int j = 0; j < TestModel::getTestStockCount(); j++) {
    Stock& stock = TestModel::getTestStock(j);
    std::cout << "STOCK: " << stock.symbol << std::endl;
    
    unsigned int totalTime = 0;
    for (unsigned int i = 0; i < TestModel::getNumberOfDates(); i++) {
      StockModel& stockModel = resetAllModelsForStock(j);
      
      std::cout << "DATE: " << TestModel::getDateAtIndex(i) << std::endl;
      std::cout << "--------------------" << std::endl;
      
      TestModel::setDate(TestModel::getDateAtIndex(i));
      if(!FileManager::readQuoteAtStockIndex(j)) {
        continue;
      }
      
      unsigned int index = 0;
      stockModel.multiplier = 1;
      while(stockModel.multiplier < 4) {
        stockModel.standardDevHigh = 0;
        while(stockModel.standardDevHigh <= 100) {
          stockModel.bollingerBandLength = 0;
          while(stockModel.bollingerBandLength <= 100) {
            for (unsigned int marketTime = 0; marketTime < TestModel::totalTimeQuotes(j); marketTime++) {
              RestCall::mockRestCall(stock, marketTime);
              //BuySell::buyOrSell(stock);
            }
            
            sums[index] += TestModel::sumOfWilliamsVix;
            bottoms[index] += TestModel::williamsVixBottoms;
            index++;
            
            TestModel::resetStockData();
            Model::setStopBuying(false);
            Model::setPurchasedStockSymbol("");
            TestModel::sumOfWilliamsVix = 0;
            TestModel::williamsVixBottoms = 0;
            stockModel.bollingerBandLength += 5;
          }
          stockModel.standardDevHigh += 5;
        }
        stockModel.multiplier++;
      }
    }
    
    StockModel& stockModel = stock.getStockModel();
    unsigned int index = 0;
    stockModel.multiplier = 1;
    while(stockModel.multiplier < 4) {
      stockModel.standardDevHigh = 0;
      while(stockModel.standardDevHigh <= 100) {
        stockModel.bollingerBandLength = 0;
        while(stockModel.bollingerBandLength <= 100) {
          unsigned int width = 10;
          float sum = sums[index];
          unsigned int bottom = bottoms[index];
          index++;
          
          float average = sum / bottom;
          std::cout << std::setw(width) << stockModel.multiplier
          << std::setw(width) << stockModel.bollingerBandLength
          << std::setw(width) << stockModel.standardDevHigh
          << std::setw(width) << sum
          << std::setw(width) << bottom
          << std::setw(width) << average
          << std::setw(width) << average / bottom
          << std::setw(width) << average / sum
          << std::endl;
          
          stockModel.bollingerBandLength += 5;
        }
        stockModel.standardDevHigh += 5;
      }
      stockModel.multiplier++;
    }
  }
}

void runWilliamsVix() {
  TestModel::initialize();
  
  for (unsigned int j = 0; j < TestModel::getTestStockCount(); j++) {
    Stock& stock = TestModel::getTestStock(j);
    std::cout << "STOCK: " << stock.symbol << std::endl;
    
    unsigned int totalTime = 0;
    for (unsigned int i = 0; i < TestModel::getNumberOfDates(); i++) {
      StockModel& stockModel = resetAllModelsForStock(j);
      
      std::cout << "DATE: " << TestModel::getDateAtIndex(i) << std::endl;
      std::cout << "--------------------" << std::endl;
      
      TestModel::setDate(TestModel::getDateAtIndex(i));
      if(!FileManager::readQuoteAtStockIndex(j)) {
        continue;
      }

      for (unsigned int marketTime = 0; marketTime < TestModel::totalTimeQuotes(j); marketTime++) {
        RestCall::mockRestCall(stock, marketTime);
        BuySell::buyOrSell(stock);
      }
    }
  }
}

void testSimpleMovingAverage() {
  const unsigned int smal = 100;
  const unsigned int mal = 100;
  const unsigned int sl = 10;
  
  TestModel::initialize();
  
  const unsigned int totalSums = (smal + 1) * (mal + 1) * (sl + 1);
  float* sums = new float[totalSums];
  for (unsigned int i = 0;  i < totalSums; i++) {
    sums[totalSums] = 0;
  }
  
  for (unsigned int j = 0; j < TestModel::getTestStockCount(); j++) {
    Stock& stock = TestModel::getTestStock(j);
    std::cout << "STOCK: " << stock.symbol << std::endl;
    
    unsigned int totalTime = 0;
    for (unsigned int i = 0; i < TestModel::getNumberOfDates(); i++) {
      StockModel& stockModel = resetAllModelsForStock(j);
      
      std::cout << "DATE: " << TestModel::getDateAtIndex(i) << std::endl;
      std::cout << "--------------------" << std::endl;
      
      TestModel::setDate(TestModel::getDateAtIndex(i));
      if(!FileManager::readQuoteAtStockIndex(j)) {
        continue;
      }

      unsigned int index = 0;
      stockModel.shiftedMovingAverageLength = 1;
      while(stockModel.shiftedMovingAverageLength <= smal) {
        stockModel.movingAverageLength = 1;
        while(stockModel.movingAverageLength <= mal) {
          stockModel.shiftLength = 1;
          while(stockModel.shiftLength <= sl) {
            //if (stockModel.movingAverageLength <= stockModel.shiftedMovingAverageLength) {
              for (unsigned int marketTime = 0; marketTime < TestModel::totalTimeQuotes(j); marketTime++) {
                RestCall::mockRestCall(stock, marketTime);
                BuySell::buyOrSell(stock);
              }
              
              if (!isnan(stock.getPercentageMade())) {
                sums[index] += stock.getPercentageMade();
              }
            //}
            
            index++;
            TestModel::resetStockData();
            Model::setStopBuying(false);
            Model::setPurchasedStockSymbol("");
            stockModel.shiftLength++;
          }
          stockModel.movingAverageLength += 1;
        }
        stockModel.shiftedMovingAverageLength += 1;
      }
    }
    
    StockModel& stockModel = stock.getStockModel();
    unsigned int index = 0;
    stockModel.shiftedMovingAverageLength = 1;
    while(stockModel.shiftedMovingAverageLength <= smal) {
      stockModel.movingAverageLength = 1;
      while(stockModel.movingAverageLength <= mal) {
        stockModel.shiftLength = 1;
        while(stockModel.shiftLength <= sl) {
          if (stockModel.movingAverageLength <= stockModel.shiftedMovingAverageLength) {
            float sum = sums[index];
            index++;
          
            std::cout << "\t" << stockModel.shiftLength
            << "\t" << stockModel.shiftedMovingAverageLength
            << "\t" << stockModel.movingAverageLength
            << "\t\t" << sum
            << std::endl;
          }
          
          stockModel.shiftLength++;
        }
        stockModel.movingAverageLength += 1;
      }
      stockModel.shiftedMovingAverageLength += 1;
    }
  }
}

#include <iomanip>
#include <sstream>
int main(void)
{
  StockRunner::runDailyProfits();
  //runProfitMaximizationForIndividualStocks();
  
  //StockRunner::dailyProfitsTimeSpan();
  //maximizeTimeSpan();
  
  //testWilliamsVix();
  //runWilliamsVix();
  
  //testSimpleMovingAverage();
  
  return 0;
}
