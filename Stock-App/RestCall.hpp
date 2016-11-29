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

#include "Response.hpp"

class RestCall {
  public:
    static Response response;
    static CURL* curlHandle;
  
    static void init();
    static void quotes();
    static void buy();
    static void sell();
  
    static void mockRestCall(const unsigned int _marketTime);
  
  private:
    static CURL* quotesHandle;
  
    static void initializeQuotesHandle();
  
    static size_t WriteMemoryCallback(void* _contents, size_t _size, size_t _nmemb, void* _userp);
};

#endif /* RestCall_hpp */
