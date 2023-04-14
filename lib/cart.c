#include <cart.h>

int cart_load(char *cart, struct cart_context* cart_ctx) {
    snprintf(cart_ctx->filename, FILENAME_SIZE, "%s", cart);

    FILE *fp = fopen(cart_ctx->filename, "r");
    if (!fp) {
        printf("Failed to open: %s\n", cart_ctx->filename);
        return -1;
    }

    fseek(fp, 0, SEEK_END);
    cart_ctx->rom_size = ftell(fp);

    rewind(fp);

    cart_ctx->rom_data = malloc(cart_ctx->rom_size);
    fread(cart_ctx->rom_data, cart_ctx->rom_size, 1, fp);
    fclose(fp);

    cart_ctx->header = (struct rom_header *)(cart_ctx->rom_data + HEADER_OFFSET);
    cart_ctx->header->title[15] = 0;

    return 0;
}