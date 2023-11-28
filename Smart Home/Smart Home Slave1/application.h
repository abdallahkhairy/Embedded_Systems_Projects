/* 
 * File:   application.h
 * Author: Abdullah Khairy
 *
 * Created on November 28, 2022, 9:53 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

/* Section : Includes */
#include "ECU_Layer/ecu_layer_init.h"
#include "MCAL_Layer/EEPROM/hal_eeprom.h"
#include "MCAL_Layer/Timer0/hal_timr0.h"
#include "MCAL_Layer/Timer1/hal_timr1.h"
#include "MCAL_Layer/Timer2/hal_timr2.h"
#include "MCAL_Layer/Timer3/hal_timr3.h"
#include "MCAL_Layer/Interrupt/mcal_external_interrupt.h"
#include "MCAL_Layer/ADC/hal_adc.h"
#include "MCAL_Layer/CCP/hal_ccp.h"
#include "MCAL_Layer/usart/hal_usart.h"
#include "MCAL_Layer/SPI/hal_spi.h"
#include "MCAL_Layer/I2C/hal_i2c.h"

/* Section: Macro Declarations */

/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */
extern keypad_t keypad1;
extern led_t led_red_car;
extern led_t led_green_car;
extern led_t led_red_people;
extern led_t led_green_people;
extern led_t ready_yellow;
extern segment_t seg1;
extern segment_t seg2;
extern chr_lcd_8bit_t lcd_2;
extern chr_lcd_4bit_t lcd_1;
extern dc_motor_t dc_motor_1;
extern dc_motor_t dc_motor_2;

/* Section: Function Declarations */
void application_initialize(void);

#endif	/* APPLICATION_H */

