#include <avr/io.h>
#include <Keypad.h>
#include <LiquidCrystal.h>

const int rs = A1, en = A0, d4 = 13, d5 = 12, d6 = 11, d7 = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'} 
};
byte rowPins[ROWS] = {6, 7, 8, 9};
byte colPins[COLS] = {2, 3, 4, 5};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

/*
String jaut0 = "12*12-140=";
String jaut1 = "2+2-1=";
String jaut2 = "2+2x2=";
String jaut3 = "2^2+5=";
String jaut4 = "100/20+1=";
String jaut5 = "7-8+9+5-14=";
String jaut6 = "54+45-90=";
String jaut7 = "158+4-150=";
String jaut8 = "84+8*2/6-5+14=";
String jaut9 = "125/5-19=";
String jautajumi[]={jaut0,jaut1,jaut2,jaut3,jaut4,jaut5,jaut6,jaut7,jaut8,jaut9};
*/

char kodaChar[]={'1','2','3','4','5','6','7','8','9','0'};
int p = 0;
int ans = 0;
int rNum = 0;
int pins[5]={1,0,A5,A4,A2};
int correct=0;
int binCode[5];
int pinCode[5];
char kods[5];
char defKods[5];
int t=0;
int exploaded=0;
int defused=0;
int easyMode=0;
int tries=0;
int mode=0;
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;

//=============================[SETUP]==============================
void setup(){
  lcd.begin(16, 2);
  pinMode(A2,INPUT);
  pinMode(A4,INPUT);
  pinMode(A5,INPUT);
  pinMode(A3,OUTPUT); //buzzer
}

//=============================[B_MENU_EASY_MODE_1_0]==============================
void menuB(){
      tone(A3, 100);
      delay(100);
      noTone(A3);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Enable easy mode");
      lcd.setCursor(0, 1);
      lcd.print("'A'-Yes  'B'-No");
      
      char keyC = keypad.waitForKey();
      switch (keyC){
        case 'A':{
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Easy mode ON");
      easyMode = 1;
      tone(A3, 600);
      delay(100);
      tone(A3, 300);
      delay(100);
      tone(A3, 500);
      delay(100);
      noTone(A3);
      delay(200);
          mainMenu();
          break;
        }
        case 'B':{
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Easy mode OFF");
      easyMode = 0;
      tone(A3, 300);
      delay(100);
      tone(A3, 100);
      delay(100);
      tone(A3, 400);
      delay(100);
      noTone(A3);
      delay(200);          
          mainMenu();
          break;
        }
        default:
          menuB();
        }
  }

//=============================[CLEAR_STATS?]==============================
void clearStats(){
      tone(A3, 100);
      delay(100);
      noTone(A3);
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print(" Clear stats?");
      lcd.setCursor(0, 1);
      lcd.print("'A'-Yes  'B'-No");
      
      char keyC = keypad.waitForKey();
      switch (keyC){
        case 'A':{
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Stats cleared");
          defused=0;
          exploaded=0;          
      tone(A3, 600);
      delay(100);
      tone(A3, 300);
      delay(100);
      tone(A3, 500);
      delay(100);
      noTone(A3);
          mainMenu();
          break;
        }
        case 'B':{
          mainMenu();
          break;
        }
        default:
          clearStats();
        }
}

//=============================[MENU_C]==============================
void menuC(){
  lcd.clear();
  lcd.setCursor(0, 0);  
  lcd.print("BOMB STATISTICS:");
  lcd.setCursor(0, 1);  
  lcd.print("* CLEAR   D EXIT");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Defused  :");
  lcd.setCursor(10, 0);
  lcd.print(defused);
  lcd.setCursor(0, 1);
  lcd.print("Exploaded:");
  lcd.setCursor(10, 1);
  lcd.print(exploaded);

  char key = keypad.waitForKey();
    switch (key){
    case 'D':{
    tone(A3, 100);
      delay(100);
      noTone(A3);
      if (mode = 0){
        mainMenu();
        }
      else if(mode = 1){
         idleScreen2();
        }
      break;
      }
    case '*':{
      clearStats();
      break;
    }
      
    default:
    tone(A3, 100);
      delay(100);
      noTone(A3);
      menuC();
  }
}
//=============================[NO_BOOM]==============================
void noBoom(){
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  tries=0;
  defused++;
  lcd.clear();
  lcd.setCursor(0, 0);
  digitalWrite(1, LOW);
  digitalWrite(0, HIGH);
  lcd.print("Bomb has");
  lcd.setCursor(0, 2);
  lcd.print("been defused!");
  lcd.noCursor();
  tone(A3, 500,100);
  delay(100);
  tone(A3, 200,100);
  delay(100);
  tone(A3, 600,100);
  delay(100);
  tone(A3, 400,100);
  delay(100);
  tone(A3, 800,100);
  delay(80);
  tone(A3, 700,100);
  delay(1000);
  noTone(A3);
  digitalWrite(0, LOW);
  lcd.clear();
    idleScreen();
}
//=============================[BOOM]==============================
void boom(){
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);  
  tries=0;
  exploaded++;
