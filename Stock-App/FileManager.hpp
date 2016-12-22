//
//  FileManager.hpp
//  Stock-App
//
//  Created by Matt Wood on 10/19/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#ifndef FileManager_hpp
#define FileManager_hpp

#include <fstream>
#include <map>
#include <string>

#include "TimeQuote.hpp"

class FileManager {
  public:
    static bool readQuotes();
    static bool readQuoteAtStockIndex(const unsigned int& _index);
  
    static void writeQuoteToFile(const TimeQuote& _timeQuote);
  
    static std::string readStockSymbolsForQuotes();
  
    static void writeProfitsForSymbol(const std::string& _symbol, const std::string& _data);
  
  private:
    static std::map<std::string, std::ofstream*> symbolFiles;
  
    static bool readQuotes(const unsigned int& _index);
  
    static void writeDataForSymbol(const std::string& _symbol, const std::string& _data);
    static void writeDataToFile(const std::string& _data, std::ofstream& _file);
};

#endif /* FileManager_hpp */
