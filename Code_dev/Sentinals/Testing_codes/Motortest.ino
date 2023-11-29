#define ENCA 18 // Yellow
#define ENCB 19 // White
#define EN1 24
#define INA_1 6
#define INB_1 7
int pos = 0;
int prev_pos = 0;
float moving_avg;
float speedSet;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

pinMode(INA_1,OUTPUT);
pinMode(INB_1,OUTPUT);
pinMode(EN1,OUTPUT);
pinMode(ENCA,INPUT);
pinMode(ENCB,INPUT);
pinMode(A8,INPUT);

digitalWrite(EN1,HIGH);
digitalWrite(INB_1,HIGH);

attachInterrupt(digitalPinToInterrupt(ENCA),readEncoder,RISING);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  int speed = map(analogRead(8),0,1023,0,255);
  analogWrite(INA_1,speed);

  moving_avg = 0;
  for (int i=0;i<5;i++){
    moving_avg += (pos - prev_pos);
    prev_pos = pos;
    delay(10);
  }
  
  Serial.println((String)moving_avg + " " + (String)speed);
}

void readEncoder(){
  int b = digitalRead(ENCB);
  if(b>0){
    pos++;
  }
  else{
    pos--;
  }
}