/********************************************************************************/
/********************************************************************************/
/*****************       Aathur:Shehab Ahmed Ragaai          ********************/
/*****************       Layer:MCAL                          ********************/
/*****************       SWC:SPI                             ********************/
/*****************       version:1.00                        ********************/
/********************************************************************************/
/********************************************************************************/

#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"SPI_register.h"
#include"SPI_interface.h"
#include"SPI_config.h"
#include"SPI_private.h"

void SPI_voidMasterInit(void)
{
	/*Master Init*/
	SET_BIT(SPCR,SPCR_MSTR);

	/*SET Clock Init*/
	SET_BIT(SPCR,SPCR_SPR0);
	CLEAR_BIT(SPCR,SPCR_SPR1);
	CLEAR_BIT(SPCR,SPCR_SPI2X);

	/*SPI Enable*/
	SET_BIT(SPCR,SPCR_SPE);
}
void SPI_voidSlaveInit(void)
{
	/*Slave Init*/
	CLEAR_BIT(SPCR,SPCR_MSTR);


	/*SPI Enable*/
	SET_BIT(SPCR,SPCR_SPE);
}
u8 SPI_u8Transeive(u8 Copy_u8Data)
{
	/*Send Data*/
	SPDR=Copy_u8Data;
	/*Waiting for receive from slave and tansmit data from Master*/
	 while(GET_BIT(SPSR,SPSR_SPIF)==0);
	 /*Read Updated Data*/
	 return SPDR;
}


