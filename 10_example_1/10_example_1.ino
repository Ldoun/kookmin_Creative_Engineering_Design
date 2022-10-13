#include <Servo.h>
#define PIN_SERVO 10

Servo myservo;
int cnt = 0;
unsigned long now,t_time;

void setup() {
  run(0);
  Serial.begin(57600);
}

void loop() {
  while(true){
    cnt += 1;
    now = micros();
    run(cnt);
    t_time = micros() - now;
    Serial.print(t_time);
    Serial.print(' ');
    Serial.println(cnt);
    //Serial.println(t_time +':'+cnt);
    delay(500);    
  }
}

void run(int degree){
  myservo.attach(PIN_SERVO); 
  myservo.write(0);
  myservo.write(degree);
}
