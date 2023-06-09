#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3f, 16, 2);
void starpixel(); // //lcd 화면 전체에 별 출력

unsigned long prev_time=0; //millis()이전의 시간을 저장
unsigned long now_time=0; //현재 시간을 저장
int speakerPin = 8; //부저
int check1=10; //적외선 센서
int check2=11;
int check3=12;
int check4=13;
double tones[]  = {
        195.9977, 246.9417,  
        293.6648 , 391.9954, 
        493.8833, 207.6523, 
        261.6256, 311.1270, 
        415.3047, 523.2511, 
        233.0819, 293.6648, 
        349.2282, 466.1638, 
        587.3295}; //효과음
int numTones = 15; //효과음 개수
unsigned int sum=0; //저금통안에 있는 돈
unsigned int coin500=500, coin100=100, coin50=50, coin10=10; //코인 금액;
int count=1;
byte coinPixel0[8] = {
        B01110,
        B11111,
        B11111,
        B11011,
        B11011,
        B11111,
        B11111,
        B01110
};
byte coinPixel1[8] = {
        B01100,
        B11110,
        B11110,
        B10110,
        B10110,
        B11110,
        B11110,
        B01100
};
byte coinPixel2[8] = {
        B00100,
        B00100,
        B00100,
        B00100,
        B00100,
        B00100,
        B00100,
        B00100
};
byte coinPixel3[8] = {
        B00110,
        B01111,
        B01111,
        B01101,
        B01101,
        B01111,
        B01111,
        B00110
};
byte coinPixel4[8] = {
        B01110,
        B11111,
        B11111,
        B11011,
        B11011,
        B11111,
        B11111,
        B01110
};
byte starPixel0[8] = {
       
        B11100,
        B11100,
        B01110,
        B00110,
        B00000,
        B00000,
        B00000,
        B00000
        
};
byte starPixel1[8] = {
     
        B00111,
        B00111,
        B01110,
        B01100,
        B00000,
        B00000,
        B00000,
        B00000
        
};
byte starPixel2[8] = {
        B00000,
        B00000,
        B00000,
        B00001,
        B00001,
        B00011,
        B11111,
        B01111
};
byte starPixel3[8] = {
        B00000,
        B00000,
        B00000,
        B10000,
        B10000,
        B11000,
        B11111,
        B11110
};





void setup() 
{ 
   lcd.begin();
   lcd.backlight();
   lcd.createChar(0, coinPixel0); //문자를 저장.
   lcd.createChar(1, coinPixel1);
   lcd.createChar(2, coinPixel2);
   lcd.createChar(3, coinPixel3);
   lcd.createChar(4, coinPixel4);
   lcd.createChar(5, starPixel0);
   lcd.createChar(6, starPixel1);
   lcd.createChar(7, starPixel2);
   lcd.createChar(8, starPixel3);
   pinMode(speakerPin, OUTPUT);
   pinMode(check1,INPUT);
   pinMode(check2,INPUT);
   pinMode(check3,INPUT);
   pinMode(check4,INPUT);
   prev_time=millis(); //현재 시간 저장
}


void loop() 
{ 
    now_time=millis();
    lcd.setCursor(0,0);
    lcd.print("Smart Piggy Bank");
    lcd.setCursor(5,1);
    lcd.print(sum);
    lcd.setCursor(10,1);
    lcd.print("W");
    
    if(digitalRead(check1)==0){ //적외선 센서에 동전이 인식되면 실행.
        for (int j = 0; j < numTones; j++) //효과음 출력.
        {
            starpixel(); //lcd화면 전체에 별 출력
            tone(speakerPin, tones[j]);
            delay(10);
        }
        tone(speakerPin, tones[14]); //끝음을 더 길게.
        delay(50);
        noTone(speakerPin);
        sum=sum+coin10; //총 금액을 더해줌.
    }
    else if(digitalRead(check2)==0){
        for (int j = 0; j < numTones; j++)
        {
            starpixel();
            tone(speakerPin, tones[j]);
            delay(10);
        }
        tone(speakerPin, tones[14]);
        delay(50);
        noTone(speakerPin);
        sum=sum+coin50;
    }
    else if(digitalRead(check3)==0){
       
        for (int j = 0; j < numTones; j++)
        {
            starpixel();
            tone(speakerPin, tones[j]);
            delay(10);
        }
        tone(speakerPin, tones[14]);
        delay(50);
        noTone(speakerPin);
        sum=sum+coin100;
    }
    else if(digitalRead(check4)==0){
         
        for (int j = 0; j < numTones; j++)
        {
            starpixel();
            tone(speakerPin, tones[j]);
            delay(10);
        }
        tone(speakerPin, tones[14]);
        delay(50);
        noTone(speakerPin);
        sum=sum+coin500;
    }
    if (now_time-prev_time>=200){ //딜레이를 쓰지 않고 움직이는 도트(딜레이를 쓰면 센서값을 바로바로 못읽음.)
        prev_time=now_time;
        if(count<5) {  //돌아가는 코인 출력
        lcd.setCursor(0,1);
        lcd.write(byte(count));
        lcd.setCursor(1,1);
        lcd.write(byte(count));
        lcd.setCursor(2,1);
        lcd.write(byte(count));
        lcd.setCursor(3,1);
        lcd.write(byte(count));
        lcd.setCursor(4,1);
        lcd.write(byte(count));
        lcd.setCursor(11,1);
        lcd.write(byte(count));
        lcd.setCursor(12,1);
        lcd.write(byte(count));
        lcd.setCursor(13,1);
        lcd.write(byte(count));
        lcd.setCursor(14,1);
        lcd.write(byte(count));
        lcd.setCursor(15,1);
        lcd.write(byte(count));
        count++;
        }
        else
          count=1;
     }
}
void starpixel(){ //lcd 화면 전체에 별 출력
        int i, j;
        for(i=0; i<16; i+=2){
            lcd.setCursor(i+1,1);
            lcd.write(byte(5));
            lcd.setCursor(i,1);
            lcd.write(byte(6));
            lcd.setCursor(i,0);
            lcd.write(byte(7));
            lcd.setCursor(i+1,0);
            lcd.write(byte(8));
        }
        lcd.clear(); //별모양이 남아있지 않게 lcd 초기화.
}
