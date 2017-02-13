#if !defined(SETUP_H)
#define SETUP_H

#define TICKS_PER_MS (100000)
#define TICKS_PER_US (100)
#define BAUDRATE (9600)	// Serial data rate

void setup(void);
void systick_setup(void);
void led_setup(void);
void emitter_setup(void);
void button_setup(void);
void usart_setup(void);

#endif
