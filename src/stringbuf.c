#include "stringbuf.h"
#include <stdlib.h>
#include <string.h>

int docset_sb_init(DocSetStringBuf *buf, size_t capacity)
{
    char * data = calloc(capacity, sizeof(*data));
    if (!data) return 0;

    buf->data = data;
    buf->size = 0;
    buf->capacity = capacity;
    return 1;
}

void docset_sb_destroy(DocSetStringBuf *buf)
{
    if (buf) {
        free(buf->data);
        memset(buf, 0, sizeof(*buf));
    }
}

int docset_sb_assign(DocSetStringBuf *buf,
                     const char *data,
                     size_t len)
{
    docset_sb_reserve(buf, len + 1);
    memcpy(buf->data, data, len);
    buf->data[len] = '\0';
    buf->size = len;
    return 1;
}

int docset_sb_reserve(DocSetStringBuf *buf,
                      size_t size)
{
    if (buf->capacity < size) {
        size_t capx2 = buf->capacity * 2;
        size_t new_cap = capx2 > size ? capx2 : size;
        char * n = realloc(buf->data, new_cap);
        if (!n) return 0;
        buf->capacity = new_cap;
        buf->data = n;
    }
    return 1;
}

char *docset_sb_new_string(DocSetStringBuf *buf)
{
    size_t n = buf->size + 1;
    char *copy = malloc(n);
    if (!copy) return NULL;
    memcpy(copy, buf->data, n);
    return copy;
}

char *docset_strdup(const char *str)
{
    size_t n;
    char *copy;

    if (str == NULL) return NULL;

    n = strlen(str);
    copy = malloc(n + 1);

    if (!copy) return NULL;

    strcpy(copy, str);

    return copy;
}
