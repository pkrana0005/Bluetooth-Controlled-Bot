#include<Servo.h>
Servo myservo;
#define rmp  9//Replacing rmp with 3 every where in the program, so that we don't have to remember pin no.,as it is difficult to remember
#define rmn 10 //Same way as above
#define lmp 7 //Same way as above
#define lmn 8 //Same way as above
#define echo 3
#define trig 2
//#define led 13
#define rir 4
#define lir 5

int duration;
int cm;
int right_IR_reading;
int left_IR_reading;
char key;

void setup() 
{
  myservo.attach(6); 
  pinMode(rmp,OUTPUT); //Pintype declaration i.e. which pin is input and which output. As Arduino has to intruct motor to move,motor pins will be output
  pinMode(rmn,OUTPUT); //Same as above. And "rmn" and "rmp" means 'right motor negitive terminal' and 'right motor positive terminal' respectively. And so on for others.
  pinMode(lmp,OUTPUT); //Same as above
  pinMode(lmn,OUTPUT); //Same as above
  pinMode(echo,INPUT);
  pinMode(trig,OUTPUT);
 // pinMode(led,OUTPUT);
  pinMode(lir,INPUT);
  pinMode(rir,INPUT);
  myservo.write(90);
  Serial.begin(9600); //9600 is default baud rate at which bluetooth module transfers information to Arduino
  
}

void loop()
{
  if(Serial.available()) //"Serial.available()" is a function which checks if Arduino is recieving information from Bluetooth module,if it is recieving signal then condition inside if() becomes true and then if()'s body is executed 
  {
    key=Serial.read();
    Serial.println(key);  
    switch(key)
      { case 'C':{//digitalWrite(led,HIGH);
                  bc();
                  break;}
        case 'O':{//digitalWrite(led,HIGH);
                  oa();
                  break;}
        case 'I':{lf();break;}
        case 'S':{st();break;}
        }
     }
    }
//function definitions
void bc()
{Serial.print("bcc");
//digitalWrite(led,HIGH);
  while(1)
  { Serial.print("inside bc() while"); 
    Serial.println(Serial.read()); 
     key=Serial.read(); //"Serial.read()" is a function which reads recieved information and here we are storing recieved information as character variable "key"  
    Serial.println(key); 
    switch(key) //Now using switch() case we are trying to match recieved character with listed cases
    {
      case 'F':{Serial.print("fm");fm(); break;} // case for forward motion.here 'F' is used because we will be assigning it to a button in Android app
      case 'B':{bm();break;}  //case for backward motion. bm(),fm(),etc. are function calls.
      case 'L':{lm();break;}  //case for left motion. In each case 'break' statement is compulsory else after selection of a particular case all the cases after that case will automatically get executed
      case 'R':{rm();break;}  //case for right motion
      case 'S':{st();break;} 
      case 'O':{//digitalWrite(led,LOW);
                  st();
                  oa();
                   break;}
      case 'I':{//digitalWrite(led,LOW);
                st();lf();
                break;}
    }
       
    }
}



void oa()
  {//digitalWrite(led,HIGH);
    while(1){
      delay(200);
      check();
   while(cm<=15||cm<0)
   {
    st();
    delay(20);
    myservo.write(0);
    delay(200); 
    check();
    if(cm>15)
    { 
      myservo.write(90);
      srm();
      delay(700);
      st();
      delay(50);
      check();
      }
      else
      {
        myservo.write(180);
        delay(200);
        check();
        if(cm>15)
          { 
            myservo.write(90);
            slm();
            delay(700);
            st();
            delay(100);
            check();
          }
          else st();
      }
   }
   check();
   while(cm>15)
   {
    fm();
    check();
   }
        key=Serial.read();
        switch(key)
        {
          case 'C':st();bc();break;
          case 'I':st();lf();break;
          case 'S':st();break;
          }
   
      }
  
    
  }



void lf()
{
  while(1)
  {
    
  ircheck();
  if(left_IR_reading==1&&right_IR_reading==1)
  {
    fm();
    
  }
  else if(left_IR_reading==0&&right_IR_reading==1)
  { 
    
    while(left_IR_reading==0)
    {
      lm();
      ircheck();
    }
  }
  else if(left_IR_reading==1&&right_IR_reading==0)
  {
    while(right_IR_reading==0)
    {
      rm();
      ircheck();
    }
  }
  else if(left_IR_reading==0&&right_IR_reading==0)
  {
    st();
    
  }

 key=Serial.read();
        switch(key)
        {
          case 'C':st();bc();break;
          case 'I':st();oa();break;
          case 'S':st();break;
          }
    }
  }

void ircheck()
{ 
  right_IR_reading=digitalRead(rir);
  left_IR_reading=digitalRead(lir);
  Serial.print("left_IR_reading=");
  Serial.println(left_IR_reading);
  Serial.print("right_IR_reading=");
  Serial.println(right_IR_reading);
  }

void fm() //forward motion function definition
{Serial.print("fm ---");
  digitalWrite(lmp,HIGH); // Conditions For forward motion
  digitalWrite(lmn,LOW); // for forward motion we will assume that supplying all positive terminals of motors with positive potential(i.e.HIGH) and supplying all negative terminals of motors with zero or negative potential(i.e.LOW) the bot moves forward and so on for other motions
  digitalWrite(rmn,LOW);
  digitalWrite(rmp,HIGH);
}
void bm() //backward motion function definition
{
   digitalWrite(lmp,LOW); // Conditions For backward motion
  digitalWrite(lmn,HIGH);
  digitalWrite(rmn,HIGH);
  digitalWrite(rmp,LOW);
}
void lm() //left motion function definition
{
   digitalWrite(rmn,LOW); // Conditions For left motion
   digitalWrite(rmp,HIGH);
   digitalWrite(lmp,LOW);
   digitalWrite(lmn,LOW);
}
void rm() //right motion function definition
{
   digitalWrite(lmp,HIGH); // Conditions For right motion
   digitalWrite(lmn,LOW);
   digitalWrite(rmn,LOW);
   digitalWrite(rmp,LOW);
   
 }
void st() //stop motion function definition
{
   digitalWrite(lmp,LOW); // Conditions For stoping motion
    digitalWrite(lmn,LOW);
    digitalWrite(rmn,LOW);
    digitalWrite(rmp,LOW);
}
void srm()
{
  digitalWrite(rmp,LOW);
  digitalWrite(rmn,HIGH);
  digitalWrite(lmp,HIGH);
  digitalWrite(lmn,LOW);
   }
   
void slm()
{
  digitalWrite(rmp,HIGH);
  digitalWrite(rmn,LOW);
  digitalWrite(lmp,LOW);
  digitalWrite(lmn,HIGH);
   }
 void check()
{
   digitalWrite(trig,LOW);
   delayMicroseconds(10);
   digitalWrite(trig,HIGH);
   delayMicroseconds(20);
   digitalWrite(trig,LOW);
   duration=pulseIn(echo,HIGH);
   cm=duration/29/2;
   Serial.print("Distance=");
   Serial.println(cm);
  }
  
