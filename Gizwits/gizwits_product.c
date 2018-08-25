/**
************************************************************
* @file         gizwits_product.c
* @brief        Gizwits control protocol processing, and platform-related hardware initialization 
* @author       Gizwits
* @date         2017-07-19
* @version      V03030000
* @copyright    Gizwits
*
* @note         Gizwits is only for smart hardware
*               Gizwits Smart Cloud for Smart Products
*               Links | Value Added | Open | Neutral | Safety | Own | Free | Ecology
*               www.gizwits.com
*
***********************************************************/
#include <stdio.h>
#include <string.h>
#include "gizwits_product.h"
#include "stm32f10x_usart.h"
#include "include.h"

static uint32_t timerMsCount;

/** Current datapoint */
dataPoint_t currentDataPoint;

/**@} */
/**@name Gizwits User Interface
* @{
*/

/**
* @brief Event handling interface

* Description:

* 1. Users can customize the changes in WiFi module status

* 2. Users can add data points in the function of event processing logic, such as calling the relevant hardware peripherals operating interface

* @param [in] info: event queue
* @param [in] data: protocol data
* @param [in] len: protocol data length
* @return NULL
* @ref gizwits_protocol.h
*/
int8_t gizwitsEventProcess(eventInfo_t *info, uint8_t *gizdata, uint32_t len)
{
  uint8_t i = 0;
  dataPoint_t *dataPointPtr = (dataPoint_t *)gizdata;
  moduleStatusInfo_t *wifiData = (moduleStatusInfo_t *)gizdata;
  protocolTime_t *ptime = (protocolTime_t *)gizdata;
  
#if MODULE_TYPE
  gprsInfo_t *gprsInfoData = (gprsInfo_t *)gizdata;
#else
  moduleInfo_t *ptModuleInfo = (moduleInfo_t *)gizdata;
#endif

  if((NULL == info) || (NULL == gizdata))
  {
    return -1;
  }

  for(i=0; i<info->num; i++)
  {
    switch(info->event[i])
    {
		case EVENT_Switch_Total:  //开关机
        currentDataPoint.valueSwitch_Total = dataPointPtr->valueSwitch_Total;
        GIZWITS_LOG("Evt: EVENT_Switch_Total %d \n", currentDataPoint.valueSwitch_Total);
        if(0x01 == currentDataPoint.valueSwitch_Total)
        {
          //user handle
			TaskMan_State.power_sw = currentDataPoint.valueSwitch_Total;
        }
        else
        {
          //user handle    
			TaskMan_State.power_sw = currentDataPoint.valueSwitch_Total;
			TaskMan_TaskStop();
			EasyGUI_Message(&Activity_main_window, "关机了！");
			TaskMan_State.auto_shutdown = 0;
			TaskMan_State.auto_start = 0;
        }
        break;
      case EVENT_Switch_Node:   //开始暂停洗碗
        currentDataPoint.valueSwitch_Node = dataPointPtr->valueSwitch_Node;
        GIZWITS_LOG("Evt: EVENT_Switch_Node %d \n", currentDataPoint.valueSwitch_Node);
        if(0x01 == currentDataPoint.valueSwitch_Node)  
        {
          //user handle
			if(TaskMan_State.mode2==1 || TaskMan_State.power_sw==0)
			{
				TaskMan_State.mode1 = 0;
				break;
			}
			else
				TaskMan_State.mode1 = 1;
			switch(currentDataPoint.valueClean_Procedures)
			{
				case 0:
					TaskMan_TaskStart(Task_Auto);
					break;
				case 1:
					TaskMan_TaskStart(Task_NormX2);
					break;
				case 2:
					TaskMan_TaskStart(Task_Norm);
					break;
				case 3:
					TaskMan_TaskStart(Task_Fruit);
					break;
				case 4:
					TaskMan_TaskStart(Task_Cavity);
					break;
				default:
					break;
				
			}
        }
        else
        {
          //user handle    
			TaskMan_TaskStop();
			EasyGUI_WindowShow(&Activity_main_window);
        }
        break;
      case EVENT_Switch_Custody:   //开始暂停保管
        currentDataPoint.valueSwitch_Custody = dataPointPtr->valueSwitch_Custody;
        GIZWITS_LOG("Evt: EVENT_Switch_Custody %d \n", currentDataPoint.valueSwitch_Custody);
        if(0x01 == currentDataPoint.valueSwitch_Custody)
        {
          //user handle
			if(TaskMan_State.mode1==1 || TaskMan_State.power_sw==0)
			{
				TaskMan_State.mode2 = 0;
				break;
			}
			else
				TaskMan_State.mode2 = 1;
			switch(currentDataPoint.valueCustody)
			{
				case 0:
					TaskMan_TaskStart(Task_Wind);
					break;
				case 1:
					TaskMan_TaskStart(Task_Light);
					break;
				case 2:
					TaskMan_TaskStart(Task_Light);
					break;				
				default:
                    break;
			}
        }
        else
        {
          //user handle    
			TaskMan_TaskStop();
			EasyGUI_WindowShow(&Activity_main_window);
        }
        break;

      case EVENT_Clean_Procedures:  //清洗程序
        currentDataPoint.valueClean_Procedures = dataPointPtr->valueClean_Procedures;
        GIZWITS_LOG("Evt: EVENT_Clean_Procedures %d\n", currentDataPoint.valueClean_Procedures);
	    
		switch(currentDataPoint.valueClean_Procedures)
		{
		  case Clean_Procedures_VALUE0:
			//user handle
			
			break;
		  case Clean_Procedures_VALUE1:
			//user handle
			
			break;
		  case Clean_Procedures_VALUE2:
			//user handle
			
			break;
		  case Clean_Procedures_VALUE3:
			//user handle
			
			break;
		  case Clean_Procedures_VALUE4:
			//user handle
			
			break;
		  default:
			break;
		}
		
        break;
      case EVENT_Custody:     //保管模式
        currentDataPoint.valueCustody = dataPointPtr->valueCustody;
        GIZWITS_LOG("Evt: EVENT_Custody %d\n", currentDataPoint.valueCustody);
        switch(currentDataPoint.valueCustody)
        {
          case Custody_VALUE0:
            //user handle
		    
            break;
          case Custody_VALUE1:
            //user handle
		    
            break;
          case Custody_VALUE2:
            //user handle
		    	
            break;
          default:
            break;
        }
        break;

	  case EVENT_Timing_Order_On:  //定时开机
        currentDataPoint.valueTiming_Order_On = dataPointPtr->valueTiming_Order_On;
        GIZWITS_LOG("Evt:EVENT_Timing_Order_On %d\n",currentDataPoint.valueTiming_Order_On);
        //user handle
		TaskMan_State.auto_start = currentDataPoint.valueTiming_Order_On * 60;
        break;
      case EVENT_Timing_Off:     //定时关机
        currentDataPoint.valueTiming_Off = dataPointPtr->valueTiming_Off;
        GIZWITS_LOG("Evt:EVENT_Timing_Off %d\n",currentDataPoint.valueTiming_Off);
        //user handle
		TaskMan_State.auto_shutdown = currentDataPoint.valueTiming_Off * 60;
        break;


      case WIFI_SOFTAP:
        break;
      case WIFI_AIRLINK:
        break;
      case WIFI_STATION:
        break;
      case WIFI_CON_ROUTER:
 
        break;
      case WIFI_DISCON_ROUTER:
 
        break;
      case WIFI_CON_M2M:
 
        break;
      case WIFI_DISCON_M2M:
        break;
      case WIFI_RSSI:
        GIZWITS_LOG("RSSI %d\n", wifiData->rssi);
        break;
      case TRANSPARENT_DATA:
        GIZWITS_LOG("TRANSPARENT_DATA \n");
        //user handle , Fetch data from [data] , size is [len]
        break;
      case WIFI_NTP:
        GIZWITS_LOG("WIFI_NTP : [%d-%d-%d %02d:%02d:%02d][%d] \n",ptime->year,ptime->month,ptime->day,ptime->hour,ptime->minute,ptime->second,ptime->ntp);
        break;
      case MODULE_INFO:
            GIZWITS_LOG("MODULE INFO ...\n");
      #if MODULE_TYPE
            GIZWITS_LOG("GPRS MODULE ...\n");
            //Format By gprsInfo_t
      #else
            GIZWITS_LOG("WIF MODULE ...\n");
            //Format By moduleInfo_t
            GIZWITS_LOG("moduleType : [%d] \n",ptModuleInfo->moduleType);
      #endif
    break;
      default:
        break;
    }
  }

  return 0;
}

