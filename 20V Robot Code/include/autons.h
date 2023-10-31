#pragma once
#include "drive.h"

class Drive;

extern Drive robot;

void default_constants();

void Close_Mid_Score();
void Close_Desc_Mid();
void Close_Desc_Shoot_Touch();
void Close_Score_Desc_Touch();

void Far_Score();
void Far_Score_Touch();

void Sit();

void drive_test();
void turn_test();
void swing_test();
void full_test();
void odom_test();
void tank_odom_test();