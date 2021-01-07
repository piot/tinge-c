/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include <flood/out_stream.h>
#include <tinge/tinge.h>

void tingeStateInit(TingeState* self, struct FldOutStream* stream)
{
    self->stream = stream;
    self->eightBit = 1;
}

void tingeStateFgColor(TingeState* self, uint8_t fgColor)
{
    if (self->eightBit) {
        fldOutStreamWritef(self->stream, "\033[38;5;%dm", fgColor);
    } else {
        if (fgColor >= 0 && fgColor <= 7) {
            fgColor += 30;
        } else if (fgColor >= 8 && fgColor <= 15) {
            fgColor += 90 - 8;
        } else
        {
            // Unsupported
            fgColor = 0;
        }
        fldOutStreamWritef(self->stream, "\033[%dm", fgColor);
    }
}

void tingeStateFgColorIndex(TingeState* self, uint8_t fgColorIndex)
{
    static const uint8_t niceColors[] = {
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x09, 0x0a, 0xe2, 0x0c, 0x0d, 0x16,
        0x17, 0x3d, 0x48, 0x5c, 0x6f, 0xb2, 0xc6, 0xce, 0xd0, 0xd8, 0xdb, 0xdd,
    };

    tingeStateFgColor(self, niceColors[fgColorIndex % 24]);
}

void tingeStateReset(TingeState* self)
{
    if (self->eightBit) {
        fldOutStreamWritef(self->stream, "\033[39m");
    } else {
        fldOutStreamWritef(self->stream, "\033[0m");
    }
}

FldOutStream* tingeStateStream(TingeState* self)
{
    return self->stream;
}

const char* tingeStateToString(TingeState* self)
{
    if (self->stream->pos >= self->stream->size) {
        return 0;
    }
    self->stream->octets[self->stream->pos] = 0;
    return (const char*) self->stream->octets;
}
