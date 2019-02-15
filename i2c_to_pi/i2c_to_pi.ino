#include <Wire.h>

#define SLAVE_ADDRESS 0x04



void setup()
{
Serial.begin(9600);
Wire.begin(SLAVE_ADDRESS);
Wire.onRequest(sendData);
Wire.onReceive(receiveData);
}    

void sendData()
{
    Wire.write(5);
}
void receiveData(int howMany)
{
  int data = Wire.read();
  Serial.print("  Received Data  ");
  Serial.print(data);
}
void loop()
{
 
}





