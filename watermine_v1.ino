#define PIN_TRIGGER 8 
#define PIN_ECHO    2
#define PIN_MOTOR 3
#define PIN_BUTTON 4
#define PIN_LED 5// disarmed: led is on
const int SENSOR_MAX_RANGE = 300; // max senor range in cm
unsigned long duration;
unsigned int distance;
int wert;
int taster;
int tasterstate=0;
int killswitch=1;
void setup(){
  Serial.begin(9600);
  pinMode(PIN_TRIGGER, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_MOTOR, OUTPUT);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  Serial.println("#### (c) Paul Treier 2021 ####"
}

void loop(){
  digitalWrite(PIN_TRIGGER, LOW);
  delayMicroseconds(2);

  digitalWrite(PIN_TRIGGER, HIGH);
  delayMicroseconds(10);

  duration = pulseIn(PIN_ECHO, HIGH);
  distance = duration/58;

  if (distance > SENSOR_MAX_RANGE || distance <= 0){//debug with serial monitor
    Serial.println("Sensor range!");
  } else {
    Serial.println("Distance to object: " + String(distance) + " cm");
  }

  taster = digitalRead(PIN_BUTTON);//check if button is pressed
  
  if(tasterstate==0){//killswitch
    if(taster==0){
      digitalWrite(PIN_LED,1);
      delay(1000);
      digitalWrite(PIN_LED,0);
      delay(500);
      killswitch=0;
      tasterstate=1;
      digitalWrite(PIN_LED,1);
    }
  }else if(tasterstate==1){
    if(taster==0){
      digitalWrite(PIN_LED, 0);
      killswitch=1;
      delay(1000);
      tasterstate=0;
     }
  }
  
  if(killswitch==1){//check if mine is disarmed
    
    if (distance<100){//check distance

      digitalWrite(PIN_MOTOR,1);
      delay(4000);
      digitalWrite(PIN_MOTOR,0);
      
    }
  }
}
