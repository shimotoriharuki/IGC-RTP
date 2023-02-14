/*
 * Flash_F405.c
 *
 *  Created on: 2023/02/09
 *      Author: ryuku
 */

#include "Flash_F405.h"

//FLASH_SR_SNBはビット6:3　セクタ数を3ビットシフトした値
#define FLASH_SECTOR6		0x30	//0x0110000
#define FLASH_SECTOR7		0x38	//0x0111000
#define FLASH_SECTOR8		0x40	//0x1000000
#define FLASH_SECTOR9		0x48	//0x1001000
#define FLASH_SECTOR10		0x50	//0x1010000
#define FLASH_SECTOR11		0x58	//0x1011000

// flash use address
const uint32_t start_adress_sector6  = 	0x8040000; //sentor6 start address
const uint32_t end_adress_sector6 	 = 	0x805FFFF;
const uint32_t start_adress_sector7  = 	0x8060000; //sentor7 start address
const uint32_t end_adress_sector7 	 = 	0x807FFFF;
const uint32_t start_adress_sector8  = 	0x8080000; //sentor8 start address
const uint32_t end_adress_sector8 	 = 	0x809FFFF;
const uint32_t start_adress_sector9  = 	0x80A0000; //sentor9 start address
const uint32_t end_adress_sector9 	 = 	0x80BFFFF;
const uint32_t start_adress_sector10 =  0x80C0000; //sentor10 start address
const uint32_t end_adress_sector10 	 = 	0x80DFFFF;
const uint32_t start_adress_sector11 =  0x80E0000; //sentor11 start address
//const uint32_t middle_adress_sector11 = 0x80E3CAF; //sentor11 midle address
const uint32_t end_adress_sector11 	 = 	0x80FFFFF;

inline static void FLASH_Unlock(void)
{
	FLASH->KEYR =  0x45670123;
	FLASH->KEYR =  0xCDEF89AB;
}

inline static void FLASH_Lock(void)
{
	FLASH->CR |= FLASH_CR_LOCK;

}

void FLASH_WaitBusy(void)
{
	while(FLASH->SR & FLASH_SR_BSY);//BSYがクリアされるまで待機
}

void FLASH_Erease7(void)
{
	FLASH_Unlock();

	FLASH_WaitBusy();

	FLASH->CR |= FLASH_CR_SER;//SER Bitset
	FLASH->CR |= FLASH_SECTOR7 & FLASH_CR_SNB_Msk;//セクタ選択
	FLASH->CR |= FLASH_CR_STRT;//STRT Bitset

	FLASH_WaitBusy();

	FLASH_Lock();
}

void FLASH_Erease9(void)
{
	FLASH_Unlock();

	FLASH_WaitBusy();

	FLASH->CR |= FLASH_CR_SER;//SER Bitset
	FLASH->CR |= FLASH_SECTOR9 & FLASH_CR_SNB_Msk;//セクタ選択
	FLASH->CR |= FLASH_CR_STRT;//STRT Bitset

	FLASH_WaitBusy();

	FLASH_Lock();
}

void FLASH_Erease10(void)
{
	FLASH_Unlock();

	FLASH_WaitBusy();

	FLASH->CR |= FLASH_CR_SER;//SER Bitset
	FLASH->CR |= FLASH_SECTOR10 & FLASH_CR_SNB_Msk;//セクタ選択
	FLASH->CR |= FLASH_CR_STRT;//STRT Bitset

	FLASH_WaitBusy();

	FLASH_Lock();
}

void FLASH_Erease11(void)
{
	FLASH_Unlock();

	FLASH_WaitBusy();

	FLASH->CR |= FLASH_CR_SER;//SER Bitset
	FLASH->CR |= FLASH_SECTOR11 & FLASH_CR_SNB_Msk;//セクタ選択
	FLASH->CR |= FLASH_CR_STRT;//STRT Bitset

	FLASH_WaitBusy();

	FLASH_Lock();
}

