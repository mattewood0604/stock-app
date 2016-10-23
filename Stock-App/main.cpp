//
//  main.cpp
//  Stock-App
//
//  Created by Matt Wood on 10/13/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#include <unistd.h>

#include "FileManager.hpp"
#include "Model.hpp"
#include "RestCall.hpp"
#include "TestModel.hpp"

void runTests() {
  std::vector<std::string> dates = TestModel::dates;
  for (unsigned int i = 0; i < dates.size(); i++) {
    TestModel::setDate(dates[i]);
    FileManager::readQuotes();
    RestCall::mockCall();
    TestModel::resetTestData();
  }
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
  runTests();
  return 0;
}
