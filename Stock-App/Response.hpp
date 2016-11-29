//
//  Response.hpp
//  Stock-App
//
//  Created by Matt Wood on 10/15/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#ifndef Response_hpp
#define Response_hpp

#include <string>

class Response {
  public:
    char* memory;
    size_t size;
  
    void init();
    void log() const;
    void parseQuotes() const;
};

#endif /* Response_hpp */