lcd.clear();
digitalWrite(1, HIGH);
lcd.setCursor(0, 0);
digitalWrite(A2, HIGH);
tone(A3, 500);
lcd.print("*   BOOOOOOM   *");
lcd.setCursor(0, 1);
lcd.noCursor();
delay(2000);
noTone(A3);
digitalWrite(1, LOW);
digitalWrite(A2, LOW);
lcd.clear();
    idleScreen();
}

//=============================[NO_BOOM_2]==============================
void noBoom2(){
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  tries=0;
  defused++;
  lcd.clear();
  lcd.setCursor(0, 0);
  digitalWrite(1, LOW);
  digitalWrite(0, HIGH);
  lcd.print("Bomb has");
  lcd.setCursor(0, 2);
  lcd.print("been defused!");
  lcd.noCursor();
  tone(A3, 500,100);
  delay(100);
  tone(A3, 200,100);
  delay(100);
  tone(A3, 600,100);
  delay(100);
  tone(A3, 400,100);
  delay(100);
  tone(A3, 800,100);
  delay(80);
  tone(A3, 700,100);
  delay(1000);
  noTone(A3);
  digitalWrite(0, LOW);
  lcd.clear();
    idleScreen2();

}
//=============================[BOOM_2]==============================
void boom2(){
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);  
  tries=0;
  exploaded++;
lcd.clear();
digitalWrite(1, HIGH);
lcd.setCursor(0, 0);
digitalWrite(A2, HIGH);
tone(A3, 500);
lcd.print("*   BOOOOOOM   *");
lcd.setCursor(0, 1);
lcd.noCursor();
delay(2000);
noTone(A3);
digitalWrite(1, LOW);
digitalWrite(A2, LOW);
lcd.clear();
idleScreen2();
}

//==================================[CODE_CHECK]==============================
void codeCheck(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Checking code");
  lcd.setCursor(0,1);
  for(int i=0;i<15;i++){
  lcd.print("#");
  delay(50);  
    }
        if(easyMode == 0){      
            if(defKods[0] == kods[0] && defKods[1] == kods[1] && defKods[2] == kods[2] && defKods[3] == kods[3] && defKods[4] == kods[4]){
            noBoom();
            }
        else {
            boom();
            }
        }
          else if(easyMode == 1){
             if(defKods[0] == kods[0] && defKods[1] == kods[1] && defKods[2] == kods[2] && defKods[3] == kods[3] && defKods[4] == kods[4] && tries<=3){
              noBoom();
            }
          else if(easyMode = 1 && defKods != kods && tries<3){
            lcd.clear();
            lcd.print("Wrong code!");
            lcd.setCursor(0,1);
            lcd.print("Try again!");
            delay(500);
              p = 0;
              lcd.clear();
              CountDown();
          }
            else{
            boom();
            }
        }
}


