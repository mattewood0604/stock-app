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

#include "FileManager.hpp"
#include "Model.hpp"
#include "RestCall.hpp"
#include "StockModel.hpp"
#include "StockRunner.hpp"
#include "TestModel.hpp"

void calculateProfits(const Stock& _stock, const StockModel& _stockModel, float* _profits) {
//void calculateProfits(const Stock& _stock, const StockModel& _stockModel, float**** _profits) {
  if (_stockModel.getShortTimePeriods() < _stockModel.getLongTimePeriods()) {
    for (unsigned int marketTime = 0; marketTime < TestModel::totalTimeQuotes(); marketTime++) {
      RestCall::mockRestCall(marketTime);
    }
  }
  
  if (!isnan(_stock.getPercentageMade())) {
    std::cout << _stockModel.getWTimePeriods() << "\t" << _stockModel.getLongTimePeriods() << "\t" << _stockModel.getShortTimePeriods() << "\t" << _stockModel.getMaxCandleTime() / 1000 << std::endl;
    
    _profits[((_stockModel.getMaxCandleTime() / 1000) + _stockModel.getShortTimePeriods() * _stockModel.getLongTimePeriods()) + (_stockModel.getWTimePeriods() * _stockModel.getLongTimePeriods() * _stockModel.getShortTimePeriods() * (_stockModel.getMaxCandleTime() / 1000))] += (_stock.getPercentageMade() * 1000000) / 1000000;
    //_profits[_stockModel.getWTimePeriods()][_stockModel.getLongTimePeriods()][_stockModel.getShortTimePeriods()][_stockModel.getMaxCandleTime() / 1000] += (_stock.getPercentageMade() * 1000000) / 1000000;
  }
}

void runProfitTests() {
  const unsigned int wTimePeriods = TestModel::maximumWTimePeriods + 1;
  const unsigned int longTimePeriods = TestModel::maximumLongTimePeriods + 1;
  const unsigned int shortTimePeriods = TestModel::maximumShortTimePeriods + 1;
  const unsigned int candleTimes = TestModel::maximumCandleTime / 1000;
  
  /*
  float**** newProfits = new float***[wTimePeriods];
  for (unsigned int w = 0; w < wTimePeriods; w++) {
    newProfits[w] = new float**[longTimePeriods];
    for (unsigned int l = 0; l < longTimePeriods; l++) {
      newProfits[w][l] = new float*[shortTimePeriods];
      for (unsigned int s = 0; s < shortTimePeriods; s++) {
        newProfits[w][l][s] = new float[candleTimes];
        for (unsigned int c = 0; c < candleTimes; c++) {
          newProfits[w][l][s][c] = 0.0f;
        }
      }
    }
  }
   */
  
  float* profits = new float[wTimePeriods * longTimePeriods * shortTimePeriods * candleTimes];
  for (unsigned int wTime = 0; wTime < wTimePeriods; wTime++) {
    for (unsigned int longTime = 0; longTime < longTimePeriods; longTime++) {
      for (unsigned int shortTime = 0; shortTime < shortTimePeriods; shortTime++) {
        for (unsigned int candleTime = 0; candleTime < candleTimes; candleTime++) {
          profits[(candleTime + shortTime * longTime) + (wTime * longTime * shortTime * candleTime)] = 0;
        }
      }
    }
  }
  
  TestModel::initialize();

  for (unsigned int i = 0; i < TestModel::getNumberOfDates(); i++) {
    TestModel::hardResetStock();
    Stock& stock = TestModel::getTestingStock();
    StockModel& stockModel = stock.getStockModel();
    stockModel.reset();
    
    std::cout << "DATE: " << TestModel::getDateAtIndex(i) << std::endl;
    std::cout << "--------------------" << std::endl;
    TestModel::setDate(TestModel::getDateAtIndex(i));
    FileManager::readQuotes();
    
    while (stockModel.getWTimePeriods() <= TestModel::maximumWTimePeriods) {
      
      while (stockModel.getLongTimePeriods() <= TestModel::maximumLongTimePeriods) {
        
        while (stockModel.getShortTimePeriods() <= TestModel::maximumShortTimePeriods) {
          
          while (stockModel.getMaxCandleTime() <= TestModel::maximumCandleTime) {
            calculateProfits(stock, stockModel, profits);
            
            TestModel::resetStockData();
            stockModel.incrementMaxCandleTime();
          }
          
          stockModel.resetMaxCandleTime();
          stockModel.incrementShortTimePeriods();
        }
        
        stockModel.resetShortTimePeriods();
        stockModel.incrementLongTimePeriods();
      }
      
      stockModel.resetLongTimePeriods();
      stockModel.incrementWTimePeriods();
    }
  }
  
  std::cout << "\n\n\n\n\n\n\n\n\n\n";
  std::cout << "WTIME\tLONG\tSHORT\tCANDLE\tPROFIT" << std::endl;
  std::cout << "---------------------------" << std::endl;
  
  std::string profitData;
  profitData.append("WTIME\tLONG\tSHORT\tCANDLE\tPROFIT\n");
  profitData.append("---------------------------\n");
  
  for (unsigned int wTime = 2; wTime < wTimePeriods; wTime++) {
    for (unsigned int longTime = 10; longTime < longTimePeriods; longTime++) {
      for (unsigned int shortTime = 10; shortTime < shortTimePeriods; shortTime++) {
        for (unsigned int candleTime = 0; candleTime < candleTimes; candleTime++) {
          float profit = profits[(candleTime + shortTime * longTime) + (wTime * longTime * shortTime * candleTime)]; //newProfits[wTime][longTime][shortTime][candleTime];
          if (profit > 0 && profit < 1000) {
            std::cout << wTime << "\t" << longTime << "\t" << shortTime << "\t" << candleTime << "\t" << profit << std::endl;
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
    }
  }
  
  FileManager::writeProfitsForSymbol(TestModel::stockSymbol, profitData);
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

// 9:06 PM


int main(void)
{
  //StockRunner::runStocks();
  //StockRunner::runDailyProfits();
  runProfitTests();
  
  return 0;
}
