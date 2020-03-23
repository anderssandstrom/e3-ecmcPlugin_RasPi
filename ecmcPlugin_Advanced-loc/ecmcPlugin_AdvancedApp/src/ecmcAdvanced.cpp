/*************************************************************************\
* Copyright (c) 2019 European Spallation Source ERIC
* ecmc is distributed subject to a Software License Agreement found
* in file LICENSE that is included with this distribution. 
*
*  ecmcAdvanced.cpp
*
*  Created on: Mar 22, 2020
*      Author: anderssandstrom
*      Credits to  https://github.com/sgreg/dynamic-loading 
*
\*************************************************************************/
#include "ecmcPluginDataRefs.h"
#include "ecmcAdvanced.h"

double GetSampleRate(void* ecmcRefs) {
  printf("GetSampleRate()\n");
  if(ecmcRefs) {
    ecmcPluginDataRefs* dataFromEcmc = (ecmcPluginDataRefs*)ecmcRefs;
    return dataFromEcmc->sampleTimeMS;
  }
  return -1;
}
