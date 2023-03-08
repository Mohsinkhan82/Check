
#include <stdio.h>
#include "stm8l10x.h"
#include "stm8l10x_spi.h"

static void CLK_Config(void);
void Delay (uint16_t nCount);
  
void SPI_write(unsigned char byte1, unsigned char byte2, unsigned char byte3);

int main(){
  
  CLK_Config();
   
  GPIO_Init(GPIOB, GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Fast);
  GPIO_Init(GPIOB, GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Fast);
  GPIO_Init(GPIOB, GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Fast);
  
  GPIO_Init(GPIOC, GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Fast);
  SPI_DeInit();
  SPI_Init( SPI_FirstBit_MSB, SPI_BaudRatePrescaler_128, SPI_Mode_Master,SPI_CPOL_Low, 
           SPI_CPHA_1Edge,SPI_Direction_1Line_Tx, SPI_NSS_Soft);
  
  SPI_Cmd(ENABLE);
  GPIO_SetBits(GPIOB,GPIO_Pin_4);

    
while(1)
{
    SPI_write(0x30, 0x00, 0xC9); // R-11912   34B1A
    Delay(100);
    
    SPI_write(0x0F, 0xD9, 0xC4); //CONTROL-  FC938  FD964 
    Delay(4500);
    
    SPI_write(0x03, 0x4B, 0x1A); //N-200C9   3000C9
    Delay(10000);
    
  //   //4FC92C
}  
  return 0;
}
  
void SPI_write(unsigned char byte1, unsigned char byte2, unsigned char byte3)
{
    while(SPI_GetFlagStatus(SPI_FLAG_BSY));
  
    GPIO_ResetBits(GPIOB,GPIO_Pin_4); 
    SPI_SendData(byte1);
    while(SPI_GetFlagStatus(SPI_FLAG_BSY));
    while(!SPI_GetFlagStatus(SPI_FLAG_TXE));  
    SPI_SendData(byte2);
    while(SPI_GetFlagStatus(SPI_FLAG_BSY)); 
    while(!SPI_GetFlagStatus(SPI_FLAG_TXE));
    SPI_SendData(byte3);
    while(SPI_GetFlagStatus(SPI_FLAG_BSY)); 
    while(!SPI_GetFlagStatus(SPI_FLAG_TXE));
    //Delay(200);
    GPIO_SetBits(GPIOB,GPIO_Pin_4);
    //Delay(200);
    
    
}
  
static void CLK_Config(void)
{
  /*Enable clock SPI */
  
 // CLK_DeInit();              
 // CLK_HSICmd(); 
  CLK_CCOConfig( CLK_Output_ClockMasterDiv2);
  CLK_CCOCmd( ENABLE);
 
  CLK_PeripheralClockConfig(CLK_Peripheral_SPI, ENABLE);
  
  /*Enable clock USART */
 // CLK_PeripheralClockConfig(CLK_Peripheral_USART, ENABLE); 
}

void Delay(uint16_t nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {
    nCount--;
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}
#endif

