#define rmp 12 //Replacing rmp with 3 every where in the program, so that we don't have to remember pin no.,as it is difficult to remember
#define rmn 13 //Same way as above
#define lmp 10 //Same way as above
#define lmn 11 //Same way as above
#define rmen A0
#define lmen A1
char key;
String command;
void setup() 
{
  pinMode(rmp,OUTPUT); //Pintype declaration i.e. which pin is input and which output. As Arduino has to intruct motor to move,motor pins will be output
  pinMode(rmn,OUTPUT); //Same as above. And "rmn" and "rmp" means 'right motor negitive terminal' and 'right motor positive terminal' respectively. And so on for others.
  pinMode(lmp,OUTPUT); //Same as above
  pinMode(lmn,OUTPUT); //Same as above
  pinMode(rmen,OUTPUT);
  pinMode(lmen,OUTPUT);
  Serial.begin(9600); //9600 is default baud rate at which bluetooth module transfers information to Arduino
  analogWrite(rmen,130);
  analogWrite(lmen,135);
}

void loop()
{
  while(Serial.available()) //"Serial.available()" is a function which checks if Arduino is recieving information from Bluetooth module,if it is recieving signal then condition inside if() becomes true and then if()'s body is executed 
  {
    delay(10);
    key=Serial.read();
    command+=key;
    
  }
  
  if(command=="forward"){fm();}
  else if(command == "backward"){bm();}
  else if(command == "left"){lm();}
  else if(command == "right"){rm();}
  else if(command == "stop"){st();}

  command="";

}

//function definitions
void fm() //forward motion function definition
{
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
