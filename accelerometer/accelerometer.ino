#include <NewPing.h>


#define LED4 4
#define LED6 6
#define buzzer 12 // buzzer pin
#define led 13 //led pin
 
#define x A0 // x_out pin of Accelerometer
#define y A1 // y_out pin of Accelerometer
#define z A2 // z_out pin of Accelerometer
 
/*variables*/
int xsample=0;
int ysample=0;
int zsample=0;
long start;
int buz=0;
 
/*Macros*/
#define samples 50
#define maxVal 20 // max change limit
#define minVal -20 // min change limit
#define buzTime 5000 // buzzer on time
 
void setup()
{
Serial.begin(9600); // initializing serial
Serial.print("Calibrating.....");
Serial.print("Please wait...");
pinMode(buzzer, OUTPUT);
pinMode(led, OUTPUT);
buz=0;
digitalWrite(buzzer, buz);
digitalWrite(led, buz);
for(int i=0;i<samples;i++) // taking samples for calibration
{
xsample+=analogRead(x);
ysample+=analogRead(y);
zsample+=analogRead(z);
}
 
xsample/=samples; // taking avg for x
ysample/=samples; // taking avg for y
zsample/=samples; // taking avg for z
 
delay(3000);
Serial.print("Calibrated");
delay(1000);
Serial.print("Device Ready");
delay(1000);
}
 
void loop()
{
int value1=analogRead(x); // reading x out
int value2=analogRead(y); //reading y out
int value3=analogRead(z); //reading z out
 
int xValue=xsample-value1; // finding change in x
int yValue=ysample-value2; // finding change in y
int zValue=zsample-value3; // finding change in z
 
/*displying change in x,y and z axis values over lcd*/
Serial.print(xValue);
Serial.print(yValue);
Serial.print(zValue);
delay(100);
 
/* comparing change with predefined limits*/
if(xValue < minVal || xValue > maxVal || yValue < minVal || yValue > maxVal || zValue < minVal || zValue > maxVal)
{
if(buz == 0)
digitalWrite(LED4, HIGH);
buz=1;
}
 
else if(buz == 1) // buzzer flag activated then alerting earthquake
{
digitalWrite(LED6, HIGH);
}
 
else
{

}
 
digitalWrite(buzzer, buz); // buzzer on and off command
digitalWrite(led, buz); // led on and off command
 
/*sending values to processing for plot over the graph*/
Serial.print("x=");
Serial.println(xValue);
Serial.print("y=");
Serial.println(yValue);
Serial.print("z=");
Serial.println(zValue);
Serial.println(" $");
}