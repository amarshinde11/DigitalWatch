/***************************************************************************************************************************
* @file: config_vic.c
* @brief: This is VIC Driver file contains, Vectored Interrupt Controller Config function definitions
*					
* @uthor: amar.shinde
* @created: 29/04/2023.
****************************************************************************************************************************/
#include"config_vic.h"

void config_vic( uint32_t intr_no, void(*IntrHandler)(void)__irq, uint32_t slot_no )
{
		VICIntSelect &=  ~(1 << intr_no);
		switch( slot_no )
		{
				case SLOT0:	 	VICVectCntl0 = (intr_no | (1 << 5));
											VICVectAddr0 = (uint32_t)IntrHandler;
					break;
				case SLOT1:		VICVectCntl1 = (intr_no | (1 << 5));
											VICVectAddr1 = (uint32_t)IntrHandler;
					break;
				case SLOT2:   VICVectCntl2 = (intr_no | (1 << 5));
											VICVectAddr2 = (uint32_t)IntrHandler;
					break;
				case SLOT3:		VICVectCntl3 = (intr_no | (1 << 5));
											VICVectAddr3 = (uint32_t)IntrHandler;
					break;
				case SLOT4:		VICVectCntl4 = (intr_no | (1 << 5));
											VICVectAddr4 = (uint32_t)IntrHandler;
					break;
				case SLOT5:		VICVectCntl5 = (intr_no | (1 << 5));
											VICVectAddr5 = (uint32_t)IntrHandler;
					break;
				case SLOT6:		VICVectCntl6 = (intr_no | (1 << 5));
											VICVectAddr6 = (uint32_t)IntrHandler;
					break;
				case SLOT7:		VICVectCntl7 = (intr_no | (1 << 5));
											VICVectAddr7 = (uint32_t)IntrHandler;
					break;
				case SLOT8:		VICVectCntl8 = (intr_no | (1 << 5));
											VICVectAddr8 = (uint32_t)IntrHandler;
					break;
				case SLOT9:		VICVectCntl9 = (intr_no | (1 << 5));
											VICVectAddr9 = (uint32_t)IntrHandler;
					break;
				case SLOT10:	VICVectCntl10 = (intr_no | (1 << 5));
											VICVectAddr10 = (uint32_t)IntrHandler;
					break;
				case SLOT11:	VICVectCntl11 = (intr_no | (1 << 5));
											VICVectAddr11 = (uint32_t)IntrHandler;	
					break;
				case SLOT12:	VICVectCntl12 = (intr_no | (1 << 5));
											VICVectAddr12 = (uint32_t)IntrHandler;
					break;
				case SLOT13:	VICVectCntl13 = (intr_no | (1 << 5));
											VICVectAddr13 = (uint32_t)IntrHandler;
					break;
				case SLOT14:	VICVectCntl14 = (intr_no | (1 << 5));
											VICVectAddr14 = (uint32_t)IntrHandler;
					break;
				case SLOT15:	VICVectCntl15 = (intr_no | (1 << 5));
											VICVectAddr15 = (uint32_t)IntrHandler;
					break;
		}
}

void Irq_Intr_Enable( uint32_t intr_no )
{
		VICIntEnable = (1 << intr_no); 
}

void Irq_Intr_Disable( uint32_t intr_no )
{
		VICIntEnClr = (1 << intr_no);
}

