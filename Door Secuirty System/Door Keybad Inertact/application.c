/* 
 * File:   application.c
 * Author: Abdullah Khairy
 *
 */

#include "application.h"

void mian_menu(void);
void enter_password(void);
void get_password(void);
void check_password(void);
void enter_new_password(void);
void save_password(void);

uint8 check_both_passwords(void);

void EUSART_RxDefaultInterruptHandler (void);
void Timer1_DefaultInterruptHandler(void);

usart_t usart_obj ={
    .baudrate = 9600,
    .baudrate_gen_gonfig = BAUDRATE_ASYN_8BIT_lOW_SPEED,   
    .usart_tx_cfg.usart_tx_enable = EUSART_ASYNCHRONOUS_TX_ENABLE,
    .usart_tx_cfg.usart_tx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE,
    .usart_tx_cfg.usart_tx_9bit_enable = EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE,
    .usart_rx_cfg.usart_rx_enable = EUSART_ASYNCHRONOUS_RX_ENABLE,
    .usart_rx_cfg.usart_rx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE,
    .usart_rx_cfg.usart_rx_9bit_enable = EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE,
    .EUSART_TxDefaultInterruptHandler = NULL,
    .EUSART_RxDefaultInterruptHandler = EUSART_RxDefaultInterruptHandler,
    .EUSART_FramingErrorHandler = NULL,
    .EUSART_OverrunErrorHandler = NULL
};

uint8 display = ZERO_INIT;
uint8 keypad_value = ZERO_INIT;
uint8 rec_data = ZERO_INIT;
uint32 eeprom_value1 = ZERO_INIT;
uint8 entered_password[6];
uint8 password_confrim[6];
uint8 counter =0; 
uint8 no_of_tries = 0; 
uint8 dirct_flag = 0; 
uint8 dirct_confirm_flag = 0;
uint8 passwords_matched = 0;

int main() { 
    Std_ReturnType ret  = E_NOT_OK;
    application_initialize();
    while(1){
        switch(display){
            case 0:
                mian_menu();
                break;
            case 1:
                no_of_tries =0;
                ret = lcd_4bit_clear(&lcd_1);
                ret = lcd_4bit_send_string_pos(&lcd_1, 1, 1, "*******************");
                ret = lcd_4bit_send_string_pos(&lcd_1, 2, 1, "*  Door Unlocked  *");
                ret = lcd_4bit_send_string_pos(&lcd_1, 3, 1, "*******************");
                ret = lcd_4bit_send_string_pos(&lcd_1, 4, 1, "You have 10 Seconds");
                __delay_ms(5000); 
                ret = lcd_4bit_clear(&lcd_1);
                display = 0;
            break;
            case 2:
                no_of_tries++;
                ret = lcd_4bit_clear(&lcd_1);
                ret = lcd_4bit_send_string_pos(&lcd_1, 1, 1, "XXXXXXXXXXXXXXXXXXXX");
                ret = lcd_4bit_send_string_pos(&lcd_1, 2, 1, "X Invalid Password X");
                ret = lcd_4bit_send_string_pos(&lcd_1, 3, 1, "XXXXXXXXXXXXXXXXXXXX");
                ret = lcd_4bit_send_string_pos(&lcd_1, 4, 1, ">> Try Number : ");
                ret = lcd_4bit_send_char_data_pos(&lcd_1, 4, 17 , no_of_tries + '0');
                __delay_ms(2000); 
                ret = lcd_4bit_clear(&lcd_1);
                display = 0;
            break;
            case 3:
                dirct_confirm_flag =0;
                enter_new_password();
                dirct_confirm_flag =1;
                enter_new_password();
                dirct_confirm_flag =0;
            break;
            case 4:
                save_password();
                ret = lcd_4bit_clear(&lcd_1);
                ret = lcd_4bit_send_string_pos(&lcd_1, 1, 1, "********************");
                ret = lcd_4bit_send_string_pos(&lcd_1, 2, 1, "* Password Changed *");
                ret = lcd_4bit_send_string_pos(&lcd_1, 3, 1, "*   Successfully   *");
                ret = lcd_4bit_send_string_pos(&lcd_1, 4, 1, "********************");
                __delay_ms(3500); 
                ret = lcd_4bit_clear(&lcd_1);
                display = 0;
            break;
            case 5:
                ret = lcd_4bit_clear(&lcd_1);
                ret = lcd_4bit_send_string_pos(&lcd_1, 1, 1, "XXXXXXXXXXXXXXXXXXXX");
                ret = lcd_4bit_send_string_pos(&lcd_1, 2, 1, "X Passwords Didn`t X");
                ret = lcd_4bit_send_string_pos(&lcd_1, 3, 1, "X Match Try Again  X");
                ret = lcd_4bit_send_string_pos(&lcd_1, 4, 1, "XXXXXXXXXXXXXXXXXXXX");
                __delay_ms(3500); 
                ret = lcd_4bit_clear(&lcd_1);
                display = 0;
            break;
            default: display =0;
            
        }
        
    }
    return (EXIT_SUCCESS);
}

void application_initialize(void){
    Std_ReturnType ret = E_NOT_OK;
    ecu_layer_init();
    ret = EUSART_ASYNC_Init(&usart_obj);
}

/**
 * Display Main Menu
 * then go to next Menu
 */
