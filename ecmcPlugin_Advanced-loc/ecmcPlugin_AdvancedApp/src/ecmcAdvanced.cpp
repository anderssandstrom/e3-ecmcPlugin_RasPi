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

// read rt sample time 
double getSampleRate(void* ecmcRefs) {
  printf("\n##########GetSampleRate()####################\n");
  if(ecmcRefs) {
    ecmcPluginDataRefs* dataFromEcmc = (ecmcPluginDataRefs*)ecmcRefs;
    // call report()!    
    return dataFromEcmc->sampleTimeMS;
  }
  return -1;
}

// Demo simple use of asynPort. Most ecmc data can be accessed from asynPort 
void useAsynPort(void* ecmcRefs) {
  printf("\n##########useAsynPort()####################\n");
  if(ecmcRefs) {
    ecmcPluginDataRefs* dataFromEcmc = (ecmcPluginDataRefs*)ecmcRefs;
    // call report()!
    dataFromEcmc->ecmcAsynPort->report(stdout,3);
  }
  return;
}
