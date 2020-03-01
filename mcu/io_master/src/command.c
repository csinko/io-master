#include "core.h"
#include "command.h"
#include "mcu_conf.h"
#include "stm32h7xx_hal.h"
#include "uart.h"
#include <string.h>
#include <stdlib.h>

uint8_t current_command[5] = {0};
IOM_COMMAND_STATUS command_status = IOM_CS_NEW;

void ProcessCommand(IOM_Output_Buffer buffer) {
    //New command, should be 1 byte
    if(command_status == IOM_CS_NEW) {
        if (buffer.length != 1) {
            //Garbage
            free(buffer.data);
            uint8_t* pData = malloc(1);
            UARTQueueRXData(pData, 1);
            return;
        }
        current_command[0] = *(buffer.data);
        free(buffer.data);
        uint8_t commTag = (current_command[0] & 0b01110000) >> 4;
        uint8_t bytesToGet = 1;
        if (commTag > 0 && commTag < 5) {
            command_status = IOM_CS_INCOMPLETE;
            bytesToGet = 4;
        } else if (commTag == 0) {
            command_status = IOM_CS_INCOMPLETE;
            bytesToGet = 2;
        }
        uint8_t* pData = malloc(bytesToGet);
        UARTQueueRXData(pData, bytesToGet);
        return;
    }
    if (command_status == IOM_CS_INCOMPLETE) {
       if (buffer.length > 4) {
           //Garbage
           free(buffer.data);
           uint8_t* pData = malloc(1);
           UARTQueueRXData(pData, 1);
           return;
       } 
       memcpy(&current_command[1], buffer.data, buffer.length);
       free(buffer.data);
       command_status = IOM_CS_NEW;
       RunCommand(&current_command[0]);
       uint8_t* pData = malloc(1);
       UARTQueueRXData(pData, 1);
       return;
    }
}

void RunCommand(uint8_t* comm)
{
    uint8_t readWrite = (*(comm) & 0b10000000) >> 7;
    uint8_t commTag = (*(comm) & 0b01110000) >> 4;

    if(readWrite != 0)
    {
        //Set cases
        switch(commTag)
        {
            case 0:
                SetTargetDeviceVolt(comm);
                break;
            case pin1Params:
            case pin2Params:
            case pin3Params:
            case pin4Params:
                SetPinParams(commTag, comm);
                break;
            case dataSpeed:
                SetDataSpeed(comm);
                break;
            case signalMode:
                SetSignalMode(comm);
                break;
            default:
                //error case
                break;
        }        
    }
    else
    {
        //Get cases
        switch(commTag)
        {
            case targetDeviceVolt:
                GetTargetDeviceVolt(comm);
                break;
            case pin1Params:
            case pin2Params:
            case pin3Params:
            case pin4Params:
                GetPinParams(commTag, comm);
                break;
            case dataSpeed:
                GetDataSpeed(comm);
                break;
            case signalMode:
                GetSignalMode(comm);
                break;
            default:
                //error case
                break;
        }        
    }
    
    return;
}

