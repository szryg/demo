/*******************/
2018-08-14
版本V0.1
/**********************/

机智云  /*注意*/
 1.平台是 生成其他平台代码 
2. 将对应的生成的Utils 与 Gizwits 的文件夹 添加到工程
3. 数据操控在 gizwits_product.c 内。
4. 使用机智云需要 工程有 串口初始化（与WIFI通讯） 定时器初始化（1Ms系统定时）
5.                      需要在   串口中断服务函数调用   UART_IRQ_FUN() ;
6.                      需要在   定时器中断服务函数调用  TIMER_IRQ_FUN(); 

7.问题 串口 发送没有等待 函数名（USART_SendData()  新库函数没有 ） 由于使用 stm32需要取消注释 
8. 如果使用串口1 注释usart.c中的 函数 int fputc(int ch, FILE *f)

    while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
    return ch;

 内东西

int32_t uartWrite(uint8_t *buf, uint32_t len) {
for(i=0; i<len; i++)
    {
		
    while(USART_GetFlagStatus(UART5, USART_FLAG_TXE) == RESET);
  //确认 前面发完再发		    USART_SendData(UART5, buf[i]);//STM32 test demo
        //Serial port to achieve the function, the buf[i] sent to the module
      
      if(i >=2 && buf[i] == 0xFF)

       {
          //Serial port to achieve the function, the 0x55 sent to the module
 
         USART_SendData(UART5, 0x55);//STM32 test demo
 
       }

    }

}

/********************************/
void UART_IRQ_FUN(void)
{

  uint8_t value = 0;

  value = USART_ReceiveData(UART5);//STM32 test demo

  gizPutData(&value, 1);

}