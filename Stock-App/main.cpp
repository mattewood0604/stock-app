//
//  main.cpp
//  Stock-App
//
//  Created by Matt Wood on 10/13/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#include "Model.hpp"
#include "RestCall.hpp"

int main(void)
{
  RestCall::init();
  
  //while (Model::isMarketOpen()) {
  RestCall::quotes();
  Model::logQuotes();
  FileManager::writeQuotes();
  //}
  
  return 0;
}

/*
 #include <iostream>
 #include <fstream>
 #include <map>
 #include <string>
 
 std::map<std::string, std::ofstream*> symbolFiles;
 
 void writeDataToFile(const std::string& _data, std::ofstream& _file) {
	uint64_t pos = _file.tellp();
	_file.seekp(pos);
	_file.write(_data.c_str(), _data.size());
	_file.flush();
 }
 
 void writeDataForSymbol(const std::string& _symbol, const std::string& _data) {
	std::ofstream* symbolFile = symbolFiles[_symbol];
	if (symbolFile != NULL) {
 writeDataToFile(_data, *symbolFile);
	}
	else {
 std::string fileName = _symbol + ".csv";
 symbolFile = new std::ofstream(fileName);
 if (symbolFile->is_open()) {
 writeDataToFile(_data, *symbolFile);
 symbolFiles[_symbol] = symbolFile;
 }
 else {
 delete symbolFile;
 }
	}
 }
 
 int main(int argc, char const *argv[]) {
	std::string outputFilename[] = {"JNUG", "TWLO", "CLF", "JNUG"};
 
	std::string data = "testing\n";
 
	// Loop through all the time quotes
	// Write the csv version of the quote to the symbol name
 
	for (int i = 0; i < 4; ++i) {
 writeDataForSymbol(outputFilename[i], data); // symbol, timeSlot.toCSV
	}
 
	return 0;
 }
 
 
 */
