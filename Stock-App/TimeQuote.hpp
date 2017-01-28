//
//  TimeQuote.hpp
//  Stock-App
//
//  Created by Matt Wood on 10/15/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#ifndef TimeQuote_hpp
#define TimeQuote_hpp

#include <string>

class TimeQuote {
  public:
    enum FROM { JSON, CSV };
  
    TimeQuote(const std::string& _json, FROM _from = JSON, const std::string& _symbol = "");
  
    void writeToFile() const;
  
    void log() const;
    std::string toCSV() const;
  
    const std::string& getSymbol() const;
    
    std::string json;
  
    uint64_t dayTime;
    float price;
  
  private:
    std::string symbol;
    uint16_t bidQty;
    float bid;
    uint16_t offerQty;
    float offer;
    float percent;
    float change;
  
    static std::string bidKey;
    static std::string bidQtyKey;
    static std::string offerKey;
    static std::string offerQtyKey;
    static std::string timeKey;
    static std::string percentKey;
    static std::string changeKey;
    static std::string priceKey;
    static std::string symbolKey;
  
    void fromCSV(const std::string& _symbol, const std::string& _quote);
  
    int parseInt(const std::string& _key) const;
    float parseFloat(const std::string& _key) const;
    std::string parseString(const std::string& _key) const;
    uint64_t parseTime() const;
};


#endif /* TimeQuote_hpp */
