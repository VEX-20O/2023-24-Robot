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
#include "LAH/odom.h"
#include "LAH/drive.h"
#include "LAH/util.h"
#include "LAH/PID.h"
#include "autons.h"

#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)