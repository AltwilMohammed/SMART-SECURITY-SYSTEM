

//Smart Security System Project. Code 
// By Mohammed Altwil & Maged Abdullah Al-Jabri.

#include <SoftwareSerial.h>
#include<Servo.h>
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
int x=LOW;
SoftwareSerial gsm(10,11);
Servo ss1;
Servo s2;

#define buzzer 22
// #define current_lizer 23

#define water 24
#define cont_sensor 25  
#define current 26
//#define  led1 27
//#define  led2 28
#define  fan 29
#define  led 30
#define Relay1 41
#define Relay2 43
#define ir3 32
// #define ir4 34
#define gas 36
#define fire 38
//#define button 40
//#define button1 42
//#define LDR 44
 
LiquidCrystal_I2C lcd(0x27,16,2);
const byte ROWS = 4; // 4 lines
const byte COLS = 4; // 4 columns
char keys [ROWS] [COLS] ={
  { '1', '2', '3', 'A'},
  { '4', '5', '6', 'B'},
  { '7', '8', '9', 'C'},
  { '*', '0', '#', 'D'}
};
// Connect the keyboard to 2 3 4 5 (columns) and 6 7 8 9 (lines)
byte rowPins [ROWS] = {9, 8, 7, 6}; // Lines
byte colPins [COLS] = {5, 4, 3, 2}; // Columns


//Initialize an instance of the keypad class
Keypad keypad = Keypad(makeKeymap (keys), rowPins, colPins, ROWS, COLS);



   String smsgas="Gas Leaks in The Building";
  String smsfire="FIRE IN THE Building";
   String erro="ERROR:send ON or OFF just";
   String erro2="ERROR";
   String offstate="the Security system is on the OFF state";
   String onstate="The Security system is on the ON state";    
   String money="there is someone in the moneybank room";
   String pass_error="someone enter an error password  and the system will change the password,New pass is  ";
  String change_pass="Do you want the system to change the password or by you?.....send #system or #me";
  String new_pass="Send as follows # old pass * new pass";
  String change_Over="New icon changed by Keyboard: ";
 String next_pass="new password is  ";
 
    String password[12][1]={ {"1212"},{"4455"},{"3561"},{"3312"},{"1042"},{"6951"},{"8075"},{"1206"},{"3103"},{"4950"},{"5039"} ,{"2041"}};

 String New1password_entered;
 String Newpassword_entered;
 String password_entered;

   String old;
   String newpass;
 
 int  c_no_match=0;
 int coun=0;
 int c_change=0;
 int c_lizer=0;
 int row=0;
 int  count_open=0;
 int c_off=0;
 int c_g=0;
 int c_f=0;
int c_money=0;
 int coun_2dor=0;
 int close_coun=0;

String smsRecieve;
   void ON_state();
    void OFF_state();
void SendMessage(String sms);
void SendMessage1(String sms1);
void  check_change();
void change();
  void  check_rec();
     void check_sensor();
    // void check_lizer();
   void  dor_on_state();
     void dor();
      void close_dor();
       void open_dor();
  void open_dor2();

void setup() {

   ss1.attach(12);
  s2.attach(13);

        pinMode(ir3,INPUT);
    //    pinMode(ir4,INPUT);
        pinMode(gas,INPUT);
        pinMode(fire,INPUT);
        //  pinMode(button,INPUT);
       // pinMode(button1,INPUT);
     //   pinMode(LDR,INPUT);

        pinMode(Relay1,OUTPUT);
        pinMode(Relay2,OUTPUT);
       pinMode(led,OUTPUT);
 //       pinMode(led1,OUTPUT);
  //     pinMode(led2,OUTPUT);
        pinMode(buzzer,OUTPUT);
        pinMode(water,OUTPUT);
    //    pinMode(current_lizer,OUTPUT);
        pinMode(current,OUTPUT);
        pinMode(cont_sensor,OUTPUT);
         pinMode(fan,OUTPUT);

        digitalWrite(Relay1,LOW);
          digitalWrite(Relay2,LOW);
         digitalWrite(led,LOW);
    //     digitalWrite(led1,LOW);
      //   digitalWrite(led2,LOW);
         digitalWrite(buzzer,LOW);
         digitalWrite(water,LOW);
      //   digitalWrite(current_lizer,LOW);
         digitalWrite(current,LOW);
         digitalWrite(cont_sensor,LOW);
         digitalWrite(fan,LOW);

        //   digitalWrite(button,LOW);
        // digitalWrite(button1,LOW);
      
          ss1.write(120);
       s2.write(110);
     digitalWrite(Relay1,HIGH);
     digitalWrite(Relay2,HIGH);
  // to activate the HOLD state
  unsigned int time_hold = 4;
  keypad.setHoldTime(time_hold);
  // Anti rebound
  unsigned int time_anti_rebond = 4; // 4 ms
  keypad.setDebounceTime(time_anti_rebond);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Hello");

   
  delay(50);
  Serial.begin(9600);
  gsm.begin(9600);
  Serial.println("Initializing...");  
   delay(500); 
     Serial.println("welcome");
    gsm.println("AT"); //Handshaking with SIM900
  gsm.println("AT+CMGF=1");
  delay(1000);
  gsm.println("AT+CMGS=\"+967715478733\"\r"); //replace  by your number
  delay(500);
  gsm.println("Welcome to the Discrete Math project.....The System is starting in work:send #ON to  activate the Security circuit , #OFF to stop  the Security circuit..");
  delay(100);
  gsm.write(0x1a);
  delay(100);
   gsm.println("AT+CNMI=2,2,2,0,0"); // Decides how newly arrived SMS messages should be handled


}
 



