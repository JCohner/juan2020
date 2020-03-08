#include <ServoESP32.h>
#include <PS4Controller.h>

static const int MRPin = A0; // Right motor PWM (speed)
static const int MLPin = A1; // Left motor PWM (speed)
static const int DPin = 12;

Servo rightMotor;
Servo leftMotor;
Servo drumMotor;

int stop = 1500;
int l = 1500;
int r = 1500;

void receivePacket() { 

  int L_mapped,R_mapped,drum_mapped;
  int lx;

  if(PS4.data.analog.stick.lx < 10 && PS4.data.analog.stick.lx > -10){
    lx = 0;
  }
  else {
    lx = PS4.data.analog.stick.lx;
  }
  
  int L_bm = PS4.data.analog.stick.ly + lx;
  int R_bm = - lx + PS4.data.analog.stick.ly;
  int drum_bm = PS4.data.analog.button.r2;
  
  L_mapped = map(L_bm, 127, -128, 1000, 2000);
  R_mapped = map(R_bm, 127, -128, 1112, 1888);
  drum_mapped = map(drum_bm,0,255,1500,2000);                                    


  /*if(PS4.event.button_down.up){
    l++;
  }
  if(PS4.event.button_down.down){
    l--;
  }
  if(PS4.event.button_down.triangle){
    r++;
  }
  if(PS4.event.button_down.cross){
    r--;
  }*/

  //if(L_mapped < 1525 && L_mapped > 1475) L_mapped = stop;
  //if(R_mapped < 1520 && R_mapped > 1480) R_mapped = stop;
 
  leftMotor.writeMicroseconds(L_mapped);
  rightMotor.writeMicroseconds(R_mapped);
  drumMotor.writeMicroseconds(drum_mapped);

  
    
    
    
    Serial.print("r2 button at ");
    Serial.println(drum_mapped);

}

void controllerConnect() {
  Serial.println("Connected!.");
  PS4.setLed(255,255,255); 
}

void setup() {
  Serial.begin(115200);
  rightMotor.attach(MRPin);
  leftMotor.attach(MLPin);
  drumMotor.attach(DPin);
  //PS4.attach(receivePacket);
  PS4.attachOnConnect(controllerConnect);
  PS4.begin("01:02:03:04:05:67");
}

void loop() {
  if(PS4.isConnected()){
    
    receivePacket();
  }
}
