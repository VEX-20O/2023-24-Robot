#include "vex.h"

//480x272
  //starting bottom x coord, side length, color, starting bottom y coord
void DrawDiamond(int bl,int leng, color col, int y){
  int rx, ry, lx, ly, tmx, tmy;
  rx = bl+leng*cos(to_rad(45));
  ry = y-leng*sin(to_rad(45));
  tmx = rx-leng*cos(to_rad(45));
  tmy = ry-leng*sin(to_rad(45));
  lx = bl - leng*cos(to_rad(45));
  ly = ry;
  Brain.Screen.setPenColor(col);
  Brain.Screen.drawLine(bl,y, rx,ry);
  Brain.Screen.drawLine(rx,ry,tmx,tmy);
  Brain.Screen.drawLine(tmx,tmy,lx,ly);
  Brain.Screen.drawLine(lx,ly,bl,y);

}

void DrawField(){
  Brain.Screen.setPenColor(white);
  Brain.Screen.drawRectangle(50,200,480-100,15);
  Brain.Screen.drawRectangle(50, 200, 15, -100);
  Brain.Screen.drawLine(65, 200-50, 50+15+50, 200);
  Brain.Screen.drawRectangle(480-100+50, 200, -15, -100);
  Brain.Screen.drawLine(480-65, 200-50, 480-150, 200);
  Brain.Screen.drawRectangle(150, 150, 480-300, 15);
}
void DrawAuto1(){DrawField();
  Brain.Screen.setPenColor(red);
  Brain.Screen.drawRectangle(115, 180, 30, 30);
  Brain.Screen.setPenColor(white);
}
void DrawAuto2(){DrawField();
  DrawDiamond(115, 30, red, 200);
  DrawDiamond(115,16,green,200-12);
  Brain.Screen.setPenColor(green);
  Brain.Screen.drawRectangle(50+15, 150, 16, 16);
  Brain.Screen.setPenColor(white);
}
void DrawAuto3(){DrawField();

}
void DrawAuto4(){DrawField();

}
void DrawAuto5(){DrawField();

}
void DrawAuto6(){DrawField();

}
void DrawAuto7(){DrawField();

}