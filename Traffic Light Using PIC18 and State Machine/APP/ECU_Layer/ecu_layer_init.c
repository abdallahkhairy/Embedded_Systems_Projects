
#include "Chr_LCD/ecu_chr_lcd.h"
#include "KeyPad/ecu_keypad.h"
#include "7_Segment/ecu_seven_segment.h"
#include "LED/ecu_led.h"
#include "DC_Motor/ecu_dc_motor.h"


segment_t seg1 = {
    .segment_pins[0].port = PORTC_INDEX,
    .segment_pins[0].pin = GPIO_PIN0,
    .segment_pins[0].logic = GPIO_LOW,
    .segment_pins[0].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[1].port = PORTC_INDEX,
    .segment_pins[1].pin = GPIO_PIN1,
    .segment_pins[1].logic = GPIO_LOW,
    .segment_pins[1].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[2].port = PORTC_INDEX,
    .segment_pins[2].pin = GPIO_PIN2,
    .segment_pins[2].logic = GPIO_LOW,
    .segment_pins[2].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[3].port = PORTC_INDEX,
    .segment_pins[3].pin = GPIO_PIN3,
    .segment_pins[3].logic = GPIO_LOW,
    .segment_pins[3].direction = GPIO_DIRECTION_OUTPUT,
    .segment_type = SEGMENT_COMMON_CATHODE
};


/* Traffic Light
segment_t seg2 = {
    .segment_pins[0].port = PORTC_INDEX,
    .segment_pins[0].pin = GPIO_PIN4,
    .segment_pins[0].logic = GPIO_LOW,
    .segment_pins[0].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[1].port = PORTC_INDEX,
    .segment_pins[1].pin = GPIO_PIN5,
    .segment_pins[1].logic = GPIO_LOW,
    .segment_pins[1].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[2].port = PORTC_INDEX,
    .segment_pins[2].pin = GPIO_PIN6,
    .segment_pins[2].logic = GPIO_LOW,
    .segment_pins[2].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[3].port = PORTC_INDEX,
    .segment_pins[3].pin = GPIO_PIN7,
    .segment_pins[3].logic = GPIO_LOW,
    .segment_pins[3].direction = GPIO_DIRECTION_OUTPUT,
    .segment_type = SEGMENT_COMMON_CATHODE
};
*/


chr_lcd_4bit_t lcd_1 = {
    .lcd_rs.port = PORTD_INDEX,
    .lcd_rs.pin = GPIO_PIN0,
    .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_rs.logic = GPIO_LOW,
    .lcd_en.port = PORTD_INDEX,
    .lcd_en.pin = GPIO_PIN1,
    .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_en.logic = GPIO_LOW,
    .lcd_data[0].port = PORTD_INDEX,
    .lcd_data[0].pin = GPIO_PIN2,
    .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[0].logic = GPIO_LOW,
    .lcd_data[1].port = PORTD_INDEX,
    .lcd_data[1].pin = GPIO_PIN3,
    .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[1].logic = GPIO_LOW,
    .lcd_data[2].port = PORTD_INDEX,
    .lcd_data[2].pin = GPIO_PIN4,
    .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[2].logic = GPIO_LOW,
    .lcd_data[3].port = PORTD_INDEX,
    .lcd_data[3].pin = GPIO_PIN5,
    .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[3].logic = GPIO_LOW
};


/* Traffic Light
led_t led_red_car = {._led.port = PORTA_INDEX, ._led.pin = GPIO_PIN0, ._led.logic = LED_OFF};
led_t led_green_car = {._led.port = PORTA_INDEX, ._led.pin = GPIO_PIN1, ._led.logic = LED_OFF};

led_t led_red_people = {._led.port = PORTA_INDEX, ._led.pin = GPIO_PIN2, ._led.logic = LED_OFF};
led_t led_green_people = {._led.port = PORTA_INDEX, ._led.pin = GPIO_PIN3, ._led.logic = LED_OFF};

led_t ready_yellow = {._led.port = PORTA_INDEX, ._led.pin = GPIO_PIN5, ._led.logic = LED_OFF};
*/
/*
chr_lcd_4bit_t lcd_1 = {
    .lcd_rs.port = PORTC_INDEX,
    .lcd_rs.pin = GPIO_PIN0,
    .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_rs.logic = GPIO_LOW,
    .lcd_en.port = PORTC_INDEX,
    .lcd_en.pin = GPIO_PIN1,
    .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_en.logic = GPIO_LOW,
    .lcd_data[0].port = PORTC_INDEX,
    .lcd_data[0].pin = GPIO_PIN2,
    .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[0].logic = GPIO_LOW,
    .lcd_data[1].port = PORTC_INDEX,
    .lcd_data[1].pin = GPIO_PIN3,
    .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[1].logic = GPIO_LOW,
    .lcd_data[2].port = PORTC_INDEX,
    .lcd_data[2].pin = GPIO_PIN4,
    .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[2].logic = GPIO_LOW,
    .lcd_data[3].port = PORTC_INDEX,
    .lcd_data[3].pin = GPIO_PIN5,
    .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[3].logic = GPIO_LOW
};
 * */
