#include <Arduino.h>
#include <../lib/FlexCAN_Library/FlexCAN.h>
#include <MsTimer2.h>

FlexCAN CANbus(1000000);
CAN_message_t msg;
uint16_t rawEncVal;

//              (モータのアドレス, データ長, 中身)
void canbusWrite(uint8_t addr,uint8_t len,uint8_t *message){
  msg.len = len;
  msg.id = 0x140 + addr;
  for (int i = 0; i < len; i++) {
    msg.buf[i] = message[i];
  }
  CANbus.write(msg);
  digitalWrite(LED_BUILTIN,HIGH);
}

void canbusRead(){
  CAN_message_t rxmsg;
  CANbus.read(rxmsg);

  if(rxmsg.buf[0] == 0x90){
    rawEncVal = rxmsg.buf[2];
    rawEncVal += rxmsg.buf[3] << 8;
  }
}

// 一定周期毎に実行
void timerInt(){
  canbusRead();
  uint8_t buf[8] = {0};
  buf[0] = 0x90;
  canbusWrite(1,8,buf);
}

void setup() {
  pinMode(LED_BUILTIN,OUTPUT);

  CANbus.begin();
  Serial.begin(115200);
  
  MsTimer2::set(1, timerInt); //[ms]//0.5msごとでも良さそう。
  MsTimer2::start();
}

void loop() {

  digitalWrite(LED_BUILTIN,LOW);
  delay(200);
  Serial.println(rawEncVal);
}