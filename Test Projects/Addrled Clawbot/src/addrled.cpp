    #include "vex.h"
    
    addressable_led::addressable_led(triport::port &port, int32_t max = MAX_LEDS) :
        _index(port.index()),
        _id(port.id()),
        maxled(max <= MAX_LEDS ? max : MAX_LEDS)
      {};

      void addressable_led::clear(color col) {
        for(int i=0;i<maxled;i++) {
          ledbuffer[i] = col;
        }
        set( ledbuffer, 0, maxled, 0);
      }

      void addressable_led::set( uint32_t *pData, uint32_t nOffset, uint32_t nLength, uint32_t options ) {
        vexAdiAddrLedSet( _index, _id, pData, nOffset, nLength, options );

        // make copy if different buffer
        if( pData != ledbuffer ) {
          uint32_t *p = pData;
          for(int i=nOffset;i<nLength && i<maxled;i++)
            ledbuffer[i] = *p++;
        }
      }

      void addressable_led::set(color col) {
        for(int i=0;i<maxled;i++) {
          ledbuffer[i] = col;
        }
      }

      void addressable_led::rotate( int n ) {
          if( abs(n) >= maxled )
            return;

          if( n > 0 ) {
            // make a copy
            memcpy( tmpbuffer, ledbuffer, sizeof(ledbuffer));
            memcpy( &ledbuffer[n], &tmpbuffer[0], (maxled-n)*sizeof(uint32_t) );
            memcpy( &ledbuffer[0], &tmpbuffer[maxled-1-n], (n)*sizeof(uint32_t) );          
          }
          else {
            n = -n;
            memcpy( tmpbuffer, ledbuffer, sizeof(ledbuffer));
            memcpy( &ledbuffer[0], &tmpbuffer[n], (maxled-n)*sizeof(uint32_t) );
            memcpy( &ledbuffer[maxled-n], &tmpbuffer[0], (n)*sizeof(uint32_t) );          
          }
      }

      void addressable_led::flush() {
        set( ledbuffer, 0, maxled, 0);
      }

      int32_t addressable_led::max() {
        return maxled;
      }