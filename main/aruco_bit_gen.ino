int aruco_bit_gen()
{ 
int i=0;

  for (id_no = 0 ;id_no <4 ; id_no++)
  { 
    for(id_n1 = 7 ;id_bit_no>-1 ;id_bit_no--)
    {

      byte_ar_data[id_no][id_n1] = bitRead(SIM[id_no],id_n1);//received
    }
  }
}

void aruco_data_print()
{
  for (id_no = 0 ;id_no <4 ; id_no++)
  { 
    for(id_n2 = 0 ; id_n2 <4 ; id_n2++)
    {
      if ( byte_ar_data[id_no][0] == 1 )
      {
        Serial.print("1:Queen_Ant_Hill_,\t");

        id_out[id_no][0] = 1;
      }   
      else if (  byte_ar_data[id_no][0] == 0 )
      {
        Serial.print("0:Regular_Ant_Hill_,\t");
        id_out[id_no][0] = 0;
      } 

      if (byte_ar_data[id_no][1] == 0 && byte_ar_data[id_no][2] == 0 )
      {
        Serial.print("00:Ant_Hill_0_UL_,\t");

        id_out[id_no][1] = 0;
      }
      else if (byte_ar_data[id_no][1] == 0 && byte_ar_data[id_no][2] == 1 )
      {
        Serial.print("01:Ant_Hill_1_UR_,\t"); 
        id_out[id_no][1] = 1;
      }
      else if (byte_ar_data[id_no][1] == 1 && byte_ar_data[id_no][2] == 0 )
      {
        Serial.print("10:Ant_Hill_2_DR_,\t"); 
        id_out[id_no][1] = 2;
      }
      else if (byte_ar_data[id_no][1] == 1 && byte_ar_data[id_no][2] == 1 )
      {
        Serial.print("11:Ant_Hill_3_DL_,\t");
        id_out[id_no][1] = 3;
      }


      if (byte_ar_data[id_no][3] == 0 && byte_ar_data[id_no][4] == 0 )
      {
        Serial.print("00:Serv2_No_Supply_,\t");
        id_out[id_no][1] = 11;
      }
      else if (byte_ar_data[id_no][3] == 0 && byte_ar_data[id_no][4] == 1 )
      {
        Serial.print("01:Serv2_Honey_R_____,\t");
        id_out[id_no][1] = 22;
      }
      else if (byte_ar_data[id_no][3] == 1 && byte_ar_data[id_no][4] == 0 )
      {
        Serial.print("10:Serv2_Leaves_G____,\t");
        id_out[id_no][1] = 33;
      }
      else if (byte_ar_data[id_no][3] == 1 && byte_ar_data[id_no][4] == 1 )
      {
        Serial.print("11:Serv2_Wood_B______,\t");
        id_out[id_no][1] = 44;
      }



      if (byte_ar_data[id_no][5] == 0 && byte_ar_data[id_no][6] == 0 )
      {
        Serial.print("00:Serv1_No_Supply___,\t");
        id_out[id_no][2] = 11;
      }
      else if (byte_ar_data[id_no][5] == 0 && byte_ar_data[id_no][6] == 1 )
      {
        Serial.print("01:Serv1_Honey_R______,\t");
        id_out[id_no][2] = 22;
      }
      else if (byte_ar_data[id_no][5] == 1 && byte_ar_data[id_no][6] == 0 )
      {
        Serial.print("10:Serv1_Leaves_G_____,\t");
        id_out[id_no][2] = 33;
      }
      else if (byte_ar_data[id_no][5] == 1 && byte_ar_data[id_no][6] == 1 )
      {
        Serial.print("11:Serv1_Wood_B________,\t");
        id_out[id_no][2] = 44;
      }

      if ( byte_ar_data[id_no][7] == 1 )
      {
        Serial.print("1:Trash_Y___\t\n");
        id_out[id_no][3] = 1;
      }
      else if ( byte_ar_data[id_no][7] == 0 )
      {
        Serial.print("0:No_Trash_Y \t\n");
        id_out[id_no][3] = 0;
      }
    
    }
  }

}


