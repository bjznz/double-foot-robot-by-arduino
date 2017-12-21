#include <Servo.h>
#include "double-foot.h"

const int pinLED = 13;
double_foot dfoot;

void setup_HCSR04()
{
    pinMode(A0, OUTPUT); //->HC-SR04 input/Trig
    pinMode(A1, INPUT); //->HC-SR04 output/Echo
}

float getDistance()
{
    digitalWrite(A0, HIGH); //使发出发出超声波信号接口高电平10μs ，这里是至少10μs 
    delayMicroseconds(10); 
    digitalWrite(A0, LOW);  // 保持发出超声波信号接口低电平 
    float pulse_time = pulseIn(A1, HIGH);  //  读出接收脉冲的时间 
    float distance= pulse_time/58;       // 将脉冲时间转化为距离（单位：厘米） 
    distance = (int(distance * 100.0)) / 100.0; //保留两位小数 

    Serial.println(distance);   // 输出距离值  
    return distance;
}

void setup()
{
  dfoot.setup();
  setup_HCSR04();
  pinMode(pinLED,OUTPUT); 
  digitalWrite(pinLED, HIGH);//点亮LED
  Serial.begin(115200);
 
  //Serial.println("Wanring!!Do suggest you hold the robot!");
  //delay(3000);
  Serial.println("Let's go...");    
}

void action_1()
{     
    dfoot.lean_left();  //身体向左侧倾斜
    dfoot.r2_lift(30); //抬右腿
    dfoot._move(3,dfoot.r0,90);//右脚掌放平
    dfoot.l1_lift(30); //左侧身体前倾度数
    dfoot._move(0,dfoot.l0,90);//左脚掌恢复至中间位置,左侧身体恢复到中间位置(此时身体前倾)
    dfoot._move(0,dfoot.l0,60);//左脚向右扭，身体向右倾度数，让右脚落地
    dfoot._move(3,dfoot.r0,70);//右脚向右扭,让身体往右侧倾斜
    dfoot._move(2,dfoot.l2,120);//左腿向前迈步    
    dfoot._move(0,dfoot.l0,90); //左脚掌放平  
      
    dfoot._move(1,dfoot.l1,90); //左腿伸直
    dfoot._move(3,dfoot.r0,90); //右脚掌放平(右侧身体恢复直立位置)
    dfoot.head_restore(); //抬头//最上面两个舵机放平
}

void action_2()
{  
    dfoot.init_servo();        
    dfoot.lean_right();  //向右倾斜
    dfoot.l2_lift(30);   //抬左腿
    dfoot._move(0,dfoot.l0,90);//左脚掌放平
    dfoot.r1_lift(30); //右侧身体前倾度数
    dfoot._move(3,dfoot.r0,90);//右脚掌恢复至中间位置,右侧身体恢复到中间位置(此时身体前倾)
    dfoot._move(3,dfoot.r0,120);//右脚掌向左扭/顶，身体向左侧倾斜
    dfoot._move(0,dfoot.l0,110);//左脚向左扭，身体向左倾斜    
    dfoot._move(5,dfoot.r2,60);//右腿向前迈步    
    dfoot._move(3,dfoot.r0,90);//右脚掌放平  
    
    dfoot._move(4,dfoot.r1,90);//右腿伸直
    dfoot._move(0,dfoot.l0,90);
  dfoot.head_restore();
}

void action_3()
{  
    dfoot.init_servo();        

    dfoot.lean_right();  //向右倾斜
    dfoot.RestoreServo(0);     
    for(int index=0;index<3;++index)
    {              
      dfoot._move(0,dfoot.l0,120);
      dfoot.RestoreServo(0);     
    }

    dfoot.l2_lift(30);   //抬左腿
    dfoot._move(4,dfoot.r1,60); //右侧后仰
    dfoot.RestoreServo(4);
    dfoot._move(2,dfoot.l2,70); //左腿后抬
     dfoot._move(4,dfoot.r1,120);
    dfoot.RestoreServo(4);
    dfoot.RestoreServo(2);
    dfoot.RestoreServo(3);   
}
    

void loop()
{ 
  float distance = getDistance();
   if( distance <=0 || distance >= 4 )
  {
    digitalWrite(pinLED, LOW);//点亮LED
    delay(200);
    digitalWrite(pinLED, HIGH);//点亮LED
    return;
  }
   // delay(10000);
    action_2();
    action_3();

   delay(300);
   dfoot.foot_dance();
   dfoot.foot_dance();
   delay(100);
   dfoot.init_servo();    
   dfoot.knee_dance();
   delay(100);
   action_1();
   delay(100);   

 //  delay(50000);
}


