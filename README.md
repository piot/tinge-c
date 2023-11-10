# Tinge

A tiny and simplistic C99 library for writing color text to the terminal.

Dependency towards [flood](https://github.com/piot/flood-c).

Example:

```c
    uint8_t temp[16 * 1024];
    FldOutStream outStream;
    fldOutStreamInit(&outStream, temp, 16 * 1024);

    TingeState state;

    tingeStateInit(&state, &outStream);

    tingeStateFgColor(&state, 23);
    fldOutStreamWritef(&outStream, " Hello '%s', this is in a new color ", "World");
    tingeStateReset(&state);

    printf("result:\n%s", tingeToString(&state));
```

See more in the provided example: [main.c](src/examples/main.c).

[screenshot](docs/images/tinge_macos_14.png)
