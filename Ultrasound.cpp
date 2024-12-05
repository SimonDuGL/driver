#include <Wire.h>
#include "Ultrasound.h"

Ultrasound::Ultrasound()
{
  Wire.begin();
}

//Write byte
bool Ultrasound::wireWriteByte(uint8_t addr, uint8_t val)
{
    Wire.beginTransmission(addr);
    Wire.write(val);
    if( Wire.endTransmission() != 0 ) 
    {
        return false;
    }
    return true;
}

//Write multiple bytes
bool Ultrasound::wireWriteDataArray(uint8_t addr, uint8_t reg,uint8_t *val,unsigned int len)
{
    unsigned int i;

    Wire.beginTransmission(addr);
    Wire.write(reg);
    for(i = 0; i < len; i++) 
    {
        Wire.write(val[i]);
    }
    if( Wire.endTransmission() != 0 ) 
    {
        return false;
    }
    return true;
}

//Read the specified length byte
int Ultrasound::wireReadDataArray(uint8_t addr, uint8_t reg, uint8_t *val, unsigned int len)
{
    unsigned char i = 0;  
    /* Indicate which register we want to read from */
    if (!wireWriteByte(addr, reg)) 
    {
        return -1;
    }
    Wire.requestFrom(addr, len);
    while (Wire.available()) 
    {
        if (i >= len) 
        {
            return -1;
        }
        val[i] = Wire.read();
        i++;
    }
    /* Read block data */    
    return i;
}

//Set ultrasonic rgb to breathing light mode
//r1，g1，b1 represent the breathing cycle of the rgb light on the right, for example,20，20，20，which means a cycle of 2s
//r2，g2，b2 represent the breathing cycle of the rgb light on the left 
void Ultrasound::Breathing(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2)
{
  uint8_t breathing[6]; 
  uint8_t value = RGB_WORK_BREATHING_MODE;
  
  wireWriteDataArray(ULTRASOUND_I2C_ADDR, RGB_WORK_MODE, &value, 1);
  breathing[0] = r1;breathing[1] = g1;breathing[2] = b1;//RGB1 blue
  breathing[3] = r2;breathing[4] = g2;breathing[5] = b2;//RGB2
  wireWriteDataArray(ULTRASOUND_I2C_ADDR, RGB1_R_BREATHING_CYCLE,breathing,6); //Send color value
}

//Set the color of the ultrasonic rgb light
//r1, g1, b1 represent the ratio of the three primary colors of the rgb lamp on the right, the range is 0-255
//r2, g2, b2 represent the ratio of the three primary colors of the rgb lamp on the left, the range is 0-255
void Ultrasound::Color(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2)
{
  uint8_t RGB[6]; 
  uint8_t value = RGB_WORK_SIMPLE_MODE;
  
  wireWriteDataArray(ULTRASOUND_I2C_ADDR, RGB_WORK_MODE,&value,1);
  RGB[0] = r1;RGB[1] = g1;RGB[2] = b1;//RGB1
  RGB[3] = r2;RGB[4] = g2;RGB[5] = b2;//RGB2
  wireWriteDataArray(ULTRASOUND_I2C_ADDR, RGB1_R,RGB,6);
}

//Get the distance measured by ultrasonic in mm
u16 Ultrasound::GetDistance()
{
  u16 distance;
  wireReadDataArray(ULTRASOUND_I2C_ADDR, 0,(uint8_t *)&distance,2);
  return distance;
}

void Ultrasound::rainbow_color()             ////Gradient rainbow light
{ 

      if(i<33&&i>=0){
          r=255;
          g=7.65*i;
          b=0;
      }else if(i<50&&i>=33){
          r=750-15*i;
          g=255;
          b=0;
      }else if(i<=66&&i>=50){
          r=0;
          g=255;
          b=15*i-750;
      }else if(i<=83&&i>66){
          r=0;
          g=1250-15*i;
          b=255;
      }else if(i<=100&&i>83){
          r=9*i-750;
          g=0;
          b=255;
      }else{
          r=5*i-350;
          g=0;
          b=1500-12.5*i;
        }
      i++;
      if(i>120)
      i=0;
      Color(r, g,b, r, g, b);

 }
