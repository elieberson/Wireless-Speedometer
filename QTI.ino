//changable constants
int QTI = 7;      //QTI IR sensor input
int LED = 13;  //LED indicator. THis is built on arduino but can be changed for different LED's
int rotper = 10; //number of rotations of the wheel per input to rtimes 

//sensor data
int data = 0;            //Data from the sensor
unsigned long stime = 0; //Time at restarting the test

//rotation counter variables
int pc = LOW;            //previous color
unsigned long rtime = 0;  //Result time
unsigned long rtimes[60]; //Holds time at which each inputed rotation was recorded
int count = 0;            //holds next spot in array rtimes. Is also the number of rotations that have occured
int rcount = 0;           //number of rotations since starting.
boolean wait = true;  //initial wait for signal to start

void setup(){
  pinMode(QTI, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  start();
}

void loop(){
  if(Serial.available() && Serial.read() == 'd'){last();}  //if end of test, run last
  data = digitalRead(QTI);
  if(pc==HIGH && data==LOW){     //if rotation occurred
    rtime = millis()-stime;        //set relative time
    if ((++rcount)%rotper==0){   //if every rotpe amount or rotations record data
      rtimes[count++]=rtime;
      if(count==1){
        Serial.println(String(rotper) + ":" + String(rtime));
      }else{
        Serial.println(String(rotper) + ":" + String(rtime-rtimes[count-2]));
      }
    }
  }
  if(data==LOW){                //LED indicator
    digitalWrite(LED,HIGH);
  }else{
    digitalWrite(LED,LOW);
  }
  pc=data;                      //set previous
}

//Gives instructions and waits to begin main loop
void start(){
  Serial.println("Press s to begin and d to end");
  while(wait){
    pc = digitalRead(QTI);
    if(pc==LOW){
      digitalWrite(LED,HIGH);
    }else{
      digitalWrite(LED,LOW);
    }
    if(Serial.available() && Serial.read()=='s'){
      wait=false;
    }
  }
  wait = true;
  stime = millis();
}

void last(){
  if(rcount%rotper != 0){
    if(count<1){
      Serial.println(String(rcount) + ":" + String(rtime));
    }else{
      Serial.println(String(rcount%rotper) + ":" + String(rtime-rtimes[count-1]));
    };
  }  
  count=0;
  rcount=0;
  start();
}
