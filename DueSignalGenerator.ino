#include <Arduino.h>

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = DAC0; // Output generated signal 1
const int analogOutPin2 = DAC1; // Output generated signal 2

int v_trap[512];
int v_tria[512];
int v_sin[512];
int v_ecg[512];

void setup();
void loop();
void setup() {
  int y=0;
  int z=0;
  int q=75;
  int P0=75, P1=20, P2=50, P3=40, P=15;
  int Q1=10, Q=25;
  int R1=45, R=150;
  int S1=30, S2=10, S=170;
  int T1=50, T2=100, T3=125, T=35;
  for (int ind = 0; ind <= 511; ind ++) {

    v_trap[ind] = y;
    v_tria[ind] = z;
    v_ecg[ind] = q;

    float angle_rad = ind * M_PI / 256;
    v_sin[ind] = 127+128*sin(angle_rad);

    if (ind<128) { y+=2; z++; }
    else if (ind<256) { y=255; z++; }
    else if (ind<384) { y-=2; z--; }
    else if (ind<512) { y=0; z--; }

    if (ind<P1) q=P0;
    else if (ind<P1+P2) q=P0+P*(-sin(10*M_PI/(P2+20))+sin((10+ind-P1)*M_PI/(P2+20)));
    else if (ind<P1+P2+P3) q=P0;
    else if (ind<P1+P2+P3+Q1) q=P0-Q*(ind-P1-P2-P3)/Q1;
    else if (ind<P1+P2+P3+Q1+R1) q=P0-Q+R*(ind-P1-P2-P3-Q1)/R1;
    else if (ind<P1+P2+P3+Q1+R1+S1) q=P0-Q+R-S*(ind-P1-P2-P3-Q1-R1)/S1;
    else if (ind<P1+P2+P3+Q1+R1+S1+S2) q=P0-Q+R-S+(Q-R+S)*(ind-P1-P2-P3-Q1-R1-S1)/S2;
    else if (ind<P1+P2+P3+Q1+R1+S1+S2+T1) q=P0;
    else if (ind<P1+P2+P3+Q1+R1+S1+S2+T1+T2) q=P0+T*(-sin(15*M_PI/(T2+30))+sin((15+ind-P1-P2-P3-Q1-R1-S1-S2-T1)*M_PI/(T2+30)));
    else q=P0;
  }
}

int x = 0;

void loop() {
  analogWrite(analogOutPin, v_sin[x]);
  analogWrite(analogOutPin2, v_ecg[x]);
  x++; if (x>=512) x=0;
}
