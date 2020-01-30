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
            targetDeviceVolt:
                setTargetDeviceVolt(comm);
                break;
            pin1Params:
            pin2Params:
            pin3Params:
            pin4Params:
                setPinParams(commTag, comm);
                break;
            dataSpeed:
                setDataSpeed(comm);
                break;
            signalMode:
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
            targetDeviceVolt:
                getTargetDeviceVolt(comm);
                break;
            pin1Params:
            pin2Params:
            pin3Params:
            pin4Params:
                getPinParams(commTag, comm);
                break;
            dataSpeed:
                getDataSpeed(comm);
                break;
            signalMode:
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
    uint8_t resState;
    uint16_t VH = (comm[2]<<8) | comm[3];
    uint16_t VL = (comm[4]<<8) | comm[5];

    return;
}

void setTargetDeviceVolt(uint8_t* comm)
{
    uint16_t Volt = (comm[2]<<8) | comm[3];

    return;
}

void setSignalMode(uint8_t* comm)
{
    bool mode = comm[1] & 0b0001;

    return;
}

void setDataSpeed(uint8_t* comm)
{
    uint speed;//TODO: Update when Set Data Speed Commmand established

    return;
}

void setPinParams(uint8_t pinNum, uint8_t* comm)
{
    uint8_t resState = comm[1] & 0b0011;
    uint16_t VH = (comm[2]<<8) | comm[3];
    uint16_t VL = (comm[4]<<8) | comm[5];

    //set pins via resState q
    //set VH
    //set VL
    return;
}

void getTargetDeviceVolt()
{
    uint16_t Volt;

    return;
}

void getSignalMode()
{
    bool mode;

    return;
}

void getDataSpeed()
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