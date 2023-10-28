/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Program:      20V Over Under 2023-34 Code                               */
/*    Author:       Eric Lind                                                 */
/*    Created:      10/13/23                                                  */
/*    Description:  ...                                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/
//

#pragma once
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "v5.h"
#include "v5_vcs.h"

#include "robot-config.h"
#include "odom.h"
#include "drive.h"
#include "util.h"
#include "PID.h"
#include "autons.h"

const int   v_screen_origin_x = 150;
const int   v_screen_origin_y = 20;
const int   v_screen_width    = 316;
const int   v_screen_height   = 212;

#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)