void SetPinParams(uint8_t pinNum, uint8_t* comm)
{
    uint8_t pullDown = comm[0] & 0b0001;
    uint8_t pullUp = (comm[0] & 0b0010) >> 1;
    //If pullDown and pullUp are enabled, then board is in tristate mode
    uint8_t triState = pullDown & pullUp;
    uint16_t VH = (comm[1]<<8) | comm[2];
    uint16_t VL = (comm[3]<<8) | comm[4];

    GPIO_TypeDef* pullDownPort = 0;
    uint16_t pullDownPin = 0;
    GPIO_TypeDef* pullUpPort = 0;
    uint16_t pullUpPin = 0;

    GPIO_TypeDef* triStatePort = 0;
    uint16_t triStatePin = 0;

    switch(pinNum) {
        case 1:
            pullDownPort = IO_1_PD_N_GPIO_Port;
            pullDownPin = IO_1_PD_N_Pin;
            pullUpPort = IO_1_PU_GPIO_Port;
            pullUpPin = IO_1_PU_Pin;
            triStatePort = IO_1_TRIS_N_GPIO_Port;
            triStatePin = IO_1_TRIS_N_Pin;
            break;
        case 2:
            pullDownPort = IO_2_PD_N_GPIO_Port;
            pullDownPin = IO_2_PD_N_Pin;
            pullUpPort = IO_2_PU_GPIO_Port;
            pullUpPin = IO_2_PU_Pin;
            triStatePort = IO_2_TRIS_N_GPIO_Port;
            triStatePin = IO_2_TRIS_N_Pin;
            break;
        case 3:
            pullDownPort = IO_3_PD_N_GPIO_Port;
            pullDownPin = IO_3_PD_N_Pin;
            pullUpPort = IO_3_PU_GPIO_Port;
            pullUpPin = IO_3_PU_Pin;
            triStatePort = IO_3_TRIS_N_GPIO_Port;
            triStatePin = IO_3_TRIS_N_Pin;
            break;
        case 4:
            pullDownPort = IO_4_PD_N_GPIO_Port;
            pullDownPin = IO_4_PD_N_Pin;
            pullUpPort = IO_4_PU_GPIO_Port;
            pullUpPin = IO_4_PU_Pin;
            triStatePort = IO_4_TRIS_N_GPIO_Port;
            triStatePin = IO_4_TRIS_N_Pin;
            break;
        default:
            break;
    }

    if (triState != 0) {
        //Dsiable the Pulldown and Pullup Pins
        HAL_GPIO_WritePin(pullDownPort, pullDownPin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(pullUpPort, pullUpPin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(triStatePort, triStatePin, GPIO_PIN_RESET);

    } else if (pullDown != 0) {
        HAL_GPIO_WritePin(triStatePort, triStatePin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(pullUpPort, pullUpPin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(pullDownPort, pullDownPin, GPIO_PIN_RESET);

    } else if (pullUp != 0) {
        HAL_GPIO_WritePin(triStatePort, triStatePin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(pullDownPort, pullDownPin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(pullUpPort, pullUpPin, GPIO_PIN_SET);
    }
    //writeExtDac(true, pinNum, VH);
    //writeExtDac(false, pinNum, VL);

}

void SetTargetDeviceVolt(uint8_t* comm)
{
    //uint16_t Volt = (comm[1]<<8) | comm[2];
    HAL_Delay(1000);

    //writeMcuDac(1, Volt);
    return;
}

void SetSignalMode(uint8_t* comm)
{
    //bool mode = comm[0] & 0b0001;

    //HAL_GPIO_WritePin(IO_1_2_DIFF_GPIO_Port, IO_1_2_DIFF_Pin, mode);// might need to cast mode as GPIO_PinState
    //HAL_GPIO_WritePin(IO_3_4_DIFF_GPIO_Port, IO_3_4_DIFF_Pin, mode);
    ////HAL_GPIO_WritePin(IO_5_6_DIFF_GPIO_Port, IO_5_6_DIFF_Pin, mode);
    ////HAL_GPIO_WritePin(IO_7_8_DIFF_GPIO_Port, IO_7_8_DIFF_Pin, mode);

    //HAL_GPIO_WritePin(IO_1_2_TERM_N_GPIO_Port, IO_1_2_TERM_N_Pin, !mode);// might need to cast mode as GPIO_PinState
    //HAL_GPIO_WritePin(IO_3_4_TERM_N_GPIO_Port, IO_3_4_TERM_N_Pin, !mode);
    ////HAL_GPIO_WritePin(IO_5_6_TERM_N_GPIO_Port, IO_5_6_TERM_N_Pin, !mode);
    ////HAL_GPIO_WritePin(IO_7_8_TERM_N_GPIO_Port, IO_7_8_TERM_N_Pin, mode);

    return;
}

void SetDataSpeed(uint8_t* comm)
{
    //uint speed;//TODO: Update when Set Data Speed Commmand established

    //return;
}

void GetPinParams(uint8_t pinNum, uint8_t* comm)
{
    //uint8_t resStates;
    //switch(pinNum)
    //{
    //    case 1:
    //        resStates = (HAL_GPIO_ReadPin(IO_1_PU_GPIO_Port, IO_1_PU_Pin)<<1) & HAL_GPIO_ReadPin(IO_1_PD_GPIO_N_Port, IO_1_PD_N_Pin);
    //        break;
    //    case 2:
    //        resStates = (HAL_GPIO_ReadPin(IO_2_PU_GPIO_Port, IO_2_PU_Pin)<<1) & HAL_GPIO_ReadPin(IO_2_PD_GPIO_N_Port, IO_2_PD_N_Pin);
    //        break;
    //    case 3:
    //        resStates = (HAL_GPIO_ReadPin(IO_3_PU_GPIO_Port, IO_3_PU_Pin)<<1) & HAL_GPIO_ReadPin(IO_3_PD_GPIO_N_Port, IO_3_PD_N_Pin);
    //        break;
    //    case 4:
    //        resStates = (HAL_GPIO_ReadPin(IO_4_PU_GPIO_Port, IO_4_PU_Pin)<<1) & HAL_GPIO_ReadPin(IO_4_PD_GPIO_N_Port, IO_4_PD_N_Pin);
    //        break;
    //    default:
    //        //error
    //}
    //comm[0] = comm[0] & resState;
    ////get VH
    //comm[1] = readExtDac(true, true, pinNum);
    //comm[2] = readExtDac(true, false, pinNum);
    ////get VL
    //comm[3] = readExtDac(false, true, pinNum);
    //comm[4] = readExtDac(false, false, pinNum);
    //return;
}

void GetTargetDeviceVolt(uint8_t* comm)
{
    //device volt is on Dac channel 1
    // last 12 bits are the channel 1 output
    //uint16_t Volt = HAL_DAC_GetValue(&hdac1, DAC1_CHANNEL_1); // & 0x00000FFF
    //return;
}

void GetSignalMode(uint8_t* comm)
{
    //comm[0] = comm[0] & HAL_GPIO_ReadPin(IO_1_2_DIFF_GPIO_Port, IO_1_2_DIFF_Pin);
    //return;
}

void GetDataSpeed(uint8_t* comm)
{
    //uint8_t speed;//TODO: Update when Get Data Speed Commmand established
    //return;
}

