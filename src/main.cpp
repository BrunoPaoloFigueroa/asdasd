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
unsigned char a = 0;

void config_PCI(void){
    EIMSK |= 0x03;          // Habilita INT0 y INT1
    EICRA |= 0x0A;          // INT0 e INT1 en flanco de bajada

    DDRD &= ~(0x0C);        // PD2 y PD3 como entrada (0x04 y 0x08)
    PORTD |= 0x0C;          // Pull-up en PD2 y PD3
}

ISR(INT0_vect){
    if (a < 99) a++;
}

ISR(INT1_vect){
    if (a > 0) a--;
}

unsigned char decodificar(unsigned char valor){
    switch(valor){
        case 0: return 0x01;
        case 1: return 0x02;
        case 2: return 0x04;
        case 3: return 0x08;
        case 4: return 0x01;
        case 5: return 0x02;
        case 6: return 0x04;
        case 7: return 0x08;
        case 8: return 0x01;
        case 9: return 0x02;
        default: return 0x00;
    }
}

int main(void){
    DDRB |= 0x0F;           // PB0–PB3 como salidas
    DDRD |= 0xC0;           // PD6 y PD7 como salidas (0x40 y 0x80)

    PORTD &= ~(0xC0);       // PD6 y PD7 apagados

    config_PCI();
    sei();

    while (1){
        unsigned char u = a % 10;
        unsigned char d = a / 10;

        // Mostrar decenas
        PORTD &= ~(0x80);   // Apaga unidades (PD7)
        PORTD |= 0x40;      // Enciende decenas (PD6)
        PORTB = (PORTB & 0xF0) | (decodificar(d) & 0x0F);
        _delay_ms(5);

        // Mostrar unidades
        PORTD &= ~(0x40);   // Apaga decenas (PD6)
        PORTD |= 0x80;      // Enciende unidades (PD7)
        PORTB = (PORTB & 0xF0) | (decodificar(u) & 0x0F);
        _delay_ms(5);
    }

    return 0;
}








