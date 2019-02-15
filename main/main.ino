
#include<Wire.h>

/*###############################################################################################
 #################################################################################################
 -----------------------constant function of the start here --------------------------------------*/

#define enright  11              //enabling pwm pin on right pin
#define righta   4               //enabling right motor on/off  
#define rightb   12              //enabling right motor on/off
#define enleft   3               //enabling pwm pin on left pin
#define lefta    7               //enabling left motor on/off
#define leftb    8               //enabling left motor on/off
#define max_left 490             //defining the max value encounter by the left sensor
#define min_left 20              //defining the min value encounter by the left sensor
#define max_center 410           //defining the max value encounter by the center sensor
#define min_center 20            //defining the min value encounter by the center sensor
#define max_right 500            //defining the max value encounter by the right sensor
#define min_right 20             //defining the min value encounter by the right sensor
#define speed_right 150    //giving the pwm value for the right sensor  
#define speed_left 148    //giving the pwm value for the left sensor  
#define SLAVE_ADDRESS1 0x08
#define SLAVE_ADDRESS2 0x04 
/*-----------------------     end here                     --------------------------------------*/


int curr_node = 3;
int supply_taken = 0;
int s_l = 0, da = 6;
int s_r = 0;
int col, count = 0;
int req_bl[6] = {2, 2, 3, 1, 0, 0};
int status_supply[6] = {0};
int supply_center = 3;
int simu_supp[] = {1, 2, 3, 0, 3, 1, 2};

/*###############################################################################################
 #################################################################################################
 ----------------------- functions are define here --------------------------------------*/
int cases(int value);                          //taking the different output from the state
int right_turn(int state ,int turn_full);      //function for taking right turn till the line detected
int left_turn (int state ,int turn_full);       //function for taking left turn till the line detected
int start_node();                              //function for making a small forward turn till the middle line is detected    
void sensor_data();                             //function to get sensor data
int bck_node_2_node(int state);                //function for maoving backward the bot from one node to the another node
int fwd_node_2_node(int state);                //function for maoving forward  the bot from one node to the another node
int line_bck(int state);                       //function for maoving backward the bot from line  to the another node
int line_fwd(int state);                       //function for maoving forward  the bot from line  to the another node


/*--------------------------    end here                   --------------------------------------*/

/*###############################################################################################
 #################################################################################################
 -----------------------different varialble initiallize here --------------------------------------*/

unsigned int s_lft = 72 ,s_rgt = 68;                      //left = 162, right = 153
unsigned int fwd_go = 22,turn_go = 22;                     //random values
unsigned int previous_millis = 0;                          //function for define the time period for the hardware timer                   
unsigned long interval = 1000;                             //interval of the millis function
unsigned int state =00 ,i=0 ,node=0,turn=0; 
unsigned int flag_rgt=0,flag_lft=0,flag_bck=0,flag_fwd=0;
int turn_full = 0;
unsigned int right = 0 ;                                   //taking the sensor value using map function for left sensor  
unsigned int center = 0;                                   //taking the sensor value using map function for center sensor
unsigned int left = 0;                                     //taking the sensor value using map function for right sensor




unsigned long current_time = 0;
unsigned int sen_pin[]={
  A0,A1,A2};                         //line sensor input 
int SIM[4] = {
  0},id_rx[4];
unsigned int reading_i[3];                                 //input of the sensor value
unsigned int reading_o[3];                                 //input of the sensor value
int node_count = 0;    //initialize node count
int data = -1;
int QAH = -1;                                              //-1 means No sim is ant hill



unsigned int id_no,id_n1,id_n2;
unsigned int byte_ar_data[4][8],id_bit_no,id_out[4][4]={
  9};
char Category[25],Hill[25],Serv2[25],Serv1[25],Trash[25];
/*-----------------------setup  function of the end here --------------------------------------*/




/*###############################################################################################
 #################################################################################################
 -----------------------setup function of the start here --------------------------------------*/



void setup()
{ 
  Serial.begin(9600);  //initializing the serial monitor for viewing    
  Wire.begin(SLAVE_ADDRESS1);
  pinMode(sen_pin[0], INPUT);                    //initialing left sensor as input
  pinMode(sen_pin[1], INPUT);                    //initialing center sensor as input
  pinMode(sen_pin[2], INPUT);                    //initialing right sensor as input

  //initializing motor driver pins
  pinMode(enright, OUTPUT);                      //making the right pwm pin as enable 
  pinMode(righta, OUTPUT);                       //making the right pin as output 
  pinMode(rightb, OUTPUT);                       //making the right pin as output 
  pinMode(lefta, OUTPUT);                        //making the left  pin as output 
  pinMode(leftb, OUTPUT);                        //making the left  pin as output 
  pinMode(enleft, OUTPUT);                       //making the left pwm pin as enable 

  //start_2_CN();
  line_fwd(state);
  grip_up();
  turn_full=90 ;
  left_turn(state);
  //detect_aruco();
  //line_bck(state);  
  //fwd_node_2_node(state);
  //millis_delay(50);
  //turn_full = 180;
  //right_turn(state);
  //bck_node_2_node(state); 
  //aruco_data_print(); 




}    
/*-----------------------setup  function of the end here --------------------------------------*/

/*###############################################################################################
 #################################################################################################
 -----------------------loop function of the start here --------------------------------------*/

void loop()
{

}
/*-----------------------loop  function of the end here --------------------------------------*/




