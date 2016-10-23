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

class FileManager {
  public:
    static void readQuotes();
    static void writeQuotes();
  
  private:
    static std::map<std::string, std::ofstream*> symbolFiles;
  
    static void writeDataForSymbol(const std::string& _symbol, const std::string& _data);
    static void writeDataToFile(const std::string& _data, std::ofstream& _file);
};

#endif /* FileManager_hpp */
