/********************************************************************************/
/********************************************************************************/
/*****************       Aathur:Shehab Ahmed Ragaai          ********************/
/*****************       Layer:MCAL                          ********************/
/*****************       SWC:UART                            ********************/
/*****************       version:1.00                        ********************/
/********************************************************************************/
/********************************************************************************/

#ifndef UART_REGISTER_H_
#define UART_REGISTER_H_

#define UDR   *((volatile u8*)0X2C)
#define UCSRA *((volatile u8*)0X2B)
#define UCSRA_UDRE 5
#define UCSRA_RXC  7

#define UCSRB *((volatile u8*)0X2A)
#define UCSRB_UCSZ2  2
#define UCSRB_TXEN   3
#define UCSRB_RXEN   4
#define UCSRB_UDRIE  5
#define UCSRB_RXCIE  7

#define UCSRC *((volatile u8*)0X40)
#define UCSRC_UCSZ0  1
#define UCSRC_UCSZ1  2
#define UCSRC_USBS   3
#define UCSRC_UPM0   4
#define UCSRC_UPM1   5
#define UCSRC_UMSEL  6
#define UCSRC_URSEL  7


#define UBRRH *((volatile u8*)0X40)
#define UBRRL *((volatile u8*)0X29)



#endif
