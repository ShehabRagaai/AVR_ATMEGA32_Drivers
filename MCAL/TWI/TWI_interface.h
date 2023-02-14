/********************************************************************************/
/********************************************************************************/
/*****************       Aathur:Shehab Ahmed Ragaai          ********************/
/*****************       Layer:MCAL                          ********************/
/*****************       SWC:TWI                             ********************/
/*****************       version:1.00                        ********************/
/********************************************************************************/
/********************************************************************************/

#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_
typedef enum
{
   NoError,
   StartError,
   RepeatStartError,
   SlaveAddrssWriteError,
   SlaveAddrssReadError,
   SendDatatError,
   ReceiveDatatError
}ERROR_STATE;
void TWI_voidMASTERInit(void);
void TWI_voidSlaveRInit(u8 Copy_u8SlaveAddress);
ERROR_STATE TWI_SendStartCondition(void);
ERROR_STATE TWI_ResendStartCondition(void);
ERROR_STATE TWI_MasterSendSlaveAdressWithWrite(u8 Copy_u8SlaveAddress);
ERROR_STATE TWI_MasterSendSlaveAdressWithRead(u8 Copy_u8SlaveAddress);

ERROR_STATE TWI_MasterSendData(u8 Copy_u8Data);
ERROR_STATE TWI_MasterReceiveData(u8*Copy_u8ReciveData);
void TWI_voidSendStopCondition(void);
#endif
