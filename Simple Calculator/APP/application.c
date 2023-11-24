/* 
 * File:   application.c
 * Author: Abdullah Khairy
 *
 */

#include "application.h"

void loading_screen(void);
void lcd_write(void);
void calculate(void);



uint8 keypad_value = ZERO_INIT;
uint32 num1 = ZERO_INIT;
uint8 operator = ZERO_INIT;
uint32 num2 = ZERO_INIT;
uint8 num2_flag = ZERO_INIT;
uint32 result = ZERO_INIT;
uint8 result_txt[11];
int main() { 
    Std_ReturnType ret  = E_NOT_OK;
    application_initialize();
    lcd_4bit_send_string_pos(&lcd_1, 2, 6, "WELCOME");
    __delay_ms(2000);
    ret = lcd_4bit_clear(&lcd_1);
    loading_screen();
    ret = lcd_4bit_clear(&lcd_1);
 
    while(1){
        ret = keypad_get_value(&keypad1, &keypad_value);
        if(isdigit(keypad_value) && !num2_flag){
            num1 = (num1*10)+(keypad_value-'0');
            lcd_write();
        }
        else if(('+' == keypad_value) || ('-' == keypad_value) || ('*' == keypad_value) || ('/' == keypad_value)){
           operator = keypad_value;
           num2_flag =1;
           lcd_write();
        }
        else if(isdigit(keypad_value) && num2_flag){
               num2 = (num2*10)+(keypad_value-'0');
               lcd_write();
        }
        else if('=' == keypad_value){
           lcd_write();
           calculate();
        }
        else if('#' == keypad_value){
           ret = lcd_4bit_clear(&lcd_1);
           num2_flag = num1 = num2 = 0;
           
         }else{ /* Nothing */}
         
         
    }
    return (EXIT_SUCCESS);
}

void application_initialize(void){
    Std_ReturnType ret = E_NOT_OK;
    ecu_layer_init();
}

void loading_screen(void){
    lcd_4bit_send_string_pos(&lcd_1, 1, 1, "Loading");
    uint8 counter = ZERO_INIT;
    uint8 l_lcd1_counter = ZERO_INIT;
    for(counter=8; counter<=15*2; ++counter){
        l_lcd1_counter++;
        lcd_4bit_send_char_data_pos(&lcd_1, 1, 8+l_lcd1_counter, '.');
        __delay_ms(100);
        if(7 == l_lcd1_counter ){
            lcd_4bit_send_string_pos(&lcd_1, 1, 8, "         ");
            l_lcd1_counter =0;
        }else{ /* Nothing */ }
    }
    lcd_4bit_send_string_pos(&lcd_1, 1, 8, "         ");
}

void lcd_write(void){
    Std_ReturnType ret  = E_NOT_OK;
    uint8 not_pressed = '\0';
    if(not_pressed != keypad_value){
        ret = lcd_4bit_send_char_data(&lcd_1, keypad_value);
        keypad_value = not_pressed;
        __delay_ms(500);
    }else{ /* Nothing */}
}

void calculate(void){
    Std_ReturnType ret  = E_NOT_OK;
    switch(operator){
        case '+' : result = num1 + num2; break;
        case '-' : result = num1 - num2; break; 
        case '*' : result = num1 * num2; break; 
        case '/' :
            if(0 == num2){
                ret = lcd_4bit_send_string_pos(&lcd_1, 4, 1, "CAN`T DIVIDE BY ZERO");
                return ;
            }else{
            result = num1 / num2;
            }
            break; 
        default : ;
    }
    ret = convert_uint32_to_string(result, result_txt);
    ret = lcd_4bit_send_string_pos(&lcd_1, 4, 15, result_txt);
}