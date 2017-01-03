//
//  RestCall.cpp
//  Stock-App
//
//  Created by Matt Wood on 10/15/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "FileManager.hpp"
#include "Model.hpp"
#include "Response.hpp"
#include "RestCall.hpp"
#include "TestModel.hpp"

Response RestCall::response;

std::string RestCall::authenticationToken = "";
std::string RestCall::accountUrl = "https://api.robinhood.com/accounts/5QY77902/";

CURL* RestCall::quotesHandle = NULL;
CURL* RestCall::authenticationHandle = NULL;
CURL* RestCall::availableCashHandle = NULL;

void RestCall::init() {
  response.init();
  
  initializeQuotesHandle();
  initializeAuthenticationHandle();
  
  authenticate();
  initializeAvailableCashHandle();
  
  // Create a handle for each type of rest call
  // Quotes
  // Buy/Sell
}

void RestCall::initializeQuotesHandle() {
  quotesHandle = curl_easy_init();
  
  std::string quotesURL = "https://api.robinhood.com/quotes/?symbols=";
  std::string quotesSymbols = FileManager::readStockSymbolsForQuotes();
  quotesURL.append(quotesSymbols);
  
  curl_easy_setopt(quotesHandle, CURLOPT_URL, quotesURL.c_str());
  
  curl_easy_setopt(quotesHandle, CURLOPT_WRITEFUNCTION, RestCall::WriteMemoryCallback);
  curl_easy_setopt(quotesHandle, CURLOPT_WRITEDATA, (void*)&response);
}

void RestCall::initializeAuthenticationHandle() {
  authenticationHandle = curl_easy_init();
  
  curl_easy_setopt(authenticationHandle, CURLOPT_CUSTOMREQUEST, "POST");
  curl_easy_setopt(authenticationHandle, CURLOPT_URL, "https://api.robinhood.com/api-token-auth/");
  
  struct curl_slist* headers = NULL;
  headers = curl_slist_append(headers, "Accept: application/json");
  curl_easy_setopt(authenticationHandle, CURLOPT_HTTPHEADER, headers);
  
  curl_easy_setopt(authenticationHandle, CURLOPT_POSTFIELDS, "username=mattewood&password=1OrangeHippoWithAn!");
  curl_easy_setopt(authenticationHandle, CURLOPT_WRITEFUNCTION, RestCall::WriteMemoryCallback);
  curl_easy_setopt(authenticationHandle, CURLOPT_WRITEDATA, (void*)&response);
}

void RestCall::initializeAvailableCashHandle() {
  availableCashHandle = curl_easy_init();
  
  curl_easy_setopt(availableCashHandle, CURLOPT_URL, accountUrl.c_str());
  
  struct curl_slist* headers = NULL;
  std::string authorization = "Authorization: Token ";
  if (!authenticationToken.size()) {
    std::cout << "Error: Authentication Token NULL in initializeAvailableCashHandle" << std::endl;
  }
  authorization.append(authenticationToken);
  headers = curl_slist_append(headers, authorization.c_str());
  curl_easy_setopt(availableCashHandle, CURLOPT_HTTPHEADER, headers);
  
  curl_easy_setopt(availableCashHandle, CURLOPT_WRITEFUNCTION, RestCall::WriteMemoryCallback);
  curl_easy_setopt(availableCashHandle, CURLOPT_WRITEDATA, (void*)&response);
}