//===================================[COUNTDOWN_v2]==============================
void CountDown(){
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
    while(t>=0){
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis >= 1000){
            previousMillis = currentMillis;
            t=t-1;
            //lcd.clear();
            lcd.setCursor(5,0);
            lcd.print(t);
            lcd.print("   ");
            tone(A3,300,200);
        }
            else if(currentMillis-previousMillis >= 10){
                char a = keypad.getKey();
                if(a != NO_KEY){
                defKods[p] = a;
                lcd.setCursor(p+5,1);
                lcd.print(defKods[p]);
                p++;
                }
            }
                if(p>4){
                  codeCheck();
                  }
            
          if(t<=0){
           boom();
          }
      }
}
/*
//===========================================[QUESTIONS]==========================================
void questions(){
  randomSeed(millis());
  rNum = random(0,9);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(jautajumi[rNum]);
  char key = keypad.waitForKey();
  if(key != NO_KEY){
     tone(A3, 300, 100);
        lcd.setCursor(0, 1);
        lcd.print(key);
        delay(500);
        lcd.clear();
  }
  randomSeed(millis());
  rNum = random(0,9);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(jautajumi[rNum]);
  char key1 = keypad.waitForKey();
  if(key1 != NO_KEY){
     tone(A3, 300, 100);
        lcd.setCursor(0, 1);
        lcd.print(key1);
        delay(500);
        lcd.clear();
  }
        p=0;
        CountDown();
}
*/
//=================================================================================================================================================================================<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//=============================[CUSTOM_TIMER]==============================
void customTimer(){
        t=0;
        lcd.setCursor(0, 0);  
        lcd.print("'A' +10 'B' -10");
        lcd.setCursor(2, 1);
        lcd.print("* to select");
        delay(1000);
        lcd.clear();
        lcd.setCursor(0, 0);  
        lcd.print(" Choose timer:");

        while(1){
        lcd.clear();
        lcd.setCursor(0, 0);  
        lcd.print("Time: ");
        lcd.print(t);
          char keyT = keypad.getKey();

            if(keyT == 'A'){
              t = t + 10;
              }
              else if(keyT == 'B'){
                t = t - 10;
                }
                else if(keyT == '*' && t>0){ 
                  lcd.clear(); 
                  lcd.setCursor(5, 0);  
                  lcd.print("Time: "); 
                  lcd.print(t);
                  delay(1000);
                  t=t+1;
                  lcd.clear(); 
                  CountDown();
                  }
                  else if (keyT == '*' && t<10){
                    lcd.clear();
                    lcd.setCursor(1, 0);
                    lcd.print("Time has to be");
                    lcd.setCursor(6, 1);
                    lcd.print("positive");
                    delay(1000);
                    lcd.clear(); 
                    customTimer();
                    }
                    delay(10);
          }
}
//=============================[TIMER]==============================
void timer(){
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  lcd.clear();
  lcd.setCursor(0, 0);  
  lcd.print(" Choose timer");
  lcd.setCursor(0, 1);
  lcd.print(" with A,B,C,D");
  delay(1000);
  lcd.clear();
     lcd.print(" A:10sec B:20sec");
     lcd.setCursor(0, 1);
     lcd.print(" C:30sec D:CUSTM");
  lcd.noCursor();
  char keyT = keypad.waitForKey();
       switch (keyT) {
     case 'A': 
     {
      //t=181;    //3min
      t=11;
     tone(A3, 300, 100);
     digitalWrite(0,HIGH);
     delay(100);
     digitalWrite(0,LOW);
     lcd.clear();
     lcd.print(">A:10sec B:20sec");
     lcd.setCursor(0, 1);
     lcd.print(" C:30sec D:CUSTM");
     lcd.noCursor();
      delay(200);
      lcd.clear();
      CountDown();
      break;
      }
     case 'B': 
     {
      //t=301;  //5min
      t=21;
     tone(A3, 300, 100);
     digitalWrite(0,HIGH);
     delay(100);
     digitalWrite(0,LOW);
      lcd.clear();
     lcd.print(" A:10sec>B:20sec");
     lcd.setCursor(0, 1);
     lcd.print(" C:30sec D:CUSTM");
     lcd.noCursor();
      delay(200);
      lcd.clear();
      CountDown();
      break;
      }
        case 'C': 
     {
      //t=601;
      t=31;
     tone(A3, 300, 100);
     digitalWrite(0,HIGH);
     delay(100);
     digitalWrite(0,LOW);
      lcd.clear();
     lcd.print(" A:10sec B:20sec");
     lcd.setCursor(0, 1);
     lcd.print(">C:30sec D:CUSTM");
     lcd.noCursor();
      delay(200);
      lcd.clear();
      CountDown();
      break;
      }
        case 'D': 
        {
      //t=901;
     tone(A3, 300, 100);
     digitalWrite(0,HIGH);
     delay(100);
     digitalWrite(0,LOW);
      lcd.clear();
     lcd.print(" A:10sec B:20sec");
     lcd.setCursor(0, 1);
     lcd.print(" C:30sec>D:CUSTM");
     lcd.noCursor();
      delay(200);
      lcd.clear();
      //CountDown();
      customTimer();
      break;
      }
      
      default:
      timer();
       }      //switch
}           //timer
//=============================[IDLE]==============================
void idleScreen(){
      noTone(A3);
  lcd.clear();
  lcd.print("Any key to start");
  lcd.setCursor(0, 1);
  lcd.print(" '*' for setup");

    char key = keypad.waitForKey();                         //gaida ievadi no personas.
    switch (key){
      case '*':{
      tone(A3, 100);
      delay(100);
      noTone(A3);
      mainMenu();
      break;
      }
    default:
    tone(A3,100,100);
    start();
      }
}

