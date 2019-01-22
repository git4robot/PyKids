//http://www.circuitbasics.com/setting-up-a-5v-relay-on-the-arduino/
//https://blog.csdn.net/c80486/article/details/52622042
//https://tompig.iteye.com/blog/1396904
include <math.h>

int pinOut = 10;
int pinDigitron = 2; //管脚D2连接到数码管的A脚，D3连B... D9连h

//定义一个数组表：不同数字的abcdefgh各段的取值
unsigned char abcdefgh[][8] = {
{1,1,1,1,1,1,0,0},  //0
{0,1,1,0,0,0,0,0},  //1
{1,1,0,1,1,0,1,0},  //2
{1,1,1,1,0,0,1,0},  //3
{0,1,1,0,0,1,1,0},  //4
{1,0,1,1,0,1,1,0},  //5
{1,0,1,1,1,1,1,0},  //6
{1,1,1,0,0,0,0,0},  //7
{1,1,1,1,1,1,1,0},  //8
{1,1,1,1,0,1,1,0},  //9
{1,1,1,0,1,1,1,0},  //A
{0,0,1,1,1,1,1,0},  //b
{1,0,0,1,1,1,0,0},  //C
{0,1,1,1,1,0,1,0},  //d
{1,0,0,1,1,1,1,0},  //E
{1,0,0,0,1,1,1,0},  //F
};
  
//在数码管中显示数字的函数
void displayDigit(unsigned char digit) {
  if ( digit >= 16 ) return;
  for (unsigned char x=0; x<8; x++)
    digitalWrite( pinDigitron + x, abcdefgh[digit][x] );
}

double Thermistor(int RawADC) {
 double Temp;
 Temp = log(10000.0*((1024.0/RawADC-1))); 
 Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
 Temp = Temp - 273.15;          
 Temp = (Temp * 9.0)/ 5.0 + 32.0; 
 return Temp;
}

void setup() {
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  
  //8段数码管，设置各脚为输出状态 
  for(int x=0; x<8; x++)
    pinMode(pinDigitron+x, OUTPUT);  
}

void loop() {             
  int val;                
  double temp;            
  val=analogRead(0);      
  temp=Thermistor(val);
  displayDigit(x);  
  Serial.print("Temperature = ");
  Serial.print(temp);   
  Serial.println(" F");
  if (temp >= 150){
    digitalWrite(pinOut, LOW);
  }
  else {
    digitalWrite(pinOut, HIGH);
  }
  delay(500);            
}
