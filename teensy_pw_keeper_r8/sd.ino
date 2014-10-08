void write_to_sd()
{
  /* open the file test.txt on the sd card for writing  */
  myFile = SD.open("test.txt", FILE_WRITE); 
 
  /* if file available write all 10 passwords to file  */
  if (myFile) {
    myFile.write(pw1,16);
    myFile.write('\n');
    myFile.write(pw2,16);
    myFile.write('\n');
    myFile.write(pw3,16);
    myFile.write('\n');
    myFile.write(pw4,16);
    myFile.write('\n');
    myFile.write(pw5,16);
    myFile.write('\n');
    myFile.write(pw6,16);
    myFile.write('\n');
    myFile.write(pw7,16);
    myFile.write('\n'); 
    myFile.write(pw8,16);
    myFile.write('\n');
    myFile.write(pw9,16);
    myFile.write('\n');
    myFile.write(pw10,16);
    myFile.write('\n');    
    myFile.close();
  }
}


void read_all_password_data()
{
  for(int i = 0; i <= 9; i++)
  {
    /* read first line of sd card */
    sd_data = readFile(i+1);
    
    /* if a password exists on the line we are reading */
    if(sd_data.length() > 5)
    {
       switch(i)
       {
         /* if we are reading line 0 (line 1 on sd card) */
         case 0:
           /* itterate over the sixteen bits that make up the password */
           for(int k = 0; k <= 15; k++)
           {
             /* store the 16 bits in pw1 char array */
             pw1[k] = sd_data[k];
           }
           /* reset data buffer for next read */
           sd_data = "";  
           break;
         /* if we are reading line 1 (line 2 on sd card) */  
         case 1:
           /* itterate over the sixteen bits that make up the password */
           for(int k = 0; k <= 15; k++)
           {
             /* store the 16 bits in pw2 char array */
             pw2[k] = sd_data[k];           
           }    
           /* reset data buffer for next read */
           sd_data = "";       
           break;
         /* if we are reading line 2 (line 3 on sd card) */  
         case 2:
           /* itterate over the sixteen bits that make up the password */
           for(int k = 0; k <= 15; k++)
           {
             /* store the 16 bits in pw3 char array */
             pw3[k] = sd_data[k];          
           }   
           /* reset data buffer for next read */
           sd_data = "";      
           break;
         /* if we are reading line 3 (line 4 on sd card) */  
         case 3:
           /* itterate over the sixteen bits that make up the password */
           for(int k = 0; k <= 15; k++)
           {
             /* store the 16 bits in pw4 char array */ 
             pw4[k] = sd_data[k];           
           }  
           /* reset data buffer for next read */   
           sd_data = "";      
           break;
         /* if we are reading line 4 (line 5 on sd card) */  
         case 4:
           /* itterate over the sixteen bits that make up the password */
           for(int k = 0; k <= 15; k++)
           {
             /* store the 16 bits in pw5 char array */
             pw5[k] = sd_data[k];           
           }   
           /* reset data buffer for next read */
           sd_data = "";        
           break;
         /* if we are reading line 5 (line 6 on sd card) */  
         case 5:
           /* itterate over the sixteen bits that make up the password */
           for(int k = 0; k <= 15; k++)
           {
             /* store the 16 bits in pw6 char array */
             pw6[k] = sd_data[k];           
           }    
           /* reset data buffer for next read */
           sd_data = "";       
           break;
         /* if we are reading line 6 (line 7 on sd card) */  
         case 6:
           /* itterate over the sixteen bits that make up the password */
           for(int k = 0; k <= 15; k++)
           {
             /* store the 16 bits in pw7 char array */
             pw7[k] = sd_data[k];           
           }    
           /* reset data buffer for next read */
           sd_data = "";       
           break;
         /* if we are reading line 7 (line 8 on sd card) */  
         case 7:
           /* itterate over the sixteen bits that make up the password */
           for(int k = 0; k <= 15; k++)
           {
             /* store the 16 bits in pw8 char array */
             pw8[k] = sd_data[k];          
           }   
           /* reset data buffer for next read */
           sd_data = "";        
           break;
         /* if we are reading line 8 (line 9 on sd card) */  
         case 8:
           /* itterate over the sixteen bits that make up the password */
           for(int k = 0; k <= 15; k++)
           {
             /* store the 16 bits in pw9 char array */
             pw9[k] = sd_data[k];            
           }     
           /* reset data buffer for next read */
           sd_data = "";      
           break;
         /* if we are reading line 9 (line 10 on sd card) */  
         case 9:
           /* itterate over the sixteen bits that make up the password */
           for(int k = 0; k <= 15; k++)
           {
             /* store the 16 bits in pw10 char array */
             pw10[k] = sd_data[k];          
           }   
           /* reset data buffer for next read */
           sd_data = "";        
           break;
         
         default:
           break;
       }
    }
  }
}

String readFile(int line)
{
  myFile = SD.open("test.txt",FILE_READ);
  if(myFile)
  {
    String received = "";
    int cur = 0;
    char ch;
    while (myFile.available())
    {
      ch = myFile.read();
      if(ch == '\n' && received.length() >= 16) 
      {
        cur++;
        if(cur == line)
        {
          myFile.close();
          return String(received);
        }
        received = "";
      }
      else
      {
        received += ch;
      }
    }
  }
  return "";
}


