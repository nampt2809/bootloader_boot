//--thanhcm3--12--06--23--

#include "header_files.h"


static uint8_t flash_chip_select_spi1(uint8_t state);
static uint8_t flash_write_byte(SPI_Type *base,uint8_t byte);
static uint8_t flash_read_byte(SPI_Type *base);
static uint8_t flash_write_enable(SPI_Type *base);
static uint8_t flash_wait_for_write_end(SPI_Type *base);

///1.
uint8_t init_flash(SPI_Type *base){
  uint8_t err = NO_ERR; 
  USER_SPI1_WP_OFF;
  USER_SPI1_HOLD_ON;
  spi_master_config_t userConfig;
  /* Init SPI master */
  /*
  * masterConfig->enableStopInWaitMode = false;
  * masterConfig->polarity = kSPI_ClockPolarityActiveHigh;
  * masterConfig->phase = kSPI_ClockPhaseFirstEdge;
  * masterConfig->direction = kSPI_MsbFirst;
  * masterConfig->dataMode = kSPI_8BitMode;
  * masterConfig->txWatermark = kSPI_TxFifoOneHalfEmpty;
  * masterConfig->rxWatermark = kSPI_RxFifoOneHalfFull;
  * masterConfig->pinMode = kSPI_PinModeNormal;
  * masterConfig->outputMode = kSPI_SlaveSelectAutomaticOutput;
  * masterConfig->baudRate_Bps = 500000U;
  */
  userConfig.polarity = kSPI_ClockPolarityActiveLow;
  SPI_MasterGetDefaultConfig(&userConfig);
  
  SPI_MasterInit(base, &userConfig, USER_SPI1_MASTER_CLK_FREQ);
  
  return err; 
}

///2.===========================================================================
static uint8_t flash_chip_select_spi1(uint8_t state){
  uint8_t err = NO_ERR;
  
  if(state == LOW)
  {
    USER_FLASH_SPI1_CS_LOW;
  }
  else if(state == HIGH)
  {
    USER_FLASH_SPI1_CS_HIGH;
  }else 
  {
    err = ERR;
  }
  
  return err;
  
}

///3. ==========================================================================

static uint8_t flash_write_byte(SPI_Type *base,uint8_t byte){
  uint8_t retVal      =   0;
  spi_transfer_t xfer = {0};
  xfer.txData   = &byte;
  xfer.rxData   = &retVal;
  xfer.dataSize = 1; 
  SPI_MasterTransferBlocking(base, &xfer);
  return retVal;
}

///4. ==========================================================================
static uint8_t flash_read_byte(SPI_Type *base)
{
  return (flash_write_byte(base,sFLASH_DUMMY_BYTE));
}
///5. ==========================================================================

static uint8_t flash_write_enable(SPI_Type *base)
{
  uint8_t err = NO_ERR;
  
  /*!< Select the FLASH: Chip Select low */
  flash_chip_select_spi1(LOW);

  /*!< Send "Write Enable" instruction */
  flash_write_byte(base,sFLASH_CMD_WREN);

  /*!< Deselect the FLASH: Chip Select high */
  flash_chip_select_spi1(HIGH);
  
  return err;
}

///6.==========================================================================
static uint8_t flash_wait_for_write_end(SPI_Type *base)
{
  uint8_t err = NO_ERR;
  uint8_t flashstatus = 0;

  /*!< Select the FLASH: Chip Select low */
  flash_chip_select_spi1(LOW);

  /*!< Send "Read Status Register" instruction */
  flash_write_byte(base,sFLASH_CMD_RDSR);

  /*!< Loop as long as the memory is busy with a write cycle */
  do
  {
    /*!< Send a dummy byte to generate the clock needed by the FLASH
    and put the value of the status register in FLASH_Status variable */
    flashstatus = flash_write_byte(base,sFLASH_DUMMY_BYTE);

  }
  while ((flashstatus & sFLASH_WIP_FLAG) == SET); /* Write in progress */

  /*!< Deselect the FLASH: Chip Select high */
  flash_chip_select_spi1(HIGH);
  
  return err;
}

///7.==========================================================================
uint8_t  flash_erase_sector(SPI_Type *base, uint32_t SectorAddr)
{
  uint8_t err = NO_ERR;
  /*!< Send write enable instruction */
  flash_write_enable(base);

  /*!< Sector Erase */
  /*!< Select the FLASH: Chip Select low */
  flash_chip_select_spi1(LOW);
  /*!< Send Sector Erase instruction */
  flash_write_byte(base,sFLASH_CMD_SE);
  /*!< Send SectorAddr high nibble address byte */
  flash_write_byte(base,(SectorAddr & 0xFF0000) >> 16);
  /*!< Send SectorAddr medium nibble address byte */
  flash_write_byte(base,(SectorAddr & 0xFF00) >> 8);
  /*!< Send SectorAddr low nibble address byte */
  flash_write_byte(base,SectorAddr & 0xFF);
  /*!< Deselect the FLASH: Chip Select high */
  flash_chip_select_spi1(HIGH);

  /*!< Wait the end of Flash writing */
  flash_wait_for_write_end(base);
  
  return err;
}

