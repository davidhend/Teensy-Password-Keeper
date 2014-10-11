#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Entropy.h>
#include "Arduino.h"
#include <AES.h>
#include <SD.h>

/* number of encryption bits to be used */
#define KEYBITS 256
/* oled display reset pin */
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

/* SD card CS pin */
const int CS_Pin = 10;

/* SD card file constructor */
File myFile;

/* encryption key */
uint8_t encryptionKey[32] = {
  0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,
  0,0
};

/* used when reading sd card */
String sd_data = "";

/* temporary plain text password buffer */
unsigned char plaintext[16];
/* temporary encrypted password buffer*/
unsigned char ciphertext[16];

/* holds encrypted password 1 */
unsigned char pw1[16] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
/* holds encrypted password 2 */
unsigned char pw2[16] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
/* holds encrypted password 3 */
unsigned char pw3[16] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
/* holds encrypted password 4 */
unsigned char pw4[16] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
/* holds encrypted password 5 */
unsigned char pw5[16] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
/* holds encrypted password 6 */
unsigned char pw6[16] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
/* holds encrypted password 7 */
unsigned char pw7[16] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
/* holds encrypted password 8 */
unsigned char pw8[16] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
/* holds encrypted password 9 */
unsigned char pw9[16] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
/* holds encrypted password 10 */
unsigned char pw10[16] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};

/* Initialise the encryption code */
unsigned long rk[RKLENGTH(KEYBITS)];
/* used during encryption / decryption */
int nrounds = 0;
/* password creation buffer */
char pw[9];

/* button pad connection variables */
const int buttonPin_0 = 8;  /* Select IN */ 
const int buttonPin_1 = 7;  /* Left */
const int buttonPin_2 = 6;  /* Down */ 
const int buttonPin_3= 5;   /* Up */
const int buttonPin_4= 4;   /* Right */ 
const int buttonPin_5= 3;   /* Back Switch */

/* button pas states */
int buttonState_0 = 0;
int buttonState_1 = 0;
int buttonState_2 = 0;
int buttonState_3 = 0;
int buttonState_4 = 0;
int buttonState_5 = 0;

/* used to keep track of which profile is selected */
int profile_selected = 99;

char *yes_no_options[] = {
  "No", "Yes"};

char *profile_options[] = {
  "- Email", "- Bank", "- 3rd Party Pay", "- Unused", "- Unused", "- Unused", "- Unused", "- Unused", "- Unused", "- Unused"};

char *main_menu_options[] = {
  "- Select Profile","- Display Password","- Generate Password","- Transmit Password"};

/* initial selection (first option = 0) */
int highlight_option=0; 

void setup()
{
  /* init oled display */
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  /* init serial interface */
  Serial.begin(57600);
  /* init bluetooth interface */
  Serial1.begin(115200);
  /* init entropy library */
  Entropy.Initialize();
  /* show splashscreen */
  display.display(); 
  /* wait for 2 seconds */
  delay(2000);
  /* clear oled display */
  display.clearDisplay();
  /* set text size */
  display.setTextSize(1);
  /* set text color */
  display.setTextColor(WHITE);
  /* set cursor position */
  display.setCursor(30,0);
  /* display text to lcd */
  display.println("PIN Needed"); 
  /* send display data to lcd */ 
  display.display();
  /* get authorization from android device */
  get_authorization();
  /* clear oled display */
  display.clearDisplay();
  /* SD card CS pin */
  pinMode(CS_Pin, OUTPUT);
  /* set select button to input */
  pinMode(buttonPin_0, INPUT);
  /* set left button to input */
  pinMode(buttonPin_1, INPUT);
  /* set down button to input */ 
  pinMode(buttonPin_2, INPUT);  
  /* set up button to input */   
  pinMode(buttonPin_3, INPUT); 
  /* set right button to input */   
  pinMode(buttonPin_4, INPUT);   
  /* set back button to input */   
  pinMode(buttonPin_5, INPUT); 
  /* if SD card fails to init display error on lcd */
  if(!SD.begin(CS_Pin))
  {
    /* do nothing */
  }
  read_all_password_data();
}

