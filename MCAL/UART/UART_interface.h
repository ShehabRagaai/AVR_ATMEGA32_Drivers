/********************************************************************************/
/********************************************************************************/
/*****************       Aathur:Shehab Ahmed Ragaai          ********************/
/*****************       Layer:MCAL                          ********************/
/*****************       SWC:UART                            ********************/
/*****************       version:1.00                        ********************/
/********************************************************************************/
/********************************************************************************/

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

void UART_voidInit(void);
u8 UART_u8SendCharSynch(u8 Copy_u8Data);
u8 UART_u8ReciveCharSynch(u8*Copy_PuRecieveData);
u8 UART_u8ReceiveCharASynch(u8*Copy_u8Data,void (*copy_PvNotifacation)(void));
u8 UART_u8SendCharASynch(u8 Copy_u8Data,void (*copy_PvNotifacation)(void));
void UART_u8SendStringSynch(u8*Copy_u8Data);
void UART_u8ReceiveStringSynch(u8 *Copy_P8ReceiveData,u8 Copy_u8Size);
u8 UART_u8SendStringASynch(u8*Copy_Pu8Data,void (*copy_PvNotifacation)(void));
u8 UART_u8ReceiveStringASynch(u8 *Copy_P8ReceiveData,u8 Copy_u8Size,void (*copy_PvNotifacation)(void));


#endif 
