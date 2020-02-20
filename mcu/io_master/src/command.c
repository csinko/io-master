#include "configureIOMaster.c"

enum commandTag
 {
    targetDeviceVolt = 0,
    pin1Params,         
    pin2Params,         
    pin3Params,        
    pin4Params,
    dataSpeed,
    signalMode,    
};

void runCommand(uint8_t* comm)
{
    bool readWrite;
    uint8_t commTag = (comm[1] & 0b01110000)>>4;

    if(readWrite)
    {
        //Set cases
        switch(commTag)
        {
            case targetDeviceVolt:
                setTargetDeviceVolt(comm);
                break;
            case pin1Params:
            case pin2Params:
            case pin3Params:
            case pin4Params:
                setPinParams(commTag, comm);
                break;
            case dataSpeed:
                setDataSpeed(comm);
                break;
            case signalMode:
                setSignalMode(comm);
                break;
            default:
                //error case
        }        
    }
    else
    {
        //Get cases
        switch(commTag)
        {
            case targetDeviceVolt:
                getTargetDeviceVolt(comm);
                break;
            case pin1Params:
            case pin2Params:
            case pin3Params:
            case pin4Params:
                getPinParams(commTag, comm);
                break;
            case dataSpeed:
                getDataSpeed(comm);
                break;
            case signalMode:
                getSignalMode(comm);
                break;
            default:
                //error case
        }        
    }
    
    return;
}

void setPinParams(uint8_t pinNum, uint8_t* comm)
{
    bool pullDown = comm[0] & 0b0001;
    bool pullUp = comm[0] & 0b0010;
    uint16_t VH = (comm[1]<<8) | comm[2];
    uint16_t VL = (comm[3]<<8) | comm[4];
    switch(pinNum)
    {
        case 1:
            HAL_GPIO_WritePin(IO_1_PD_GPIO_N_Port, IO_1_PD_N_Pin, pullDown);
            HAL_GPIO_WritePin(IO_1_PU_GPIO_Port, IO_1_PU_Pin, pullUp);
            break;
        case 2:
            HAL_GPIO_WritePin(IO_2_PD_N_GPIO_Port, IO_2_PD_N_Pin, pullDown);
            HAL_GPIO_WritePin(IO_2_PU_GPIO_Port, IO_2_PU_Pin, pullUp);
            break;
        case 3
            HAL_GPIO_WritePin(IO_3_PD_N_GPIO_Port, IO_3_PD_N_Pin, pullDown);
            HAL_GPIO_WritePin(IO_3_PU_GPIO_Port, IO_3_PU_Pin, pullUp);
            break;
        case 4:
            HAL_GPIO_WritePin(IO_4_PD_GPIO_N_Port, IO_4_PD_N_Pin, pullDown);
            HAL_GPIO_WritePin(IO_4_PU_GPIO_Port, IO_4_PU_Pin, pullUp);
            break;
        default:
            //error
    }
    writeExtDac(true, pinNum, VH);
    writeExtDac(false, pinNum, VL);

    return;
}

void setTargetDeviceVolt(uint8_t* comm)
{
    uint16_t Volt = (comm[1]<<8) | comm[2];

    writeMcuDac(1, Volt);
    return;
}

void setSignalMode(uint8_t* comm)
{
    bool mode = comm[0] & 0b0001;

    HAL_GPIO_WritePin(IO_1_2_DIFF_GPIO_Port, IO_1_2_DIFF_Pin, mode);// might need to cast mode as GPIO_PinState
    HAL_GPIO_WritePin(IO_3_4_DIFF_GPIO_Port, IO_3_4_DIFF_Pin, mode);
    //HAL_GPIO_WritePin(IO_5_6_DIFF_GPIO_Port, IO_5_6_DIFF_Pin, mode);
    //HAL_GPIO_WritePin(IO_7_8_DIFF_GPIO_Port, IO_7_8_DIFF_Pin, mode);

    HAL_GPIO_WritePin(IO_1_2_TERM_N_GPIO_Port, IO_1_2_TERM_N_Pin, !mode);// might need to cast mode as GPIO_PinState
    HAL_GPIO_WritePin(IO_3_4_TERM_N_GPIO_Port, IO_3_4_TERM_N_Pin, !mode);
    //HAL_GPIO_WritePin(IO_5_6_TERM_N_GPIO_Port, IO_5_6_TERM_N_Pin, !mode);
    //HAL_GPIO_WritePin(IO_7_8_TERM_N_GPIO_Port, IO_7_8_TERM_N_Pin, mode);

    return;
}

void setDataSpeed(uint8_t* comm)
{
    uint speed;//TODO: Update when Set Data Speed Commmand established

    return;
}

void getPinParams(uint8_t pinNum, uint8_t* comm)
{
    uint8_t resStates;
    switch(pinNum)
    {
        case 1:
            resStates = (HAL_GPIO_ReadPin(IO_1_PU_GPIO_Port, IO_1_PU_Pin)<<1) & HAL_GPIO_ReadPin(IO_1_PD_GPIO_N_Port, IO_1_PD_N_Pin);
            break;
        case 2:
            resStates = (HAL_GPIO_ReadPin(IO_2_PU_GPIO_Port, IO_2_PU_Pin)<<1) & HAL_GPIO_ReadPin(IO_2_PD_GPIO_N_Port, IO_2_PD_N_Pin);
            break;
        case 3:
            resStates = (HAL_GPIO_ReadPin(IO_3_PU_GPIO_Port, IO_3_PU_Pin)<<1) & HAL_GPIO_ReadPin(IO_3_PD_GPIO_N_Port, IO_3_PD_N_Pin);
            break;
        case 4:
            resStates = (HAL_GPIO_ReadPin(IO_4_PU_GPIO_Port, IO_4_PU_Pin)<<1) & HAL_GPIO_ReadPin(IO_4_PD_GPIO_N_Port, IO_4_PD_N_Pin);
            break;
        default:
            //error
    }
    comm[0] = comm[0] & resState;
    //get VH
    comm[1] = readExtDac(true, true, pinNum);
    comm[2] = readExtDac(true, false, pinNum);
    //get VL
    comm[3] = readExtDac(false, true, pinNum);
    comm[4] = readExtDac(false, false, pinNum);
    return;
}

void getTargetDeviceVolt(uint8_t* comm)
{
    uint16_t Volt;

    return;
}

void getSignalMode(uint8_t* comm)
{
    comm[0] = comm[0] & HAL_GPIO_ReadPin(IO_1_2_DIFF_GPIO_Port, IO_1_2_DIFF_Pin);

    return;
}

void getDataSpeed(uint8_t* comm)
{
    uint speed;//TODO: Update when Get Data Speed Commmand established

    return;
}

void getPinParams(uint8_t* comm)
{
    comm[1] = comm[1] & resState;
    comm[2] = 

    return;
}