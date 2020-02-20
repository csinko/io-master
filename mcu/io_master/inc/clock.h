#ifndef __IOM_CLOCK_H
#define __IOM_CLOCK_H
#ifdef __cplusplus
extern "C" {
#endif

#include "core.h"


//
// @brief Initalize the System Clock
//
// @return IOM_OK if ok, an IOM_ERROR if there
// are any issues 
//

IOM_ERROR InitSystemClock(void);

#ifdef __cplusplus
}
#endif

#endif