//
//  MemoryChunk.hpp
//  Stock-App
//
//  Created by Matt Wood on 10/15/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#ifndef MemoryChunk_hpp
#define MemoryChunk_hpp

#include <stdio.h>

class MemoryChunk {
  public:
    char* memory;
    size_t size;
  
    void log() const;
    void parse() const;
  
  private:
  
};

#endif /* MemoryChunk_hpp */
