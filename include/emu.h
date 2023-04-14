#pragma once

#include <common.h>

struct emu_context{
    bool paused;
    bool running;
    uint64_t ticks;
};

int emu_run(int argc, char **argv);
