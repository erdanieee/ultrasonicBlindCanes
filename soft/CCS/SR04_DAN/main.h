#include <16F88.h>
#device adc=8

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES HS                       //High speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)
#FUSES PUT                      //Power Up Timer
#FUSES MCLR                     //Master Clear pin enabled
#FUSES BROWNOUT               	//brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection
#FUSES NOWRT                    //Program memory not write protected
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES NOPROTECT                //Code not protected from reading
#FUSES FCMEN                    //Fail-safe clock monitor enabled
#FUSES IESO                     //Internal External Switch Over mode enabled



#define TIMER1_PRELOAD    2985   //aprox 100ms@(20MHz,1:8)
#define TIMER_STEP        51.2   //tiempo de cada paso del reloj. 51,2us@(20MHz,1:256,8bit)
#define TIMER_LOOP        13107  //aprox 13,11ms@(20MHz,1:256)
#define PIN_SIGNAL      PIN_B0
#define PIN_LED_ON      PIN_B4
#define PIN_LED_DATA    PIN_B5
#define PIN_RS232_XMIT  PIN_A0   //pines compatibles con placa pruebas
#define PIN_RS232_RCV   PIN_A1   //pines compatibles con placa pruebas


#use delay(clock=20000000)
#use rs232(baud=9600,parity=N,xmit=PIN_RS232_XMIT,rcv=PIN_RS232_RCV,bits=8)