boolean loop_draw = false;
void loop()
{
  /* Read button inputs */
  buttonState_0 = digitalRead(buttonPin_0); /* IN */
  buttonState_1 = digitalRead(buttonPin_1); /* Left */
  buttonState_2 = digitalRead(buttonPin_2); /* Down */
  buttonState_3 = digitalRead(buttonPin_3); /* Up */
  buttonState_4 = digitalRead(buttonPin_4); /* Right */
  buttonState_5 = digitalRead(buttonPin_5); /* Switch */

  /* if the down button is pressed */
  if(buttonState_2)           
  {
    /* clear the display */
    display.clearDisplay();
    /* increment screen selection */
    highlight_option--; 
    /* allow the lcd to re-draw */
    loop_draw = false;    
  }
  /* if the up button it pressed*/
  else if (buttonState_3)
  {
    /* clear the display */
    display.clearDisplay();
    /* decrement screen selection */
    highlight_option++; 
    /* allow the lcd to re-draw */  
    loop_draw = false;    
  }
  
  /* if we get to the last botton selection move to the top selection 
     if we get tot the last top selection move to bottom selection */
  if (highlight_option < 0) highlight_option = 3; 
  else if (highlight_option > 3) highlight_option = 0;  
  
  /* re-draw the screen if something changed otherwise dont both re-drawing display */
  if(loop_draw == false)
  {
    /* set the text font size */
    display.setTextSize(1);
    /* set the text color */
    display.setTextColor(WHITE);
    /* set the starting location of the cursor */
    display.setCursor(40,0);
    /* display menu to screen */
    display.println("Menu");

    /* display the profile selections */
    for (int i=0;i<4;i++) 
    {
      /* if we are currently drawing what we have selected */
      if(highlight_option == i) 
      { 
        /* highlight the option */
        display.setTextColor(BLACK, WHITE); 
      } 
      /* otherwise */
      else 
      {
        /* draw the text normally */
        display.setTextColor(WHITE); 
      }
      /* go the the next line of the display  */
      display.setCursor(0,10+i*10); 
      /* display the menu options as we progress throught the loop */
      display.println(main_menu_options[i]); 
    }
    /* send the display data to the lcd */ 
    display.display();
    /* set flag to indicate that we dont need to re-draw the
       screen unless something changes.                   */
    loop_draw = true; 
    }
  /* small delay between itterations (otherwise 
     the button presses occur too quickly)*/
  delay(75);
  
  /* if the select button is pressed */
  if (buttonState_0)
  {
    /* handle menu selection */
    perform_action();
  }
}

