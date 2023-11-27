/*!
 * @file  DFRobot_URM13.cpp
 * @brief  DFRobot_URM13.cpp Initialize the I2C,
 * @n      obtain URM13 basic information, measure distance and internal temperature, select the sensor communication interface and set the sensor parameters
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license  The MIT License (MIT)
 * @author  [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2021-09-15
 */


#include "DFRobot_URM13.h"
#include "i2c.h"
#include "../debug_toolbox/Inc/uart_tools.h"




int URM13_begin(uint8_t i2cAddr)
{

    uint8_t id;
    if(0 == readReg(URM13_PID_REG_I2C, &id, sizeof(id),i2cAddr)){   // Judge whether the data bus is successful
      DBG("ERR_DATA_BUS");
      return ERR_DATA_BUS;
    }
    DBG("real sensor id="); DBG(id, HEX );
    if( 0x02 != id ){   // Judge whether the chip version matches
      DBG("ERR_IC_VERSION");
      return ERR_IC_VERSION;
    }


  HAL_Delay(200);
  DBG("begin ok!");

  return NO_ERR;
}

void refreshBasicInfo(uint8_t i2cAddr)
{
   uint8_t basicInfoI2C;
   readReg(URM13_ADDR_REG_I2C, &basicInfoI2C, 3, i2cAddr);   // I2C basic information length is 3 bytes
   udebug_formatted("%d",basicInfoI2C);
}

void setADDR(uint8_t addr,uint8_t i2cAddr)
{

    if((0x01 <= addr) && (0x7F >= addr)){
      writeReg(URM13_ADDR_REG_I2C, &addr, sizeof(addr),i2cAddr);
    }

}

uint16_t getDistanceCm(uint8_t i2cAddr)
{
  uint8_t buf[2] = {0};

  uint16_t distanceCm;


  readReg(URM13_DISTANCE_MSB_REG_I2C, &buf, 2, i2cAddr);

  distanceCm = (buf[0] << 8) | buf[1];


  return distanceCm;
}

float getInternalTempretureC(uint8_t i2cAddr)
{
  uint8_t buf[2] = {0};

  readReg(URM13_INTERNAL_TEMP_MSB_REG_I2C, buf, sizeof(buf),i2cAddr);

  return (float)(int16_t)((buf[0] << 8) | buf[1]) / 10;
}

void setExternalTempretureC(float temp, uint8_t i2cAddr)
{
  if((-10 < temp) && (70 > temp)){
    int16_t temperature = (int16_t)(temp * 10);   // written ambient temperature data, unit is ℃, resolution is 0.1℃, signed number
    uint8_t buf[2] = {0};
    buf[0] = (uint8_t)((temperature & 0xFF00) >> 8);
    buf[1] = (uint8_t)(temperature & 0x00FF);

      writeReg(URM13_EXTERNAL_TEMP_MSB_REG_I2C, buf, sizeof(buf),i2cAddr);

  }
}

void setMeasureMode(uint8_t mode, uint8_t i2cAddr) {
	// uint8_t data = 0;
	// readReg(URM13_CONFIG_REG_I2C, &data, sizeof(data));
	// DBG(data);
	writeReg(URM13_CONFIG_REG_I2C, &mode, sizeof(mode), i2cAddr);

	/*
	 if(mode & eMeasureRangeModeShort){
	 _measureRangeMode = eMeasureRangeModeShort;
	 }else{
	 _measureRangeMode = eMeasureRangeModeLong;
	 }*/
}

void passiveMeasurementTRIG(uint8_t i2cAddr)
{
    uint8_t mode = 0x01;
    writeReg(URM13_COMMAND_REG_I2C, &mode, sizeof(mode), i2cAddr);

}

uint8_t getNoiseLevel(uint8_t i2cAddr)
{
  uint8_t mode = 0;
  readReg(URM13_NOISE_REG_I2C, &mode, sizeof(mode),i2cAddr);
  return mode;
}

void setMeasureSensitivity(uint8_t mode,uint8_t i2cAddr)
{
  writeReg(URM13_SENSITIVITY_REG_I2C, &mode, sizeof(mode), i2cAddr);
}


/************ Initialization of I2C interfaces reading and writing ***********/


/*
DFRobot_URM13_I2C(uint8_t i2cAddr, TwoWire *pWire, eInterfaceMode_t interfaceURM13)
  :DFRobot_URM13(interfaceURM13)
{
  _deviceAddr = i2cAddr;
  _pWire = pWire;
}*/




size_t writeReg(uint8_t reg, const void* pBuf, size_t size, uint8_t i2cAddr)
{
  if (pBuf == NULL)
  {
    DBG("pBuf ERROR!! : null pointer");
    return 0;  // Ou une valeur d'erreur appropriée.
  }

  if (HAL_I2C_Mem_Write(&hi2c1, i2cAddr<<1, reg, 1, (uint8_t*)pBuf, size, HAL_MAX_DELAY) != HAL_OK)
  {
    return 0;
  }

  return size;
}

size_t readReg(uint8_t reg, void* pBuf, size_t size, uint8_t i2cAddr)
{
  if (pBuf == NULL)
  {
    DBG("pBuf ERROR!! : null pointer");
    return 0;  // Ou une valeur d'erreur appropriée.
  }

  // Début de la transmission
  if (HAL_I2C_Mem_Write(&hi2c1, i2cAddr << 1, reg, 1, (uint8_t*)pBuf, size, HAL_MAX_DELAY) != HAL_OK)
  {
    // Gestion de l'erreur
    // Ici, vous pouvez afficher un message d'erreur ou renvoyer une valeur d'erreur au lieu d'appeler Error_Handler().
    return 0;  // Ou une valeur d'erreur appropriée.
  }

  // Début de la réception
  if (HAL_I2C_Mem_Read(&hi2c1, i2cAddr << 1, reg, 1, (uint8_t*)pBuf, size, HAL_MAX_DELAY) != HAL_OK)
  {
    // Gestion de l'erreur
    // Ici, vous pouvez afficher un message d'erreur ou renvoyer une valeur d'erreur au lieu d'appeler Error_Handler().
    return 0;  // Ou une valeur d'erreur appropriée.
  }

  return size;  // Ou le nombre d'octets lus, selon votre application.
}
