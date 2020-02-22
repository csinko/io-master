#ifndef __IOM_TIMER_H
#define __IOM_TIMER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "core.h"

TIM_HandleTypeDef htim8;

IOM_ERROR InitTimers(void);

#ifdef __cplusplus
}
#endif
#endif