void RestCall::buy() {
  /*
  curlHandle = curl_easy_init();
  
  curl_easy_setopt(curlHandle, CURLOPT_CUSTOMREQUEST, "POST");
  curl_easy_setopt(curlHandle, CURLOPT_URL, "https://webux.ustocktrade.com/res");
  
  struct curl_slist* headers = NULL;
  headers = curl_slist_append(headers, "x-auth-token: bLYU97hV06hJlwzERdn8E78w3Tk74eL+0biuVwSWfrQseEn4/Ms9ul/HXu4aeoD3GbeZp4RshhlGtvUckfeYDuToxQJELDuvmbSu0oWmQXoou6lTgLHkDg==");
  curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, headers);
  
  unsigned int orderQty = 1;
  float price = 1.0f;
  unsigned long long time = 1;
  
  std::string postData = "req={'_msgType':'com.ust.sp.msg.ClientReqMessage','accountID':'M000003482','targetID':'PORT','validate':true,'requestedCount':0,'reqMsgList':[{'_msgType':'com.ust.sharedmsgs.NewOrderMsg','clOrderID':'M000003482Cl14761291601714','side':'BUY','partyID':'M000003482','instID':'203','orderQty':";
  postData.append(std::to_string(orderQty));
  postData.append(",'timeInForce':'DAY','validityUnit':'DAY','validity':1,'orderType':'MARKET','price':");
  postData.append(std::to_string(price));
  postData.append("'clientSendTime':");
  postData.append(std::to_string(time));
  postData.append("}]}&tg=GATE&tp='?'");
  
  curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDS, postData.c_str());
  curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, RestCall::WriteMemoryCallback);
  curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, (void*)&response);
  curl_easy_setopt(curlHandle, CURLOPT_ACCEPT_ENCODING, "gzip");
  */
}

size_t RestCall::WriteMemoryCallback(void* _contents, size_t _size, size_t _nmemb, void* _userp) {
  size_t realsize = _size * _nmemb;
  Response* mem = (Response*)_userp;
  
  mem->memory = (char*)realloc(mem->memory, mem->size + realsize + 1);
  if(mem->memory == NULL) {
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }
  
  memcpy(&(mem->memory[mem->size]), _contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
  
  return realsize;
}

void RestCall::authenticate() {
  CURLcode returnCode = curl_easy_perform(authenticationHandle);
  if (returnCode != CURLE_OK) {
    fprintf(stderr, "AUTHENTICATION: curl_easy_perform() failed: %s\n", curl_easy_strerror(returnCode));
  }
  else {
    response.log();
  }
  
  authenticationToken = response.parseAuthentication();
  response.size = 0;
}

void RestCall::quotes() {
  CURLcode ret = curl_easy_perform(quotesHandle);
  if(ret != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(ret));
  }
  else {
    response.log();
  }
  
  response.parseQuotes();
  response.size = 0;
}

void RestCall::getAvailableBalance() {
  CURLcode ret = curl_easy_perform(availableCashHandle);
  if(ret != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(ret));
  }
  else {
    Model::loggingEnabled = true;
    response.log();
  }
  
  Model::setBuyingPower(response.parseBuyingPower());
  
  response.size = 0;
}

//
// This only needs to be called once a year
//
void RestCall::getAllOpenDays() {
  for (unsigned int month = 1; month <= 12; month++) {
    for (unsigned int day = 1; day <= 31; day++) {
      CURL* allDatesHandle = curl_easy_init();
      
      curl_easy_setopt(allDatesHandle, CURLOPT_WRITEFUNCTION, RestCall::WriteMemoryCallback);
      curl_easy_setopt(allDatesHandle, CURLOPT_WRITEDATA, (void*)&response);
      
      std::string datesUrl = "https://api.robinhood.com/markets/XNYS/hours/2017-";
      if (month < 10) {
        datesUrl.append("0");
        datesUrl.append(std::to_string(month));
      }
      else {
        datesUrl.append(std::to_string(month));
      }
      datesUrl.append("-");
      
      if (day < 10) {
        datesUrl.append("0");
        datesUrl.append(std::to_string(day));
      }
      else {
        datesUrl.append(std::to_string(day));
      }
      datesUrl.append("/");
      
      curl_easy_setopt(allDatesHandle, CURLOPT_URL, datesUrl.c_str());
      curl_easy_perform(allDatesHandle);
      if (response.parseOpenDays()) {
        if (month < 10) {
          std::cout << "0" << month;
        }
        else {
          std::cout << month;
        }
        std::cout << "_";
        
        if (day < 10) {
          std::cout << "0" << day;
        }
        else {
          std::cout << day;
        }
        std::cout << "_2017" << std::endl;
      }
      response.size = 0;
    }
  }
}

void RestCall::mockRestCall(Stock& _stock, const unsigned int& _marketTime) {
  const TimeQuote& quote = _stock.getTestQuote(_marketTime);
  _stock.addTimeToCandles(quote);
}
