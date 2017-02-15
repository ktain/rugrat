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
void adc_setup(void);
void motor_setup(void);
void encoder_setup(void);
uint32_t readADC(uint32_t channel);
void readSensors(void);

extern volatile uint32_t rawVoltage;
extern volatile uint32_t rawSensorVal[7];

#endif
