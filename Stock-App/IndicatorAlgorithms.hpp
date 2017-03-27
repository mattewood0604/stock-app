//
//  IndicatorAlgorithms.hpp
//  Stock-App
//
//  Created by Matt Wood on 12/18/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#ifndef IndicatorAlgorithms_hpp
#define IndicatorAlgorithms_hpp

#include "Stock.hpp"

class IndicatorAlgorithms {
  public:
    static void calculateWaveTrend(Stock& _stock);
  
    static void supertrendAlgorithm(Stock& _stock);
  
    static void williamsVix(Stock& _stock);
  
    static void simpleMovingAverages(Stock& _stock);
  
  private:
    static void calculateAveragePriceEMA(Stock& _stock);
    static void calculateWs(Stock& _stock);
  
    static float averageTrueRange(Stock& _stock);
    static float standardDeviation(Stock& _stock, const float& _williamsVix);
  
    static float highest(Stock& _stock, const unsigned int& _barsBack);
};

#endif /* IndicatorAlgorithms_hpp */
