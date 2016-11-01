//
//  FileManager.cpp
//  Stock-App
//
//  Created by Matt Wood on 10/19/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#include <iostream>
#include <iostream>
#include <fstream>
#include <string>

#include "FileManager.hpp"
#include "Model.hpp"
#include "TestModel.hpp"

std::map<std::string, std::ofstream*> FileManager::symbolFiles;

void FileManager::readQuotes() {
  std::ifstream* symbolFile = new std::ifstream(TestModel::quotesDirectory());
  
  if (!symbolFile->is_open())
  {
    std::cout << "ERROR" << std::endl;
  }
  
  symbolFile->seekg(0, symbolFile->end);
  unsigned int fileLength = (unsigned int)symbolFile->tellg();
  symbolFile->seekg(0, symbolFile->beg);
  
  char* symbolFileData = new char[fileLength];
  symbolFile->read(symbolFileData, fileLength);
  
  std::string quotes = std::string(symbolFileData);
  Stock& stock = TestModel::getTestingStock(); //TestModel::stockForSymbol(TestModel::stockSymbol);
  int lastNewlineIndex = -1;
  for (unsigned int i = 0; i < fileLength; i++)
  {
    if (quotes[i] == '\n') {
    		std::string quote = quotes.substr(lastNewlineIndex + 1, i - lastNewlineIndex - 1);
        TimeQuote timeQuote = TimeQuote(quote, TimeQuote::FROM::CSV);
        stock.addQuoteToTestData(timeQuote);
    		lastNewlineIndex = i;
    }
  }
  
  delete [] symbolFileData;
}

void FileManager::writeQuotes() {
  for (unsigned int i = 0; i < Model::totalTimeQuotes(); i++) {
    const TimeQuote& timeQuote = Model::getTimeQuote(i);
    std::string symbol = timeQuote.getSymbol();
    std::string csv = timeQuote.toCSV();
    writeDataForSymbol(symbol, csv);
  }
}

void FileManager::writeDataForSymbol(const std::string& _symbol, const std::string& _data) {
  std::ofstream* symbolFile = symbolFiles[_symbol];
  if (symbolFile != NULL) {
    writeDataToFile(_data, *symbolFile);
  }
  else {
    std::string fileName = _symbol + ".csv";
    symbolFile = new std::ofstream(Model::quotesDirectory + fileName, std::ofstream::out | std::ofstream::app);
    if (symbolFile->is_open()) {
      writeDataToFile(_data, *symbolFile);
      symbolFiles[_symbol] = symbolFile;
    }
    else {
      delete symbolFile;
    }
  }
}

void FileManager::writeProfitsForSymbol(const std::string& _symbol, const std::string& _data) {
  std::string fileName = "/Users/Matt/Desktop/symbol_profits/" + _symbol + "-profits.txt";
  std::ofstream symbolFile = std::ofstream(fileName);
  writeDataToFile(_data, symbolFile);
}

void FileManager::writeDataToFile(const std::string& _data, std::ofstream& _file) {
  uint64_t pos = _file.tellp();
  _file.seekp(pos);
  _file.write(_data.c_str(), _data.size());
  _file.flush();
}