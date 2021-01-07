/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include <flood/out_stream.h>
#include <stdio.h>
#include <tinge/tinge.h>

#include <clog/clog.h>

clog_config g_clog;

static void tyran_log_implementation(enum clog_type type, const char* string)
{
    (void) type;
    fprintf(stderr, "%s\n", string);
}

int main(int argc, char* argv[])
{
    g_clog.log = tyran_log_implementation;

    uint8_t temp[16 * 1024];
    FldOutStream outStream;
    fldOutStreamInit(&outStream, temp, 16 * 1024);
    TingeState state;

    tingeStateInit(&state, &outStream);
    state.eightBit = 1;

    for (size_t i = 0; i < 256; ++i) {
        tingeStateFgColor(&state, i);
        if ((i % 16) == 0) {
            fldOutStreamWritef(&outStream, "\n");
        }
        fldOutStreamWritef(&outStream, " %02X ", i);
        tingeStateReset(&state);
    }

    fldOutStreamWritef(&outStream, "\n\n");
    for (size_t i = 0; i < 24; ++i) {
        tingeStateFgColorIndex(&state, i);
        fldOutStreamWritef(&outStream, " %02X ", i);
        tingeStateReset(&state);
    }

    printf("output:\n%s", tingeStateToString(&state));
}