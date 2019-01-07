/* © Robocell,CCA
 * This code is given during Autonomous robotics workshop organised  by Robocell,CCA on 21,22,23 Sept,2018. 
 * For details visit https://www.facebook.com/RobocellNITDgp/ 
 *  
 * FUNCTIONING:
 *This is the code for a simplest bluetooth controled robot
 */


#define rmp 9 //Replacing rmp with 3 every where in the program, so that we don't have to remember pin no.,as it is difficult to remember
#define rmn 10 //Same way as above
#define lmp 8 //Same way as above
#define lmn 7 //Same way as above

char key;
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
    key=Serial.read(); //"Serial.read()" is a function which reads recieved information and here we are storing recieved information as character variable "key"  
    
  }

 switch(key) //Now using switch() case we are trying to match recieved character with listed cases
    {
      case 'F':{forward(); break;} // case for forward motion.here 'F' is used because we will be assigning it to a button in Android app
      case 'B':{backward();break;}  //case for backward motion. backward(),forward(),etc. are function calls.
      case 'L':{left();break;}  //case for left motion. In each case 'break' statement is compulsory else after selection of a particular case all the cases after that case will automatically get executed
      case 'R':{right();break;}  //case for right motion
      default:{stops();break;}  //case for stoping motion if any other key than listed above is pressed
    }
    
  delay(150);
  key= 'S';
  

}

//function definitions
void forward()
{
  digitalWrite(rmp,HIGH);
  digitalWrite(rmn,LOW);
  digitalWrite(lmp,LOW);
  digitalWrite(lmn,HIGH);
  }

void backward()
{
  digitalWrite(rmp,LOW);
  digitalWrite(rmn,HIGH);
  digitalWrite(lmp,HIGH);
  digitalWrite(lmn,LOW);
  }
  
void right()
{
  digitalWrite(rmp,LOW);
  digitalWrite(rmn,LOW);
  digitalWrite(lmp,LOW);
  digitalWrite(lmn,HIGH);
   }
   
void left()
{
  digitalWrite(rmp,HIGH);
  digitalWrite(rmn,LOW);
  digitalWrite(lmp,LOW);
  digitalWrite(lmn,LOW);
   }
void stops()
{
  digitalWrite(lmp,LOW);
  digitalWrite(lmn,LOW);
  digitalWrite(rmn,LOW);
  digitalWrite(rmp,LOW);
  
}
