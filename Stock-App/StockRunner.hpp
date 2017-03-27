//
//  StockRunner.hpp
//  Stock-App
//
//  Created by Matt Wood on 11/25/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#ifndef StockRunner_hpp
#define StockRunner_hpp

class StockRunner {
  public:
    static void runStocks();
    static void runDailyProfits();
    static void dailyProfitsTimeSpan();
    static void runProfitMaximizer();
  
  private:
    static void logDateForIndex(const unsigned int& _index);
  
    static float runDailyStocksForSetDate();
    static float runDailyTimeSpanForSetDate();
  
    static int totalNumberOfTrades;
    static int totalNumberOfNegativeTrades;
};

#endif /* StockRunner_hpp */
