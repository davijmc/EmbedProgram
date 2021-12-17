//#include <xc.h>

void delay(){
    volatile unsigned char j, k;
    for (j = 0; j < 41; j++){
        for (k = 0; k < 3; k++);
    }
}