void mian_menu(void){
    Std_ReturnType ret  = E_NOT_OK;
    ret = lcd_4bit_send_string_pos(&lcd_1, 1, 1, "Menu :");
    ret = lcd_4bit_send_string_pos(&lcd_1, 2, 1, "******");
    ret = lcd_4bit_send_string_pos(&lcd_1, 3, 1, "1- Enter Password");
    ret = lcd_4bit_send_string_pos(&lcd_1, 4, 1, "2- Change Password");
    ret = keypad_get_value(&keypad1, &keypad_value);
    if('1' == keypad_value){
        dirct_flag = 1;
        enter_password();
    }else if('2' == keypad_value){
        dirct_flag = 2;
        enter_password();
    }else{ /* */}
}

/**
 * Display Password Entering Menu
 * to open the door
 */
void enter_password(void){
    Std_ReturnType ret  = E_NOT_OK;
    ret = lcd_4bit_clear(&lcd_1);
    ret = lcd_4bit_send_string_pos(&lcd_1, 1, 1, "Enter 6 Digits");
    if( 1 == dirct_flag){
        ret = lcd_4bit_send_string_pos(&lcd_1, 2, 1, "PIN To Enter");
    }else if( 2 == dirct_flag){
        ret = lcd_4bit_send_string_pos(&lcd_1, 2, 1, "Current ");
    }else{ /* */}
    ret = lcd_4bit_send_string_pos(&lcd_1, 3, 1, "Password : ");
    __delay_ms(500);
    keypad_value ='\0';
    while (counter < 6) {
        keypad_get_value(&keypad1, &keypad_value);
        get_password();
    }
    ret = lcd_4bit_send_string_pos(&lcd_1, 4, 1, "Press = To Continue");
    ret = keypad_get_value(&keypad1, &keypad_value);
    while('=' != keypad_value){
        ret = keypad_get_value(&keypad1, &keypad_value);
    }
    counter =0; 
    ret = lcd_4bit_clear(&lcd_1);
    check_password();
}

/**
 * Display Creating New Password Menu
 * to change the password
 */
void enter_new_password(void){
    Std_ReturnType ret  = E_NOT_OK;
    ret = lcd_4bit_clear(&lcd_1);
    
   ret = lcd_4bit_send_string_pos(&lcd_1, 1, 1, "Enter 6 Digits");
    if( 0 == dirct_confirm_flag){
        ret = lcd_4bit_send_string_pos(&lcd_1, 2, 1, "New");
    }else if( 1 == dirct_confirm_flag){
        ret = lcd_4bit_send_string_pos(&lcd_1, 2, 1, "New Again ");
    }else{ /* */}
    ret = lcd_4bit_send_string_pos(&lcd_1, 3, 1, "Password : ");
    __delay_ms(500);
    keypad_value ='\0';
    while (counter < 6) {
        keypad_get_value(&keypad1, &keypad_value);
        get_password();
    }
    ret = lcd_4bit_send_string_pos(&lcd_1, 4, 1, "Press = To Continue");
    ret = keypad_get_value(&keypad1, &keypad_value);
    while('=' != keypad_value){
        ret = keypad_get_value(&keypad1, &keypad_value);
    }
    counter =0; 
    ret = lcd_4bit_clear(&lcd_1);
    if( 0 == dirct_confirm_flag){
    }else if( 1 == dirct_confirm_flag){
        if(check_both_passwords()){
            display = 4;
        }else{
            display = 5;
        }       
    }else{ /* */}
}

/**
 * Acquire Password From the Keypad
 */
void get_password(){
    uint8 not_pressed = '\0';
    if(not_pressed != keypad_value ){
        if( 0 == dirct_confirm_flag){
            entered_password[counter] = keypad_value;
        }else if( 1 == dirct_confirm_flag){
            password_confrim[counter] = keypad_value;
        }else{ /* */}
        lcd_4bit_send_char_data_pos(&lcd_1 ,3 ,12+counter ,keypad_value);
        __delay_ms(300);
        lcd_4bit_send_char_data_pos(&lcd_1 ,3 ,12+counter ,'*');
        keypad_value = not_pressed;
        counter++;
        __delay_ms(300);
    }else{ /* Nothing */}
}

/**
 * Compare Entered Password With Saved
 * Password In EEPROM Connected to The Other MCU
 */
void check_password(void){
    if( 1 == dirct_flag){
        EUSART_ASYNC_WriteByteNonBlocking('e');
    }else if( 2 == dirct_flag){
        EUSART_ASYNC_WriteByteNonBlocking('c');
    }else{ /* */}
    for (uint8 i = 0; i < 6; i++) {
        __delay_ms(5);
        EUSART_ASYNC_WriteByteNonBlocking(entered_password[i]);
    }
}

/**
 * Send The New Password To Be Saved 
 * In EEPROM Connected to The Other MCU
 */
void save_password(void){
    EUSART_ASYNC_WriteByteNonBlocking('s');
    for (uint8 i = 0; i < 6; i++) {
        __delay_ms(5);
        EUSART_ASYNC_WriteByteNonBlocking(password_confrim[i]);
    }
}

/**
 * in EEPROM Connected to The Other MCU
 * @return true or false
 */
uint8 check_both_passwords(void){
    for (uint8 i = 0; i < 6; i++) {
        if( entered_password[i] != password_confrim[i]){
            return 0;
        }
    }
    return 1;
}

void EUSART_RxDefaultInterruptHandler (void){
    Std_ReturnType ret = E_NOT_OK;
    ret = EUSART_ASYNC_ReadByteNonBlocking(&rec_data);
    if( 'Y' == rec_data){
        display = 1;
    }else if( 'N' == rec_data){ 
        display = 2;
    }else if( 'K' == rec_data){ 
        display = 3;
    }else{ /* to be .. */}
    
}