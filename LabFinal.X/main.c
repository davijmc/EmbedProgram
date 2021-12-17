#include "pic18f4520.h"
#include "lcd.h"
#include "adc.h"
#include "bits.h"
#include "io.h"
#include "so.h"
#include "ssd.h"
#include "timer.h"
#include "atraso.h"
#include "config.h"
#include "keypad.h"

#define L_ON  0x0F
#define L_OFF 0x08
#define L_CLR 0x01//clear
#define L_L1  0x80//linha 1
#define L_L2  0xC0//linha 2

static char v0;

unsigned int leitura = 0, tempo = 0, alt =0, vel = 0;
unsigned char estado = 0, falha = 0;

void LeTeclado(void){
    if(kpRead() != leitura){
        leitura = kpRead();
        
        switch(kpReadKey()){
            case 'U':
                if(estado == 0){
                    vel = 100;
                    estado = 1;
                    PORTD = 0xFF;
                }else if((estado != 3)&&(falha == 0)){
                    estado = 3;
                    PORTD = 0xFF;
                }
                if(vel>0)alt = alt + vel;
                tempo = tempo + 1;
                break;
            case 'L':
                if((alt<1500)&&(vel<401)){
                    vel = vel + 50;
                }
                if(vel>0)alt = alt + vel;
                tempo = tempo + 1;
                break;
            case 'D':
                if(vel>49){
                    vel = vel - 50;
                }else{
                    vel = 0;
                }
                if(vel>0)alt = alt + vel;
                tempo = tempo + 1;
                break;
            case 'R':
                if(vel>2){
                    vel = vel - 3;
                }else{
                    vel = 0;
                }
                if(vel>0)alt = alt + vel;
                tempo = tempo + 1;
                break;
            case 'S':
                falha = 1;
                tempo = tempo + 1;
                if(vel>0)alt = alt + vel;
                break;
            default:
                break;
        }
        if(estado == 2){
            alt=alt-10;
            if(vel<50){
                alt=alt-40;
            }
        }
    }
}

void main(void){
    int x = 0;
    TRISD = 0x00;
    PORTD = 0x00;
    
    soInit();
    kpInit();
    lcdInit();
    ssdInit();
    timerInit();
    
    lcdCommand(L_CLR);
    for(;;){
        switch(estado){
            case 1:
                if(vel < 45){
                    falha = 1;
                }
                if(tempo >= 3){
                    estado = 2;
                }
                break;
            case 2:
                if(alt < 30){
                    falha = 2;
                }
                break;
            case 3:
                if((tempo > 5)&&(vel <= 5)&&(alt<1001)){
                    estado = 4;
                }else{
                    falha = 2;
                }
                break;
        }
        switch(falha){
            case 0:
                PORTD = 0b00000010;//RGB verde
                break;
            case 1:
                PORTD = 0b00000011;//RGB amarelo
                break;
            case 2:
                PORTD = 0b00000001;//RGB vermelho
                break;
        }
        if(falha == 0){
            LeTeclado();
            kpDebounce();
        }
        lcdCommand(L_L1);
        lcdString("V:");
        lcdNumber(vel);
        lcdString(" T:");
        lcdNumber(tempo);

        lcdCommand(L_L2);
        lcdString("H:");
        lcdNumber(alt);

        v0 = estado;
        ssdDigit(x, 0);
        ssdDigit(x, 1);
        ssdDigit(x, 2);
        ssdDigit(v0, 3);
        ssdUpdate();
        atraso_ms(100);
    }
}