#pragma once
#include "drive.h"

class Drive;

extern Drive robot;

void default_constants();

#define AUTO1 "Skills"
void Skills();
void DrawAuto1();

#define AUTO2 "Close Desc-Shoot-Over Mid"
void Close_Mid_Score();
void DrawAuto2();

#define AUTO3 "Close Knock Mid-Score"
void Close_Desc_Mid();
void DrawAuto3();

#define AUTO4 "Close Desc-Shoot-Touch"
void Close_Desc_Shoot_Touch();
void DrawAuto4();

#define AUTO5 "Close Score-Desc-Touch"
void Close_Score_Desc_Touch();
void DrawAuto5();

#define AUTO6 "Far Score 4-5"
void Far_Score();
void DrawAuto6();

#define AUTO7 "Far Score 2-Touch"
void Far_Score_Touch();
void DrawAuto7();

#define AUTO8 "Do Nothing"
void Sit();

void Far_Score_MidS();
void TestA();
void VisionChase(float speed, float pturn, float pdrive, vex::vision::signature vis, float timeout, float lungedist);

void drive_test();
void turn_test();
void swing_test();
void full_test();
void odom_test();
void tank_odom_test();
