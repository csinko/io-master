#include "log.h"
#include "uart.h"

void IOMLog(const char* msg) {
    UARTSendString(msg);
}