
/*###############################################################################################
 #################################################################################################
 ----------------------- header file calling of the start here --------------------------------------*/





/*----------------------- header  of the end  here --------------------------------------*/




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
void receiveData(int byteCount)
{

  data = Wire.read();
 
}

