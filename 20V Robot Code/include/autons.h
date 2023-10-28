#pragma once
#include "LAH/drive.h"

class Drive;

extern Drive chassis;

void default_constants();

void OppSide_Desc_Mid();
void Opp_WP();
void OppSide_Desc_Score();
void SameSide_Score();
void SameSide_NoMid();
void Sit();

void drive_test();
void turn_test();
void swing_test();
void full_test();
void odom_test();
void tank_odom_test();