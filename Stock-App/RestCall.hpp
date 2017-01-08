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
#include <cstring>

#include "Response.hpp"

class RestCall {
  public:
    static Response response;
  
    static void init();
  
    // Called Once
    static std::string idForStockSymbol(const std::string& _symbol);
  
    // Called Multiple Times
    static void quotes();
    static void getAvailableBalance();
  
    // Called Never
    static void getAllOpenDays();
  
    static void buy();
    static void sell();
  
    static void mockRestCall(Stock& _stock, const unsigned int& marketTime);
  
  private:
    static CURL* quotesHandle;
    static CURL* authenticationHandle;
    static CURL* availableCashHandle;
  
    static std::string authenticationToken;
    static std::string accountUrl;
  
    static void authenticate();
  
    static void initializeQuotesHandle();
    static void initializeAuthenticationHandle();
    static void initializeAvailableCashHandle();
  
    static size_t WriteMemoryCallback(void* _contents, size_t _size, size_t _nmemb, void* _userp);
};

#endif /* RestCall_hpp */
