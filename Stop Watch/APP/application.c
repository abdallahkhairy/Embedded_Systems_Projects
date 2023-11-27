/*
 * File:   application.c
 * Author: Abdullah Khairy
 *
 */

#include "application.h"
void TMR0_DefaultInterruptHandler(void);
void Int0_APP_ISR(void);
void Int1_APP_ISR(void);
void Int2_APP_ISR(void);

timer0_t timer0 = {.TMR0_InterruptHandler = TMR0_DefaultInterruptHandler,
                   .prescaler_enable = TIMER0_PRESCALER_ENABLE_CFG,
                   .prescaler_value = TIMER0_PRESCALER_DIV_BY_32,
                   .timer0_mode = TIMER0_TIMER_MODE,
                   .timer0_preload_value = 3036,
                   .timer0_register_size = TIMER0_16BIT_REGISTER_MODE};
interrupt_INTx_t int0_obj = {.EXT_InterruptHandler = Int0_APP_ISR,
                             .edge = INTERRUPT_RISING_EDGE,
                             .priority = INTERRUPT_HIGH_PRIORITY,
                             .source = INTERRUPT_EXTERNAL_INT0,
                             .mcu_pin.port = PORTB_INDEX,
                             .mcu_pin.pin = GPIO_PIN0,
                             .mcu_pin.direction = GPIO_DIRECTION_INPUT};
interrupt_INTx_t int1_obj = {.EXT_InterruptHandler = Int1_APP_ISR,
                             .edge = INTERRUPT_RISING_EDGE,
                             .priority = INTERRUPT_HIGH_PRIORITY,
                             .source = INTERRUPT_EXTERNAL_INT1,
                             .mcu_pin.port = PORTB_INDEX,
                             .mcu_pin.pin = GPIO_PIN1,
                             .mcu_pin.direction = GPIO_DIRECTION_INPUT};
interrupt_INTx_t int2_obj = {.EXT_InterruptHandler = Int2_APP_ISR,
                             .edge = INTERRUPT_RISING_EDGE,
                             .priority = INTERRUPT_HIGH_PRIORITY,
                             .source = INTERRUPT_EXTERNAL_INT2,
                             .mcu_pin.port = PORTB_INDEX,
                             .mcu_pin.pin = GPIO_PIN2,
                             .mcu_pin.direction = GPIO_DIRECTION_INPUT};
pin_config_t seg1_enable = {.port = PORTD_INDEX,
                            .pin = GPIO_PIN0,
                            .direction = GPIO_DIRECTION_OUTPUT,
                            .logic = GPIO_LOW};
pin_config_t seg2_enable = {.port = PORTD_INDEX,
                            .pin = GPIO_PIN1,
                            .direction = GPIO_DIRECTION_OUTPUT,
                            .logic = GPIO_LOW};
pin_config_t seg3_enable = {.port = PORTD_INDEX,
                            .pin = GPIO_PIN2,
                            .direction = GPIO_DIRECTION_OUTPUT,
                            .logic = GPIO_LOW};
pin_config_t seg4_enable = {.port = PORTD_INDEX,
                            .pin = GPIO_PIN3,
                            .direction = GPIO_DIRECTION_OUTPUT,
                            .logic = GPIO_LOW};
pin_config_t seg5_enable = {.port = PORTD_INDEX,
                            .pin = GPIO_PIN4,
                            .direction = GPIO_DIRECTION_OUTPUT,
                            .logic = GPIO_LOW};
pin_config_t seg6_enable = {.port = PORTD_INDEX,
                            .pin = GPIO_PIN5,
                            .direction = GPIO_DIRECTION_OUTPUT,
                            .logic = GPIO_LOW};

uint8 seconds = 0, minutes = 0, hours = 0;
int main() {
  Std_ReturnType ret = E_NOT_OK;
  application_initialize();
  TIMER0_MODULE_DISABLE();
  while (1) {
    ret = gpio_pin_write_logic(&seg6_enable, GPIO_LOW);
    ret = seven_segement_write_number(&seg1, (uint8)(seconds / 10));
    ret = gpio_pin_write_logic(&seg1_enable, GPIO_HIGH);
    __delay_us(100);  // this delay is because 6seg mux is needing specific Fosc
    ret = gpio_pin_write_logic(&seg1_enable, GPIO_LOW);
    ret = seven_segement_write_number(&seg1, (uint8)(seconds % 10));
    ret = gpio_pin_write_logic(&seg2_enable, GPIO_HIGH);
    __delay_us(100);
    ret = gpio_pin_write_logic(&seg2_enable, GPIO_LOW);
    ret = seven_segement_write_number(&seg1, (uint8)(minutes / 10));
    ret = gpio_pin_write_logic(&seg3_enable, GPIO_HIGH);
    __delay_us(100);
    ret = gpio_pin_write_logic(&seg3_enable, GPIO_LOW);
    ret = seven_segement_write_number(&seg1, (uint8)(minutes % 10));
    ret = gpio_pin_write_logic(&seg4_enable, GPIO_HIGH);
    __delay_us(100);
    ret = gpio_pin_write_logic(&seg4_enable, GPIO_LOW);
    ret = seven_segement_write_number(&seg1, (uint8)(hours / 10));
    ret = gpio_pin_write_logic(&seg5_enable, GPIO_HIGH);
    __delay_us(100);
    ret = gpio_pin_write_logic(&seg5_enable, GPIO_LOW);
    ret = seven_segement_write_number(&seg1, (uint8)(hours % 10));
    ret = gpio_pin_write_logic(&seg6_enable, GPIO_HIGH);
    __delay_us(100);
  }
  return (EXIT_SUCCESS);
}

void application_initialize(void) {
  Std_ReturnType ret = E_NOT_OK;
  ecu_layer_init();
  ret = Timer0_Init(&timer0);
  ret = Interrupt_INTx_Init(&int0_obj);
  ret = Interrupt_INTx_Init(&int1_obj);
  ret = Interrupt_INTx_Init(&int2_obj);
  ret = gpio_pin_intialize(&seg1_enable);
  ret = gpio_pin_intialize(&seg2_enable);
  ret = gpio_pin_intialize(&seg3_enable);
  ret = gpio_pin_intialize(&seg4_enable);
  ret = gpio_pin_intialize(&seg5_enable);
  ret = gpio_pin_intialize(&seg6_enable);
}

void TMR0_DefaultInterruptHandler(void) {
  seconds++;
  if (60 == seconds) {
    seconds = 0;
    minutes++;
  } else { /* Nothing */
  }

  if (60 == minutes) {
    minutes = 0;
    hours++;
  } else { /* Nothing */
  }
  /*
   * if(24 == hours){
       seconds=0;
       minutes++;
   }
   else{}
   this case if it was a Normal Clock */
}

void Int0_APP_ISR(void) { TIMER0_MODULE_ENABLE(); }
void Int1_APP_ISR(void) { TIMER0_MODULE_DISABLE(); }
void Int2_APP_ISR(void) {
  seconds = 0, minutes = 0, hours = 0;
  TIMER0_MODULE_ENABLE();
}