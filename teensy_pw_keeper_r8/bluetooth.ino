/* keeps track of secondary authentication status */
boolean pin_needed = true;
/* keeps track of pin attempts */
int pin_attempts = 0;
/* used when comparing andriod pin number */
int counter = 0;
/* clear the string that holds the pin */
String bt_data = "";

void get_authorization()
{
 /* while we still need a pin number */
 while(pin_needed){
   /* read the bluetooth adapter for incoming data */
   if(Serial1.available() > 0){
     /* read the data as a char */
     char c = Serial1.read();
     /* append the char we read to the string that holds the pin number */
     bt_data += c;
   }

   if(bt_data.length() >= 102){
     parse_data();
     bt_data = ""; 
     pin_needed = false;
   }
 }
 
}

void parse_data()
{
  int start = bt_data.indexOf("start:");
  int coma_1 = bt_data.indexOf(",", start + 1);
  int coma_2 = bt_data.indexOf(",", coma_1 + 1);
  int coma_3 = bt_data.indexOf(",", coma_2 + 1);
  int coma_4 = bt_data.indexOf(",", coma_3 + 1);
  int coma_5 = bt_data.indexOf(",", coma_4 + 1);
  int coma_6 = bt_data.indexOf(",", coma_5 + 1);
  int coma_7 = bt_data.indexOf(",", coma_6 + 1);
  int coma_8 = bt_data.indexOf(",", coma_7 + 1);
  int coma_9 = bt_data.indexOf(",", coma_8 + 1);
  int coma_10 = bt_data.indexOf(",", coma_9 + 1);
  int coma_11 = bt_data.indexOf(",", coma_10 + 1);
  int coma_12 = bt_data.indexOf(",", coma_11 + 1);
  int coma_13 = bt_data.indexOf(",", coma_12 + 1);
  int coma_14 = bt_data.indexOf(",", coma_13 + 1);
  int coma_15 = bt_data.indexOf(",", coma_14 + 1);
  int coma_16 = bt_data.indexOf(",", coma_15 + 1);
  int coma_17 = bt_data.indexOf(",", coma_16 + 1);
  int coma_18 = bt_data.indexOf(",", coma_17 + 1);
  int coma_19 = bt_data.indexOf(",", coma_18 + 1);
  int coma_20 = bt_data.indexOf(",", coma_19 + 1);
  int coma_21 = bt_data.indexOf(",", coma_20 + 1);
  int coma_22 = bt_data.indexOf(",", coma_21 + 1);
  int coma_23 = bt_data.indexOf(",", coma_22 + 1);
  int coma_24 = bt_data.indexOf(",", coma_23 + 1);
  int coma_25 = bt_data.indexOf(",", coma_24 + 1);
  int coma_26 = bt_data.indexOf(",", coma_25 + 1);
  int coma_27 = bt_data.indexOf(",", coma_26 + 1);
  int coma_28 = bt_data.indexOf(",", coma_27 + 1);
  int coma_29 = bt_data.indexOf(",", coma_28 + 1);
  int coma_30 = bt_data.indexOf(",", coma_29 + 1);
  int coma_31 = bt_data.indexOf(",", coma_30 + 1);
  int endp = bt_data.indexOf("end", coma_31 + 1);
  
  String val_1 = bt_data.substring(start+6, coma_1);
  String val_2 = bt_data.substring(coma_1+1, coma_2);
  String val_3 = bt_data.substring(coma_2+1, coma_3);
  String val_4 = bt_data.substring(coma_3+1, coma_4);
  String val_5 = bt_data.substring(coma_4+1, coma_5);
  String val_6 = bt_data.substring(coma_5+1, coma_6);
  String val_7 = bt_data.substring(coma_6+1, coma_7);
  String val_8 = bt_data.substring(coma_7+1, coma_8);
  String val_9 = bt_data.substring(coma_8+1, coma_9);
  String val_10 = bt_data.substring(coma_9+1, coma_10);
  String val_11 = bt_data.substring(coma_10+1, coma_11);
  String val_12 = bt_data.substring(coma_11+1, coma_12);
  String val_13 = bt_data.substring(coma_12+1, coma_13);
  String val_14 = bt_data.substring(coma_13+1, coma_14);
  String val_15 = bt_data.substring(coma_14+1, coma_15);
  String val_16 = bt_data.substring(coma_15+1, coma_16);
  String val_17 = bt_data.substring(coma_16+1, coma_17);
  String val_18 = bt_data.substring(coma_17+1, coma_18);
  String val_19 = bt_data.substring(coma_18+1, coma_19);
  String val_20 = bt_data.substring(coma_19+1, coma_20);
  String val_21 = bt_data.substring(coma_20+1, coma_21);
  String val_22 = bt_data.substring(coma_21+1, coma_22);
  String val_23 = bt_data.substring(coma_22+1, coma_23);
  String val_24 = bt_data.substring(coma_23+1, coma_24);
  String val_25 = bt_data.substring(coma_24+1, coma_25);
  String val_26 = bt_data.substring(coma_25+1, coma_26);
  String val_27 = bt_data.substring(coma_26+1, coma_27);
  String val_28 = bt_data.substring(coma_27+1, coma_28);
  String val_29 = bt_data.substring(coma_28+1, coma_29);
  String val_30 = bt_data.substring(coma_29+1, coma_30);
  String val_31 = bt_data.substring(coma_30+1, coma_31);
  String val_32 = bt_data.substring(coma_31+1, endp-1);
  
  encryptionKey[0] = val_1.toInt();
  encryptionKey[1] = val_2.toInt();
  encryptionKey[2] = val_3.toInt();
  encryptionKey[3] = val_4.toInt();
  encryptionKey[4] = val_5.toInt();
  encryptionKey[5] = val_6.toInt();
  encryptionKey[6] = val_7.toInt();
  encryptionKey[7] = val_8.toInt();
  encryptionKey[8] = val_9.toInt();
  encryptionKey[9] = val_10.toInt();
  encryptionKey[10] = val_11.toInt();
  encryptionKey[11] = val_12.toInt();
  encryptionKey[12] = val_13.toInt();
  encryptionKey[13] = val_14.toInt();
  encryptionKey[14] = val_15.toInt();
  encryptionKey[15] = val_16.toInt();
  encryptionKey[16] = val_17.toInt();
  encryptionKey[17] = val_18.toInt();
  encryptionKey[18] = val_19.toInt();
  encryptionKey[19] = val_20.toInt();
  encryptionKey[20] = val_21.toInt();
  encryptionKey[21] = val_22.toInt();
  encryptionKey[22] = val_23.toInt();
  encryptionKey[23] = val_24.toInt();
  encryptionKey[24] = val_25.toInt();
  encryptionKey[25] = val_26.toInt();
  encryptionKey[26] = val_27.toInt();
  encryptionKey[27] = val_28.toInt();
  encryptionKey[28] = val_29.toInt();
  encryptionKey[29] = val_30.toInt();
  encryptionKey[30] = val_31.toInt();
  encryptionKey[31] = val_32.toInt();
  
}
