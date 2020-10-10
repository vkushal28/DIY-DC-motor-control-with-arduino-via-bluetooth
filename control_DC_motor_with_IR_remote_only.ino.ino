#include <IRremote.h>
#define pwm1      5
#define pwm2      7

int IRPIN = 10;
int successLED = 11;
int maxReachLED = 13;
int minReachLED = 12;
int leftBeep = 9;
int rightBeep = 8;

boolean motor_dir = 0;
int motor_speed = 128;     // 128 in the mimimum & 928 is the maximum
int temp_speed;
int motor_direction;
int startSpeed;
int endSpeed = 0;
boolean terminateAction = 0;


IRrecv irrecv(IRPIN);

decode_results result;

// this is array holding codes for Remote
int remoteValues[] ={
            16769055, // vol-
            16754775, // vol+
            16761405, // STOP/PLAY
            16753245, // CH-
            16769565, // CH+
            16736925, // CH  
            16748655, //EQ
            16750695, //100+
            16738455, //startFromZero
             // HEX CODES
            "FFE01F", // vol-
            "FFA857", // vol+
            "FFC23D", // STOP/PLAY
            "FFA25D", // CH-
            "FFE21D", // CH+
            "FF629D", // CH  
            "FF906F", // EQ    
            "FF9867", // 100+ 
            "FF6897", // startFromZero       
            };
// remote key names to be associated
 String remoteKeys[] ={
            "speedDown",
            "speedUp",
            "stopPlay",
            "directionLeft",
            "directionRight",
            "dec100",
            "motSpeed",
            "inc100",
            "startFromZero",

            "speedDown",
            "speedUp",
            "dec100",
            "directionLeft",
            "directionRight",
            "stopPlay",
            "motSpeed",
            "inc100",
            "startFromZero",
            };

void setup()
{
  Serial.begin(9600);
  pinMode(successLED, OUTPUT);
  pinMode(maxReachLED, OUTPUT);
  pinMode(minReachLED, OUTPUT);
  pinMode(leftBeep, OUTPUT);
  pinMode(rightBeep, OUTPUT);
  pinMode(pwm1, OUTPUT);
  pinMode(pwm2, OUTPUT);
//  Serial.println("Enabling machine to work.....");
  irrecv.enableIRIn();
//  Serial.println("Ready to rock");
  digitalWrite(successLED, HIGH);  
  delay(100);                 
  digitalWrite(successLED, LOW);
  delay(100);
  digitalWrite(successLED, HIGH);  
  delay(100);  
  digitalWrite(successLED, LOW);
  delay(100);
  digitalWrite(successLED, HIGH);
  delay(50);
  digitalWrite(successLED, LOW);
}

void loop() 
{
  if (irrecv.decode(&result)) 
  {
    validateKeyPress(result.value);
//    Serial.println(result.value, HEX);
    irrecv.resume(); 
  }
  delay(100);

  if(motor_dir)
    analogWrite(pwm1, motor_speed);
  else
    analogWrite(pwm2, motor_speed);   
}

void validateKeyPress(int x)
{
  int found=0;
  for(int i=0; i< sizeof(remoteValues)/sizeof(int); i++)
  {
      if(remoteValues[i] == x) 
      {
//        Serial.print("Key pressed:");
//        Serial.println(remoteKeys[i]); 
        performActions(remoteKeys[i]);
        digitalWrite(successLED, HIGH);  
        delay(50);                 
        digitalWrite(successLED, LOW);
        found=1;
      } // if matched
  }
}

