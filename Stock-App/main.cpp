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

#include "FileManager.hpp"
#include "Model.hpp"
#include "RestCall.hpp"
#include "StockModel.hpp"
#include "TestModel.hpp"

void runTests() {
  TestModel::initialize();

  for (unsigned int i = 0; i < TestModel::dates.size(); i++) {
    std::cout << "DATE: " << TestModel::dates[i] << std::endl;
    std::cout << "--------------------" << std::endl;
    TestModel::setDate(TestModel::dates[i]);
    FileManager::readQuotes();
    
    for (unsigned int marketTime = 0; marketTime < TestModel::totalTimeQuotes(); marketTime++) {
      RestCall::mockRestCall(marketTime);
    }
    
    TestModel::logMoneyMade();
    TestModel::resetTestData();
  }
}

void runProfitTests() {
  TestModel::initialize();

  std::time_t startTime = std::time(nullptr);
  
  Stock& stock = TestModel::getTestingStock(); //TestModel::stockForSymbol(TestModel::stockSymbol);
  StockModel& stockModel = stock.getStockModel();
  stockModel.reset();
  
  for (unsigned int i = 0; i < TestModel::dates.size(); i++) {
    Stock& stock = TestModel::getTestingStock(); //TestModel::stockForSymbol(TestModel::stockSymbol);
    stock = Stock(TestModel::stockSymbol);
    StockModel& stockModel = stock.getStockModel();
    stockModel.reset();
    
    std::cout << "DATE: " << TestModel::dates[i] << std::endl;
    std::cout << "--------------------" << std::endl;
    TestModel::setDate(TestModel::dates[i]);
    FileManager::readQuotes();
    
    while (stockModel.getLongTimePeriods() <= 100) {
      std::cout << "LTP: " << stockModel.getLongTimePeriods() << std::endl;
      std::cout << "--------------------" << std::endl;
      
      while (stockModel.getShortTimePeriods() <= 50) {
        std::cout << "STP: " << stockModel.getShortTimePeriods() << std::endl;
        std::cout << "--------------------" << std::endl;
        
        while (stockModel.getMaxCandleTime() <= 60000) {
          std::cout << "MCT: " << stockModel.getMaxCandleTime() << std::endl;
          std::cout << "--------------------" << std::endl;
          
          for (unsigned int marketTime = 0; marketTime < TestModel::totalTimeQuotes(); marketTime++) {
            RestCall::mockRestCall(marketTime);
          }
          
          TestModel::logMoneyMade();
          TestModel::resetStockData();
          stockModel.incrementMaxCandleTime();
        }
        
        stockModel.resetMaxCandleTime();
        stockModel.incrementShortTimePeriods();
      }
      
      stockModel.resetShortTimePeriods();
      stockModel.incrementLongTimePeriods();
    }
  }
  
  std::time_t endTime = std::time(nullptr);
  
  std::cout << (endTime - startTime) / 60.0f << std::endl;
  
  /*
    [StockModel resetLongTimePeriods];
    [StockModel resetShortTimePeriods];
    [StockModel resetMaxCandleTime];
    
    for (NSString* date in [Model datesForTesting]) {
      NSLog(@"%@", date);
      [Model reset];
      [Model setTestRunDate:date];
      [DataFileManager loadTestDataForSymbol:symbol];
      
      NSInteger longTimePeriods = [StockModel longTimePeriods];
      while (longTimePeriods <= 100) {
        NSLog(@"%ld", longTimePeriods);
        
        NSInteger shortTimePeriods = [StockModel shortTimePeriods];
        while (shortTimePeriods <= 50) {
          NSLog(@"%ld", shortTimePeriods);
          
          NSInteger maxCandleTime = [StockModel maxCandleTime];
          while (maxCandleTime < 60000) {
            NSLog(@"%ld", maxCandleTime);
            [StockRunner runTests];
            
            [StockModel incrementMaxCandleTime];
            maxCandleTime = [StockModel maxCandleTime];
          }
          [StockModel resetMaxCandleTime];
          
          [StockModel incrementShortTimePeriods];
          shortTimePeriods = [StockModel shortTimePeriods];
        }
        [StockModel resetShortTimePeriods];
        
        [StockModel incrementLongTimePeriods];
        longTimePeriods = [StockModel longTimePeriods];
      }
      
      NSLog(@"%f", [StockModel maxMoney]);
      
      [StockModel resetLongTimePeriods];
      [StockModel resetShortTimePeriods];
      [StockModel resetMaxCandleTime];
    }
   */
}

void runStocks() {
  RestCall::init();
  
  while (1) {
    RestCall::quotes();
    FileManager::writeQuotes();
    Model::logQuotes();
    Model::resetTimeQuotes();
    sleep(2);
  }
}

int main(void)
{
  //runStocks();
  //runTests();
  runProfitTests();
  return 0;
}
