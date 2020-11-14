int enA=10;                                         
int enB=11;
int LmotorUp = 8;
int LmotorDn = 9; 
int RmotorUp = 12;  
int RmotorDn = 13;
int redPin = 6;
int whitePin=7;
int sensorPin = A0; 
int sensorValue = 0;  
int spd;
int sstate;
int lstate;  //state of white light. 0 means off , 1 means on
unsigned long timer0 = 2000; 
unsigned long timer1 = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(LmotorUp,OUTPUT);
  pinMode(LmotorDn,OUTPUT);
  pinMode(RmotorUp,OUTPUT);
  pinMode(RmotorDn,OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(whitePin, OUTPUT);
  spd=250; //motor speed 
  digitalWrite(redPin,LOW);
  digitalWrite(whitePin,LOW);
  Serial.println("Initiated");
  sstate=0;                                           
  lstate=0;  //light state initiation
} 
  

void loop()
{ 
  sensorValue = analogRead(sensorPin);  //reads ldr value, if value less than 4,light should be on
      if((sensorValue/10)<4|| lstate==1){  //cheecks if ldr value is less than 4 or user has set lstate=1(which means on)
        digitalWrite(whitePin, HIGH);                
      }
      else{
        digitalWrite(whitePin,LOW);
      }
  if(Serial.available()>0)                            //checks if bluetooh command is avaiable
  { 
    timer1 = millis();                                //store the initial time  
    int input = Serial.read(); 
    switch(input)
    {
     case 'w' : MoveF();
     break;
     case 's' : MoveB(); 
     break;
     case 'a' : MoveL();
     break;
     case 'd' : MoveR();
     break;
     case 'f' : Speed();
     break;
     case 'g' : Sturn();
     break;
     case 'x' : Light();
     break;
     default : Stop();
     break;
    }
  } 
  else{
    timer0 = millis();  //store 2nd time if there is no bluetooth command available  
    if((timer0 - timer1)>250){ //checks if difference between two timer is greater than 250 mili sec , if yes then the car should stop 
       Stop();
    }
  }
}

void MoveF()
{
  Serial.println("Forward");
  digitalWrite(LmotorUp,HIGH);
  digitalWrite(LmotorDn,LOW);
  analogWrite(enA, spd);
  digitalWrite(RmotorUp,HIGH);
  digitalWrite(RmotorDn,LOW);
  analogWrite(enB, spd);
  digitalWrite(redPin, LOW);
}

void MoveB()
{
  Serial.println("Backward");
  digitalWrite(LmotorUp,LOW);
  digitalWrite(LmotorDn,HIGH);
  analogWrite(enA, spd);
  digitalWrite(RmotorUp,LOW);
  digitalWrite(RmotorDn,HIGH);
  analogWrite(enB, spd);
  digitalWrite(redPin, LOW);
  digitalWrite(redPin, LOW);
}

void MoveL()
{
  Serial.println("Left");
  if(sstate==0)
  {
    digitalWrite(LmotorUp,LOW); 
    digitalWrite(LmotorDn,LOW);
  }
  else if(sstate==1){
    digitalWrite(LmotorUp,LOW);
    digitalWrite(LmotorDn,HIGH);
    analogWrite(enA, spd);
  }
  digitalWrite(RmotorUp,HIGH);
  digitalWrite(RmotorDn,LOW);
  analogWrite(enB, spd);
  digitalWrite(redPin, LOW);
  digitalWrite(redPin, LOW);
}

void MoveR()
{
  Serial.println("Right");
  digitalWrite(LmotorUp,HIGH);
  digitalWrite(LmotorDn,LOW);
  analogWrite(enA, spd);
  if(sstate==0)
  {
    digitalWrite(RmotorUp,LOW);
    digitalWrite(RmotorDn,LOW);
  }
  else if(sstate==1)
  {
    digitalWrite(RmotorUp,LOW);
    digitalWrite(RmotorDn,HIGH);
    analogWrite(enB, spd);
  }
  digitalWrite(redPin, LOW);
}

void Stop()
{
  Serial.println("Stop");
  digitalWrite(LmotorUp,LOW);
  digitalWrite(LmotorDn,LOW);
  digitalWrite(RmotorUp,LOW);
  digitalWrite(RmotorDn,LOW);
  digitalWrite(redPin, HIGH);
}

void Speed()  //motor speed control function, range 0-255.less than 100 is too low so we are using 100 minimum and 250 max 
{
  spd=spd+75;
  if(spd>250)
  {
    spd=100;
  }
  if(spd<175)
  {
    Serial.println("Speed LOW");
  }
  else if(spd<250)
  {
    Serial.println("Speed MEDIUM");
  }
  else
  {
    Serial.println("Speed High");
  }
}


void Sturn() //360 degree left right toggle 
{
 if(sstate==0)
  {
    sstate=1;
  }
 else if(sstate==1)
  {
    sstate=0;
  } 
}

void Light() //White light control toggle
{
 if(lstate==0)
  {
    lstate=1;
  }
 else if(lstate==1)
  {
    lstate=0;
  } 
}