/**
* User data acquisition

* Here users need to achieve in addition to data points other than the collection of data collection, can be self-defined acquisition frequency and design data filtering algorithm

* @param none
* @return none
*/
void userHandle(void)
{
 /*

    */
    
}

/**
* Data point initialization function

* In the function to complete the initial user-related data
* @param none
* @return none
* @note The developer can add a data point state initialization value within this function
*/
void userInit(void)
{
    memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));
    
    /** Warning !!! DataPoint Variables Init , Must Within The Data Range **/ 
    /*
      currentDataPoint.valueSwitch_Total = ;
      currentDataPoint.valueSwitch_Node = ;
      currentDataPoint.valueSwitch_Custody = ;
      currentDataPoint.valueClean_Procedures = ;
      currentDataPoint.valueCustody = ;
      currentDataPoint.valueTiming_Order_On = ;
      currentDataPoint.valueTiming_Off = ;
    */

}


/**
* @brief  gizTimerMs

* millisecond timer maintenance function ,Millisecond increment , Overflow to zero

* @param none
* @return none
*/
void gizTimerMs(void)
{
    timerMsCount++;
}

/**
* @brief gizGetTimerCount

* Read system time, millisecond timer

* @param none
* @return System time millisecond
*/
uint32_t gizGetTimerCount(void)
{
    return timerMsCount;
}

