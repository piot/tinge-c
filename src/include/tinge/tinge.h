/*----------------------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved. https://github.com/piot/tinge-c
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------------------*/
#ifndef TINGE_STATE_H
#define TINGE_STATE_H

#include <stdint.h>

struct FldOutStream;

typedef struct TingeState {
    struct FldOutStream* stream;
    int eightBit;
} TingeState;

void tingeStateInit(TingeState* self, struct FldOutStream* stream);
void tingeStateFgColor(TingeState* self, uint8_t fgColor);
void tingeStateFgColorIndex(TingeState* self, uint8_t fgColor);
struct FldOutStream* tingeStateStream(TingeState* self);
const char* tingeStateToString(TingeState* self);
void tingeStateReset(TingeState* self);

#endif
