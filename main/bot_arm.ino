
/*###############################################################################################
 #################################################################################################
 ----------------------- header file calling of the start here --------------------------------------*/


#include <Servo.h>

/*----------------------- header  of the end  here --------------------------------------*/




Servo myservo;
/*-----------------------     end here                     --------------------------------------*/


//###############################################################



class bot_arm
{
  Servo servo;                                          // create servo object to control a servo

    int pos;                                              // initialising varialble 


public:  

  void Attach(int pin) 
  {
    servo.attach(pin);  
  }

  void Detach()
  {
    servo.detach();
  }

  void millis_servo(int interval)  //Function provides required hardware delays for servo
  {

    unsigned long  current_time = millis();
    while(millis()<current_time+interval)
    {

    }

  } 


  void increase(int angle1,int angle2)
  {
    for(pos = angle1; pos <= angle2; pos += 1) // goes from 0 degrees to 180 degrees
    {
      servo.write(pos);

      millis_servo(30);

    }
    millis_servo(0);

  }

  void decrease(int angle1,int angle2)
  {
    for(pos = angle1; pos>=angle2; pos-=1)
      // goes from 180 degrees to 0 degrees
    {
      servo.write(pos);
      // tell servo to go to position in variable 'pos'
      millis_servo(30);
      // waits 15ms for the servo to reach the position
    }
    millis_servo(50);
  }
};

bot_arm picker;//servo at picker
bot_arm griper;//servo at gripper
bot_arm core;//servo at base
/*--------------------  classes function of the end here --------------------------------------*/


/*###############################################################################################
 #################################################################################################
 ------------------      gripper function start here          ---------------------*/
int grip()
{
  // The code below rotates the the two servo with defined angle in corresponding upward and downward direction by calling the function in defined class 
  picker.Attach(9);             // attaches the servo on pin 9 to the servo object
  griper.Attach(5);
  picker.increase(40,175);
  griper.increase(120,180);
  picker.decrease(174,27);
  griper.decrease(180,105);
  griper.increase(105,180);
  picker.increase(26,170);
  griper.decrease(180,130);
  picker.decrease(174,40);
  griper.increase(130,180);
}  

//------------------      gripper function start here          ---------------------*/_


int bit_read(int num)
{
  if(bitRead(num, 6) == 0 && bitRead(num, 5) == 0)
  {
    if(bitRead(num, 7) == 1)
      QAH = 0;
    SIM[0] = num;
  }
  if(bitRead(num, 6) == 0 && bitRead(num, 5) == 1)
  {
    if(bitRead(num, 7) == 1)
      QAH = 1;
    SIM[1] = num;
  }
  if(bitRead(num, 6) == 1 && bitRead(num, 5) == 0)
  {
    if(bitRead(num, 7) == 1)
      QAH = 2;
    SIM[2] = num;
  }
  if(bitRead(num, 6) == 1 && bitRead(num, 5) == 1)
  {
    if(bitRead(num, 7) == 1)
      QAH = 3;
    SIM[3] = num;
  }
}



int detect_aruco()
{
  // The code below rotates the the two servo with defined angle in corresponding upward and downward direction by calling the function in defined class 
  core.Attach(10);             // attaches the servo on pin 9 to the servo object
  //################################DATA1################################
  data = -1;
  core.decrease(80,35);
  Wire.onRequest(sendData1);

  while(data == -1)
  {
    Wire.onReceive(receiveData);
  }
  //  Serial.print("###########################DATA REUCEIVED#################### \n");
  //
  //  Serial.print(data);
  bit_read(data);


  //################################DATA2################################  
  data=-1;
  core.increase(35, 120);

  Wire.onRequest(sendData2);

  while(data == -1)
  {
    Wire.onReceive(receiveData);
  }
  //  Serial.print("###########################DATA REUCEIVED#################### \n");
  //
  //  Serial.print(data);
  bit_read(data);
  //################################180TURN################################ 
  turn_full = 180;

  flag_lft = 0;
  left_turn(state);
  millis_delay(200);
  line_bck(state);

  turn_full = 0;
  //################################DATA3################################ 
  data = -1;

  Wire.onRequest(sendData4);

  while(data == -1)
  {
    Wire.onReceive(receiveData);
  }
  //  Serial.print("###########################DATA REUCEIVED#################### \n");
  //
  //  Serial.print(data);
  bit_read(data);
  //################################DATA4################################ 
  data = -1;
  core.decrease(120, 35);

  Wire.onRequest(sendData3);

  while(data == -1)
  {
    Wire.onReceive(receiveData);
  }
  //  Serial.print("###########################DATA REUCEIVED#################### \n");
  //
  //  Serial.print(data);
  bit_read(data);
  //#################MOVE SERVO BACK TO ITS POSITION#########

}  


/*-------------------- gripper function of the end here --------------------------------------*/
void grip_up()
{
 // The code below rotates the the two servo with defined angle in corresponding upward and downward direction by calling the function in defined class 
  picker.Attach(9);             // attaches the servo on pin 9 to the servo object
  griper.Attach(5);
  picker.increase(40,175);
  griper.increase(120,180);
  picker.decrease(174,27);
}