void perform_action()
{
  /* used to determine when the screen needs to be re-drawn */
  boolean option0_draw = false;
  /* if the user chooses select profile */
  if(highlight_option == 0)
  {
    /* small delay to wait for select button to settle */
    delay(75);
    /* clear the lcd */
    display.clearDisplay();
    /* while we are in the profile selection menu */
    while(1)
    {
      /* Read button inputs */
      buttonState_0 = digitalRead(buttonPin_0); /* IN */
      buttonState_1 = digitalRead(buttonPin_1); /* Left */
      buttonState_2 = digitalRead(buttonPin_2); /* Down */
      buttonState_3 = digitalRead(buttonPin_3); /* Up */
      buttonState_4 = digitalRead(buttonPin_4); /* Right */
      buttonState_5 = digitalRead(buttonPin_5); /* Switch */
      
      /* if the user pressed the down button */
      if(buttonState_2)            
      {
        /* clear the display */
        display.clearDisplay();
        /* increment screen selection */
        highlight_option--;
        /* allow menu 1 to re-draw */
        option0_draw = false;      
      }
      /* if the user pressed the up button */
      else if (buttonState_3)   
      {
        /* clear the display */
        display.clearDisplay();
        /* decrement screen selection */
        highlight_option++; 
        /* allow menu 1 to re-draw */ 
        option0_draw = false;     
      }
      
      /* if we get to the last botton selection move to the top selection 
         if we get tot the last top selection move to bottom selection */
      if (highlight_option < 0) highlight_option = 9; 
      else if (highlight_option > 9) highlight_option = 0;
      
      /* re-draw the screen if something changed otherwise dont both re-drawing display */
      if(option0_draw == false)
      {
        /* set the text font size */
        display.setTextSize(1);
        /* set the text color */
        display.setTextColor(WHITE);
        /* set the cursor position */
        display.setCursor(25,0);
        /* display text to lcd */
        display.println("Select Profile");
      
        /* if we are displaying the top 5 selections */
        if(highlight_option <= 4)
        {
      
        /* display the profile selections */
        for (int i=0;i<5;i++) 
        { 
          /* if we are currently drawing what we have selected */
          if(highlight_option == i) 
          { 
            /* highlight the option */
            display.setTextColor(BLACK, WHITE); 
          } 
          /* otherwise */
          else 
          {
            /* draw the text normally */
            display.setTextColor(WHITE); 
          }
          /* go the the next line of the display  */
          display.setCursor(0,10+i*10); 
          /* display the menu options as we progress throught the loop */
          display.print(profile_options[i]);
          /* if we are drawing the profile we selected */
          if(profile_selected == i){
            /* place indicator for currently selected profile */
            display.println("<");
          /* otherwise */
          }else{
            /* dont do anything*/
            display.println();
          } 
        }
        /* if we are displaying bottom 5 selections */
        }else if(highlight_option >= 5){

        /* display the profile selections */
        for (int i=5;i<10;i++) 
        { 
          /* if we are currently drawing what we have selected */
          if(highlight_option == i) 
          { 
            /* highlight the option */
            display.setTextColor(BLACK, WHITE); 
          } 
          /* otherwise */
          else 
          {
            /* draw the text normally */
            display.setTextColor(WHITE); 
          }
          /* go to the next line fo the display */
          display.setCursor(0,10+(i-5)*10); 
          /* display the menu options as we progress throught the loop */
          display.print(profile_options[i]);
          /* if we are drawing the profile we selected */
          if(profile_selected == i){
            /* place indicator for currently selected profile */
            display.println("<");
          /* otherwise */
          }else{
            /* do nothing */
            display.println();
          } 
        }        
      }
      
      /* send the display data to lcd */
      display.display();
      /* allow main menu to be re-drawn */
      option0_draw = true;
      }
      
      /* small delay otheriwse button presses occur too quickly */
      delay(75);
      
      /* if the user presses the select button */
      if (buttonState_0){
        /* profile selected becomes the option we selected */
        profile_selected = highlight_option; 
        /* clear the display */
        display.clearDisplay(); 
        /* allow menu 1 to re-draw */
        option0_draw = false; 
      }

      /* if the user pressed the back button */
      buttonState_5 = digitalRead(buttonPin_5); 
      if(buttonState_5 == HIGH)
      {
        /* clear the display */
        display.clearDisplay();
        /* re-set the highlight to first selection */
        highlight_option = 0;
        /* allow main menu to re-draw */
        loop_draw = false;
        /* return to main menu */
        break;
      }
    }
  } //end option 0
  
  /* if the user selected display password */
  if(highlight_option == 1)
  {
    /* used to determine when the screen needs to be re-drawn */
    boolean option1_draw = false;
    /* clear the display */
    display.clearDisplay();
    /* set decrypt flag to false */
    boolean decryptDone = false;
    /* while we are in the display password menu */
    while(1)
    {  
      if(option1_draw == false)
      {
        /* set the text font size */
        display.setTextSize(1);
        /* set the text color */
        display.setTextColor(WHITE);
        /* set the cursor position */
        display.setCursor(0,0);
      
        /* if a profile has been selected */
        if(profile_selected != 99)
        {
          /* and we have not already decrypted the password */
          if(decryptDone == false)
          {
            /* read all the passwords from sd */
            read_all_password_data();
            /* decrypted the current profile selected */
            decrypt(profile_selected + 1);
            /* set decryption flag to true */
            decryptDone = true;
          }
        
          /* display the decrypted password */
          for (uint8_t i=0; i < 16; i++) {
            /* display text to lcd */
            display.write(plaintext[i]);
          }    

          /* clear non-encrypted data from memory */
          for(int i = 0; i <= 16; i++){
            plaintext[i] = ' ';
          }
                 
        }
        /* otherwise */
        else
        {
          /* display text to lcd */
          display.println("No profile selected.");
        }
      
        /* send display data to lcd */
        display.display();
     
        option1_draw = true; 
      }
      
      /* if the user pressed the back button */
      buttonState_5 = digitalRead(buttonPin_5); 
      if(buttonState_5 == HIGH)
      {
        /* clear the display */
        display.clearDisplay();
        /* set the highlight option to what is was in the previous menu */
        highlight_option = 1;
        /* allow the main menu to re-draw */
        loop_draw = false;
        /* return to main menu */
        break;   
      }   
    } 

  }// end option 1
  
  /* flag that controls when option 2 menu can re-draw */
  boolean option2_draw = false;
  /* if the user selected Generate Password */
  if(highlight_option == 2)
  {
    /* small delay to wait for select button to settle */
    delay(75);
    /* clear the display */
    display.clearDisplay();
    /* set the highlight option to the first selection */
    highlight_option = 0;
    /* while we are in the password generation menu */    
    while(1)
    {
      /* Read button inputs */
      buttonState_0 = digitalRead(buttonPin_0); /* IN */
      buttonState_1 = digitalRead(buttonPin_1); /* Left */
      buttonState_2 = digitalRead(buttonPin_2); /* Down */
      buttonState_3 = digitalRead(buttonPin_3); /* Up */
      buttonState_4 = digitalRead(buttonPin_4); /* Right */
      buttonState_5 = digitalRead(buttonPin_5); /* Switch */
      
      /* if the user pressed the down button */
      if(buttonState_2)            
      {
        /* clear the display */
        display.clearDisplay();
        /* increment screen selection */
        highlight_option--; 
        /* allow option2 menu to re-draw */
        option2_draw = false;     
      }
      /* if the user pressed the up button */
      else if (buttonState_3)   
      {
        /* clear the display */
        display.clearDisplay();
        /* decrement screen selection */
        highlight_option++;   
        /* allow option2 menu to re-draw */
        option2_draw = false;    
      }
      
      /* if we get to the last botton selection move to the top selection 
         if we get tot the last top selection move to bottom selection */
      if (highlight_option < 0) highlight_option = 0; 
      else if (highlight_option > 1) highlight_option = 1;
      
      /* re-draw the screen if something changed otherwise dont both re-drawing display */
      if(option2_draw == false)
      {
        /* set the text font size */
        display.setTextSize(1);
        /* set the text color */
        display.setTextColor(WHITE);
        /* */
        display.setCursor(40,0);
        /* display text to lcd */
        display.println("Menu");
  
        /* display the profile selections */
        for (int i=0;i<2;i++) 
        {
          /* if we are currently drawing what we have selected */
          if(highlight_option == i) 
          { 
            /* highlight the selected option */
            display.setTextColor(BLACK, WHITE); 
          } 
          /* otherwise */
          else 
          {
            /* draw the text normally */
            display.setTextColor(WHITE); 
          }
        /* go the the next line of the display  */
        display.setCursor(0,10+i*10); 
        /* display the menu options as we progress throught the loop */
        display.println(yes_no_options[i]); 
        }  
        /* send the display data to lcd */
        display.display();
        /* allow the option 2 menu to re-draw */
        option2_draw = true;
      }
      
      /* small delay otheriwse button presses occur too quickly */
      delay(75);
      
      /* if the user presses the select button */
      if (buttonState_0){
        /* if the user chooses no */
        if(highlight_option == 0)
        {
          /* clear the display */
          display.clearDisplay();
          /* set the highlight option to what is was in the previous menu */
          highlight_option = 2;
          /* allow the main menu to re-draw */
          loop_draw = false;
          /* small ammount of delay */
          delay(50);
          /* return to main menu */
          break;       
        }
        
        /* if the user chooses yes */
        if(highlight_option == 1)
        {
          /* if there is already a profile selected */
          if(profile_selected != 99)
          {
            /* generate a new password */
            generate_new_password();
            /* encrypt the password and store the password in the profile selected 
               1 is added because profile_selected starts at 0 and pw starts with 1*/
            encrypt(profile_selected + 1);
            /* delete the file that stores the passwords */
            SD.remove("test.txt");
            /* write all the passwords to the sd card */
            write_to_sd();
            /* clear the display */
            display.clearDisplay();
            /* set the text font size */
            display.setTextSize(1);
            /* set the text color */
            display.setTextColor(WHITE);
            /* set the cursor position */
            display.setCursor(0,0);
            /* display text to screen */
            display.println("New Password Created");
            /* send the display data to lcd */
            display.display();
            /* give the user 1 seconds to read the message */
            delay(1000);
            /* clear the display */
            display.clearDisplay();
            /* allow the loop menu to re-draw */
            loop_draw = false;
            /* set the highlight option to what is was in the previous menu */
            highlight_option = 2;
            /* return to main menu  */
            break; 
          /* */            
          }else{
            /* clear the display */
            display.clearDisplay();
            /* set the text font size */
            display.setTextSize(1);
            /* set the text color */
            display.setTextColor(WHITE);
            /* */
            display.setCursor(0,0);  
            /* display text to the lcd */
            display.println("No profile selected.");
            /* send the display data to lcd */
            display.display(); 
            /* give the user 1 seconds to read the message */
            delay(1000);
            /* clear the display */
            display.clearDisplay();
            /* set the highlight option to what is was in the previous menu */
            highlight_option = 2;
            /* allow the loop menu to re-draw */
            loop_draw = false;
            /* return to main menu */
            break;             
          }
        }
      }  
     
      /* if the user pressed the back button */
      buttonState_5 = digitalRead(buttonPin_5); 
      if(buttonState_5 == HIGH)
      {
        /* clear the display */
        display.clearDisplay();
        /* set the highlight option to what it was in the previous menu */
        highlight_option = 2;
        /* allow the main menu to re-draw */
        loop_draw = false;
        /* return to main menu */
        break;
      }
    }  
  }// end option 2

  /* if the user chooses to transmit password to pc */
  if(highlight_option == 3)
  {
    /* while we are in the transmit password menu */
    while(1)
    {
      /* clear the display */
      display.clearDisplay();
      /* set the text size */
      display.setTextSize(1);
      /* set the text color */
      display.setTextColor(WHITE);
      /* set the cursor position */
      display.setCursor(0,0); 
      
      /* if a profile has been selected */
      if(profile_selected != 99)
      {
        /* read all the passwords from the sd */
        read_all_password_data();
        /* decrypt password for currently selected profile */
        decrypt(profile_selected + 1);

        /* transmit passowrd to pc */
        for (uint8_t i=0; i < 16; i++) {
          /* ising the keyboard interface xfer password */
          Keyboard.print((char)plaintext[i]);
        }    

        /* clear non-encrypted data from memory */
        for(int i = 0; i <= 15; i++){
          plaintext[i] = ' ';
        }        
        
        /* display text to lcd */
        display.println("Sent Password to PC");
        /* send the display data to lcd */
        display.display();
        /* small delay for user to read text */
        delay(500);
        /* clear the display */
        display.clearDisplay();
        /* set the highlight option to what is was in the previous menu */
        highlight_option = 3;
        /* allow the main menu to re-draw */
        loop_draw = false;
        /*return to main menu  */
        break;
      /* otherwise */     
      }else{
        /* display text to lcd */
        display.println("No profile selected.");
        /* send display data to lcd */
        display.display();
        /* small delay for user to read text */
        delay(2000);
        /* clear the display */
        display.clearDisplay();
        /* set the highlight option to what it was in the previous menu */
        highlight_option = 3;
        /* allow the main menu to re-draw */
        loop_draw = false;
        /* return to main menu */
        break;         
      }
      
      /* if the user pressed the back button */
      buttonState_5 = digitalRead(buttonPin_5); 
      if(buttonState_5)
      {
        /* clear the display */
        display.clearDisplay();
        /* set the highlight option to what is was in the previous menu */
        highlight_option = 3;
        /* allow the main menu to re-draw */
        loop_draw = false;
        /* return to main menu */
        break;
      }
    } 
  }
}




