#include "double-foot.h"

#include <inttypes.h>

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

void double_foot::_move(Servo &servo,int from,int to)
{  
  if(from < to)
  {
    for(int angle = from;angle<=to;angle++)
    {
      servo.write(angle);
      delay(SERVO_FOOT_DELAY);
    }
  }
  else
  {
    for(int angle = from;angle>=to;angle--)
    {
       servo.write(angle);
       delay(SERVO_FOOT_DELAY);
    }
  }
}

void double_foot::_move(int servo_num,int from,int to)
{
  switch(servo_num)
  {
    case 0:
        Serial.print("l0:from ");
        Serial.print(from);
        Serial.print(" to ");
        Serial.println(to);
        _move(servo_l_0,from,to);
        l0 = to;
        break;
    case 1:
        Serial.print("l1:from ");
        Serial.print(from);
        Serial.print(" to ");
        Serial.println(to);
        _move(servo_l_1,from,to);
        l1 = to;
        break;
    case 2:
        Serial.print("l2:from ");
        Serial.print(from);
        Serial.print(" to ");
        Serial.println(to);
        _move(servo_l_2,from,to);
        l2 = to;
        break;
        
    case 3:
    case 10:
        Serial.print("r0:from ");
        Serial.print(from);
        Serial.print(" to ");
        Serial.println(to);
        _move(servo_r_0,from,to);
        r0 = to;
        break;
    case 4:
    case 11:
        Serial.print("r1:from ");
        Serial.print(from);
        Serial.print(" to ");
        Serial.println(to);
        _move(servo_r_1,from,to);
        r1 = to;
        break;
    case 5:
    case 12:
        Serial.print("r2:from ");
        Serial.print(from);
        Serial.print(" to ");
       Serial.println(to);
        _move(servo_r_2,from,to);
        r2 = to;
        break;

    default:
      break;        
  }
}

void double_foot::RestoreServo(int servo_num)
{
  switch(servo_num)
  {
    case 0:        
        _move(servo_num,l0,90);   
        break;
    case 1:       
        _move(servo_num,l1,90);       
        break;
    case 2:
        _move(servo_num,l2,90);   
        break;
        
    case 3:
    case 10:
         _move(servo_num,r0,90);   
        break;
    case 4:
    case 11:
         _move(servo_num,r1,90);   
        break;
    case 5:
    case 12:
        _move(servo_num,r2,90);   
        break;

    default:
      break;        
  } 
}

void double_foot::setup()
{
    servo_l_0.attach(3);
    servo_l_1.attach(5);
    servo_l_2.attach(6);

    servo_r_0.attach(9);
    servo_r_1.attach(10);
    servo_r_2.attach(11);

    init_servo();
}
void double_foot::init_servo()
{
  servo_l_0.write(90);
  servo_l_1.write(90);
  servo_l_2.write(90);
  servo_r_0.write(90);
  servo_r_1.write(90);
  servo_r_2.write(90);

  l0 = 90;
  l1 = 90;
  l2 = 90;
  r0 = 90;
  r1 = 90;
  r2 = 90;
}

void double_foot::foot_dance()
{
  int t0 = 60,t1 = 120;
   for(int angle = 90;angle<=t1;angle++)
    {
      servo_r_0.write(180-angle);
      servo_l_0.write(angle);      
      delay(SERVO_FOOT_DELAY);
    }

  for(int angle = t1;angle>=t0;angle--)
    {
      servo_l_0.write(angle);
      servo_r_0.write(180-angle);
      delay(SERVO_FOOT_DELAY);
    }

   for(int angle = t0;angle<=90;angle++)
    {
      servo_l_0.write(angle);
      servo_r_0.write(180-angle);
      delay(SERVO_FOOT_DELAY);
    }    
}

void double_foot::knee_dance()
{
  int t0 = 60,t1 = 120;
   for(int angle = 90;angle<=t1;angle++)
    {
      servo_l_1.write(angle);
      servo_r_1.write(180-angle);
      delay(SERVO_FOOT_DELAY);
    }

  for(int angle = t1;angle>=t0;angle--)
    {
      servo_l_1.write(angle);
      servo_r_1.write(180-angle);
      delay(SERVO_FOOT_DELAY);
    }

   for(int angle = t0;angle<=90;angle++)
    {
      servo_l_1.write(angle);
      servo_r_1.write(180-angle);
      delay(SERVO_FOOT_DELAY);
    }    
}

void double_foot::head_dance()
{
  int t0 = 60,t1 = 120;
   for(int angle = 90;angle<=t1;angle++)
    {
      servo_l_2.write(angle);
      servo_r_2.write(180-angle);
      delay(SERVO_FOOT_DELAY);
    }

  for(int angle = t1;angle>=t0;angle--)
    {
      servo_l_2.write(angle);
      servo_r_2.write(180-angle);
      delay(SERVO_FOOT_DELAY);
    }

   for(int angle = t0;angle<=90;angle++)
    {
      servo_l_2.write(angle);
      servo_r_2.write(180-angle);
      delay(SERVO_FOOT_DELAY);
    }    
}

void double_foot::head_restore()
{
   for(int angle=l2;angle>=90;angle--)
   {
       servo_l_2.write(angle);
       servo_r_2.write(180-angle);
       delay(SERVO_FOOT_DELAY);
   }

   l2 = 90;
   r2 = 90;
}

int double_foot::lean_left()
{  
   int t0 = 90,t1 = 105;
   for(int angle = t0;angle<=t1;angle++)
    {
      servo_l_0.write(angle);
      servo_r_0.write(angle);
      delay(SERVO_FOOT_DELAY);
    }

    delay(200);
    int t2 = 110;
    for(int angle = t1;angle<=t2;angle++)
    {    
      servo_l_0.write(angle);
      delay(2*SERVO_FOOT_DELAY);
    }

    l0 = t2;
    r0 = t1;

    return t2;
}

void double_foot::r2_lift(int _angle)
{
  int angle=90;
  for(;angle>=90-_angle;angle--)
  {
     servo_r_2.write(angle);
     delay(SERVO_FOOT_DELAY);
  }
  r2 = angle;
}

void double_foot::l1_lift(int _angle)
{
    _move(1,l1,90-_angle);
}

int double_foot::lean_right()
{  
   int t0 = 90,t1 = 75;
   for(int angle = t0;angle>=t1;--angle)
    {
      servo_l_0.write(angle);
      servo_r_0.write(angle);
      delay(SERVO_FOOT_DELAY);
    }

    delay(200);
    int t2 = 65;
    for(int angle1 = t1;angle1>=t2;--angle1)
    {    
      servo_r_0.write(angle1);
      delay(2*SERVO_FOOT_DELAY);
    }

    r0 = t2;
    l0 = t1;

    return t2;
}

void double_foot::l2_lift(int _angle)
{
  int angle=90;
  for(;angle<=90+_angle;++angle)
  {
     servo_l_2.write(angle);
     delay(SERVO_FOOT_DELAY);
  }
  l2 = angle;
}

void double_foot::r1_lift(int _angle)
{
    _move(4,r1,90+_angle);
}

void double_foot::test(Servo &servo)
{
  _move(servo,90,120);
  _move(servo,120,60);
  _move(servo,60,90);
}
