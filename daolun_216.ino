#include <Servo.h>   //调用库函数
Servo servo;      //定义舵机变量名
int servoPin = 9;   //定义舵机接口9，只有9或者10可用

int trigPin =2;    // // trig接2端口
int echoPin = 3;   // echo接3端口
long duration, distance;   //定义变量，用于存取数据
long aver[3];   //定义数组，用于存取数据

void setup() {     
  servo.attach(servoPin);   //设定舵机的接口，9或者10接口可利用 
 pinMode(trigPin, OUTPUT);   //设置为输出模式 触发
  pinMode(echoPin, INPUT);   //设置其为输入模式  回声
  servo.write(0);    //用于设定舵机旋转角度的语句，可设定的角度范围是0°到180°。
  delay(1000);     //延时1S；
  servo.detach();  //使舵机与其接口分离，该接口9可继续被用作PWM接口。
} 
//超声波测距，子程序
void measure() {  
  digitalWrite(trigPin, LOW);//给一个低电平
  delayMicroseconds(5);//时间为5毫秒
  digitalWrite(trigPin, HIGH);//给一个高电平
  delayMicroseconds(15);//时间为15毫秒
  digitalWrite(trigPin, LOW);//再给一个低电平
  duration = pulseIn(echoPin, HIGH);//接收高电平时间
  distance = duration *0.034 / 2;//计算距离
}

void loop() { 

//将测量数值记录在数组里面
  for (int i=0;i<=2;i++) {   
    measure();               
    aver[i]=distance;     
       
    delay(50);           
  }
 //算三次的平均值
  distance=(aver[0]+aver[1]+aver[2])/3; 
   Serial.println(distance);   //打印
//如果距离小于40，转动舵机70°
  if (distance<40) {
    servo.attach(servoPin); //设定舵机的接口，9接口可利用  
    delay(1);
    servo.write(70);  //转动舵机70°
    delay(5000);  //延时5秒
    servo.write(0);    //转回0°
    delay(1000);//延时1秒
    servo.detach();      //使舵机与其接口分离，该接口9可继续被用作PWM接口。

  }
}