///8.===========================================================================
uint8_t flash_erase_bulk(SPI_Type *base,uint32_t BlockAddr)
{
  uint8_t err = NO_ERR;
  /*!< Send write enable instruction */
  flash_write_enable(base);

  /*!< Sector Erase */
  /*!< Select the FLASH: Chip Select low */
  flash_chip_select_spi1(LOW);
  /*!< Send Sector Erase instruction */
  flash_write_byte(base,sFLASH_CMD_BE);
  /*!< Send SectorAddr high nibble address byte */
  flash_write_byte(base,(BlockAddr & 0xFF0000) >> 16);
  /*!< Send SectorAddr medium nibble address byte */
  flash_write_byte(base,(BlockAddr & 0xFF00) >> 8);
  /*!< Send SectorAddr low nibble address byte */
  flash_write_byte(base,BlockAddr & 0xFF);
  /*!< Deselect the FLASH: Chip Select high */
  flash_chip_select_spi1(HIGH);

  /*!< Wait the end of Flash writing */
  flash_wait_for_write_end(base);
  
  return err;
}

///9.===========================================================================
uint8_t flash_erase_chip(SPI_Type *base)
{
  uint8_t err = NO_ERR;
  /*!< Send write enable instruction */
  flash_write_enable(base);

  /*!< Bulk Erase */
  /*!< Select the FLASH: Chip Select low */
  flash_chip_select_spi1(LOW);
  /*!< Send Bulk Erase instruction  */
  flash_write_byte(base,sFLASH_CMD_CE);
  /*!< Deselect the FLASH: Chip Select high */
  flash_chip_select_spi1(HIGH);

  /*!< Wait the end of Flash writing */
  flash_wait_for_write_end(base);
  return err;
}

///10. =========================================================================

