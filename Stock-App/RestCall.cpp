//
//  RestCall.cpp
//  Stock-App
//
//  Created by Matt Wood on 10/15/16.
//  Copyright © 2016 MattWood. All rights reserved.
//

#include <stdlib.h>
#include <string.h>

#include "RestCall.hpp"

MemoryChunk RestCall::memoryChunk;
CURL* RestCall::curlHandle = NULL;

void RestCall::init() {
  memoryChunk.memory = (char*)malloc(1);
  memoryChunk.size = 0;
  
  curlHandle = curl_easy_init();
  
  curl_easy_setopt(curlHandle, CURLOPT_CUSTOMREQUEST, "POST");
  curl_easy_setopt(curlHandle, CURLOPT_URL, "https://webux.ustocktrade.com/res");
  
  struct curl_slist* headers = NULL;
  headers = curl_slist_append(headers, "x-auth-token: bLYU97hV06hJlwzERdn8E78w3Tk74eL+0biuVwSWfrQseEn4/Ms9ul/HXu4aeoD3GbeZp4RshhlGtvUckfeYDuToxQJELDuvmbSu0oWmQXoou6lTgLHkDg==");
  curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, headers);
  
  curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDS, "req={'_msgType':'com.ust.sp.msg.ClientReqMessage','accountID':'M000003482','validate':true,'requestedCount':0,'reqMsgList':[{'_msgType':'com.ust.sharedmsgs.feed.QuoteReq','instruments':['11','72','76','86','89','203','220','246','287','335','359','377','416','426','431','490','534','537','642','736','823','866','914','1059','1155','1181','1202','1223','1232','1310','1379','1394','1405','1434','1465','1615','1636','1657','1837','1856','1917','2006','2007','2023','2051','2102','2117','2145','2280','2406','2564','2606','2773','2776','2781','2782','2791','2828','2885','2895','3006','3050','3111','3150','3164','3167','3170','3289','3394','3453','3460','3502','3536','3609','3624','3660','3670','3739','3820','3842','3865','3955','4060','4118','4278','4337','4507','4583','4624','4670','4695','4696','4698','4699','4750','4804','4827','4866','4881','4908','4920','4937','4954','4955','4982','4990','5003','5015','5063','5089','5138','5139','5145','5146','5185']}]}&tg=MDGATE&tp='?'");
  curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, RestCall::WriteMemoryCallback);
  curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, (void*)&memoryChunk);
  curl_easy_setopt(curlHandle, CURLOPT_ACCEPT_ENCODING, "gzip");
}

size_t RestCall::WriteMemoryCallback(void* _contents, size_t _size, size_t _nmemb, void* _userp) {
  size_t realsize = _size * _nmemb;
  MemoryChunk* mem = (MemoryChunk*)_userp;
  
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

void RestCall::quotes() {
  CURLcode ret = curl_easy_perform(curlHandle);
  if(ret != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(ret));
  }
  else {
    memoryChunk.log();
  }
  
  memoryChunk.parse();
}
