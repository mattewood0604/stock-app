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

void runProfitTests() {
  const unsigned int wTimePeriods = TestModel::maximumWTimePeriods + 1 - 2;
  const unsigned int longTimePeriods = TestModel::maximumLongTimePeriods + 1;
  const unsigned int shortTimePeriods = TestModel::maximumShortTimePeriods + 1;
  const unsigned int candleTimes = TestModel::maximumCandleTime / 1000;
  
  //float**** profits = new float[wTimePeriods][];
  //for (unsigned int i = 0; i < wTimePeriods; i++) {
  //  profits[i] = new float[longTimePeriods];
  //}
  
  //float**** profits = new float[wTimePeriods][longTimePeriods][shortTimePeriods][candleTimes];
  float profits[1][longTimePeriods][shortTimePeriods][candleTimes];
  
  TestModel::initialize();

  for (unsigned int i = 0; i < TestModel::getNumberOfDates(); i++) {
    TestModel::hardResetStock();
    Stock& stock = TestModel::getTestingStock(); //TestModel::stockForSymbol(TestModel::stockSymbol);
    StockModel& stockModel = stock.getStockModel();
    stockModel.reset();
    
    std::cout << "DATE: " << TestModel::getDateAtIndex(i) << std::endl;
    std::cout << "--------------------" << std::endl;
    TestModel::setDate(TestModel::getDateAtIndex(i));
    FileManager::readQuotes();
    
    //while (stockModel.getWTimePeriods() <= TestModel::maximumWTimePeriods) {
      //std::cout << "WTP: " << stockModel.getWTimePeriods() << std::endl;
      //std::cout << "--------------------" << std::endl;
      
      while (stockModel.getLongTimePeriods() <= TestModel::maximumLongTimePeriods) {
        //std::cout << "LTP: " << stockModel.getLongTimePeriods() << std::endl;
        //std::cout << "--------------------" << std::endl;
        
        while (stockModel.getShortTimePeriods() <= TestModel::maximumShortTimePeriods) {
          //std::cout << "STP: " << stockModel.getShortTimePeriods() << std::endl;
          //std::cout << "--------------------" << std::endl;
          
          while (stockModel.getMaxCandleTime() <= TestModel::maximumCandleTime) {
            //std::cout << "MCT: " << stockModel.getMaxCandleTime() << std::endl;
            //std::cout << "--------------------" << std::endl;
            
            if (stockModel.getShortTimePeriods() < stockModel.getLongTimePeriods()) {
              for (unsigned int marketTime = 0; marketTime < TestModel::totalTimeQuotes(); marketTime++) {
                RestCall::mockRestCall(marketTime);
              }
            }
            
            //TestModel::logMoneyMade();
            if (!isnan(stock.getPercentageMade())) {
              //profits[stockModel.getWTimePeriods() - 2][stockModel.getLongTimePeriods()][stockModel.getShortTimePeriods()][stockModel.getMaxCandleTime() / 1000] += stock.getPercentageMade() * 100;
              profits[0][stockModel.getLongTimePeriods()][stockModel.getShortTimePeriods()][stockModel.getMaxCandleTime() / 1000] += stock.getPercentageMade() * 1000000;
            }
            
            TestModel::resetStockData();
            stockModel.incrementMaxCandleTime();
          }
          
          stockModel.resetMaxCandleTime();
          stockModel.incrementShortTimePeriods();
        }
        
        stockModel.resetShortTimePeriods();
        stockModel.incrementLongTimePeriods();
      }
      
      //stockModel.resetLongTimePeriods();
      //stockModel.incrementWTimePeriods();
    //}
  }
  
  //std::cout << "\n\n\n\n\n\n\n\n\n\n";
  //std::cout << "WTIME\tLONG\tSHORT\tCANDLE\tPROFIT" << std::endl;
  //std::cout << "---------------------------" << std::endl;
  
  std::string profitData;
  profitData.append("LONG\tSHORT\tCANDLE\tPROFIT\n");
  profitData.append("---------------------------\n");
  
  //for (unsigned int wTime = 0; wTime < TestModel::maximumWTimePeriods - 2; wTime++) {
  for (unsigned int longTime = 0; longTime < TestModel::maximumLongTimePeriods; longTime++) {
    for (unsigned int shortTime = 0; shortTime < TestModel::maximumShortTimePeriods; shortTime++) {
      for (unsigned int candleTime = 0; candleTime < TestModel::maximumCandleTime; candleTime += 1000) {
        float profit = profits[0][longTime][shortTime][candleTime / 1000] / 10000;
        //std::cout << wTime << "\t" << longTime << "\t" << shortTime << "\t" << candleTime << "\t" << profit << std::endl;
        std::cout << longTime << "\t" << shortTime << "\t" << candleTime << "\t" << profit << std::endl;
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
  
  FileManager::writeProfitsForSymbol(TestModel::stockSymbol, profitData);
  
}

int main(void)
{
  //StockRunner::runStocks();
  StockRunner::runDailyProfits();
  
  return 0;
}
