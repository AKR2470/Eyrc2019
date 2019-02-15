
/*###############################################################################################
 #################################################################################################
 ------------------       program to follow backward line to node turn           ---------------------*/
int line_bck( int state )
{
  fwd_go = 00 ; //backward
  flag_bck =0;
  while (flag_bck != 9)
  {  
    sensor_data(); 
    current_time = millis();   

    while(flag_fwd == 3 || flag_fwd == 9 )
    { 
      if( left == 0 && center >= 1 && right >= 1) 
      { 
        while((state == 11) && (millis()<current_time+5))
        {
          state = 01;//
          cases(state);
          if ( left == 0 && center >= 1 && right >= 0)
          {
            flag_bck = 0;//any arbitary flag to call backward line to node 
            flag_fwd = 5;//any arbitary flag
            break;
          }  
        }
      } 
      if(left == 1 && center >= 1 && right == 0) 
      {
        while((state == 11) && (millis()<current_time+5))
        {
          state = 10;//
          cases(state);
          if ( left == 0 && center >= 1 && right >= 0)
          {
            flag_bck = 0;//any arbitary flag to call backward line to node 
            flag_fwd = 5;//any arbitary flag
            break;
          }
        }  
      } 
    } 

    if ((left >= 1 && center >= 2 && right >= 1) ) 
    {
      flag_bck =9;
      state = 00;//stop
      cases(state);      
    }


    else if( flag_bck == 0 )
    {   
      if(left == 0 && center >= 1 && right == 0)
      {
        state = 11;//backward
        cases(state);
      }
      else if (left >= 1 && center >= 2 && right >= 1) 
      {
        flag_bck = 9;
        state = 00;//stop
        cases(state);
      }

      else if(left >= 1 && center == 0 && right == 0)
      {
        while((state == 11) && (millis()<current_time+10))
        {
          state = 10;//right
          cases(state);
        }
      }  
      else if(left >= 1 && center >= 1 && right == 0)
      {
        flag_bck =9;
        state = 00 ;
        cases(state);   
      }
      else if(left == 0 && center == 0 && right >= 3)
      {
        while((state == 11) && (millis()<current_time+30))
        {
          state = 01;//right
          cases(state);
        }
      }
      else if(left == 0 && center >= 1 && right >= 1) 
      {
        flag_bck =9;
        state = 00;//left
        cases(state);
      } 
      else 
      {
        state=11;//backward
        cases(state);
      }
    }   

    else if (state == 01)
    {
      if (left >= 1 && center >= 1 && right >= 1) 
      {
        flag_bck =9;
        state = 00;//stop
        cases(state);
      }
      else  if(left == 0 && center >= 1 && right == 0)
      {
        state = 11;
        cases(state);
      }
      else if(left >= 1 && center == 0 && right == 0)
      {
        state = 10;//right
        cases(state);
      }  
    }   

    else  if (state == 10)
    {
      if (left >= 1 && center >= 1 && right >= 1) 
      {
        flag_bck = 9;
        state = 00;//stop
        cases(state);            
      }             
      else if(left == 0 && center >= 2 && right == 0)
      {
        state = 11;
        cases(state);
      }
      else if (left == 0 && center == 0 && right >= 2)
      {
        state = 01;//left
        cases(state);
      }  
    }
  } 




  return state; 
}
/*-------------------- backward line follow function of the end here --------------------------------------*/