uint8_t flash_write_page(SPI_Type *base,uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
  uint8_t err = NO_ERR;
  
  /*!< Enable the write access to the FLASH */
  flash_write_enable(base);

  /*!< Select the FLASH: Chip Select low */
  flash_chip_select_spi1(LOW);
  /*!< Send "Write to Memory " instruction */
  flash_write_byte(base,sFLASH_CMD_WRITE);
  /*!< Send WriteAddr high nibble address byte to write to */
  flash_write_byte(base,(WriteAddr & 0xFF0000) >> 16);
  /*!< Send WriteAddr medium nibble address byte to write to */
  flash_write_byte(base,(WriteAddr & 0xFF00) >> 8);
  /*!< Send WriteAddr low nibble address byte to write to */
  flash_write_byte(base,WriteAddr & 0xFF);

  /*!< while there is data to be written on the FLASH */
  spi_transfer_t xfer = {0};
  xfer.txData   = pBuffer;
  xfer.rxData   = NULL;
  xfer.dataSize = NumByteToWrite;
  //xfer.configFlags = EXAMPLE_LPSPI_MASTER_PCS_FOR_TRANSFER | kLPSPI_MasterPcsContinuous | kLPSPI_MasterByteSwap;
  SPI_MasterTransferBlocking(base, &xfer);        
        
  /*!< Deselect the FLASH: Chip Select high */
  flash_chip_select_spi1(HIGH);

  /*!< Wait the end of Flash writing */
  flash_wait_for_write_end(base);
  
  return err;
}
///11.==========================================================================
uint8_t flash_write_buffer(SPI_Type *base,uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
  uint8_t err = NO_ERR;
  uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;
  
  Addr = WriteAddr % sFLASH_SPI_PAGESIZE;
  count = sFLASH_SPI_PAGESIZE - Addr;
  NumOfPage =  NumByteToWrite / sFLASH_SPI_PAGESIZE;
  NumOfSingle = NumByteToWrite % sFLASH_SPI_PAGESIZE;
  
  if (Addr == 0) /*!< WriteAddr is sFLASH_PAGESIZE aligned  */
  {
    if (NumOfPage == 0) /*!< NumByteToWrite < sFLASH_PAGESIZE */
    {
      flash_write_page(base,pBuffer, WriteAddr, NumByteToWrite);
    }
    else /*!< NumByteToWrite > sFLASH_PAGESIZE */
    {
      while (NumOfPage--)
      {
        flash_write_page(base,pBuffer, WriteAddr, sFLASH_SPI_PAGESIZE);
        WriteAddr +=  sFLASH_SPI_PAGESIZE; 
        pBuffer += sFLASH_SPI_PAGESIZE;
      }
      
      flash_write_page(base,pBuffer, WriteAddr, NumOfSingle);
    }
  }
  else /*!< WriteAddr is not sFLASH_PAGESIZE aligned  */
  {
    if (NumOfPage == 0) /*!< NumByteToWrite < sFLASH_PAGESIZE */
    {
      if (NumOfSingle > count) /*!< (NumByteToWrite + WriteAddr) > sFLASH_PAGESIZE */
      {
        temp = NumOfSingle - count;
        
        flash_write_page(base,pBuffer, WriteAddr, count);
        WriteAddr +=  count;
        pBuffer += count;
        
        flash_write_page(base, pBuffer, WriteAddr, temp);
      }
      else
      {
        flash_write_page(base, pBuffer, WriteAddr, NumByteToWrite);
      }
    }
    else /*!< NumByteToWrite > sFLASH_PAGESIZE */
    {
      NumByteToWrite -= count;
      NumOfPage =  NumByteToWrite / sFLASH_SPI_PAGESIZE;
      NumOfSingle = NumByteToWrite % sFLASH_SPI_PAGESIZE;
      
      flash_write_page(base,pBuffer, WriteAddr, count);
      WriteAddr +=  count;
      pBuffer += count;
      
      while (NumOfPage--)
      {
        flash_write_page(base, pBuffer, WriteAddr, sFLASH_SPI_PAGESIZE);
        WriteAddr +=  sFLASH_SPI_PAGESIZE;
        pBuffer += sFLASH_SPI_PAGESIZE;
      }
      
      if (NumOfSingle != 0)
      {
        flash_write_page(base, pBuffer, WriteAddr, NumOfSingle);
      }
    }
  }
  return err; 
}
///12.==========================================================================
uint8_t flash_read_buffer(SPI_Type *base,uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
  uint8_t err = NO_ERR;
  /*!< Select the FLASH: Chip Select low */
  flash_chip_select_spi1(LOW);

  /*!< Send "Read from Memory " instruction */
  flash_write_byte(base, sFLASH_CMD_READ);

  /*!< Send ReadAddr high nibble address byte to read from */
  flash_write_byte( base, (ReadAddr & 0xFF0000) >> 16);
  /*!< Send ReadAddr medium nibble address byte to read from */
  flash_write_byte(base, (ReadAddr& 0xFF00) >> 8);
  /*!< Send ReadAddr low nibble address byte to read from */
  flash_write_byte(base, ReadAddr & 0xFF);

//  while (NumByteToRead--) /*!< while there is data to be read */
//  {
//    /*!< Read a byte from the FLASH */
//    *pBuffer = sFLASH_WriteByte(sFLASH_DUMMY_BYTE);
//    /*!< Point to the next location where the byte read will be saved */
//    pBuffer++;
//  }
  //
  spi_transfer_t xfer = {0};
  xfer.txData   = NULL;
  xfer.rxData   = pBuffer;
  xfer.dataSize = NumByteToRead;
  SPI_MasterTransferBlocking(base, &xfer);

  /*!< Deselect the FLASH: Chip Select high */
  flash_chip_select_spi1(HIGH);
  return err; 
}

///13.==========================================================================

//void sFLASH_ReadID(flashInfoTypedef * pFlashInfo)
//{
//  /*!< Select the FLASH: Chip Select low */
//  sFLASH_ChipSelect(LOW);
//
//  /*!< Send "RDID " instruction */
//  sFLASH_WriteByte(sFLASH_CMD_RDID);
//
//  /*!< Read a byte from the FLASH */
//  pFlashInfo->ManufacturerID = sFLASH_WriteByte(sFLASH_DUMMY_BYTE);
//
//  /*!< Read a byte from the FLASH */
//  pFlashInfo->DeviceID[0] = sFLASH_WriteByte(sFLASH_DUMMY_BYTE);
//
//  /*!< Read a byte from the FLASH */
//  pFlashInfo->DeviceID[1] = sFLASH_WriteByte(sFLASH_DUMMY_BYTE);
//
//  /*!< Deselect the FLASH: Chip Select high sFLASH_CS_HIGH*/
//  sFLASH_ChipSelect(HIGH);  
//}

///14.==========================================================================
uint8_t flash_start_read_sequence(SPI_Type *base,uint32_t ReadAddr)
{
  uint8_t err = NO_ERR;
  /*!< Select the FLASH: Chip Select low */
  flash_chip_select_spi1(LOW);

  /*!< Send "Read from Memory " instruction */
  flash_write_byte(base,sFLASH_CMD_READ);

  /*!< Send the 24-bit address of the address to read from -------------------*/
  /*!< Send ReadAddr high nibble address byte */
  flash_write_byte(base,(ReadAddr & 0xFF0000) >> 16);
  /*!< Send ReadAddr medium nibble address byte */
  flash_write_byte(base,(ReadAddr& 0xFF00) >> 8);
  /*!< Send ReadAddr low nibble address byte */
  flash_write_byte(base,ReadAddr & 0xFF);
  return err; 
}


///15.==========================================================================










































