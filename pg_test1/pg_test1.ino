
//librries used
#include <Arduino.h>
#include <Servo.h>

//pin initialisation
  #define Dir_Front 1
  #define Dir_Rear 2
 
  #define PWM_Front 3
  #define PWM_Rear 4

  #define front_servos 5
  #define rear_servos 6

  #define Green_LED 8
  #define Red_LED 8

// servo initialisation (front,back)
  Servo servo_f;
  Servo servo_r;

void setup() {
  // put your setup code here, to run once: 
  // Rover motors and servos initialisation
  Serial.begin(9600);
  pinMode(Dir_Front,OUTPUT);
  pinMode(Dir_Rear,OUTPUT);
  pinMode(PWM_Front,OUTPUT);
  pinMode(PWM_Rear,OUTPUT);
  pinMode(Green_LED, OUTPUT);
  pinMode(Red_LED, OUTPUT);

  servo_f.attach(front_servos,1019,1981); //for angles between 70° and 200° (with the center being at 135°)
  servo_r.attach(rear_servos,1019,1081); //for angles between 70° and 200° (with the center being at 135°)
  
  //all servo to 135° (looking front) (the write function goes from 0 to 90° but our servo from 0 to 270°)
  // we will replace it by the writemillis function later (need the servos documentation)
  servo_f.writeMicroseconds(1500);
  servo_r.writeMicroseconds(1500);
  

  //motor Dir set to 0 
  digitalWrite(Dir_Front, LOW);
  digitalWrite(Dir_Rear, LOW);
  // PWM set to 0
  analogWrite(PWM_Front, 0);
  analogWrite(PWM_Rear, 0);

  //set the reiciving function

  //check communication
  // if receive communication pr#define ready to receive order and activate green led

  // else pr#define no communication and activate red LED delay 2 second and try reconecting
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //check if arriving data periodically every 50 ms
  
  //gather the datas
  //enter dir value
  //control() 

}

void control(int speed,float angle){
  //front angle only to start
  int AngleMicro= (angle*2000/270) +500;
  servo_f.writeMicroseconds(AngleMicro);
  analogWrite(PWM_Front, speed);
  analogWrite(PWM_Rear, speed);
  
  // in a more complex programm if the delta angle is to big stop the rover and modify the angle

}