//=============================[CHECK_WIRES]==============================
void check(){
  lcd.clear();
  pinMode(0,INPUT);
  pinMode(1,INPUT);

  for(int i=0;i<=4;i++){
    int a=digitalRead(pins[i]);
      if(a == HIGH){
      pinCode[i]=1;
      }
      else if(a == LOW){
      pinCode[i]=0;
      }
    //lcd.setCursor(i,0);
    //lcd.print(a);
    //delay(1000);
   }
  lcd.setCursor(0,0);
  lcd.print("CHECKING");
  lcd.setCursor(0,1);
  for(int i=0;i<15;i++){
  lcd.print("#");
  delay(200);  
    }

    for(int i=0;i<=4;i++){
      if(pinCode[i] == binCode[i])
      correct++;
      }
    
            if(pinCode[0] == binCode[0] && pinCode[1] == binCode[1] && pinCode[2] == binCode[2] && pinCode[3] == binCode[3] && pinCode[4] == binCode[4]){
              noBoom2();
            }
              else{              
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("WRONG CODE");
                lcd.setCursor(0,1);
                lcd.print("TRY AGAIN!");
                delay(1000);   
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("CORRECT:");
                lcd.setCursor(5,1);
                lcd.print(correct);
                lcd.print(" / 5");
                delay(1000);
                correct=0;
                defuse();
              }
}

//=============================[DEFUSE]==============================
void defuse(){
  pinMode(0,INPUT);
  pinMode(1,INPUT);
   lcd.clear();     
    while(t>=0){
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= 1000){
        previousMillis = currentMillis;
            t=t-1;
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print(t);
            tone(A3,300,200);

            
  for(int i=0;i<=4;i++){
    int a=digitalRead(pins[i]);
      if(a == HIGH){
      pinCode[i]=1;
      }
      else if(a == LOW){
      pinCode[i]=0;
      }
    lcd.setCursor(i,1);
   }
      for(int i=0;i<=4;i++){
      lcd.setCursor(i*3+1,1);
            lcd.print(pinCode[i]);
      }
   
       }
            else if (currentMillis - previousMillis >= 100){
            char key = keypad.getKey();
            if(key == '*'){
              check();
              }
            }
     if(t<=0){
      boom2();
      }
    }
}
//=============================[WIRECUTTER]==============================
void wireCutter(){
  correct=0;
     tone(A3, 300, 100);
  pinMode(0,INPUT);
  pinMode(1,INPUT);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("GENERATING CODE");
  lcd.setCursor(0,1);
  for(int i=0;i<15;i++){
  lcd.print("#");
  delay(50);  
    }
  lcd.clear();
  
  for(int i=0;i<=4;i++){
  randomSeed(millis()*i);
  lcd.setCursor(i,0);
  int a=random(0,2);
  //lcd.print(a);
  binCode[i]=a;
  delay(100);
    }
  lcd.clear();
  lcd.print("YOU HAVE 45 SEC");
  lcd.setCursor(0,1);
  lcd.print("DEFUSE THE BOMB!");
  delay(1000);
  t=46;       
  defuse();
  
}
//=============================[MAIN_MENU_2]==============================
void mainMenu2(){
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("A GAMEMODE");
  lcd.setCursor(0, 1);
  lcd.print("B STATISTICS");
  
    char keyM = keypad.waitForKey();
       switch (keyM) {
     case 'A': 
     {
     tone(A3, 300, 100);
     digitalWrite(0,HIGH);
     delay(100);
     digitalWrite(0,LOW);
     lcd.clear();
      lcd.print(">>A GAMEMODE");
      lcd.setCursor(0, 1);
      lcd.print("B STATISTICS");
      lcd.noCursor();
      delay(500);
      lcd.clear();
      chooseGamemode();
      break;
      }
      case 'B': 
     {
     tone(A3, 300, 100);
     digitalWrite(0,HIGH);
     delay(100);
     digitalWrite(0,LOW);
     lcd.clear();
      lcd.print("A GAMEMODE");
      lcd.setCursor(0, 1);
      lcd.print(">>B STATISTICS");
      lcd.noCursor();
      delay(500);
      lcd.clear();
      menuC();
      break;
      }
    default:
    tone(A3, 100);
    delay(100);
    noTone(A3);
    mainMenu2();
      }
}
//=================================[IDLE_2]==============================
void idleScreen2(){
      noTone(A3);
  lcd.clear();
  lcd.print("Any key to start");
  lcd.setCursor(0, 1);
  lcd.print(" '*' for setup");

    char key = keypad.waitForKey();                         //gaida ievadi no personas.
    switch (key){
      case '*':{
      tone(A3, 100);
      delay(100);
      noTone(A3);
      mainMenu2();
      break;
      }
    default:
    tone(A3, 100);
    delay(100);
    noTone(A3);
    wireCutter();
      }
}

