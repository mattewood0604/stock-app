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
  std::cout << quotesSymbols << std::endl;
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

void RestCall::order(const Stock& _stock, const std::string& _type, const unsigned int& _quantity, const float& _price) {
  CURL* buyHandle = curl_easy_init();
  
  curl_easy_setopt(buyHandle, CURLOPT_CUSTOMREQUEST, "POST");
  curl_easy_setopt(buyHandle, CURLOPT_URL, "https://api.robinhood.com/orders/");
  
  struct curl_slist* headers = NULL;
  headers = curl_slist_append(headers, "Accept: application/json");
  std::string authorization = "Authorization: Token ";
  if (!authenticationToken.size()) {
    std::cout << "Error: Authentication Token NULL in initializeAvailableCashHandle" << std::endl;
  }
  authorization.append(authenticationToken);
  headers = curl_slist_append(headers, authorization.c_str());
  curl_easy_setopt(buyHandle, CURLOPT_HTTPHEADER, headers);
  
  std::string postFields = "account=";
  postFields.append(accountUrl);
  postFields.append("&instrument=");
  postFields.append(_stock.instrumentUrl);
  postFields.append("&symbol=");
  postFields.append(_stock.symbol);
  postFields.append("&type=market&time_in_force=gtc&trigger=immediate");
  postFields.append("&quantity=");
  postFields.append(std::to_string(_quantity));
  postFields.append("&side=");
  postFields.append(_type);
  postFields.append("&price=");
  postFields.append(std::to_string(_price));
  
  curl_easy_setopt(buyHandle, CURLOPT_POSTFIELDS, postFields.c_str());
  curl_easy_setopt(buyHandle, CURLOPT_WRITEFUNCTION, RestCall::WriteMemoryCallback);
  curl_easy_setopt(buyHandle, CURLOPT_WRITEDATA, (void*)&response);
  
  CURLcode returnCode = curl_easy_perform(buyHandle);
  if (returnCode != CURLE_OK) {
    fprintf(stderr, "buy %s: curl_easy_perform() failed: %s\n", _stock.symbol.c_str(), curl_easy_strerror(returnCode));
  }
  else {
    Model::loggingEnabled = true;
    response.log();
  }
  
  response.size = 0;
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

std::string RestCall::urlForStockSymbol(const std::string& _symbol) {
  CURL* stockIdHandle = curl_easy_init();
  
  std::string stockInfoUrl = "https://api.robinhood.com/instruments/?symbol=";
  stockInfoUrl.append(_symbol);
  
  curl_easy_setopt(stockIdHandle, CURLOPT_URL, stockInfoUrl.c_str());
  
  curl_easy_setopt(stockIdHandle, CURLOPT_WRITEFUNCTION, RestCall::WriteMemoryCallback);
  curl_easy_setopt(stockIdHandle, CURLOPT_WRITEDATA, (void*)&response);
  
  CURLcode returnCode = curl_easy_perform(stockIdHandle);
  if (returnCode != CURLE_OK) {
    fprintf(stderr, "idForStockSymbol %s: curl_easy_perform() failed: %s\n", _symbol.c_str(), curl_easy_strerror(returnCode));
  }
  else {
    response.log();
  }
  
  std::string url = "https://api.robinhood.com/instruments/";
  url.append(response.parseUrlForStock());
  url.append("/");
  response.size = 0;
  return url;
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
    Model::loggingEnabled = true;
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

unsigned int RestCall::getVolumeForStockSymbol(const std::string &_symbol) {
  CURL* stockFundamentalsHandle = curl_easy_init();
  
  std::string stockFundamentalsUrl = "https://api.robinhood.com/fundamentals/";
  stockFundamentalsUrl.append(_symbol);
  stockFundamentalsUrl.append("/");
  
  curl_easy_setopt(stockFundamentalsHandle, CURLOPT_URL, stockFundamentalsUrl.c_str());
  
  curl_easy_setopt(stockFundamentalsHandle, CURLOPT_WRITEFUNCTION, RestCall::WriteMemoryCallback);
  curl_easy_setopt(stockFundamentalsHandle, CURLOPT_WRITEDATA, (void*)&response);
  
  CURLcode returnCode = curl_easy_perform(stockFundamentalsHandle);
  if (returnCode != CURLE_OK) {
    fprintf(stderr, "getVolumeForStockSymbol %s: %s\n curl_easy_perform() failed: %s\n", _symbol.c_str(), stockFundamentalsUrl.c_str(), curl_easy_strerror(returnCode));
  }
  else {
    response.log();
  }
  
  unsigned int volume = response.parseAverageVolume();
  response.size = 0;
  return volume;
}

void RestCall::instruments() {
  CURL* instrumentsHande = curl_easy_init();
  
  std::string instrumentsURL = "https://api.robinhood.com/instruments/";
  
  curl_easy_setopt(instrumentsHande, CURLOPT_URL, instrumentsURL.c_str());
  
  curl_easy_setopt(instrumentsHande, CURLOPT_WRITEFUNCTION, RestCall::WriteMemoryCallback);
  curl_easy_setopt(instrumentsHande, CURLOPT_WRITEDATA, (void*)&response);
  
  CURLcode returnCode = curl_easy_perform(instrumentsHande);
  if (returnCode != CURLE_OK) {
    fprintf(stderr, "instruments: curl_easy_perform() failed: %s\n", curl_easy_strerror(returnCode));
  }
  else {
    response.log();
  }
  
  unsigned int total = 0;
  unsigned int i = 1;
  std::string nextUrl = response.nextUrlForInstruments();
  while(nextUrl.size() > 0) {
    //nextUrl.erase(std::remove(nextUrl.begin(), nextUrl.end(), '\\'), nextUrl.end());
    std::cout << "\n" << nextUrl << "\n" << std::endl;
    
    std::vector<std::string> allSymbols = response.getAllSymbolsFromInstruments();
    for (unsigned int i = 0; i < allSymbols.size(); i++) {
      unsigned int volume = RestCall::getVolumeForStockSymbol(allSymbols[i]);
      if (volume >= 5000000) {
        std::cout << allSymbols[i] << ": " << volume << std::endl;
      }
    }
    total += allSymbols.size();
    response.size = 0;
    
    instrumentsHande = curl_easy_init();
    
    curl_easy_setopt(instrumentsHande, CURLOPT_URL, nextUrl.c_str());
    
    curl_easy_setopt(instrumentsHande, CURLOPT_WRITEFUNCTION, RestCall::WriteMemoryCallback);
    curl_easy_setopt(instrumentsHande, CURLOPT_WRITEDATA, (void*)&response);
    
    returnCode = curl_easy_perform(instrumentsHande);
    if (returnCode != CURLE_OK) {
      fprintf(stderr, "instruments: curl_easy_perform() failed: %s\n", curl_easy_strerror(returnCode));
    }
    else {
      response.log();
    }
    
    nextUrl = response.nextUrlForInstruments();
    i++;
  }
  
  std::cout << i << "  " << total << std::endl;
}

void RestCall::mockRestCall(Stock& _stock, const unsigned int& _marketTime) {
  TimeQuote& quote = _stock.getTestQuote(_marketTime);
  Model::loggingEnabled = true;
  if (_stock.testQuotes.size() == 0) {
    return;
  }
  
  _stock.addTimeToCandles(quote);
}
