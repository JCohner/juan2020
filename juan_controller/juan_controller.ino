#include <ServoESP32.h>
#include <PS4Controller.h>
#include <ps4_int.h>

static const int MRPin = A0; // Right motor PWM (speed)
static const int MLPin = A1; // Left motor PWM (speed)
int stop = 92;
Servo rightMotor;
Servo leftMotor;

void receivePacket() {
  int lposDegrees = map(PS4.data.analog.stick.ly, -128, 127, 44, 142);
  int rposDegrees = map(PS4.data.analog.stick.ry, -128, 127, 44, 142);
  if(lposDegrees < 97 && lposDegrees > 87) lposDegrees = stop;
  if(rposDegrees < 97 && rposDegrees > 87) rposDegrees = stop;
  leftMotor.write(lposDegrees);
  rightMotor.write(rposDegrees);
}

void controllerConnect() {
  Serial.println("Connected!.");
  PS4.setLed(255,255,255);
}

void setup() {
  Serial.begin(115200);
  rightMotor.attach(MRPin);
  leftMotor.attach(MLPin);
  PS4.attach(receivePacket);
  PS4.attachOnConnect(controllerConnect);
  PS4.begin("01:02:03:04:05:66");
}

void loop() {
    if(PS4.isConnected()) {
      if ( PS4.event.analog_move.stick.ly ) {
          Serial.print("Left Stick y at ");
          Serial.println(PS4.data.analog.stick.lx, DEC);
      }

     
    }
}
