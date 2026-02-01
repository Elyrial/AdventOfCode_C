#ifndef AOC_COMMON_H
#define AOC_COMMON_H

#include <stddef.h>

typedef struct {
    char *data;
    size_t len;
} Buffer;

void buffer_init(Buffer *b);
void buffer_free(Buffer *b);
int  buffer_append(Buffer *b, const void *data, size_t n);

long now_micros(void);

int file_read_all(const char *path, Buffer *out);
int file_write_all(const char *path, const char *data, size_t n);

int ensure_dir_recursive(const char *path);

void str_rtrim_inplace(char *s);

int load_dotenv_if_present(const char *path);

#endif

