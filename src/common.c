#define _POSIX_C_SOURCE 200809L

#include "common.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

void
buffer_init(Buffer *b)
{
    b->data = NULL;
    b->len = 0;
}

void
buffer_free(Buffer *b)
{
    free(b->data);
    b->data = NULL;
    b->len = 0;
}

int
buffer_append(Buffer *b, const void *data, size_t n)
{
    char *p;

    p = realloc(b->data, b->len + n + 1);
    if (p == NULL) {
        return -1;
    }

    b->data = p;
    memcpy(b->data + b->len, data, n);
    b->len += n;
    b->data[b->len] = '\0';

    return 0;
}

long
now_micros(void)
{
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000000L + ts.tv_nsec / 1000L;
}

int
file_read_all(const char *path, Buffer *out)
{
    FILE *f;
    char chunk[4096];
    size_t r;

    f = fopen(path, "rb");
    if (f == NULL) {
        return -1;
    }

    buffer_init(out);

    while ((r = fread(chunk, 1, sizeof(chunk), f)) > 0) {
        if (buffer_append(out, chunk, r) != 0) {
            fclose(f);
            buffer_free(out);
            return -1;
        }
    }

    if (ferror(f)) {
        fclose(f);
        buffer_free(out);
        return -1;
    }

    fclose(f);
    return 0;
}

int
file_write_all(const char *path, const char *data, size_t n)
{
    FILE *f;

    f = fopen(path, "wb");
    if (f == NULL) {
        return -1;
    }

    if (fwrite(data, 1, n, f) != n) {
        fclose(f);
        return -1;
    }

    fclose(f);
    return 0;
}

static int
is_dir(const char *path)
{
    struct stat st;

    if (stat(path, &st) != 0) {
        return 0;
    }

    return S_ISDIR(st.st_mode);
}

int
ensure_dir_recursive(const char *path)
{
    char *tmp;
    size_t len;

    tmp = strdup(path);
    if (tmp == NULL) {
        return -1;
    }

    len = strlen(tmp);

    for (size_t i = 1; i <= len; i++) {
        if (tmp[i] == '/' || tmp[i] == '\0') {
            char saved = tmp[i];
            tmp[i] = '\0';

            if (tmp[0] != '\0' && !is_dir(tmp)) {
                if (mkdir(tmp, 0755) != 0 && errno != EEXIST) {
                    free(tmp);
                    return -1;
                }
            }

            tmp[i] = saved;
        }
    }

    free(tmp);
    return 0;
}

void
str_rtrim_inplace(char *s)
{
    size_t n;

    if (s == NULL) {
        return;
    }

    n = strlen(s);

    while (n > 0) {
        char c = s[n - 1];
        if (c == '\n' || c == '\r' || c == ' ' || c == '\t') {
            s[n - 1] = '\0';
            n--;
        } else {
            break;
        }
    }
}

void
ll_to_str(long long v, char *buf, size_t n)
{
    snprintf(buf, n, "%lld", v);
}

int
load_dotenv_if_present(const char *path)
{
    FILE *f;
    char line[4096];

    f = fopen(path, "r");
    if (f == NULL) {
        return 0;
    }

    while (fgets(line, sizeof(line), f) != NULL) {
        char *eq = strchr(line, '=');
        if (eq == NULL) {
            continue;
        }

        *eq = '\0';
        char *key = line;
        char *val = eq + 1;

        str_rtrim_inplace(key);
        str_rtrim_inplace(val);

        setenv(key, val, 1);
    }

    fclose(f);
    return 0;
}

