#include<LPC21XX.H>
#include"ctypes.h"


#define I2EN				( 1 << 6 )
#define I2SCL				( 0x1 << 4 )
#define I2SDA				( 0x1 << 6 )
#define RD					( 1 )
#define WR					( 0 )
#define I2STA				( 1 << 5 )
#define I2STO				( 1 << 4 )
#define I2SIC				( 1 << 3 )
#define I2AA				( 1 << 2 )

#define SI					( ((I2CONSET>>3)&1) )

void i2c_init( uint32_t BitRate );
uint8_t i2c_Byte_Read( uint8_t sa, uint8_t mem );
void i2c_Byte_Write( uint8_t sa, uint8_t mem, uint8_t data );
