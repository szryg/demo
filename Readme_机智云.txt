/*******************/
2018-08-14
�汾V0.1
/**********************/

������  /*ע��*/
 1.ƽ̨�� ��������ƽ̨���� 
2. ����Ӧ�����ɵ�Utils �� Gizwits ���ļ��� ��ӵ�����
3. ���ݲٿ��� gizwits_product.c �ڡ�
4. ʹ�û�������Ҫ ������ ���ڳ�ʼ������WIFIͨѶ�� ��ʱ����ʼ����1Msϵͳ��ʱ��
5.                      ��Ҫ��   �����жϷ���������   UART_IRQ_FUN() ;
6.                      ��Ҫ��   ��ʱ���жϷ���������  TIMER_IRQ_FUN(); 

7.���� ���� ����û�еȴ� ��������USART_SendData()  �¿⺯��û�� �� ����ʹ�� stm32��Ҫȡ��ע�� 
8. ���ʹ�ô���1 ע��usart.c�е� ���� int fputc(int ch, FILE *f)

    while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
    return ch;

 �ڶ���

int32_t uartWrite(uint8_t *buf, uint32_t len) {
for(i=0; i<len; i++)
    {
		
    while(USART_GetFlagStatus(UART5, USART_FLAG_TXE) == RESET);
  //ȷ�� ǰ�淢���ٷ�		    USART_SendData(UART5, buf[i]);//STM32 test demo
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