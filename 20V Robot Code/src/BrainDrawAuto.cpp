#include "vex.h"

//Brain Screen is 480x272 pixels, origin is top left

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
  Brain.Screen.drawLine(480-65, 200-50, 480-100-15, 200);
  Brain.Screen.drawRectangle(150, 150, 480-300, 15);
}
void DrawAuto1(){DrawField();
  Brain.Screen.setPenColor(red);
  Brain.Screen.drawRectangle(115, 200, 30, -30);
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
  Brain.Screen.setPenColor(red);
  Brain.Screen.drawRectangle(115, 200, 30, -30);
  Brain.Screen.setPenColor(green);
  Brain.Screen.drawRectangle(50+15, 150, 16, 16);
  Brain.Screen.drawRectangle(100, 200-15, 15, -15);
  Brain.Screen.setPenColor(white);
}
void DrawAuto4(){DrawField();
  DrawDiamond(115, 30, red, 200);
  DrawDiamond(115,16,green,200-12);
  Brain.Screen.setPenColor(green);
  Brain.Screen.drawRectangle(50+15, 150, 16, 16);
  Brain.Screen.setPenColor(white);
}
void DrawAuto5(){DrawField();
  Brain.Screen.setPenColor(red);
  Brain.Screen.drawRectangle(115, 200, 30, -30);
  Brain.Screen.setPenColor(green);
  Brain.Screen.drawRectangle(50+15+50, 200, 16, -16);
  Brain.Screen.drawRectangle(115, 200-15, 15, -15);
  Brain.Screen.setPenColor(white);
}
void DrawAuto6(){DrawField();
  Brain.Screen.setPenColor(red);
  Brain.Screen.drawRectangle(300, 195, 30, -30);
  Brain.Screen.setPenColor(green);
  Brain.Screen.drawRectangle(50+15+200, 150, 16, 16);
  Brain.Screen.drawRectangle(250, 200-15, 15, -15);
  Brain.Screen.setPenColor(white);
}
void DrawAuto7(){DrawField();
  Brain.Screen.setPenColor(red);
  Brain.Screen.drawRectangle(300, 195, 30, -30);
  Brain.Screen.setPenColor(green);
  Brain.Screen.drawRectangle(50+15+200, 150, 16, 16);
  Brain.Screen.drawRectangle(250, 200-15, 15, -15);
  Brain.Screen.setPenColor(white);
}