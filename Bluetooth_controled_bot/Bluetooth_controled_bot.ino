#define rmp 3 //Replacing rmp with 3 every where in the program, so that we don't have to remember pin no.,as it is difficult to remember
#define rmn 5 //Same way as above
#define lmp 6 //Same way as above
#define lmn 9 //Same way as above

void setup() 
{
  pinMode(rmp,OUTPUT); //Pintype declaration i.e. which pin is input and which output. As Arduino has to intruct motor to move,motor pins will be output
  pinMode(rmn,OUTPUT); //Same as above. And "rmn" and "rmp" means 'right motor negitive terminal' and 'right motor positive terminal' respectively. And so on for others.
  pinMode(lmp,OUTPUT); //Same as above
  pinMode(lmn,OUTPUT); //Same as above
  Serial.begin(9600); //9600 is default baud rate at which bluetooth module transfers information to Arduino
  
}

void loop()
{
  if(Serial.available()) //"Serial.available()" is a function which checks if Arduino is recieving information from Bluetooth module,if it is recieving signal then condition inside if() becomes true and then if()'s body is executed 
  {
    char key=Serial.read(); //"Serial.read()" is a function which reads recieved information and here we are storing recieved information as character variable "key"  
    switch(key) //Now using switch() case we are trying to match recieved character with listed cases
    {
      case 'F':{fm(); break;} // case for forward motion.here 'F' is used because we will be assigning it to a button in Android app
      case 'B':{bm();break;}  //case for backward motion. bm(),fm(),etc. are function calls.
      case 'L':{lm();break;}  //case for left motion. In each case 'break' statement is compulsory else after selection of a particular case all the cases after that case will automatically get executed
      case 'R':{rm();break;}  //case for right motion
      default:{st();break;}  //case for stoping motion if any other key than listed above is pressed
    }
    
  }
  

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
