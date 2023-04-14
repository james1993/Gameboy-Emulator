#include <common.h>
#include <emu.h>
#include <cart.h>
#include <cpu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int emu_run(int argc, char **argv)
{
    int ret = 0;
    struct cart_context* cart_ctx;
    struct emu_context* emu_ctx;

    if (argc != 2) {
        printf("Usage: emu <rom_file>\n");
        ret = -2;
        goto err;
    }

    cart_ctx = (struct cart_context*)malloc(sizeof(struct cart_context));

    ret = cart_load(argv[1], cart_ctx);
    if (ret) {
        printf("Failed to load %s: %d\n", argv[1], ret);
        goto cart_free;
    }

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    cpu_init();

    emu_ctx = (struct emu_context*)malloc(sizeof(struct emu_context));
    emu_ctx->running = true;
    emu_ctx->paused = false;
    emu_ctx->ticks = 0;

    while (emu_ctx->running) {
        if (emu_ctx->paused) {
            SDL_Delay(10);
            continue;
        }

        ret = cpu_step();
        if (ret) {
            printf("CPU stopped\n");
            goto emu_free;
        }

        emu_ctx->ticks++;
    }

emu_free:
    free(emu_ctx);
cart_free:
    free(cart_ctx->rom_data);
    free(cart_ctx);
err:
    return ret;
}