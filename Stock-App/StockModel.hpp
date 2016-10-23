//
//  StockModel.hpp
//  Stock-App
//
//  Created by Matt Wood on 10/21/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#ifndef StockModel_hpp
#define StockModel_hpp

#include <stdio.h>

class StockModel {
  public:
    static unsigned int shortTimePeriods;
    static unsigned int longTimePeriods;
  
    static unsigned int wTimePeriods;
  
    static unsigned int maxCandleTime;
  
    static float maxGain;
    static float maxLoss;
};

#endif /* StockModel_hpp */
