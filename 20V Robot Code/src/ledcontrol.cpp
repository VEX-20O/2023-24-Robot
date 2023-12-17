#include "sylib/sylib.hpp"

class ledcontrol {

    public:
      sylib::Addrled* BackLights;
      sylib::Addrled* FrontLights;
      sylib::Addrled* TailLights;
      sylib::Addrled* IntakeLights;

    ledcontrol(){}

    void defineleds(sylib::Addrled Backlight, sylib::Addrled FrontLight, sylib::Addrled TailLight, sylib::Addrled IntakeLight){
        BackLights = &Backlight;
        FrontLights = &FrontLight;
        TailLights = &TailLight;
        IntakeLights = &IntakeLight;
    }

    void setall(uint32_t ledcolor){
        BackLights->set_all(ledcolor);
        FrontLights->set_all(ledcolor);
        TailLights->set_all(ledcolor);
        IntakeLights->set_all(ledcolor);
    }

    void clear(){
        BackLights->clear();
        FrontLights->clear();
        TailLights->clear();
        IntakeLights->clear();
    }

};