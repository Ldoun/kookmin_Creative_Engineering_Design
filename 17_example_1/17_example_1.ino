#include <Servo.h>

// Arduino pin assignment

#define PIN_POTENTIOMETER 0 // Potentiometer at Pin A3
// Add IR Sensor Definition Here !!!
#define PIN_SERVO 10
#define LED_PIN 9

#define _DUTY_MIN 553  // servo full clock-wise position (0 degree)
#define _DUTY_NEU 1476 // servo neutral position (90 degree)
#define _DUTY_MAX 2399 // servo full counter-clockwise position (180 degree)

#define LOOP_INTERVAL 20   // Loop Interval (unit: msec)
#define _DIST_MIN 100.0   // minimum distance to be measured (unit: mm)
#define _DIST_MAX 250.0 
#define _EMA_ALPHA 0.1

Servo myservo;
unsigned long last_loop_time;   // unit: msec

float dist_ema, dist_raw, dist_prev = 0; 
void setup()
{
  myservo.attach(PIN_SERVO); 
  myservo.writeMicroseconds(_DUTY_NEU);
  
  Serial.begin(2000000);
}

void loop()
{
  unsigned long time_curr = millis();
  int a_value, duty;

  // wait until next event time
  if (time_curr < (last_loop_time + LOOP_INTERVAL))
    return;
  last_loop_time += LOOP_INTERVAL;

  // Remove Next line !!!
  a_value = analogRead(PIN_POTENTIOMETER);
  // Read IR Sensor value !!!
  // Convert IR sensor value into distance !!!
  // we need distance range filter here !!!
  // we need EMA filter here !!!

  //dist_raw = ((a_value -  0) * (80 -  10)) / (1024 - 0) + 10
  dist_raw = (6762.0/(a_value-9)-4.0)*10.0 - 60.0;
  if (dist_raw < _DIST_MIN) {
    dist_raw = dist_prev; 
    digitalWrite(LED_PIN, 1);
  } else if (dist_raw > _DIST_MAX) {
    dist_raw = dist_prev;       
    digitalWrite(LED_PIN, 1);
  } else {
    dist_prev = dist_raw;
    digitalWrite(LED_PIN, 0);
  }

  // Apply ema filter here  
  dist_ema  = (_EMA_ALPHA*dist_raw) + ((1-_EMA_ALPHA)*dist_ema);
  duty = _DUTY_MIN + ((dist_ema - 100.0)/ 150.0) * (_DUTY_MAX - _DUTY_MIN);
  
  myservo.writeMicroseconds(duty);

  // print IR sensor value, distnace, duty !!!
  //Serial.print("a_value:"); Serial.print(a_value);
  Serial.print(",dist_raw:"); Serial.print(dist_raw);
  Serial.print(",dist:"); Serial.print(dist_ema);
  Serial.print(",Servo:"); Serial.print(myservo.read());  
  Serial.println(" ");
}
