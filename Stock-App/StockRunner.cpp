//
//  StockRunner.cpp
//  Stock-App
//
//  Created by Matt Wood on 11/25/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <unistd.h>

#include "BuySell.hpp"
#include "FileManager.hpp"
#include "Model.hpp"
#include "RestCall.hpp"
#include "StockRunner.hpp"
#include "TestModel.hpp"

void StockRunner::runStocks() {
  bool marketBecameOpen = false;
  
  FileManager::init();
  RestCall::init();
  
  std::cout << "Begin Querying For Data..." << std::endl;
  while(1) {
  	if (Model::isMarketOpen()) {
      if (!marketBecameOpen) {
        std::cout << "Market Opened" << std::endl;
      }

    	RestCall::quotes();
      
      BuySell::buyOrSell(Model::getStockForSymbol("JNUG"));
      BuySell::buyOrSell(Model::getStockForSymbol("DUST"));
      
    	sleep(2);
      marketBecameOpen = true;
  	}
    else if (marketBecameOpen) {
      std::cout << "Market Closed" << std::endl;
      break;
    }
  }
}

void StockRunner::runDailyProfits() {
  float percentageMade = 0.0f;
  
  FileManager::init();
  TestModel::initialize();
  
  for (unsigned int i = 0; i < TestModel::getNumberOfDates(); i++) {
    TestModel::setDate(TestModel::getDateAtIndex(i));
    logDateForIndex(i);
    
    percentageMade += runDailyStocksForSetDate();
    Model::setStopBuying(false);
    
    Model::setPurchasedStockSymbol("");
    TestModel::hardResetStock();
  }
  
  std::cout << "TOTAL DAYS:\t\t\t" << TestModel::getNumberOfDates() << std::endl;
  std::cout << "TOTAL PERCENTAGE:\t" << percentageMade * 100 << std::endl;
  std::cout << "PERCENTAGE / DAY:\t" << (percentageMade * 100) / TestModel::getNumberOfDates() << std::endl;
}

void StockRunner::logDateForIndex(const unsigned int& _index) {
  std::cout << "DATE: " << TestModel::getDateAtIndex(_index) << std::endl;
  std::cout << "--------------------" << std::endl;
}

float StockRunner::runDailyStocksForSetDate() {
  FileManager::readQuotes();
  
  for (unsigned int marketTime = 0; marketTime < TestModel::totalTimeQuotes(); marketTime++) {
    for (unsigned int stockIndex = 0; stockIndex < TestModel::getTestStockCount(); stockIndex++) {
      RestCall::mockRestCall(TestModel::getTestStock(stockIndex), marketTime);
    }
    
    for (unsigned int stockIndex = 0; stockIndex < TestModel::getTestStockCount(); stockIndex++) {
      Stock& stock = TestModel::getTestStock(stockIndex);
      BuySell::buyOrSell(stock);
    }
  }
  
  TestModel::logMoneyMade();
  
  float percentageMade = 0;
  for (unsigned int i = 0; i < TestModel::getTestStockCount(); i++) {
    const Stock& stock = TestModel::getTestStock(i);
    percentageMade += !isnan(stock.getPercentageMade()) ? stock.getPercentageMade() : 0.0f;
  }
  
  return percentageMade;
}
