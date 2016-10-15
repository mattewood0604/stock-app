//
//  RestCall.hpp
//  Stock-App
//
//  Created by Matt Wood on 10/15/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#ifndef RestCall_hpp
#define RestCall_hpp

#include <curl/curl.h>

#include "MemoryChunk.hpp"

class RestCall {
  public:
    static MemoryChunk memoryChunk;
    static CURL* curlHandle;
  
    static void init();
    static void quotes();
  
    static size_t WriteMemoryCallback(void* _contents, size_t _size, size_t _nmemb, void* _userp);
  
  private:
};

#endif /* RestCall_hpp */
