/*
 * MPU6050.c
 *
 *  Created on: Jan 17, 2023
 *      Author: ryuku
 */

#include "mpu6500.h"
#include "main.h"

#define WHO_AM_I 0x75
#define PWR_MGMT_1 0x6B
#define CONFIG 0x1A
#define GYRO_CONFIG 0x1B
#define GYRO_ZOUT_H 0x47
#define GYRO_ZOUT_L 0x48
#define GYRO_FACTOR 16.4

uint8_t mon_who_am_i, mon_gyro_z;
uint16_t mon_error = 0;

SPI_HandleTypeDef hspi3;

/*
 @brief spi : read 1 byte
 @param uint8_t Register
 @return read 1byte data
*/
uint8_t read_byte( uint8_t reg )
{
  uint8_t rx_data[2];
  uint8_t tx_data[2];

  tx_data[0] = reg | 0x80;
  tx_data[1] = 0x00;  // dummy

  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, RESET);
  HAL_SPI_TransmitReceive(&hspi3, tx_data, rx_data, 2, 1);
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, SET);

  return rx_data[1];
}

/*
 @brief spi : write 1 byte
 @param uint8_t Register
 @param uint8_t Write Data
*/
void write_byte( uint8_t reg, uint8_t val )
{
  uint8_t rx_data[2];
  uint8_t tx_data[2];

  tx_data[0] = reg & 0x7F;
  tx_data[1] = val;  // write data

  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, RESET);
  HAL_SPI_TransmitReceive(&hspi3, tx_data, rx_data, 2, 1);
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, SET);
}

/*
 * @breif initialize mpu 6500
*/

void mpu6500_init( void )
{
  uint8_t who_am_i;

  HAL_Delay( 100 ); // wait start up
  who_am_i = read_byte( WHO_AM_I ); // 1. read who am i
  mon_who_am_i = who_am_i;
  //printf( "\r\n0x%x\r\n",who_am_i ); // 2. check who am i value

  // 2. error check
  if ( who_am_i != 0x70 ){
    while(1){
   //   printf( "gyro_error\r");
    mon_error = 1;
    }
  }

  HAL_Delay( 50 ); // wait

  write_byte( PWR_MGMT_1, 0x00 ); // 3. set pwr_might

  HAL_Delay( 50 );

  write_byte( CONFIG, 0x00 ); // 4. set config

  HAL_Delay( 50 );

  write_byte( GYRO_CONFIG, 0x18 ); // 5. set gyro config

  HAL_Delay( 50 );

}

/*
 * @breif read z axis
 * @return float gyro_z deg/sec
*/
float mpu6500_read_gyro_z( void )
{
  int16_t gyro_z;
  float omega;

  // H:8bit shift, Link h and l,.
  gyro_z = (int16_t)( (int16_t)(read_byte(GYRO_ZOUT_H) << 8 ) | read_byte(GYRO_ZOUT_L) );
  mon_gyro_z = gyro_z;

  omega = (float)( gyro_z / GYRO_FACTOR ); // dps to deg/sec

  return omega;
}
