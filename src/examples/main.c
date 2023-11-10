/*----------------------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved. https://github.com/piot/tinge-c
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------------------*/
#include <flood/out_stream.h>
#include <stdio.h>
#include <tinge/tinge.h>

#include <clog/clog.h>
#include <clog/console.h>

clog_config g_clog;

int main(void)
{
    g_clog.log = clog_console;

    uint8_t temp[16 * 1024];
    FldOutStream outStream;
    fldOutStreamInit(&outStream, temp, 16 * 1024);
    TingeState state;

    tingeStateInit(&state, &outStream);
    state.eightBit = 1;

    for (size_t i = 0; i < 256; ++i) {
        tingeStateFgColor(&state, (uint8_t) i);
        if ((i % 16) == 0) {
            fldOutStreamWritef(&outStream, "\n");
        }
        fldOutStreamWritef(&outStream, " %02X ", i);
        tingeStateReset(&state);
    }

    fldOutStreamWritef(&outStream, "\n\n");
    for (size_t i = 0; i < 24; ++i) {
        tingeStateFgColorIndex(&state, (uint8_t) i);
        fldOutStreamWritef(&outStream, " %02X ", i);
        tingeStateReset(&state);
    }

    printf("output:\n%s\n", tingeStateToString(&state));
}
