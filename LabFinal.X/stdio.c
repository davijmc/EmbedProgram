#include "lcd.h"
void printf(char txt[17]){
    int i;
    for(i=0; i<17; i++){
        if(txt[i] == '\n'){
            lcdCommand(0xC0);
        }
        lcdChar(txt[i]);
    }
}