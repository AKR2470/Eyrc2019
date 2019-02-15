#define enleft   3
#define righta   4
#define rightb   12
#define enright  11
#define lefta    7
#define leftb    8
#define max_left 490
#define min_left 20//was really 20
#define max_center 410
#define min_center 20//was really 20
#define max_right 500
#define min_right 20//was really 20
#define normal_speed_right 60//95
#define normal_speed_left 63//100

#define SLAVE_ADDRESS 0x08

#include <Wire.h>
#include <Servo.h> 
 
Servo myservo;

int analogPin1 = A0;  
int analogPin2 = A1;
int analogPin3 = A2;
int right = 0 ;
int right_most =0;
int center = 0;
int left = 0;
int left_most = 0;
float kp = 5;
float kd = 4.5;
float ki = 0.008;
int error = 0;
float last_error = 0.0;
float lastError2 = 0.0 ;
float integral = 0.0;
float derivative = 0.0;
float output = 0.0;
float powerA = 0.0;
float powerB = 0.0;
int node_count = 0;

unsigned int time_now = 0;

int data_rec = 99; //random value
int data = 0;


void setup()
{ 

Serial.begin(9600);
Wire.begin(SLAVE_ADDRESS);


pinMode(analogPin1, INPUT);
pinMode(analogPin2, INPUT);
pinMode(analogPin3, INPUT);
pinMode(enright, OUTPUT);
pinMode(righta, OUTPUT);
pinMode(rightb, OUTPUT);  
pinMode(lefta, OUTPUT);
pinMode(leftb, OUTPUT);
pinMode(enleft, OUTPUT);
//  analogWrite(enleft,72);
//  analogWrite(enright,68);
digitalWrite(righta, LOW);
digitalWrite(rightb, HIGH);
digitalWrite(lefta, LOW);
digitalWrite(leftb, HIGH);

myservo.attach(10); 
}    
//###############################################################

void millis_delay(int millis_delay_value) //Function provides required hardware delays
{
  time_now = millis();
  while(millis()<=millis_delay_value + time_now){}
}
//#########################################################

void sendData0()
{
  Wire.write(0);
}
void sendData1()
{   
  Wire.write(1);
}
void sendData2()
{
  Wire.write(2);
}
void sendData3()
{
  Wire.write(3);
}
void sendData4()
{
  Wire.write(4);
}
//##########################################################################################
void receiveData(int byteCount)
{

  data = Wire.read();
 
}
//#############################################################################
void read_me()
{
left_most = 0;
left = analogRead(analogPin1);     // read the input pin
center = analogRead(analogPin2);     // read the input pin
right = analogRead(analogPin3);   // read the input pin
right_most = 0;


left = map(left, min_left, max_left, 0, 3);
center = map(center, min_center, max_center, 0, 2);
right = map(right, min_right, max_right, 0, 3);

//  Serial.print("left=");
//  Serial.print(left);
//  Serial.print("\t");
//  
//  Serial.print("centre=");
//  Serial.print(center);
//  Serial.print("\t");
//  
//  Serial.print("right=");
//  Serial.print(right);
//  Serial.print("\t");
}

