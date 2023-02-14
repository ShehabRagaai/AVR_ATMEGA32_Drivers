/********************************************************************************/
/********************************************************************************/
/*****************       Aathur:Shehab Ahmed Ragaai          ********************/
/*****************       Layer:MCAL                          ********************/
/*****************       SWC:TWI                             ********************/
/*****************       version:1.00                        ********************/
/********************************************************************************/
/********************************************************************************/

#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"TWI_interface.h"
#include"TWI_config.h"
#include"TWI_private.h"
#include"TWI_register.h"
void TWI_voidMASTERInit(void)
{

	/*Set Clock Frequancy=400kbit/s*/
	TWBR=2;
	CLEAR_BIT(TWSR,TWSR_TWPS0);
	CLEAR_BIT(TWSR,TWSR_TWPS1);
	/*Enable ACK*/
	SET_BIT(TWCR,TWCR_TWEA);

	/*Enable TWI*/
	SET_BIT(TWCR,TWCR_TWEN);



}
void TWI_voidSlaveInit(u8 Copy_u8SlaveAddress)
{
	/*Set Slave Address*/
	TWAR=Copy_u8SlaveAddress<<1;
	/*Enable TWI*/
	SET_BIT(TWCR,TWCR_TWEN);
}
ERROR_STATE TWI_SendStartCondition(void)
{
	ERROR_STATE Local_ErrorState=NoError;
	/*Set Start condition Bit*/
	SET_BIT(TWCR,TWCR_TWSTA);
	/*Clear Interrupt Flag */
	SET_BIT(TWCR,TWCR_TWINT);
	/*Wait For Rising Flag Again*/
	while(GET_BIT(TWCR,TWCR_TWINT)==0);

	if((TWSR&0b11111000)!=START_ACK_STATUE)
	{
		Local_ErrorState=StartError;
	}


	return Local_ErrorState;
}
ERROR_STATE TWI_ResendStartCondition(void)
{
	ERROR_STATE Local_ErrorState=NoError;
	/*Set Start condition Bit*/
	SET_BIT(TWCR,TWCR_TWSTA);
	/*Clear Interrupt Flag */
	SET_BIT(TWCR,TWCR_TWINT);
	/*Wait For Rising Flag Again*/
	while(GET_BIT(TWCR,TWCR_TWINT)==0);

	if((TWSR&0b11111000)!=Repeat_START_ACK_STATUE)
	{
		Local_ErrorState=RepeatStartError;
	}


	return Local_ErrorState;
}
ERROR_STATE TWI_MasterSendSlaveAdressWithWrite(u8 Copy_u8SlaveAddress)
{
	ERROR_STATE Local_ErrorState=NoError;
	/*Clear Start Condition BIT*/
	CLEAR_BIT(TWCR,TWCR_TWSTA);
	/*Load Slave Address*/
	TWDR=Copy_u8SlaveAddress<<1;
	/*Clear the Least significant bit*/
	CLEAR_BIT(TWDR,0);

	/*Clear Interrupt Flag */
	SET_BIT(TWCR,TWCR_TWINT);
	/*Wait For Rising Flag Again*/
	while(GET_BIT(TWCR,TWCR_TWINT)==0);

	/*Check Statues*/
	if((TWSR&0b11111000)!=MASTER_SLA_W_ACK_STATUE)
	{
		Local_ErrorState=SlaveAddrssWriteError;
	}


	return Local_ErrorState;


}
ERROR_STATE TWI_MasterSendSlaveAdressWithRead(u8 Copy_u8SlaveAddress)
{
	ERROR_STATE Local_ErrorState=NoError;
	/*Clear Start Condition BIT*/
	CLEAR_BIT(TWCR,TWCR_TWSTA);
	/*Load Slave Address*/
	TWDR=Copy_u8SlaveAddress<<1;
	/*Set the Least significant bit*/
	SET_BIT(TWDR,0);

	/*Clear Interrupt Flag */
	SET_BIT(TWCR,TWCR_TWINT);
	/*Wait For Rising Flag Again*/
	while(GET_BIT(TWCR,TWCR_TWINT)==0);

	/*Check Statues*/
	if((TWSR&0b11111000)!=MASTER_SLA_R_ACK_STATUE)
	{
		Local_ErrorState=SlaveAddrssReadError;
	}


	return Local_ErrorState;

}

ERROR_STATE TWI_MasterSendData(u8 Copy_u8Data)
{
	ERROR_STATE Local_ErrorState=NoError;
	/*Send Data*/
	TWDR=Copy_u8Data;
	/*Clear Interrupt Flag */
	SET_BIT(TWCR,TWCR_TWINT);

	/*Wait For Rising Flag Again*/
	while(GET_BIT(TWCR,TWCR_TWINT)==0);


	if((TWSR&0b11111000)!=MASTER_SEND_DATA_ACK_STATUE)
	{
		Local_ErrorState=SendDatatError;
	}


	return Local_ErrorState;


}
ERROR_STATE TWI_MasterReceiveData(u8*Copy_u8ReciveData)
{
	ERROR_STATE Local_ErrorState=NoError;
	/*Clear Interrupt Flag */
	SET_BIT(TWCR,TWCR_TWINT);
	/*Wait For Rising Flag Again*/
	while(GET_BIT(TWCR,TWCR_TWINT)==0);

	if((TWSR&0b11111000)!=Receive_DATA_ACK_STATUE)
	{
		Local_ErrorState=ReceiveDatatError;
	}
	else
	{
		/*Read Data*/
		*Copy_u8ReciveData=TWDR;

	}

	return Local_ErrorState;

}
void TWI_voidSendStopCondition(void)
{
	/*Set Start condition Bit*/
	SET_BIT(TWCR,TWCR_TWSTO);
	/*Clear Interrupt Flag */
	SET_BIT(TWCR,TWCR_TWINT);

}
