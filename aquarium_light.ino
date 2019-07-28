#include <Wire.h>
#include <RTClib.h>
RTC_DS1307 rtc;
#define b 3
#define cw 5
#define rb 6
#define g 9
#define uv 10
#define v 11
#define fan 7
//#define ww 11
byte xB = 100 ;
byte xCW = 24 ;
byte xRB = 100 ;
byte xV =  80 ;
byte xUV = 100 ;
//byte xDR = 10 ;
byte xG = 24 ;
//byte xWW = 100 ;
byte tS = 8 ;
byte tE = 18 ;
byte t ;
byte tm ;
byte xb ;
byte xcw ;
byte xrb ;
byte xv ;
byte xuv ;
//byte xdr ;
byte xg ;
//byte xww ;
byte ts = tS + 1;
byte te = tE - 1;

void setup() {
  Serial.begin(57600);
  pinMode(b, OUTPUT);
  pinMode(cw, OUTPUT);
  pinMode(rb, OUTPUT);
  pinMode(v, OUTPUT);
  pinMode(uv, OUTPUT);
  pinMode(fan, OUTPUT);
  pinMode(g, OUTPUT);
  //pinMode(ww, OUTPUT);
  //digitalWrite(b, LOW);
  //digitalWrite(cw, LOW);
  //digitalWrite(rb, LOW);
  //digitalWrite(uv, LOW);
  //digitalWrite(dr, LOW);
  //digitalWrite(g, LOW);
  Serial.println("Aquarium Controler Started");

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");

    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop() {
  DateTime now = rtc.now();
  t = now.hour() ;
  Serial.println(t);
  if ( (ts <  t) && (t  < te ) ) {
    xb = xB ;
    xcw = xCW ;
    xrb = xRB ;
    xv = xV ;
    xuv = xUV ;
    //xdr = xDR ;
    xg = xG ;
    Serial.println("on");
    xb = map(xb , 0 , 100 , 0 , 255);
    xcw = map(xcw , 0 , 100 , 0 , 255);
    xrb = map(xrb , 0 , 100 , 0 , 255);
    xg = map(xg , 0 , 100 , 0 , 255);
    xuv = map(xuv , 0 , 100 , 0 , 255);
    xv = map(xv , 0 , 100 , 0 , 255);
    //xdr = map(xdr , 0 , 100 , 0 , 255);
    //xww = 50 ;
    digitalWrite(fan, HIGH);
    //digitalWrite(cw, HIGH);
    //digitalWrite(rb, HIGH);
    //digitalWrite(uv, HIGH);
    //digitalWrite(dr, HIGH);
    //digitalWrite(g, HIGH);
  }
  else if ( (tS <=  t) && (t  < ts) ) {
    tm = now.minute();
    xb = up(xB, tm) ;
    xcw = up(xCW, tm) ;
    xrb = up(xRB, tm) ;
    xv = up(xV, tm) ;
    xuv = up(xUV, tm) ;
    //xdr = up(xDR, tm) ;
    xg = up(xG, tm) ;
    //xww = up(xWW, tm) ;
    digitalWrite(fan, HIGH);
    Serial.println("up");
    xb = map(xb , 0 , 100 , 0 , 255);
    xcw = map(xcw , 0 , 100 , 0 , 255);
    xrb = map(xrb , 0 , 100 , 0 , 255);
    xg = map(xg , 0 , 100 , 0 , 255);
    xuv = map(xuv , 0 , 100 , 0 , 255);
    xv = map(xv , 0 , 100 , 0 , 255);
    //xdr = map(xdr , 0 , 100 , 0 , 255);
  }
  else if ( (te <= t ) && (t < tE )  ) {
    tm = now.minute();
    xb = down(xB, tm) ;
    xcw = down(xCW, tm) ;
    xrb = down(xRB, tm) ;
    xv = down(xV, tm) ;
    xuv = down(xUV, tm) ;
    //xdr = down(xDR, tm) ;
    xg = down(xG, tm) ;
    //xww = down(xWW, tm) ;
    digitalWrite(fan, HIGH);
    Serial.println("down");
    xb = map(xb , 0 , 100 , 0 , 255);
    xcw = map(xcw , 0 , 100 , 0 , 255);
    xrb = map(xrb , 0 , 100 , 0 , 255);
    xg = map(xg , 0 , 100 , 0 , 255);
    xuv = map(xuv , 0 , 100 , 0 , 255);
    xv = map(xv , 0 , 100 , 0 , 255);
    //xdr = map(xdr , 0 , 100 , 0 , 255);
  }
  else {
    xb = 0 ;
    xcw = 0 ;
    xrb = 0 ;
    xv = 0 ;
    xuv = 0 ;
    //xdr = 0 ;
    xg = 0 ;
    //xww = 0 ;
    digitalWrite(fan, LOW);
    //digitalWrite(cw, LOW);
    //digitalWrite(rb, LOW);
    //digitalWrite(uv, LOW);
    //digitalWrite(dr, LOW);
    //digitalWrite(g, LOW);
    Serial.println("off");
  }


  analogWrite(b, xb);
  analogWrite(cw, xcw);
  analogWrite(rb, xrb);
  analogWrite(g, xg);
  analogWrite(uv, xuv);
  analogWrite(v, xv);
  //analogWrite(dr, xdr);
  Serial.println(xb);
  Serial.println(xrb);
  Serial.println(xcw);
  Serial.println(xg);
  Serial.println(xuv);
  Serial.println(xv);
  delay(1000);
  t = now.hour();
}
byte up( byte x, byte t ) {
  byte z;
  z = (((x) / 60) * (t));
  return z;
}
byte down( byte x, byte t) {
  byte w;
  w = ((-1) * ((((x) / 60) * (t))) - x);
  return w;
}