//====================================[CHOOSE_GAMEMODE]==================================
void chooseGamemode(){
tone(A3, 100);
      delay(100);
      noTone(A3);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("CHOOSE GAMEMODE");
      lcd.setCursor(0, 1);
      lcd.print("A-Defusal B-Wire");
       char keyC = keypad.waitForKey();
      switch (keyC){
        case 'A':{
          mode=0;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("CODE DEFUSAL");
      easyMode = 1;
      tone(A3, 600);
      delay(100);
      tone(A3, 300);
      delay(100);
      tone(A3, 500);
      delay(100);
      noTone(A3);
      idleScreen();
          break;
        }
        case 'B':{
          mode=1;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("WIRECUTTER");
      easyMode = 0;
      tone(A3, 300);
      delay(100);
      tone(A3, 100);
      delay(100);
      tone(A3, 400);
      delay(100);
      noTone(A3);
      idleScreen2();
          break;
        }
        default:
          chooseGamemode();
        }
  }

//=============================[MAIN_MENU]==============================
void mainMenu(){
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("A MODE  B DIFF");
  lcd.setCursor(0, 1);
  lcd.print("C STAT  D EXIT");
  
    char keyM = keypad.waitForKey();
       switch (keyM) {
     case 'A': 
     {
     tone(A3, 300, 100);
     digitalWrite(0,HIGH);
     delay(100);
     digitalWrite(0,LOW);
     lcd.clear();
      lcd.print(">>MODE  B DIFF");
      lcd.setCursor(0, 1);
      lcd.print("C STAT  D EXIT");
      lcd.noCursor();
      delay(500);
      lcd.clear();
      chooseGamemode();
      break;
      }
      case 'B': 
     {
     tone(A3, 300, 100);
     digitalWrite(0,HIGH);
     delay(100);
     digitalWrite(0,LOW);
     lcd.clear();
      lcd.print("A MODE  >>DIFF");
      lcd.setCursor(0, 1);
      lcd.print("C STAT  D EXIT");
      lcd.noCursor();
      delay(500);
      lcd.clear();
      menuB();
      break;
      }
      case 'C': 
     {
     tone(A3, 300, 100);
     digitalWrite(0,HIGH);
     delay(100);
     digitalWrite(0,LOW);
     lcd.clear();
      lcd.print("A MODE  B DIFF");
      lcd.setCursor(0, 1);
      lcd.print(">>STAT  D EXIT");
      lcd.noCursor();
      delay(500);
      lcd.clear();
      menuC();
      break;
      }
      case 'D': 
     {
     tone(A3, 300, 100);
     digitalWrite(0,HIGH);
     delay(100);
     digitalWrite(0,LOW);
     lcd.clear();
      lcd.print("A MODE  B DIFF");
      lcd.setCursor(0, 1);
      lcd.print("C STAT  >>EXIT");
      lcd.noCursor();
      delay(500);
      lcd.clear();
      idleScreen();
      break;
      }
      default:
      mainMenu();
  }
}

