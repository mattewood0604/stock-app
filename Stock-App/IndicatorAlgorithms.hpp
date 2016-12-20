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
  
  private:
    static void calculateAveragePriceEMA(Stock& _stock);
    static void calculateWs(Stock& _stock);
  
};

#endif /* IndicatorAlgorithms_hpp */
