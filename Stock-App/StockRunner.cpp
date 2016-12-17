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

#include "FileManager.hpp"
#include "Model.hpp"
#include "RestCall.hpp"
#include "StockRunner.hpp"
#include "TestModel.hpp"

void StockRunner::runStocks() {
  FileManager::readStockSymbolsForQuotes();
  
  RestCall::init();
  
  while(1) {
  	if (Model::isMarketOpen()) {
    	RestCall::quotes();
    	sleep(2);
  	}
  }
}

void StockRunner::runDailyProfits() {
  float percentageMade = 0.0f;
  
  TestModel::initialize();
  
  for (unsigned int i = 0; i < TestModel::getNumberOfDates(); i++) {
    TestModel::setDate(TestModel::getDateAtIndex(i));
    logDateForIndex(i);
    
    percentageMade += runDailyStocksForSetDate();
    Model::setStopBuying(false);
    
    Model::setPurchasedStockSymbol("");
    TestModel::hardResetStock();
  }
  
  std::cout << "TOTAL PERCENTAGE: " << percentageMade * 100 << std::endl;
}

void StockRunner::logDateForIndex(const unsigned int& _index) {
  std::cout << "DATE: " << TestModel::getDateAtIndex(_index) << std::endl;
  std::cout << "--------------------" << std::endl;
}

float StockRunner::runDailyStocksForSetDate() {
  FileManager::readQuotes();
  
  for (unsigned int marketTime = 0; marketTime < TestModel::totalTimeQuotes(); marketTime++) {
    RestCall::mockRestCall(marketTime);
  }
  
  TestModel::logMoneyMade();
  
  float percentageMade = 0;
  for (unsigned int i = 0; i < TestModel::getTestStockCount(); i++) {
    const Stock& stock = TestModel::getTestStock(i);
    percentageMade += !isnan(stock.getPercentageMade()) ? stock.getPercentageMade() : 0.0f;
  }
  
  return percentageMade;
}