/**
* @brief mcuRestart

* MCU Reset function

* @param none
* @return none
*/
void mcuRestart(void)
{

}
/**@} */

/**
* @brief TIMER_IRQ_FUN

* Timer Interrupt handler function

* @param none
* @return none
*/
void TIMER_IRQ_FUN(void)
{
  gizTimerMs();
}

/**
* @brief UART_IRQ_FUN

* UART Serial interrupt function ，For Module communication

* Used to receive serial port protocol data between WiFi module

* @param none
* @return none
*/
void UART_IRQ_FUN(void)
{
  uint8_t value = 0;
  value = USART_ReceiveData(UART5);//STM32 test demo
  gizPutData(&value, 1);
}


/**
* @brief uartWrite

* Serial write operation, send data to the WiFi module

* @param buf      : Data address
* @param len       : Data length
*
* @return : Not 0,Serial send success;
*           -1，Input Param Illegal
*/
int32_t uartWrite(uint8_t *buf, uint32_t len)
{
    uint32_t i = 0;
    
    if(NULL == buf)
    {
        return -1;
    }
    
    #ifdef PROTOCOL_DEBUG
    GIZWITS_LOG("MCU2WiFi[%4d:%4d]: ", gizGetTimerCount(), len);
    for(i=0; i<len; i++)
    {
        GIZWITS_LOG("%02x ", buf[i]);
    }
    GIZWITS_LOG("\n");
    #endif

    for(i=0; i<len; i++)
    {
		while(USART_GetFlagStatus(UART5, USART_FLAG_TXE) == RESET);  //确认 前面发完再发
		USART_SendData(UART5, buf[i]);//STM32 test demo
        //Serial port to achieve the function, the buf[i] sent to the module
        if(i >=2 && buf[i] == 0xFF)
        {
          //Serial port to achieve the function, the 0x55 sent to the module
          USART_SendData(UART5, 0x55);//STM32 test demo
        }
    }


    
    return len;
}


