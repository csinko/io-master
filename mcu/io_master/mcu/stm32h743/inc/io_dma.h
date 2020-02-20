#ifndef __IO_MASTER_IO_DMA_H
#define __IO_MASTER_IO_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "core.h"

void StartDMATransfer(IOM_Output_Buffer* pBuffer);
void ResetDMA();

#ifdef __cplusplus
}
#endif
#endif