chr_lcd_8bit_t lcd_2 = {
    .lcd_rs.port = PORTC_INDEX,
    .lcd_rs.pin = GPIO_PIN6,
    .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_rs.logic = GPIO_LOW,
    .lcd_en.port = PORTC_INDEX,
    .lcd_en.pin = GPIO_PIN7,
    .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_en.logic = GPIO_LOW,
    .lcd_data[0].port = PORTD_INDEX,
    .lcd_data[0].pin = GPIO_PIN0,
    .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[0].logic = GPIO_LOW,
    .lcd_data[1].port = PORTD_INDEX,
    .lcd_data[1].pin = GPIO_PIN1,
    .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[1].logic = GPIO_LOW,
    .lcd_data[2].port = PORTD_INDEX,
    .lcd_data[2].pin = GPIO_PIN2,
    .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[2].logic = GPIO_LOW,
    .lcd_data[3].port = PORTD_INDEX,
    .lcd_data[3].pin = GPIO_PIN3,
    .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[3].logic = GPIO_LOW,
    .lcd_data[4].port = PORTD_INDEX,
    .lcd_data[4].pin = GPIO_PIN4,
    .lcd_data[4].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[4].logic = GPIO_LOW,
    .lcd_data[5].port = PORTD_INDEX,
    .lcd_data[5].pin = GPIO_PIN5,
    .lcd_data[5].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[5].logic = GPIO_LOW,
    .lcd_data[6].port = PORTD_INDEX,
    .lcd_data[6].pin = GPIO_PIN6,
    .lcd_data[6].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[6].logic = GPIO_LOW,
    .lcd_data[7].port = PORTD_INDEX,
    .lcd_data[7].pin = GPIO_PIN7,
    .lcd_data[7].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[7].logic = GPIO_LOW
};

keypad_t keypad1 = {
    .keypad_row_pins[0].port = PORTC_INDEX,
    .keypad_row_pins[0].pin = GPIO_PIN6,
    .keypad_row_pins[0].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[0].logic = GPIO_LOW,
    .keypad_row_pins[1].port = PORTC_INDEX,
    .keypad_row_pins[1].pin = GPIO_PIN7,
    .keypad_row_pins[1].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[1].logic = GPIO_LOW,
    .keypad_row_pins[2].port = PORTD_INDEX,
    .keypad_row_pins[2].pin = GPIO_PIN0,
    .keypad_row_pins[2].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[2].logic = GPIO_LOW,
    .keypad_row_pins[3].port = PORTD_INDEX,
    .keypad_row_pins[3].pin = GPIO_PIN1,
    .keypad_row_pins[3].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[3].logic = GPIO_LOW,
    .keypad_columns_pins[0].port = PORTD_INDEX,
    .keypad_columns_pins[0].pin = GPIO_PIN2,
    .keypad_columns_pins[0].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[0].logic = GPIO_LOW,
    .keypad_columns_pins[1].port = PORTD_INDEX,
    .keypad_columns_pins[1].pin = GPIO_PIN3,
    .keypad_columns_pins[1].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[1].logic = GPIO_LOW,
    .keypad_columns_pins[2].port = PORTD_INDEX,
    .keypad_columns_pins[2].pin = GPIO_PIN4,
    .keypad_columns_pins[2].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[2].logic = GPIO_LOW,
    .keypad_columns_pins[3].port = PORTD_INDEX,
    .keypad_columns_pins[3].pin = GPIO_PIN5,
    .keypad_columns_pins[3].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[3].logic = GPIO_LOW,
};

dc_motor_t dc_motor_1 = {
    .dc_motor_pin[0].port = PORTC_INDEX,
    .dc_motor_pin[0].pin = GPIO_PIN3,
    .dc_motor_pin[0].logic = DC_MOTOR_OFF_STATUS,
    .dc_motor_pin[0].direction = GPIO_DIRECTION_OUTPUT,
    .dc_motor_pin[1].port = PORTC_INDEX,
    .dc_motor_pin[1].pin = GPIO_PIN4,
    .dc_motor_pin[1].logic = DC_MOTOR_OFF_STATUS,
    .dc_motor_pin[1].direction = GPIO_DIRECTION_OUTPUT
};

dc_motor_t dc_motor_2 = {
    .dc_motor_pin[0].port = PORTD_INDEX,
    .dc_motor_pin[0].pin = GPIO_PIN2,
    .dc_motor_pin[0].logic = DC_MOTOR_OFF_STATUS,
    .dc_motor_pin[0].direction = GPIO_DIRECTION_OUTPUT,
    .dc_motor_pin[1].port = PORTD_INDEX,
    .dc_motor_pin[1].pin = GPIO_PIN3,
    .dc_motor_pin[1].logic = DC_MOTOR_OFF_STATUS,
    .dc_motor_pin[1].direction = GPIO_DIRECTION_OUTPUT
};


void ecu_layer_init(void){
    Std_ReturnType ret = E_NOT_OK;
    //ret = seven_segement_intialize(&seg1);
    //ret = seven_segement_intialize(&seg2);
    //ret = led_initialize(&led_red_car);
    //ret = led_initialize(&led_green_car);
    //ret = led_initialize(&led_red_people);
    //ret = led_initialize(&led_green_people);
    //ret = led_initialize(&ready_yellow);
    ret = dc_motor_initialize(&dc_motor_1);
    //ret = dc_motor_initialize(&dc_motor_2);
    ret = lcd_4bit_intialize(&lcd_1);
    //ret = keypad_initialize(&keypad1);

}