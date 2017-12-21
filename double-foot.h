#ifndef  DOUBLE_FOOT_H
#define DOUBLE_FOOT_H

#include <inttypes.h>
#include <Servo.h>

#define SERVO_FOOT_DELAY	23	//milliseconds

class double_foot {
public:
	double_foot():
	l0(90),l1(90),l2(90),r0(90),r1(90),r2(90)
	{		
	}

	~double_foot() {}
	
  void _move(int servo_num,int from,int to);
  void setup();
	void init_servo();
	void foot_dance();
	void knee_dance();
	void head_dance();
	int lean_left();
	void test(Servo &servo);
  void r2_lift(int _angle = 45);
  void l1_lift(int _angle);
  void head_restore();
  int lean_right();
  void l2_lift(int _angle);
  void r1_lift(int _angle);
  void RestoreServo(int servo_num);
private:
  void _move(Servo &servo, int from, int to);
  
public:
	Servo servo_l_0;
	Servo servo_l_1;
	Servo servo_l_2;
	Servo servo_r_0;
	Servo servo_r_1;
	Servo servo_r_2;

  int l0;
  int l1;
  int l2;
  int r0;
  int r1;
  int r2;
};

#endif // ! DOUBLE_FOOT_H
