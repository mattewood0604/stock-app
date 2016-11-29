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
  	if (Model::isMarketOpen())
  	{
    	RestCall::quotes();
    	sleep(2);
  	}
  }
}

void StockRunner::runDailyProfits() {
  float percentageMade = 0.0f;
  
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
    
    percentageMade += (!isnan(TestModel::getTestingStock().getPercentageMade())) ? TestModel::getTestingStock().getPercentageMade() : 0.0f;
    
    TestModel::hardResetStock();
  }
  
  std::cout << "TOTAL PERCENTAGE: " << percentageMade << std::endl;
}
