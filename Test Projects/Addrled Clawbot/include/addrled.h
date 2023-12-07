/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vex_addrled.h                                             */
/*    Author:       James Pearman                                             */
/*    Created:      1 Sept 2022                                               */
/*    Description:  Class for addressable led on 3wire expander               */
/*                                                                            */
/*----------------------------------------------------------------------------*/
//
#pragma once
#include "vex.h"

extern "C" {
  // private addressable LED API
  int32_t  vexAdiAddrLedSet( uint32_t index, uint32_t port, uint32_t *pData, uint32_t nOffset, uint32_t nLength, uint32_t options );
}

using namespace vex;

// A class for the addressable led
class addressable_led {
    public:
      static const int32_t MAX_LEDS = 64;

    private:      
      uint32_t maxled = MAX_LEDS;
      uint32_t ledbuffer[MAX_LEDS];
      uint32_t tmpbuffer[MAX_LEDS];
      int32_t _index;
      int32_t _id;
  
    public:
      addressable_led(triport::port &port, int32_t max);

      void clear( color col = color(0x000000) );

      void set( uint32_t *pData, uint32_t nOffset, uint32_t nLength, uint32_t options );

      void set( color col = color(0x000000) );

      void rotate( int n );

      void flush();

      int32_t max();
};