void FLASH_EreaseSector( uint16_t sector ){	//FLASH_SECTOR11
	HAL_FLASH_Unlock();

	FLASH_EraseInitTypeDef EraseInit;
	EraseInit.TypeErase = FLASH_TYPEERASE_SECTORS;
	EraseInit.Sector = sector;
	EraseInit.NbSectors = 1;
	EraseInit.VoltageRange = FLASH_VOLTAGE_RANGE_3;	//!< Device operating range: 2.7V to 3.6V

	uint32_t PageError = 0;
	HAL_FLASHEx_Erase(&EraseInit, &PageError);
	HAL_FLASH_Lock();
}

void FLASH_Write_HalfWord(uint32_t address, uint16_t data)
{
	FLASH_Unlock();

	FLASH_WaitBusy();

	FLASH->CR |= FLASH_PSIZE_HALF_WORD;
	FLASH->CR |= FLASH_CR_PG;

	*(__IO uint16_t*)address = data;

	FLASH_WaitBusy();

	FLASH->CR &= ~FLASH_CR_PG;

	FLASH_Lock();
}

void FLASH_Write_Word(uint32_t address, uint32_t data)
{
	FLASH_Unlock();

	FLASH_WaitBusy();

	FLASH->CR |= FLASH_PSIZE_WORD;
	FLASH->CR |= FLASH_CR_PG;

	*(__IO uint32_t*)address = data;

	FLASH_WaitBusy();

	FLASH->CR &= ~FLASH_CR_PG;

	FLASH_Lock();
}

void FLASH_Write_Word_S(uint32_t address, int32_t data)
{
	FLASH_Unlock();

	FLASH_WaitBusy();

	FLASH->CR |= FLASH_PSIZE_WORD;
	FLASH->CR |= FLASH_CR_PG;

	*(__IO int32_t*)address = data;

	FLASH_WaitBusy();

	FLASH->CR &= ~FLASH_CR_PG;

	FLASH_Lock();
}

void FLASH_Write_Word_F(uint32_t address, float data)
{
	FLASH_Unlock();

	FLASH_WaitBusy();

	FLASH->CR |= FLASH_PSIZE_WORD;
	FLASH->CR |= FLASH_CR_PG;

	*(__IO float*)address = data;

	FLASH_WaitBusy();

	FLASH->CR &= ~FLASH_CR_PG;

	FLASH_Lock();
}

//4byteごとのアクセスっぽい
void FLASH_Write_DoubleWord(uint32_t address, int64_t data)
{
	FLASH_Unlock();

	FLASH_WaitBusy();

	FLASH->CR |= FLASH_PSIZE_DOUBLE_WORD;
	FLASH->CR |= FLASH_CR_PG;

	//*(__IO int64_t*)address = data;

	*(__IO int32_t*)address = (int32_t)data;
	*(__IO int32_t*)(address + 0x04) = (int32_t)(data >> 32);

	FLASH_WaitBusy();

	FLASH->CR &= ~FLASH_CR_PG;

	FLASH_Lock();
}

/*void FLASH_Write_Byte(uint32_t address, uint8_t data)
{
	FLASH->CR &= ~(FLASH_CR_PSIZE);
	FLASH->CR |= FLASH_TYPEPROGRAM_BYTE;
	FLASH->CR |= FLASH_CR_PG;
	*(__IO uint8_t*)address = data;
	FLASH_WaitBusy();
	FLASH->CR &= ~(FLASH_CR_PG);
}
void FLASH_WriteData(uint32_t address, uint8_t* data, uint32_t size)
{
	FLASH_Unlock();
	FLASH_Erease();
	do {
		FLASH_WriteByte(address, *data);
	}while(++address, ++data, --size);
	FLASH_Lock();
}*/

void FLASH_ReadData(uint32_t address, uint32_t* data, uint32_t size)
{
  memcpy(data, (uint32_t*)address, size);
  //memcpy(コピー先のメモリブロック、コピー元のメモリブロック、コピーバイト数)
}
