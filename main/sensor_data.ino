

/*###############################################################################################
 #################################################################################################
 -----------------------function of the sensor data --------------------------------------*/

void sensor_data()
{
  reading_i[0]=analogRead(sen_pin[0]);                   // read the value from left input pin
  reading_i[1]=analogRead(sen_pin[1]);                   // read the value from center input pin
  reading_i[2]=analogRead(sen_pin[2]);                   // read the value from right input pin

  left   = map(reading_i[0], min_left, max_left, 0, 4);        //mapping the left function in fixed limit
  center = map(reading_i[1], min_center, max_center, 0, 4);//mapping the center function in fixed limit
  right  = map(reading_i[2], min_right, max_right, 0, 4);    //mapping the right function in fixed limit


  Serial.print("left= ");
  Serial.print(left);
  Serial.print("\t");

  Serial.print("centre= ");
  Serial.print(center);
  Serial.print("\t");

  Serial.print("right= ");
  Serial.print(right);
  Serial.print("\t ");
  //
  //  Serial.print(" i= ");
  //  Serial.print();
  //  Serial.print("\t ");  

  Serial.print("state= ");
  Serial.print(state);
  Serial.print("\t "); 

  Serial.print("turn full= ");
  Serial.print(turn_full);  
  
  Serial.print("flag= ");
  Serial.print(flag_rgt);
  Serial.print("\t \n"); 

}

/*-------------------- sensor_data function of the end here --------------------------------------*/


