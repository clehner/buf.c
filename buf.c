#include <stdlib.h>
#include <string.h>

#include "buf.h"

struct buf {
	size_t len;	/* current length of data */
	size_t size;   /* maximal capacity of the buffer */
	void *data[];
};

static inline void *buf_box(struct buf *buf) {
	return &buf->data;
}

static inline struct buf *buf_unbox(void *buf) {
	return buf ? &((struct buf *)buf)[-1] : NULL;
}

void buf_free(void **_buf) {
	if (*_buf) {
		free(*_buf);
		*_buf = NULL;
	}
}

void buf_truncate(void *_buf) {
	if (_buf)
		buf_unbox(_buf)->len = 0;
} 

size_t _buf_len(void *_buf, size_t item_size) {
	return _buf ? buf_unbox(_buf)->len / item_size : 0;
} 

struct buf *alloc(struct buf *buf, size_t size) {
	size_t current_size = buf ? buf->size : 0;
	if (current_size < size) {
		if (current_size > 0)
			size <<= 1;
		if (!(buf = realloc(buf, sizeof(struct buf) + size)))
			return NULL;
		buf->size = size;
	}
	return buf;
}

bool _buf_alloc(void **_buf, size_t size) {
	struct buf *buf = buf_unbox(*_buf),
			   *new_buf = alloc(buf, size);
	if (new_buf == NULL)
		return false;
	if (buf != new_buf)
		*_buf = buf_box(new_buf);
	return true;
}

bool _buf_put(void **_buf, const void *data, size_t len) {
	if (!_buf_alloc(_buf, len))
		return false;
	struct buf *buf = buf_unbox(*_buf);
	memcpy(buf->data, data, len);
	buf->len = len;
	return true;
}

bool _buf_append(void **_buf, const void *data, size_t len) {
	struct buf *buf = buf_unbox(*_buf);
	size_t rem = buf ? buf->size - buf->len : 0;
	if (len > rem) {
		if (!(buf = alloc(buf, (buf ? buf->size : 0) + len - rem)))
			return false;
		*_buf = buf_box(buf);
	}
	memcpy((char *)buf->data + buf->len, data, len);
	buf->len += len;
	return true;
}