/*
//=============================[START]==============================
void start(){
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
lcd.clear();
digitalWrite(0, HIGH);
tone(A3, 300);
lcd.setCursor(0,0);
lcd.print("[/");
lcd.setCursor(0,1);
lcd.print("LOADING");
lcd.setCursor(15,0);
lcd.print("]");
lcd.noCursor();
lcd.setCursor(2,0);
digitalWrite(1, LOW);
delay(300);
lcd.print("//");
lcd.setCursor(7,1);
lcd.print(".");
digitalWrite(0, LOW);
noTone(A3);
digitalWrite(1, HIGH);
delay(300);
lcd.setCursor(4,0);
lcd.print("//");
lcd.setCursor(8,1);
lcd.print(".");
digitalWrite(0, HIGH);
digitalWrite(1, LOW);
delay(300);
lcd.setCursor(6,0);
lcd.print("//");
lcd.setCursor(9,1);
lcd.print(".");
digitalWrite(0, LOW);
digitalWrite(1, HIGH);                   //Nomirgo gaisminas, lai paraditu, ka sakas darbiba
delay(100);
lcd.setCursor(8,0);
lcd.print("//");
digitalWrite(1, LOW);
delay(100);
lcd.print("//");
digitalWrite(1, HIGH);
delay(100);
lcd.print("//");
digitalWrite(1, LOW);
delay(100);
lcd.print("/");
delay(50);
lcd.clear();

    lcd.setCursor(0, 0);            //novieto kursoru 1.rindas kreisākajā pozicijā
    lcd.print(" This is your");    //pieprasa ievadīt kodu
    lcd.setCursor(0, 1);              //novieto kursoru otrajā rindā
    lcd.print(" 5 digit code:");
    lcd.noCursor();
    delay(1000);
    lcd.clear();
    noTone(A3);
    for(int i=0; i < 5; i++){
  randomSeed(millis());
  int a=random(0,10);
  //lcd.print(a);
  kods[i]=kodaChar[a];
  lcd.setCursor(i+6,0);
  lcd.print(kods[i]);
  delay(500);
    }
    delay(1000);
    lcd.clear();
    timer();
}
*/
//=============================[START]==============================
void start(){
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
lcd.clear();
digitalWrite(0, HIGH);
tone(A3, 300);
lcd.setCursor(0,0);
lcd.print("[/");
lcd.setCursor(0,1);
lcd.print("LOADING");
lcd.setCursor(15,0);
lcd.print("]");
lcd.noCursor();
lcd.setCursor(2,0);
digitalWrite(1, LOW);
delay(300);
lcd.print("//");
lcd.setCursor(7,1);
lcd.print(".");
digitalWrite(0, LOW);
noTone(A3);
digitalWrite(1, HIGH);
delay(300);
lcd.setCursor(4,0);
lcd.print("//");
lcd.setCursor(8,1);
lcd.print(".");
digitalWrite(0, HIGH);
digitalWrite(1, LOW);
delay(300);
lcd.setCursor(6,0);
lcd.print("//");
lcd.setCursor(9,1);
lcd.print(".");
digitalWrite(0, LOW);
digitalWrite(1, HIGH);                   //Nomirgo gaisminas, lai paraditu, ka sakas darbiba
delay(100);
lcd.setCursor(8,0);
lcd.print("//");
digitalWrite(1, LOW);
delay(100);
lcd.print("//");
digitalWrite(1, HIGH);
delay(100);
lcd.print("//");
digitalWrite(1, LOW);
delay(100);
lcd.print("/");
delay(50);
lcd.clear();

    lcd.setCursor(0, 0);            //novieto kursoru 1.rindas kreisākajā pozicijā
    lcd.print("  Enter your");    //pieprasa ievadīt kodu
    lcd.setCursor(0, 1);              //novieto kursoru otrajā rindā
    lcd.print(" 5 digit code:");
    lcd.noCursor();
    delay(1000);
    lcd.clear();
    noTone(A3);
    for(int i=0; i < 5; i++){                                
    char key=keypad.waitForKey();
    kods[i] = key;    
    digitalWrite(0, HIGH);
    tone(A3, 200);
    lcd.setCursor(i+5, 0);    //novieto kursoru pa labi katru reizi, kad mainās "i" atbilstoši masīvā esosajiem elementiem
    lcd.print(kods[i]);     //izvada skaitli
    delay(100);             //pauze    
    digitalWrite(0, LOW);
    noTone(A3);
    }
    delay(2000);
    lcd.clear();
    timer();  
}

//=============================[LOOP]==============================
void loop(){
  correct=0;
  easyMode=0;
  chooseGamemode();
}
