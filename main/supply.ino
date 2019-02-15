
int color_detect() {
  return simu_supp[curr_node];
} 

void pick(int col) {
  Serial.println("---");
  Serial.print(" Picked block");
  Serial.println(col);
}
void chk_c() {
  if (col == req_bl[count])
  { 
    pick(col);
    count++;
    simu_supp[curr_node] = 0;
  }
  else {
    status_supply[curr_node] = col;
  }
}

void take_s() {
  if (!supply_taken) {
    if (curr_node == supply_center) {
      turn_full = 90;
      left_turn(state);
      
      line_fwd(state);
      //line_bck(state);

      curr_node = 2;
      col = color_detect();
      chk_c();
      fwd_node_2_node(state);
      //line_bck(state);

      curr_node = 1;
      col = color_detect();
      chk_c();
      fwd_node_2_node(state);
      //line_bck(state);

      curr_node = 0;
      col = color_detect();
      chk_c();
      int diff = supply_center - curr_node;
      while (diff > 0) {
        bck_node_2_node(state);

        diff--;
      }
      curr_node = supply_center;
      bck_node_2_node(state);

      curr_node = 4;
      col = color_detect();
      chk_c();
      bck_node_2_node(state);

      curr_node = 5;
      col = color_detect();
      chk_c();
      bck_node_2_node(state);

      curr_node = 6;
      col = color_detect();
      chk_c();
    }
  }
}


//void setup() {
  // put your setup code here, to run once:

  //  Wire.begin(SLAVE_ADD);
  //  Wire.onReceive(receiveData2);
  //  Wire.onRequest(sendData2);
  
//}
//void sendData2() {
//  Wire.write(da);
//}
//void receiveData2() {
//
//}
//void loop() {
  // put your main code here, to run repeatedly:

//}


