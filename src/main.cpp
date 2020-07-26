#include <Arduino.h>
#include <../lib/FlexCAN_Library/FlexCAN.h>
#include <MsTimer2.h>

FlexCAN CANbus(1000000);
CAN_message_t msg;

void timerInt(){
  msg.len = 8;
  msg.id = 0x1FF;

  msg.buf[0] = 0;
  msg.buf[1] = 1;
  msg.buf[2] = 2;
  msg.buf[3] = 4;
  msg.buf[4] = 8;
  msg.buf[5] = 16;
  msg.buf[6] = 32;
  msg.buf[7] = 64;

  CANbus.write(msg);
  digitalWrite(LED_BUILTIN,HIGH);
}

void setup() {
  pinMode(LED_BUILTIN,OUTPUT);

  CANbus.begin();
  
  MsTimer2::set(10, timerInt); //[ms]
  MsTimer2::start();
}

void loop() {

  digitalWrite(LED_BUILTIN,LOW);
  delay(200);
}