void loop() {

    if(c_off==0){
        c_off++;
         Serial.println("start void loop");
      }
      check_rec();
      check_sensor();

        if(digitalRead(gas)==HIGH&&digitalRead(fire)==HIGH){
     digitalWrite(buzzer,LOW);
     digitalWrite(led,LOW);
          
    }

     

   }


  void SendMessage(String sms)                                                       // void sendmessage
{
  //Serial.println ("Sending Message");
  gsm.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  //Serial.println ("Set SMS Number");
  gsm.println("AT+CMGS=\"+967715478733\"\r"); //Mobile phone number to send message
  delay(500);
  gsm.println(sms);
  delay(100);
  gsm.write(0x1a);// ASCII code of CTRL+Z
  delay(100);
  
}           //end void sendmessage

     
  void SendMessage1(String sms1)                                           // void SendMessage1
{
  
  gsm.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  
  gsm.println("AT+CMGS=\"+967715478733\"\r"); //Mobile phone number to send message
  delay(500);
  gsm.print(sms1);
  gsm.print(password[row][0]);
  
  gsm.write(0x1a);// ASCII code of CTRL+Z
  delay(100);
  
}           //end void sendmessage


  void check_rec(){                                                 //check gsm
            gsm.println("AT+CMGF=1");
    //  Serial.println("start void gsssssm");
      delay(100);
     
     while(Serial.available())   //check the serial if Recieve any Message
  {
     gsm.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(gsm.available())
  { 
    
    char inChar=gsm.read();
      if(inChar=='#')
      {  
         char inChar=gsm.read();
          char inChar1=gsm.read();
          if(inChar=='O'&& inChar1=='n'){             //check if the recieve is ON
            Serial.println("on");
         ON_state();
           }
       else{
        char inChar2=gsm.read();
      if(inChar=='O'&& inChar1=='f'&&inChar2=='f'){      //check if the recieve is OFF
        
        Serial.println("off");
        OFF_state();
           }
           else if(inChar=='c'&&inChar1=='h'&&inChar2=='a'){
            change();
           } 
           else if(inChar=='o'&&inChar1=='p'&&inChar2=='e'){
            open_dor();
           } else if(inChar=='c'&&inChar1=='l'&&inChar2=='o'){
            close_dor();
           }
           
   else{
    Serial.println("erro rec");
        SendMessage(erro);
       }
       }
  }  
} 
}


    void OFF_state(){                                     //  off  State
       c_off==0;
  
         Serial.println("start OFF loop");
         SendMessage(offstate);
                                                 // in the OFF state(start)
     digitalWrite(cont_sensor,LOW);
     digitalWrite(current,LOW);
     // digitalWrite(current_lizer,LOW);
     
    while(1){ 
      
   lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter A TO enter");
  password_entered = "";
  lcd.setCursor(0,1);
  lcd.print("Enter B TO chang");
  lcd.setCursor(-4,2);
  lcd.print("e password");
  lcd.setCursor(8,2);
  check_rec();
  check_sensor();               
  
  while(password_entered.length() <1){
    digitalWrite(cont_sensor,LOW);
     check_rec();
     check_sensor(); 
     dor();                         
    char key = keypad.getKey ();
    if(key != NO_KEY){
      password_entered += key;
      lcd.print(key);
      }}
      delay(500);
 if(password_entered == "A"){             //enter password
  L1:  lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Enter password: ");
       password_entered = "";
      lcd.setCursor(0,1);
  while(password_entered.length() <4){
    check_rec();
    check_sensor();
    dor();                     
    char key = keypad.getKey ();
    if(key != NO_KEY){
      password_entered += key;
      lcd.print('*');
    }
  }
  if(password_entered == password[row][0]){              ///////////////////
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("password OK !");
   
     delay(100);
     open_dor();
  }

  else{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("password ERROR !");
    delay(1500);
    coun++;
   
    if(coun==3){
        lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Wait for minutes ");
     check_rec();
    check_sensor();
    delay(3000);
     check_rec();
    check_sensor();
    delay(3000);
     check_rec();
    check_sensor();
    delay(3000);
      coun=0;
              }
         else{
           lcd.clear();
           lcd.setCursor(0,0);
           lcd.print("Try Again");
           delay(1000);
           goto L1;
             }
      }}
      
    else if(password_entered =="B"){                            //change passwoard
  L2:  lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Confirm password ");
       password_entered = "";
      lcd.setCursor(0,1);
    while(password_entered.length() <4){
           dor();
          check_rec();
         check_sensor();
 
    char key = keypad.getKey ();
    if(key != NO_KEY){
      password_entered += key;
      lcd.print('*');
                    }
    }
    if(password_entered == password[row][0]){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("password OK !");
    delay(1000);
  L4:  lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Select an icon");
      Newpassword_entered = "";
      lcd.setCursor(0,1);
  while(Newpassword_entered.length() <4){
          check_rec();
          check_sensor();
           dor();
    char key = keypad.getKey ();
    if(key != NO_KEY){
      Newpassword_entered += key;
      lcd.print('*');
    }}
     delay(100);
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Confirmation");
       New1password_entered = "";
      lcd.setCursor(0,1);
  while(New1password_entered.length() <4){
             check_rec();
             check_sensor();
             dor();
    char key = keypad.getKey ();
    if(key != NO_KEY){
      New1password_entered += key;
      lcd.print('*');
    }}
    if(Newpassword_entered == New1password_entered){
     password[row][0]=New1password_entered;
     delay(500);
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("change is Over");
    SendMessage1(change_Over);      //dرسالة ان هناك شخص غير كلمة السر بنجاح   
 
     
     } else{ 
      
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("no match");
      delay(1000);
      check_sensor();
      c_no_match++;
      if(c_no_match==3){
        c_no_match=0;}
        else{  
           lcd.setCursor(1,1);
           lcd.print("again");
           delay(500);
           check_sensor();
           delay(500);
            goto L4;   }
          }
           }
    else {
       c_change++;
         if(c_change==3){
          lcd.clear();
         lcd.setCursor(5,1);
         lcd.print("ERROR");
         delay(1000);
          c_change=0;
         }else{
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("sorry..Try again");
        check_rec();
        check_sensor();
        delay(500);
          goto L2;
         }
         }
         }                //end change passwoard.....
          else if(password_entered =="C"){
            close_dor();
             }
         else{
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("ERROR");
          delay(500);
         }  
       
  }}


    void ON_state(){                                                                 //on state
       c_off==0;
       //   digitalWrite(current_lizer,HIGH);
        Serial.println("start on_state");
       SendMessage(onstate);
         digitalWrite(cont_sensor,HIGH);
          digitalWrite(current,LOW);
         delay(100);
       while(1){                         
     lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Enter password: ");
     lcd.setCursor(0,1);
  
           check_rec();
         check_sensor();
          check_money_room();
      //    check_lizer();               
         dor_on_state();
        password_entered = "";
        while(password_entered.length() <4){
          check_rec();
         check_sensor();
         dor_on_state();
       // check_lizer();
         check_money_room();
    char key = keypad.getKey ();
    if(key != NO_KEY){
      password_entered += key;
      lcd.print('*');
    }
  }
  if(password_entered == password[row][0]){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("password OK !");
    coun=0;
    count_open++;
    
    open_dor2(); 
      digitalWrite(Relay1,LOW);
      delay(30);
     open_dor();
    digitalWrite(cont_sensor,LOW);
     digitalWrite(current,LOW);
      c_money=0;
      
        lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Enter password: ");
     lcd.setCursor(0,1);
       password_entered = "";
        while(password_entered.length() <1){
          check_rec();
         check_sensor();
         dor_on_state();
       // check_lizer();
         check_money_room();
    char key = keypad.getKey ();
    if(key != NO_KEY){
      password_entered += key;
      lcd.print('*');
    }
  }  if(password_entered =="C"){
            close_dor();
             }else{
               lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" ERROR !");
    delay(1000);
             }
  }
  else{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("password ERROR !");
    count_open=0;
    delay(2000);
    coun++;
     digitalWrite(cont_sensor,HIGH);
    if(coun==3){
        row++;
        SendMessage1(pass_error);                    //send error message
        Serial.println("pass_change");
      coun=0;
       digitalWrite(buzzer,HIGH);
       digitalWrite(led,HIGH);
         for(int i=0;i<20;i++){
           check_rec();
         check_sensor();
       //  check_lizer();
          dor_on_state();
         check_money_room();        
        lcd.clear();
        delay(500);
        lcd.setCursor(5,1);
        lcd.print("ERROR");
        delay(500);   }
         digitalWrite(led,LOW);     
         digitalWrite(buzzer,LOW);         
              }else{
                lcd.clear();
               lcd.setCursor(0,1);
               lcd.print("Try again");
                  delay(1000);
                 }
      }
      if(row==10){row=0;}

       
     }          //end while
    }             //end on state              

      
    void  check_money_room(){                                        // check_money_room

         if(count_open==0){
         digitalWrite(cont_sensor,HIGH);
         delay(300);
          if(digitalRead(ir3)==LOW){
      
        if(c_money==0){
          
          digitalWrite(current,HIGH);
      digitalWrite(buzzer,HIGH);
      digitalWrite(led,HIGH);
        digitalWrite(Relay2,LOW);
        delay(20);
        coun_2dor++;
       for(int i=110;i>=0;i--){
        s2.write(i);
        delay(10);
   }
   digitalWrite(Relay2,HIGH);
     
         c_money++;
         SendMessage(money); 
       }            
                              
    }
      
       if(digitalRead(ir3)==HIGH&&digitalRead(gas)==HIGH&&digitalRead(fire)==HIGH){
     digitalWrite(buzzer,LOW);
     digitalWrite(led,LOW);
         } 
    }
    }
       void  check_lizer(){

    /*  if(digitalRead(ir4)==HIGH){
        digitalWrite(buzzer,HIGH);
        digitalWrite(led,HIGH);
        if(c_lizer==0){
          c_lizer++;
        SendMessage(moving);}
        }else{
          c_lizer==0;
        }
                           //d   امكانية تشغيل غاز مسيل الموووووع


         if(digitalRead(ir3)==HIGH&&digitalRead(gas)==HIGH&&digitalRead(fire)==HIGH){
   digitalWrite(buzzer,LOW);
  digitalWrite(led,LOW);
         }*/
      
     }
      
    void check_sensor(){                                                  //void check_sensor

        if(digitalRead(fire)==LOW){ 
           c_f++;                                //check th fire sensor
         digitalWrite(buzzer,HIGH);
         digitalWrite(led,HIGH);
         if(c_f==1){
           Serial.println("fire");
          SendMessage(smsfire);
        digitalWrite(water,HIGH);}
             } 
    else { c_f=0;
       digitalWrite(water,LOW);
         }
          
     if(digitalRead(gas)==LOW){                       // check the gas sensor
         c_g++;
        digitalWrite(buzzer,HIGH);
        digitalWrite(led,HIGH);
        if(c_g==1){
           Serial.println("gas");
          SendMessage(smsgas);
           digitalWrite(fan,HIGH);}
                }
        else{c_g=0;
         digitalWrite(fan,LOW);}

         
     }
     
    void change(){                                                  //  void change
         int l;
         Serial.println("change_pass");
         SendMessage(change_pass);
         for (l=0;l<=100;l++){
            delay(500);
     
     while(Serial.available())   //check the serial if Recieve any Message
  {
     gsm.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(gsm.available())
  {
    char inCh=gsm.read();
      if(inCh=='#')
      { 
         char inCh=gsm.read();
          char inCh1=gsm.read();
          if(inCh=='m'&& inCh1=='e'){             //check if the recieve is me
            Serial.println("me");
        SendMessage(new_pass);
        check_change();
           goto LL2;
           }
       else{
        char inCh2=gsm.read();
      if(inCh=='s'&& inCh1=='y'&&inCh2=='s'){      //check if the recieve is system
        
        Serial.println("system");
        row++;
         SendMessage1(next_pass);
         goto LL2;
           }
         
   else{
    Serial.println("erro");
      SendMessage(erro2);
        goto LL2;
       }
       }
  }
}

   
         }
         if (l>97){Serial.println("endddd  if");
          SendMessage(erro2);}
         LL2:Serial.println("end chn");
    
    }

    void  check_change(){
              int k;
              int x=1,y=1;
             old="";
             newpass="";

            for(k=0;k<=100;k++){
                delay(500);

      while(Serial.available())   //check the serial if Recieve any Message
      {
     gsm.write(Serial.read());//Forward what Serial received to Software Serial Port
     }
  while(gsm.available())
  {
    char inCx=gsm.read();
      if(inCx=='#')
      { 
          
            int inCx=gsm.read();
            old +=inCx-48;
            int inCx1=gsm.read();
            old +=inCx1-48;
            int inCx2=gsm.read();
            old +=inCx2-48;
            int inCx3=gsm.read();
            old +=inCx3-48;
          
          char inC=gsm.read();
          if ( inC=='*'){
            int inC=gsm.read();
              newpass +=inC-48;
             int inC1=gsm.read();
              newpass +=inC1-48;
            int inC2=gsm.read();
              newpass +=inC2-48;
             int inC3=gsm.read();
              newpass +=inC3-48;
              goto L10;
          }
          
          else{
            Serial.println("no *");
            goto L8;}
            
             }  
        }    
        }   

      if(k>98){Serial.println("end time");
       goto L8;
        
      }
        

         // if(row==11){row=0;}
       L10:   if(old==password[row][0]){
            password[row][0]=newpass;
             Serial.println("change ok");
            SendMessage("OK");
            goto L9;
          }
          else { Serial.println("old pass error");
            SendMessage("old pass error");
           goto L9;
          }
           
          L8:SendMessage(erro2);
          L9:Serial.println("end check change");
    }

     void dor(){
        /* digitalWrite(Relay1,LOW);
           x=digitalRead(button);
        if(x==HIGH){    // for close the dor by button
          Serial.println("close");
          for(int j=0;j<=120;j++){
           ss1.write(j);
           delay(10);
    
        }
         digitalWrite(Relay1,HIGH);
        }
         if(digitalRead(button1)==HIGH){   //for open thr dor by button from inside money room
         Serial.println("open");
          for(int i=120;i>=0;i--){
            s1.write(i);
             delay(10);
         } 
          }*/

            if(digitalRead(gas)==HIGH&&digitalRead(fire)==HIGH){
   digitalWrite(buzzer,LOW);
   digitalWrite(led,LOW);
         
  }        
      
     }
     
     void dor_on_state(){
      
     /* if(digitalRead(button)==HIGH){    // for close the dor by button
          Serial.println("close");
          for(int j=0;j<=120;j++){
           s1.write(j);
           delay(10);
    
        }
        }
         if(digitalRead(button1)==HIGH){   //for open thr dor by button from inside money room
          Serial.println("open");
          for(int i=120;i>=0;i--){
            s1.write(i);
             delay(10);
         } 
          }*/
          
           if(digitalRead(ir3)==HIGH&&digitalRead(gas)==HIGH&&digitalRead(fire)==HIGH){
     digitalWrite(buzzer,LOW);
     digitalWrite(led,LOW);
          
    }
      
     }
     void open_dor(){
      Serial.println("was open");
      digitalWrite(Relay1,LOW);
      for(int i=110;i>=0;i--){
            ss1.write(i);
             delay(10);
         }
         close_coun++;
         delay(100);
          digitalWrite(Relay1,HIGH);
         //  lcd.clear();
         open_dor2();
      c_money=0;
      digitalWrite(current,LOW);
     }

      void close_dor(){
        if(close_coun>=1){
         digitalWrite(cont_sensor,HIGH);
         Serial.println("was close");
            digitalWrite(Relay1,LOW);
        for(int j=0;j<=110;j++){
           ss1.write(j);
           delay(10);
    
        }
        delay(100);
        digitalWrite(Relay1,HIGH);
         open_dor2();
           delay(100);
         count_open=0;
         close_coun=0;
        }
      }
     void open_dor2(){
      if(coun_2dor>=1){
      digitalWrite(Relay2,LOW);
         delay(100);
   for(int j=0;j<=110;j++){
           s2.write(j);
           delay(15);
           }
     digitalWrite(Relay2,HIGH);
     coun_2dor=0;
     }
     }
