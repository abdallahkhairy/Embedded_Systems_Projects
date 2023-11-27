/*
 * File:   application.c
 * Author: Abdullah Khairy
 *
 */

#include "application.h"

uint16  lm35_res1;
uint16  lm35_res1_Celsius;
uint8   lm35_res1_str[6];

void ADC_DefaultinterruptHandler(void);

adc_conf_t adc_a0 = {
    .ADC_InterruptHandler = ADC_DefaultinterruptHandler,
    .acquisition_time = ADC_12_TAD,
    .adc_channel = ADC_CHANNEL_AN0,
    .conversion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    .result_format = ADC_RESULT_RIGHT,
    .voltage_reference = ADC_VOLTAGE_REFERENCE_DISABLED
};

ccp_t ccp1_obj = {
    .ccp_inst = CCP1_INST,
    .CCP1_InterruptHandler = NULL,
    .ccp_mode = CCP_PWM_MODE_SELECTED,
    .PWM_Frequency = 20000,
    .ccp_pin.port = PORTC_INDEX,
    .ccp_pin.pin = GPIO_PIN2,
    .ccp_pin.direction = GPIO_DIRECTION_OUTPUT,
    .timer2_prescaler_value = CCP_TIMER2_PRESCALER_DIV_BY_1,
    .timer2_postscaler_value = CCP_TIMER2_POSTSCALER_DIV_BY_1,
};

timer2_t timer2_obj = {
    .TMR2_InterruptHandler = NULL,
    .timer2_prescaler_value = TIMER2_PRESCALER_DIV_BY_1,
    .timer2_postscaler_value = TIMER2_POSTSCALER_DIV_BY_1,
    .timer2_preload_value = 0
};


int main() {
  Std_ReturnType ret = E_NOT_OK;
  application_initialize();
  ret = lcd_4bit_send_string_pos(&lcd_1, 1, 1, "--------------------");
  ret = lcd_4bit_send_string_pos(&lcd_1, 2, 2, "TEMPERATURE :");
  ret = lcd_4bit_send_string_pos(&lcd_1, 3, 1, "--------------------");

  
  
  ret = CCP_PWM_Set_Duty(&ccp1_obj, 0);
  ret = CCP_PWM_Start(&ccp1_obj);

  while(1){ 
      ret = ADC_StartConversion_Interrupt(&adc_a0, ADC_CHANNEL_AN0);
        
      lm35_res1_Celsius = round((lm35_res1*4.88f)/10);
      ret = convert_uint16_to_string(lm35_res1_Celsius, lm35_res1_str);
      lm35_res1_str[3]='C';
      ret = lcd_4bit_send_string_pos(&lcd_1, 2, 16, lm35_res1_str);
      
      if((lm35_res1_Celsius >= 20) && (lm35_res1_Celsius < 30)){     
        ret = CCP_PWM_Set_Duty(&ccp1_obj, 25);
        ret = dc_motor_move_right(&dc_motor_1);
      }
      else if((lm35_res1_Celsius >= 30) && (lm35_res1_Celsius < 35)){
        ret = CCP_PWM_Set_Duty(&ccp1_obj, 50);
        ret = dc_motor_move_right(&dc_motor_1);
      }
      else if((lm35_res1_Celsius >= 35) && (lm35_res1_Celsius < 40)){
        ret = CCP_PWM_Set_Duty(&ccp1_obj, 75);
        ret = dc_motor_move_right(&dc_motor_1);
      }
      else if(lm35_res1_Celsius >= 40){
        ret = CCP_PWM_Set_Duty(&ccp1_obj, 100);
        ret = dc_motor_move_right(&dc_motor_1);
      }
      else{
          ret = CCP_PWM_Set_Duty(&ccp1_obj, 0);
          ret = dc_motor_stop(&dc_motor_1);
      }
      
      
  }
  return (EXIT_SUCCESS);

}

void application_initialize(void){
    Std_ReturnType ret = E_NOT_OK;
    ecu_layer_init();
    ret = ADC_Init(&adc_a0);
    ret = CCP_Init(&ccp1_obj);
    ret = Timer2_Init(&timer2_obj);
    TIMER2_InterruptDisable();   
}

void ADC_DefaultinterruptHandler(void){
    Std_ReturnType ret = E_NOT_OK;
    adc_a0.adc_channel = ADC_CHANNEL_AN0;
    ret = ADC_GetConversionResult(&adc_a0, &lm35_res1);
}