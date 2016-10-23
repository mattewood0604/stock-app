//
//  StockModel.cpp
//  Stock-App
//
//  Created by Matt Wood on 10/21/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#include "StockModel.hpp"

unsigned int StockModel::shortTimePeriods = 20;
unsigned int StockModel::longTimePeriods = 40;

unsigned int StockModel::wTimePeriods = 4;

unsigned int StockModel::maxCandleTime = 30000;

float StockModel::maxGain = 0.10f;
float StockModel::maxLoss = 0.10f;