void performActions (String action)
{
//    action = "speedDown" / "speedUp" / "stopPlay" / "directionLeft" / "directionRight"
  if(action == "speedDown"){
//    Serial.println("decrease speed:");
    if( motor_speed > 128){
//       temp_speed = motor_speed - 100;
       motor_speed = motor_speed - 2;
//       Serial.println(motor_speed);
        digitalWrite(successLED, HIGH);  
        delay(50);                 
        digitalWrite(successLED, LOW);
        delay(100);
        digitalWrite(successLED, HIGH);  
        delay(50);  
        digitalWrite(successLED, LOW);
    }
    else 
      {motor_speed = 128;
//      Serial.println("reached minimum speed");
        digitalWrite(minReachLED, HIGH);  
        delay(50);                 
        digitalWrite(minReachLED, LOW);
        delay(50);
        digitalWrite(minReachLED, HIGH);  
        delay(50);  
        digitalWrite(minReachLED, LOW);
      }
    }
  else if(action == "speedUp"){
//    Serial.println("increase speed:");
    if( motor_speed < 928){
//       temp_speed = motor_speed + 100;
       motor_speed = motor_speed + 2;
//       Serial.println(motor_speed);
        digitalWrite(successLED, HIGH);  
        delay(50);                 
        digitalWrite(successLED, LOW);
        delay(100);
        digitalWrite(successLED, HIGH);  
        delay(50);  
        digitalWrite(successLED, LOW);
    }
    else
      {motor_speed = 928;
//      Serial.println("reached maximum speed");
        digitalWrite(maxReachLED, HIGH);  
        delay(50);                 
        digitalWrite(maxReachLED, LOW);
        delay(50);
        digitalWrite(maxReachLED, HIGH);  
        delay(50);  
        digitalWrite(maxReachLED, LOW);
      }
    }

else if(action == "inc100"){
//      Serial.println("increase speed by 100:");
      if( motor_speed < 928){
  //       temp_speed = motor_speed + 100;
         motor_speed = motor_speed + 100;
//         Serial.println(motor_speed);
        digitalWrite(successLED, HIGH);  
        delay(50);                 
        digitalWrite(successLED, LOW);
        delay(100);
        digitalWrite(successLED, HIGH);  
        delay(50);  
        digitalWrite(successLED, LOW);
      }
      else
        {motor_speed = 928;
//        Serial.println("reached maximum speed");
        digitalWrite(maxReachLED, HIGH);  
        delay(50);                 
        digitalWrite(maxReachLED, LOW);
        delay(50);
        digitalWrite(maxReachLED, HIGH);  
        delay(50);  
        digitalWrite(maxReachLED, LOW);
        }
       }

    else if(action == "dec100"){
//      Serial.println("decrease speed by 100:");
      if( motor_speed > 128){
  //       temp_speed = motor_speed - 100;
         motor_speed = motor_speed - 100;
//         Serial.println(motor_speed);
        digitalWrite(successLED, HIGH);  
        delay(50);                 
        digitalWrite(successLED, LOW);
        delay(100);
        digitalWrite(successLED, HIGH);  
        delay(50);  
        digitalWrite(successLED, LOW);
      }
      else
        {motor_speed = 128;
//        Serial.println("reached minimum speed");
        digitalWrite(minReachLED, HIGH);  
        delay(50);                 
        digitalWrite(minReachLED, LOW);
        delay(50);
        digitalWrite(minReachLED, HIGH);  
        delay(50);  
        digitalWrite(minReachLED, LOW);
        }
       }
    
  else if(action == "stopPlay"){
    if(!terminateAction){
        temp_speed = motor_speed;
        motor_speed = endSpeed;
        terminateAction = !terminateAction;
//        Serial.println("stop");
      }
      else {
        motor_speed = temp_speed;
        terminateAction = !terminateAction;
        digitalWrite(successLED, HIGH);  
        delay(50);                 
        digitalWrite(successLED, LOW);
        delay(50);
        digitalWrite(successLED, HIGH);  
        delay(50);  
        digitalWrite(successLED, LOW);
//        Serial.println("start");
       }
    }
  else if(action == "directionLeft"){
//    Serial.println("change direction to LEFT:");
    motor_dir = 0;                         
    if(motor_dir)
      {
        digitalWrite(pwm2, 0);
        
        }
    else
      {
        digitalWrite(pwm1, 0);
        
        }
     digitalWrite(leftBeep, HIGH);  
     delay(50);                 
     digitalWrite(leftBeep, LOW);
    }
  else if(action == "directionRight"){
//    Serial.println("change direction to RIGHT:");
    motor_dir = 1;
    if(motor_dir)
      {
        digitalWrite(pwm2, 0);
        
        }
    else
      {
        digitalWrite(pwm1, 0);
        
        }
     digitalWrite(rightBeep, HIGH);  
     delay(50);                 
     digitalWrite(rightBeep, LOW);
    }
    else if(action == "motSpeed"){
//      Serial.println("current motor speed is:");
      Serial.println(motor_speed); 
        digitalWrite(successLED, HIGH);  
        delay(50);                 
        digitalWrite(successLED, LOW);
        delay(100);
        digitalWrite(successLED, HIGH);  
        delay(50);  
        digitalWrite(successLED, LOW);
     }
    else if(action == "inc100"){
//      Serial.println("increase speed by 100:");
      if( motor_speed < 928){
  //       temp_speed = motor_speed + 100;
         motor_speed = motor_speed + 100;
//         Serial.println(motor_speed);
        digitalWrite(successLED, HIGH);  
        delay(50);                 
        digitalWrite(successLED, LOW);
        delay(100);
        digitalWrite(successLED, HIGH);  
        delay(50);  
        digitalWrite(successLED, LOW);
      }
      else
        {motor_speed = 928;
//        Serial.println("reached maximum speed");
        digitalWrite(successLED, HIGH);  
        delay(50);                 
        digitalWrite(successLED, LOW);
        delay(100);
        digitalWrite(successLED, HIGH);  
        delay(50);  
        digitalWrite(successLED, LOW);
         }
       }
     else if(action == "startFromZero"){
        motor_speed = 128;
//        Serial.println("RESET");
        digitalWrite(successLED, HIGH);  
        delay(50);                 
        digitalWrite(successLED, LOW);
        delay(100);
        digitalWrite(successLED, HIGH);  
        delay(50);  
        digitalWrite(successLED, LOW);
      }
}

