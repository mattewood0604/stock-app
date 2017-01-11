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

void calculateProfits(Stock& _stock, const StockModel& _stockModel, float**** _profits, unsigned int _index) {
  //if (_stockModel.getShortTimePeriods() <= _stockModel.getLongTimePeriods()) {
    for (unsigned int marketTime = 0; marketTime < TestModel::totalTimeQuotes(_index); marketTime++) {
      RestCall::mockRestCall(_stock, marketTime);
      _stock.buyOrSell();
    }
  //}
  
  if (!isnan(_stock.getPercentageMade())) {
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
  for (unsigned int longTime = 20; longTime < TestModel::maximumLongTimePeriods; longTime++) {
    for (unsigned int shortTime = 20; shortTime < TestModel::maximumShortTimePeriods; shortTime++) {
      for (unsigned int candleTime = 15; candleTime < TestModel::maximumCandleTime / 1000; candleTime++) {
        float profit = _profits[stockModel.getWTimePeriods()][longTime][shortTime][candleTime] / 100;
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
  
  FileManager::init();
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

int main(void)
{  
  /*for (unsigned int i = 0; i < 100; i++) {
    unsigned int volume = RestCall::getVolumeForStockSymbol(symbols[i]);
    if (volume >= 1000000) {
      std::cout << symbols[i] << ": " << volume << std::endl;
    }
  }*/
  
  //RestCall::init();
  //StockRunner::runStocks();
  
  //RestCall::init();
  //StockRunner::runDailyProfits();
  
  //const Stock& stock = TestModel::getTestStock(0);
  //RestCall::buy(stock, 1, 7.63);
  //runProfitMaximizationForIndividualStocks();
  
  ///////////////////////////////////////////////////////////////////
  //RestCall::init();
  //RestCall::getAvailableBalance();
  //RestCall::idForStockSymbol("JNUG");
  //return 0;
  
  //time_t currentTime = time(0);
  //struct tm* now = localtime(&currentTime);
  
  //std::cout << now->tm_wday << std::endl;
  /*
   while(1) {
     time_t currentTime = time(0);
     struct tm* now = localtime(&currentTime);
     if (Model::isMarketOpen()) { // Fix this for day of the week
       if (now->tm_hour >= 0 && RestCall::isMarketOpen()) {
         sleep(now until tomorrow and 9:30)
       }
     }
   }
   */
  
  
  // Below can be used so that this application can continuosly run. No other script needed.
  /*
   
   while(1) {
    // If the time >9:30 and <4 and it is a M-F
    //   If its 10 and the market isnt open
    //     Sleep until the next day
    //   Else
    //     If the new folder hasnt been created
    //       Create the new daily data folder
    //     Query for the market data
    // Else
    //   If its Friday
    //     Sleep until Moday
    //   Else
    //     Sleep until tomorrow
   
  	if (Model::isMarketOpen()) {
      if (!marketBecameOpen) {
        std::cout << "Market Opened" << std::endl;
        // Make the directory for the new day
      }
     
      RestCall::quotes();
      // buyOrSell
      sleep(2);
      marketBecameOpen = true;
    }
    else if (marketBecameOpen) {
      // Sleep here for a few an hour
      std::cout << "Market Closed" << std::endl;
      break;
    }
   }
   */
  ///////////////////////////////////////////////////////////////////
  
  return 0;
}
