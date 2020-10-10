
#include <IRremote.h>

int IRPIN = 10;

IRrecv irrecv(IRPIN);

decode_results result;

void setup()
{
  Serial.begin(9600);
  Serial.println("Enabling IRin");
  irrecv.enableIRIn();
  Serial.println("Enabled IRin");
}

void loop() 
{
  if (irrecv.decode(&result)) 
  {
    Serial.println(result.value, HEX);
    irrecv.resume(); 
  }
  delay(100);
}

