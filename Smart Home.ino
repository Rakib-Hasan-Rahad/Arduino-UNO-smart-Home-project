
#include <Wire.h>
// Include NewLiquidCrystal Library for I2C
#include <LiquidCrystal_I2C.h>

const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;
const int i2c_addr = 0x27;
LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);

#define e_s1 A0 //echo pin
#define t_s1 A1 //Trigger pin

#define e_s2 A2 //echo pin
#define t_s2 A3 //Trigger pin

int relay = 10; // Out for light 

long dis_a=0,dis_b=0;
int flag1=0, flag2=0;
int person = 0; 

//**********************ultra_read****************************
void ultra_read(int pin_t,int pin_e,long &ultra_time){
long time;
pinMode(pin_t,OUTPUT);
pinMode(pin_e,INPUT);
digitalWrite(pin_t,LOW);
delayMicroseconds(2);
digitalWrite(pin_t,HIGH);
delayMicroseconds(10);
time=pulseIn (pin_e,HIGH);
ultra_time =  time / 29 / 2; 
}


void setup()
{
  Serial.begin(9600);// initialize serial communication at 9600 bits per second:

  pinMode(relay, OUTPUT);
  // Set display type as 16 char, 2 rows
  lcd.begin(16,2);
  
  // Print on first row
  lcd.setCursor(0,0); 
  lcd.print("Welcome to smart");
  
  // Wait 1 second
  //delay(1000);
  
  // Print on second row
  lcd.setCursor(0,1);
  lcd.print("Visitor Counter");
  
  // Wait 8 seconds
  delay(4000);
  
  // Clear the display
  lcd.clear();

}

void loop(){ 
//*************************
ultra_read(t_s1,e_s1,dis_a);delay(30);
ultra_read(t_s2,e_s2,dis_b);delay(30);
//*************************

Serial.print("da:");Serial.println(dis_a);
Serial.print("db:");Serial.println(dis_b);   

if(dis_a<80 && flag1==0){flag1=1;
if(flag2==0){person = person+1;} 
}

if(dis_b<80 && flag2==0){flag2=1;
if(flag1==0){person = person-1;}
}

if(dis_a>80 && dis_b>80 && flag1==1 && flag2==1){
flag1=0, flag2=0;
delay(1000); 
}

lcd.setCursor(0, 0);
lcd.print("Total Person: ");
lcd.print(person);
lcd.print("  ");
lcd.setCursor(0,1); 
lcd.print("Light is ");

if(person>0){
  digitalWrite(relay,HIGH); 
  lcd.print("On ");}
else{
  digitalWrite(relay,LOW);
  lcd.print("Off");}
}
