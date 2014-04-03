/*
  ==============================================================================

    soundMessage.h
    Created: 24 Mar 2014 3:06:51pm
    Author:  yvan

  ==============================================================================
*/

#ifndef SOUNDMESSAGE_H_INCLUDED
#define SOUNDMESSAGE_H_INCLUDED

#include "sound.hpp"
#include "../templates/messageObject.h"


namespace YSE {
  namespace SOUND {
 
    class messageObject {
    public:
      /** The ID of a message defines how it will be stored in the implementation
      */
      MESSAGE ID;

      /** The data is stored in a union, so to not use more data as needed. Other types
      could be added to this union if needed, but they should not exeed the current
      length (Flt[3]). (Doing so won't be unsafe, but it will affect every message
      used in by all subSystems. So don't.)
      */
      union {
        Bool   boolValue;
        Flt    vecValue[3];
        Flt    floatValue;
        UInt   uintValue;
        void * ptrValue;
        SOUND_INTENT intentValue;
      };
    };
  
  }
}




#endif  // SOUNDMESSAGE_H_INCLUDED
