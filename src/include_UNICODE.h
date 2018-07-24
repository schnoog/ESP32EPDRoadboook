

String convertUnicode(String unicodeStr){
  String out = "";
  int len = unicodeStr.length();
  char iChar;
  char* error;
  for (int i = 0; i < len; i++){
     iChar = unicodeStr[i];
     if(iChar == '\\'){ // got escape char
       iChar = unicodeStr[++i];
       if(iChar == 'u'){ // got unicode hex
         char unicode[6];
         unicode[0] = '0';
         unicode[1] = 'x';
         for (int j = 0; j < 4; j++){
           iChar = unicodeStr[++i];
           unicode[j + 2] = iChar;
         }
         long unicodeVal = strtol(unicode, &error, 16); //convert the string
         out += (char)unicodeVal;
       } else if(iChar == '/'){
         out += iChar;
       } else if(iChar == 'n'){
         out += '\n';
       }
     } else {
       out += iChar;
     }
  }
  return out;
}

char* string2char(String command){
    if(command.length()!=0){
        char *p = const_cast<char*>(command.c_str());
        return p;
    }
    return 0;
}
  