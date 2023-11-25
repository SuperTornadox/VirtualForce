#include <Arduino.h>
#include <HomeSpan.h>
#include <WiFi.h>

struct Motor:Service::LightBulb //创建一个 Service类型的结构体 叫做 Motor
{
  int MotorPin;
  SpanCharacteristic *power;
  SpanCharacteristic *level; //创建一个叫做 power 的 charateristic

  Motor(int pin)
  {//构造函数,初始化设备
    power= new Characteristic::On();
    level= new Characteristic::Brightness(0);
    level->setRange(0,100,1);
    MotorPin=pin;
    Serial.print("Configured Pin: ");
    Serial.println(MotorPin);
  }
  boolean update()
  {
   int value=level->getNewVal();
   Serial.print("value =");
   Serial.println(value);
   analogWrite(MotorPin,value*4095/255);
   return true;
  }

};
void setup() 
{
  //ESP 标准波特率 115200
  Serial.begin(115200);
  
  //###################################################### MARK: Homespan #####################################################################
  homeSpan.setPairingCode("20011230");
  homeSpan.begin(Category::Lighting,"Virtual Force System");
  Serial.println("Virtual Force activated");

  new SpanAccessory();                                                          
    new Service::AccessoryInformation();  
      new Characteristic::Identify();               
      new Characteristic::Name("Virtual Force Motor01"); 
    new Motor(33);
    new Motor(25);
    new Motor(26);
    new Motor(27);

}

void loop(){
  homeSpan.poll();
}
