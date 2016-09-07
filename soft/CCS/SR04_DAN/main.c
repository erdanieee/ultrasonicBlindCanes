#include <main.h>

static unsigned long   totalTime;
static float distance;

struct PulseWith {
   int  loops;
   int  timer;
} pulseWith;

enum {
   SEND_PULSE,
   WAIT_RESP,
   RESULT_AVAILABLE,
   STAND_BY
}state;


#INT_EXT
void isr_ext(){
   if (input(PIN_SIGNAL)){      
      set_timer0(0); 
      pulseWith.loops=0;
      ext_int_edge(H_TO_L);
      state=WAIT_RESP;
      
   }else{
      output_low(PIN_LED_DATA);
      pulseWith.timer = get_timer0();
      state=RESULT_AVAILABLE;
   }
}


#INT_RTCC
void isr(){
	 pulseWith.loops++;	
   totalTime+=TIMER_LOOP;
}


#INT_TIMER1
void isr_send(){
   state=SEND_PULSE;
}




void main()
{
   setup_adc_ports(NO_ANALOGS|VSS_VDD);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_spi(SPI_SS_DISABLED);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_256);
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);
   setup_timer_2(T2_DISABLED,0,1);
   setup_ccp1(CCP_OFF);
   setup_comparator(NC_NC_NC_NC);
   enable_interrupts(INT_EXT);
   enable_interrupts(INT_RTCC);
   enable_interrupts(INT_TIMER1);
   enable_interrupts(GLOBAL);
      
   output_high(PIN_LED_ON);
   state=SEND_PULSE;   
   
   while(true){
      switch(state){
         case STAND_BY:
         case WAIT_RESP:
            break;
            
         case RESULT_AVAILABLE:
            long  loopTime  = pulseWith.loops*TIMER_LOOP;
            float timerTime = pulseWith.timer*TIMER_STEP;
         
            distance = (loopTime + timerTime) / 58;    //t=microseconds, d=centimeters
            printf("%g cm",distance);
            state=STAND_BY;
            break;
            
         case SEND_PULSE:      
            output_high(PIN_LED_DATA);            
            output_drive(PIN_SIGNAL);
            delay_us(2);
            output_high(PIN_SIGNAL);      
 					  delay_us(8);      //5us to 10us
					  output_low(PIN_SIGNAL);
            output_float(PIN_SIGNAL);
            ext_int_edge(L_TO_H);
            break;      
      }
   }
}
