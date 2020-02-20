#ifndef __IOM_USB_H
#define __IOM_USB_H
#ifdef __cplusplus
extern "C" {
#endif

#include "core.h"
#include "usbd_def.h"

USBD_HandleTypeDef hUsbDeviceFS;

IOM_ERROR InitUSB(void);

#ifdef __cplusplus
}
#endif
#endif