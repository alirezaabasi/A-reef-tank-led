#include <SoftPWM.h>
#include <SoftPWM_timer.h>

#include <Wire.h>
#include <RTClib.h>
RTC_DS1307 rtc;
#define b 9
#define cw 8
#define rb 5
#define g 7
#define uv 3
#define v 6
#define fan 10
#define ww 2
#define dr 4
byte xB = 100 ;
byte xCW = 24 ;
byte xRB = 100 ;
byte xV =  100 ;
byte xUV = 100 ;
byte xDR = 24 ;
byte xG = 24 ;
byte xWW = 24 ;
int t ;
byte tm ;
byte xb ;
byte xcw ;
byte xrb ;
byte xv ;
byte xuv ;
byte xdr ;
byte xg ;
byte xww ;
byte xfan ;
int t1 = (8 * 60) ;
int t4 = (19 * 60) ;
int t2 = t1 + 59 ;
int t3 = t4 - 60 ;
int tne = t4 + 60 ;

void setup() {
  Serial.begin(57600);
  SoftPWMBegin();
  SoftPWMSet(b, 0);
  SoftPWMSet(cw, 0);
  SoftPWMSet(rb, 0);
  SoftPWMSet(v, 0);
  SoftPWMSet(uv, 0);
  SoftPWMSet(g, 0);
  SoftPWMSet(ww, 0);
  SoftPWMSet(dr, 0);
  SoftPWMSet(fan, 0);
  SoftPWMSetFadeTime(b, 2000, 1000);
  SoftPWMSetFadeTime(cw, 2000, 1000);
  SoftPWMSetFadeTime(rb, 2000, 1000);
  SoftPWMSetFadeTime(v, 2000, 1000);
  SoftPWMSetFadeTime(uv, 2000, 1000);
  SoftPWMSetFadeTime(g, 2000, 1000);
  SoftPWMSetFadeTime(ww, 2000, 1000);
  SoftPWMSetFadeTime(dr, 2000, 1000);
  SoftPWMSetFadeTime(fan, 2000, 1000);
  //pinMode(ww, OUTPUT);
  Serial.println("Aquarium Controler Started");

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  /* if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");

     rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }*/
}

void loop() {
  /*if ( Serial.available() ) {
    char p = Serial.read ();
    if ( p = 's' ) {
     settime();
    }
    }*/
  DateTime now = rtc.now();
  tm = now.minute();
  //byte w = now.hour() ;
  //Serial.println(w);
  t = now.hour() * 60 + tm ;
  //Serial.println(t);
  if ( (t1 <  t) && (t  <= t2 ) ) {
    xb = up(xB, t) ;
    xrb = up(xRB, t) ;
    xv = up(xV, t) ;
    xuv = up(xUV, t) ;
    xcw = 0;
    xg = 0;
    xww = 0;
    xdr = 0;
    xfan = 50 ;

    //Serial.println("up");

  }
  else if ( (t2 <  t) && (t  <= t3) ) {
    xb = xB ;
    xcw = xCW ;
    xrb = xRB ;
    xv = xV ;
    xuv = xUV ;
    xdr = xDR ;
    xww = xWW ;
    xg = xG ;
    xfan = 100 ;
    //Serial.println("on");

    digitalWrite(fan, HIGH);
  }
  else if ( (t3 < t ) && (t <= t4 )  ) {
    xb = down(xB, t) ;
    xrb = down(xRB, t) ;
    xv = down(xV, t) ;
    xuv = down(xUV, t) ;
    xcw = 0;
    xg = 0;
    xdr = 0;
    xww = 0;
    xfan = 50 ;
    //Serial.println("down");

  }
  else if ( ( t4 < t ) && ( t <= tne ) )  {
    xb = 10;
    xcw = 0 ;
    xrb = 0 ;
    xv = 0 ;
    xuv = 0 ;
    xdr = 0 ;
    xg = 0 ;
    xww = 0 ;
    xfan = 0 ;

  }
  else {
    xb = 0 ;
    xcw = 0 ;
    xrb = 0 ;
    xv = 0 ;
    xuv = 0 ;
    xdr = 0 ;
    xg = 0 ;
    xww = 0 ;
    xfan = 0 ;
    //digitalWrite(cw, LOW);
    //digitalWrite(rb, LOW);
    //digitalWrite(uv, LOW);
    //digitalWrite(dr, LOW);
    //digitalWrite(g, LOW);
    //Serial.println("off");
  }

  xb = map(xb , 0 , 100 , 0 , 255);
  xcw = map(xcw , 0 , 100 , 0 , 240);
  xrb = map(xrb , 0 , 100 , 0 , 255);
  xg = map(xg , 0 , 100 , 0 , 110);
  xuv = map(xuv , 0 , 100 , 0 , 255);
  xv = map(xv , 0 , 100 , 0 , 110);
  xww = map(xww , 0 , 100 , 0 , 40);
  xdr = map(xdr , 0 , 100 , 0 , 70);
  xfan = map(xfan , 0 , 100 , 0 , 215);
  SoftPWMSet(b, xb);
  SoftPWMSet(cw, xcw);
  SoftPWMSet(rb, xrb);
  SoftPWMSet(g, xg);
  SoftPWMSet(uv, xuv);
  SoftPWMSet(v, xv);
  SoftPWMSet(ww, xww);
  SoftPWMSet(dr, xdr);
  SoftPWMSet(fan, xfan);
  //Serial.println(xb);
  //Serial.println(xrb);
  //Serial.println(xcw);
  //Serial.println(xg);
  //Serial.println(xuv);
  //Serial.println(xv);
  //delay(1000);
  //t = now.hour();
}


byte up( byte x, byte t ) {
  byte z;
  z = ((((x) / 60) * (t - t1 ))  );
  return z;
}
byte down( byte x, byte t) {
  byte w;
  w = (((-1) * (((x) / 60) * (t - t3))) + (x) );
  return w;
}
