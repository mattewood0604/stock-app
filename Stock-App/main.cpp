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
  return profitStorage;
}

void resetProfitStorage(float**** _profitStorage, unsigned int _w, unsigned int _l, unsigned int _s, unsigned int _c) {
  //for (unsigned int w = 0; w < _w; w++) {
    for (unsigned int l = 20; l < _l; l++) {
      for (unsigned int s = 20; s < _s; s++) {
        for (unsigned int c = 15; c < _c; c++) {
          _profitStorage[_w][l][s][c] = 0.0f;
        }
      }
    }
  //}
}

void calculateProfits(const Stock& _stock, const StockModel& _stockModel, float**** _profits) {
  if (_stockModel.getShortTimePeriods() < _stockModel.getLongTimePeriods()) {
    for (unsigned int marketTime = 0; marketTime < TestModel::totalTimeQuotes(); marketTime++) {
      RestCall::mockRestCall(marketTime);
    }
  }
  
  if (!isnan(_stock.getPercentageMade())) {
    _profits[_stockModel.getWTimePeriods()][_stockModel.getLongTimePeriods()][_stockModel.getShortTimePeriods()][_stockModel.getMaxCandleTime() / 1000] += (_stock.getPercentageMade() * 10000);
  }
}

StockModel& resetAllModelsForStock(Stock& _stock) {
  TestModel::hardResetStock();
  StockModel& stockModel = _stock.getStockModel();
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
  for (unsigned int longTime = 20; longTime < TestModel::maximumLongTimePeriods; longTime++) {
    for (unsigned int shortTime = 20; shortTime < TestModel::maximumShortTimePeriods; shortTime++) {
      for (unsigned int candleTime = 15; candleTime < TestModel::maximumCandleTime / 1000; candleTime++) {
        float profit = _profits[stockModel.getWTimePeriods()][longTime][shortTime][candleTime] / 100;
        totalForTheDay++;
        if (profit > TestModel::getNumberOfDates() && profit < 1000) {
          totalPositive++;
          //std::cout << longTime << "\t" << shortTime << "\t" << candleTime << "\t" << profit << std::endl;
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
  }
  //}
  
  profitData.append("--------------------");
  profitData.append("POSITIVE: ");
  profitData.append(std::to_string(totalPositive));
  profitData.append("--------------------");
  profitData.append("\n");
  profitData.append("TOTAL: ");
  profitData.append(std::to_string(totalForTheDay));
  profitData.append("--------------------");
  profitData.append("\n");
  
  FileManager::writeProfitsForSymbol(TestModel::getTestStockSymbol(0), profitData);
}

void runProfitTests() {
  float**** newProfits = createProfitStorage();
  
  TestModel::initialize();
  
  for (unsigned int j = 0; j < TestModel::getTestStockCount(); j++) {
    Stock& stock = TestModel::getTestStock(j);
    std::cout << "STOCK: " << stock.symbol << std::endl;
    StockModel& stockModel = resetAllModelsForStock(stock);
    unsigned int totalTime = 0;
    for (unsigned int i = 0; i < TestModel::getNumberOfDates(); i++) {
      stockModel = resetAllModelsForStock(stock);
      
      std::cout << "DATE: " << TestModel::getDateAtIndex(i) << std::endl;
      std::cout << "--------------------" << std::endl;
      TestModel::setDate(TestModel::getDateAtIndex(i));
      if(!FileManager::readQuotes()) {
        // Read quotes should not loop through all of the symbols
        // It should be readAllQuotes and readQuotes(_index)
        continue;
      }
      
      uint64_t startTime = (uint64_t)time(0);
      
      //while (stockModel.getWTimePeriods() <= TestModel::maximumWTimePeriods) {
      
      while (stockModel.getLongTimePeriods() <= TestModel::maximumLongTimePeriods) {
        
        while (stockModel.getShortTimePeriods() <= TestModel::maximumShortTimePeriods) {
          
          while (stockModel.getMaxCandleTime() <= TestModel::maximumCandleTime) {
            calculateProfits(stock, stockModel, newProfits);
            
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
      
      uint64_t endTime = (uint64_t)time(0);
      totalTime += (endTime - startTime);
      std::cout << "TIME TAKEN: " << endTime - startTime << std::endl;
      //stockModel.incrementWTimePeriods();
      //}
    }
    
    std::cout << "TOTAL TIME: " << totalTime << "\n\n" << std::endl;
    
    calculateAndWriteProfits(newProfits, j);
    
    resetProfitStorage(newProfits, stockModel.getWTimePeriods(), TestModel::maximumLongTimePeriods, TestModel::maximumShortTimePeriods, TestModel::maximumCandleTime / 1000);
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

// 9:06 PM


int main(void)
{
  //StockRunner::runStocks();
  StockRunner::runDailyProfits();
  //runProfitTests(); // THIS IS NOT GOING TO WORK IN ITS CURRENT STATE
  
  return 0;
}
