#pragma once
#include "drive.h"

class Drive;

extern Drive robot;

void default_constants();

#define AUTO1 "Skills"
void Skills();

#define AUTO2 "Close Knock Mid-Score"
void Close_Mid_Score();

#define AUTO3 "Close Desc-Mid Over"
void Close_Desc_Mid();

#define AUTO4 "Close Desc-Shoot-Touch"
void Close_Desc_Shoot_Touch();

#define AUTO5 "Close Score-Desc-Touch"
void Close_Score_Desc_Touch();

#define AUTO6 "Far Score 3"
void Far_Score();

#define AUTO7 "Far Score 2-Touch"
void Far_Score_Touch();

#define AUTO8 "Do Nothing"
void Sit();

void drive_test();
void turn_test();
void swing_test();
void full_test();
void odom_test();
void tank_odom_test();