#include <avr/io.h>
#define F_CPU 16000000Ul
#include <util/delay.h>
#include <avr/interrupt.h>
/*
char a=0x00;
void config_IEO(void){
    EIMSK|=(1<<INT0)|(1<<INT1);
    EICRA|=(1<<ISC01)|(1<<ISC11);
    DDRD&=~0x04;
    PORTD|=0x04;
    DDRD&=~0x08;
    PORTD|=0x08;

}

ISR(INT0_vect){

      
      a=(a+0x01)%100;  


}
ISR(INT1_vect){
  
      if(a==0x00){
       a=99;
      } 
      a=(a-0x01);  

  }

int main(void){

  DDRD|=0xF0;//dilplay
  DDRB|=0x03;//comunes
  PORTB&=~(0x03);

    config_IEO();
    sei();
    while(1){
      char u=a%10;
      char d=a/10;
      PORTB&=~0x01;
      PORTB|=0x02;
      PORTD=d&0xF0;
      _delay_ms(8);
      PORTB&=~0x02;
      PORTB|=0x01;
      PORTD=u&0xF0;
      _delay_ms(8);
    }

}


void config_PCI(void){
    PCICR|=0x01;
    PCMSK0|=0x02;
    DDRB&=~0x02;
    PORTB|=0x02;
}
ISR (PCINT0_vect){
    _delay_ms(200);
    if(PORTB&0x01){
      PORTB&=~0x01;
    }else{
      PORTB|=0x01;
    }
}

int main(void){
    DDRB|=0x01;
    PORTB&=~0x01;
    config_PCI();
    sei();
    while(1){

    }


}
*/
char a=0x00;
void config_PCI(void){
    EIMSK|=(1<<INT0)|(1<<INT1);
    EICRA|=(1<<ISC01)|(1<<ISC11);
    DDRD&=~0x04;
    PORTD|=0x04;
    DDRD&=~0x08;
    PORTD|=0x08;

}
ISR(INT0_vect){

  
  a=(a+0x01);  


}
ISR(INT1_vect){

  
  a=(a-0x01);  

}

int main(void){
  
  DDRB|=0x0F;
  DDRD|=0xC0;
  PORTD&=~(0xC0);
  char u=a%10;
      char d=a/10;
  config_PCI();
    sei();
 while(1){
  
  PORTD&=~0x80;
  PORTD|=0x40;
  PORTB|=d;
  PORTB&=0x0F;
  _delay_ms(8);
  PORTD&=~0x40;
  PORTD|=0x80;
  PORTB|=u;
  PORTB&=0x0F;
  _delay_ms(8);
  

}
return 0;
}












