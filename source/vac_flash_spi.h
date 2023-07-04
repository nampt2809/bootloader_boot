//--thanhcm3--12--06--23--

#ifndef _VAC_FLASH_SPI_H
#define _VAC_FLASH_SPI_H
//include-----------------------------------------------------------------------
//define------------------------------------------------------------------------
#define HIGH                                            1U
#define LOW                                             0U
#define SET    			                        1U

#define sFLASH_CMD_WREN           0x06  /* Write enable instruction */
#define sFLASH_CMD_RDSR           0x05  /* Read Status Register instruction  */
#define sFLASH_CMD_WRSR           0x01  /* Write Status Register instruction */
#define sFLASH_CMD_READ           0x03  /* Read from Memory instruction *///////////////////////////////

#define sFLASH_CMD_WRITE          0x02  /* Write to Memory instruction */
#define sFLASH_CMD_SE             0x20  /* Sector Erase instruction */
#define sFLASH_CMD_BE             0xD8  /* Bulk Erase instruction 0x52*/
#define sFLASH_CMD_CE             0xc7  /* Chip Erase instruction 0xC7/0x60 */
#define sFLASH_CMD_PP             0x02  /* Page Program instruction */
#define sFLASH_CMD_RDID           0x9F  /* Read identification */

#define sFLASH_WIP_FLAG           0x01  /* Write In Progress (WIP) flag */

#define sFLASH_DUMMY_BYTE         0xA5
#define sFLASH_SPI_PAGESIZE       0x100
//function----------------------------------------------------------------------
uint8_t  init_flash(SPI_Type *base);
uint8_t  flash_erase_sector(SPI_Type *base, uint32_t SectorAddr);
uint8_t  flash_erase_bulk(SPI_Type *base,uint32_t BlockAddr);
uint8_t  flash_erase_chip(SPI_Type *base);
uint8_t  flash_write_page(SPI_Type *base,uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
uint8_t  flash_write_buffer(SPI_Type *base,uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
uint8_t  flash_read_buffer(SPI_Type *base,uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
uint8_t  flash_start_read_sequence(SPI_Type *base,uint32_t ReadAddr);

//code here


#endif /* _VAC_FLASH_SPI_H */