//
//  main.cpp
//  Stock-App
//
//  Created by Matt Wood on 10/13/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#include "RestCall.hpp"

int main(void)
{
  RestCall::init();
  
  //while (1) {
    RestCall::quotes();
  //}
  
  return 0;
}
