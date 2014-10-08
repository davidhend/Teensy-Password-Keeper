void generate_new_password()
{
  /* generate first passsword */
  String password1 = getPassword(pw);
  /* generate second password */
  String password2 = getPassword(pw);
  /* combine the first and second password to create one large password */
  String combined_password = password1 + password2;
  /* convert the password string into char array */
  for(int i = 0; i <= 15; i++){
     plaintext[i] = combined_password[i];
  }  
  
  /* clear non-encrypted data from memory */
  password1 = "";
  /* clear non-encrypted data from memory */
  password2 = "";
  /* clear non-encrypted data from memory */
  combined_password = "";
}

/* This routine will convert a 6 bit value (0-63) to an acceptible password character */
char mapChar(uint32_t parm)
{
  char retval;
  if (parm < 10)           // map 0..9 to ascii 0..9
    retval = char(48 + parm);
  else if (parm < 11)      // map 10 to -
    retval = '-';
  else if (parm < 12)      // map 11 to +
    retval = '.';
  else if (parm < 38)      // map 12 to 37 to ascii A..Z
    retval = char(53 + parm);
  else if (parm < 64)      // map 38 to 63 to ascii a..z
    retval = char(59 + parm);
  else
    retval = 0;            // if parm is invalid return null  
  return(retval);
}

/* This routine uses the Entropy library to obtain truly random 6 bit values 
   and to map that to an eight character cryptographically secure password */
char *getPassword(char *pw)
{
  char ch;
  int indx;
  uint32_t tmp;
  
  
  for (indx=0; indx<8; indx++)
  { 
    tmp = mapChar(Entropy.random(64));
    pw[indx] = (char) tmp;
  }
  pw[8] = 0;
  return(pw);
}




