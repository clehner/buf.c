#ifndef BUF_H
#define BUF_H

#include <stddef.h>
#include <stdbool.h>

#define buf_free(buf) \
	_buf_free((void **)buf)

#define buf_len(buf) \
	_buf_len(buf, sizeof *buf)

#define buf_alloc(buf, size) \
	_buf_alloc(buf, size * sizeof **buf)

#define buf_put(buf, data, len) \
	_buf_put((void **)buf, data, len * sizeof **buf)

#define buf_append(buf, data, len) \
	_buf_append((void **)buf, data, len * sizeof **buf)

void buf_truncate(void *);
void _buf_free(void **);
size_t _buf_len(void *, size_t item_size);
bool _buf_alloc(void **, size_t size);
bool _buf_put(void **, const void *data, size_t len);
bool _buf_append(void **, const void *data, size_t len);

#endif
