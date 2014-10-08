void encrypt(int profile_number)
{
  if(profile_number >= 1 && profile_number <= 10)
  {
  
    /* encrypt password */
    nrounds = aesSetupEncrypt(rk, encryptionKey, KEYBITS);
    aesEncrypt(rk, nrounds, plaintext, ciphertext);

    /* clear non-encrypted data from memory */
    for(int i = 0; i <= 16; i++){
       plaintext[i] = ' ';
    }  
 
    switch(profile_number)
    {
      case 1: 
         for(int i = 0; i <= 15; i++){
           pw1[i] = ciphertext[i]; 
         }
         break;
      case 2:   
         for(int i = 0; i <= 15; i++){
           pw2[i] = ciphertext[i]; 
         }
         break; 
      case 3:
         for(int i = 0; i <= 15; i++){
           pw3[i] = ciphertext[i]; 
         }
         break; 
      case 4:
         for(int i = 0; i <= 15; i++){
           pw4[i] = ciphertext[i]; 
         }
         break;    
      case 5:
         for(int i = 0; i <= 15; i++){
           pw5[i] = ciphertext[i]; 
         }
         break;
      case 6:
         for(int i = 0; i <= 15; i++){
           pw6[i] = ciphertext[i]; 
         }
         break;       
      case 7:
         for(int i = 0; i <= 15; i++){
           pw7[i] = ciphertext[i]; 
         }
         break;
      case 8:
         for(int i = 0; i <= 15; i++){
           pw8[i] = ciphertext[i]; 
         }
         break;       
      case 9:
         for(int i = 0; i <= 15; i++){
           pw9[i] = ciphertext[i]; 
         }
         break;
      case 10:
         for(int i = 0; i <= 15; i++){
           pw10[i] = ciphertext[i]; 
         }
         break;       
       
      default:
         break;    
    }
  
  }
}

void decrypt(int profile_number)
{
  if(profile_number >= 1 && profile_number <= 10)
  {
    
    switch(profile_number)
    {
      case 1: 
         for(int i = 0; i <= 15; i++){
            ciphertext[i] = pw1[i]; 
         }
         break;
      case 2:
         for(int i = 0; i <= 15; i++){
           ciphertext[i] = pw2[i]; 
         }
         break;  
      case 3:
         for(int i = 0; i <= 15; i++){
           ciphertext[i] = pw3[i]; 
         }
         break;  
      case 4:
         for(int i = 0; i <= 15; i++){
           ciphertext[i] = pw4[i]; 
         }
         break;   
      case 5:
         for(int i = 0; i <= 15; i++){
           ciphertext[i] = pw5[i]; 
         }
         break;
      case 6:
         for(int i = 0; i <= 15; i++){
           ciphertext[i] = pw6[i]; 
         }
         break;
      case 7:
         for(int i = 0; i <= 15; i++){
           ciphertext[i] = pw7[i]; 
         }
         break;
      case 8:
         for(int i = 0; i <= 15; i++){
           ciphertext[i] = pw8[i]; 
         }
         break;
      case 9:
         for(int i = 0; i <= 15; i++){
           ciphertext[i] = pw9[i]; 
         }
         break;
      case 10:
         for(int i = 0; i <= 15; i++){
           ciphertext[i] = pw10[i]; 
         }
         break;
       
      default:
         break;    
    }  
  
    /* decrypt password */
    nrounds = aesSetupDecrypt(rk, encryptionKey, KEYBITS);
    aesDecrypt(rk, nrounds, ciphertext, plaintext);
  
  }  
}

