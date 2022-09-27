#define PIN_LED 7

int duty = 0;
int period = 0;
int flag = 1;

void setup() {
  Serial.begin(119200);
  while (!Serial){
     ;
  }
  pinMode(PIN_LED, OUTPUT);
  duty=0;
  period = set_period(10);
  flag = 1;
}

void loop() {
  // put your main code here, to run repeatedly:
  while(1){  
    Serial.println(duty);
    digitalWrite(PIN_LED, 0);
    delayMicroseconds(period * (duty / 100.0));
    digitalWrite(PIN_LED,1);
    delayMicroseconds(period - (period * (duty / 100.0)));
    if(duty == 0){
      flag = 1;
    }
    else if(duty == 100){
      flag = -1;
    }
    duty = set_duty(duty, flag);
  }
}

int set_period(int period){
  return period * 1000;
}

int set_duty(int duty, int reverse){
  return duty + reverse;
}
