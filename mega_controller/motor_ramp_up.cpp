#include "motor_ramp_up.h"

motor_ramp_up::motor_ramp_up()
{
    last_loop_time = 0;
    speed = 0;
    goal_speed = 0;
    change = 0;
}

void motor_ramp_up::setup(int new_motor_pin, int new_ramp_up_ms, int new_ramp_step){
    motor_pin = new_motor_pin;
    ramp_up_ms = new_ramp_up_ms;
    ramp_step = new_ramp_step;
    pinMode(motor_pin, OUTPUT);  // sets the pin as output
}

void motor_ramp_up::setup(int new_motor_pin){
    setup(new_motor_pin,3,5);
}

void motor_ramp_up::loop(){
    /*Serial.print("Goal: ");
    Serial.print(goal_speed);
    Serial.print("Change: ");
    Serial.println(change);*/
    //change_time
    unsigned long curr_time = millis();
    unsigned long change_time = curr_time - last_loop_time;
    if (change_time>1){
      last_loop_time = curr_time;
  
      
      if ((goal_speed<(speed+ramp_step))&&(goal_speed>(speed-ramp_step))){
          goal_speed = speed;
      }
      else if (goal_speed<speed){
          speed -= 5;
      }
      else if (goal_speed>speed){
          speed += 5;
      }
  
  
      if (speed < 0){
          speed = 0;
      }
      else if (speed > 255){
          speed = 255;
      }
  
      analogWrite(motor_pin, speed); // analogRead values go from 0 to 1023, analogWrite values from 0 to 255
    }
    
}


void motor_ramp_up::set_speed(int new_speed){
    if (new_speed < 0){
        new_speed = 0;
    }
    else if (new_speed > 255){
        new_speed = 255;
    }
    goal_speed = new_speed;
}
