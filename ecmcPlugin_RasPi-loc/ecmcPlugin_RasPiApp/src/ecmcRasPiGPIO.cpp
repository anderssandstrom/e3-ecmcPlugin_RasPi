/*************************************************************************\
* Copyright (c) 2019 European Spallation Source ERIC
* ecmc is distributed subject to a Software License Agreement found
* in file LICENSE that is included with this distribution. 
*
*  ecmcRasPiGPIO.cpp
*
*  Created on: Mar 22, 2020
*      Author: anderssandstrom
*      Credits to  https://github.com/sgreg/dynamic-loading 
*
\*************************************************************************/

// Needed to get headers in ecmc right...
#define ECMC_IS_PLUGIN

#include "ecmcRasPiGPIO.h"
#include "ecmcPluginClient.h"

// Use ecmcPluginClient.h interface
double getSampleRate() {
    
  return getEcmcSampleRate();
}

// Use ecmcPluginClient.h interface
void* getAsynPort() {
  return getEcmcAsynPortDriver();
}