void loop()
{

read_me();
calc_error();

if(error == 6)
work_on_node();
else if(error != 5 && error != 6)
pid();

}
//#######################################################################################
void pid()
{
    integral = (integral + error)/2;
    derivative = (error - 2 * last_error + lastError2);
    lastError2 = last_error;
    last_error = error;
    output = (kp * float(error) + kd * derivative + ki * integral) ;
    Serial.print("  output = ");
    Serial.print(output);
    powerA = normal_speed_right + (output*4.2); //right
    powerB = normal_speed_left - (output*4.2); //left
    
    

    digitalWrite(righta, LOW);
    digitalWrite(rightb, HIGH);
    digitalWrite(lefta, LOW);
    digitalWrite(leftb, HIGH);
    analogWrite(enleft, powerB);    //left
    analogWrite(enright, powerA);
}
//###################################################################
void calc_error()
{

if((left == 2 || left == 3) && (center == 1 || center ==2) && (right == 2|| right == 3))
error = 6; 
else if(left == 0 && center == 1 && right == 0)
error = 0;
else if(left == 1 && center == 0 && right == 0)
error = 1;
else if(left == 2 && center == 0 && right == 0)
error = 2;
else if(left == 1 && center == 1 && right == 0)
error = 3;
else if(left == 2 && center == 1 && right == 0)
error = 4;
else if(left == 0 && center == 0 && right == 1)
error = -1;
else if(left == 0 && center == 0 && right == 2)
error = -2;
else if(left == 0 && center == 1 && right == 1)
error = -3;
else if(left == 0 && center == 1 && right == 2)
error = -4;
else 
error = 5;

Serial.print(" error ");
Serial.print(error);
Serial.print("\n");


}
//################################################################
void work_on_node()
{
   
  //node_count++;    

  digitalWrite(righta, LOW);
  digitalWrite(rightb, LOW);
  digitalWrite(lefta, LOW);
  digitalWrite(leftb, LOW);
  analogWrite(enleft,0);
  analogWrite(enright,0);
  delay(100);
  
  if(node_count == 2)
  {   
      data = -1;
      for(int pos = 80; pos < 120; pos += 1)  // goes from 0 degrees to 180 degrees 
      {                                  // in steps of 1 degree 
        myservo.write(pos);              // tell servo to go to position in variable 'pos' 
        millis_delay(30);                       // waits 15ms for the servo to reach the position 
      } 
      Wire.onRequest(sendData1);
      
      while(data == -1)
      {
        Wire.onReceive(receiveData);
      }
      Serial.print("###########################DATA REUCEIVED#################### \n");
      
      Serial.print(data);   
     
      data = -1;                    //Initializing data = -1 before any data comes
      for(int pos = 120; pos>=35; pos-=1)     // goes from 180 degrees to 0 degrees 
      {                                
          myservo.write(pos);              // tell servo to go to position in variable 'pos' 
          millis_delay(30);
      }
      
      Wire.onRequest(sendData2);
     
      while(data == -1)
      {

        Wire.onReceive(receiveData);
      }
      
      Serial.print("\n###########################DATA REUCEIVED####################\n");
      Serial.print(data);
      
      for(int pos = 35; pos<=80; pos+=1)     // goes from 180 degrees to 0 degrees 
      {                                
        myservo.write(pos);              // tell servo to go to position in variable 'pos' 
        millis_delay(50);
      }
      
      millis_delay(5000);
//      digitalWrite(righta, HIGH);
//      digitalWrite(rightb, LOW);
//      digitalWrite(lefta, LOW);
//      digitalWrite(leftb, HIGH);
//      analogWrite(enleft,60);
//      analogWrite(enright,60);
//      delay(4600);
//      digitalWrite(righta, HIGH);
//      digitalWrite(rightb, LOW);
//      digitalWrite(lefta, HIGH);
//      digitalWrite(leftb, LOW);
//      analogWrite(enleft,60);
//      analogWrite(enright,60);
//      delay(2900);
//      digitalWrite(righta, LOW);
//      digitalWrite(rightb, LOW);
//      digitalWrite(lefta, LOW);
//      digitalWrite(leftb, LOW);
//      analogWrite(enleft,0);
//      analogWrite(enright,0);
//      for(int pos = 80; pos < 120; pos += 1)  // goes from 0 degrees to 180 degrees 
//      {                                  // in steps of 1 degree 
//        myservo.write(pos);              // tell servo to go to position in variable 'pos' 
//        delay(30);                       // waits 15ms for the servo to reach the position 
//      } 
//      delay(1000);
//      Wire.onRequest(sendData3);
//      Wire.onReceive(receiveData);
//      //data_rec = int(receiveData(22));
//    
//      for(int pos = 120; pos>=35; pos-=1)     // goes from 180 degrees to 0 degrees 
//      {                                
//        myservo.write(pos);              // tell servo to go to position in variable 'pos' 
//        delay(30);
//      }
//      delay(1000);
//      Wire.onRequest(sendData4);
//      Wire.onReceive(receiveData);
////       
//      while(data_rec!=2){}
//      
//      for(int pos = 35; pos<=80; pos+=1)     // goes from 180 degrees to 0 degrees 
//      {                                
//        myservo.write(pos);              // tell servo to go to position in variable 'pos' 
//        delay(30);
//      }
      
      hard_break();
      
  }
  
  if(node_count == 1)
  {
    digitalWrite(righta, LOW);
    digitalWrite(rightb, HIGH);
    digitalWrite(lefta, LOW);
    digitalWrite(leftb, HIGH);
    analogWrite(enleft,100);
    analogWrite(enright,95);
    delay(100);
  }
  

}

void left_turn() //check the name for turn
{
 digitalWrite(righta, LOW);
 digitalWrite(rightb, HIGH);
 digitalWrite(lefta, LOW);
 digitalWrite(leftb, LOW);
 while(left != 0 && center != 1 && right != 0)  
 {   
    read_me();

    analogWrite(enleft,0);
    analogWrite(enright,56);
 
 }
}

void hard_break()
{     while(1)
    {
      digitalWrite(righta, LOW);
      digitalWrite(rightb, LOW);
      digitalWrite(lefta, LOW);
      digitalWrite(leftb, LOW);
      analogWrite(enleft,0);
      analogWrite(enright,0);
    };
}


