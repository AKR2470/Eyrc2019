
/*  
 * Team Id:2683
 * Author List: e-Yantra Team 
 * Filename: 
 * Theme:  Ant Bot
 * Functions: setup(),loop(),cases(value) ,right_turn(state) , left_turn(state), start_node(), sensor_value(),node_2_node(state)
 * Global Variables:enright ,righta ,rightb  ,enleft  ,lefta ,leftb ,max_left  ,min_left  ,max_center ,min_center  ,max_right  ,min_right ,normal_speed_right  ,normal_speed_left  
 */




/*###############################################################################################
 #################################################################################################
 -----------------------class calling         here --------------------------------------*/




void millis_delay(int interval)  //Function provides required hardware delays
{
  current_time = millis();
  while(millis()<current_time+interval){
  }

} 












