# buf.c

Lightweight buffer library

# Implementation

buf.c lets you use regular pointers as expandable buffers. It uses an approach,
inspired by [sds](https://github.com/antirez/sds), of storing metadata before
the pointer value.

## API

Declare a buffer by declaring a pointer to an item type. For example, a `char
*` can be a buffer, or a `struct foo *`. Below, `TYPE` stands for the type that
you declared for the buffer.

Initialize an empty buffer by setting it to `NULL`.

```c
void buf_truncate(TYPE *);
```
Set the length of the buffer to zero, but don't free the buffer's memory.

```c
void buf_free(TYPE **);
```
Release allocated memory for the buffer, and mark it as empty buffer (set to
NULL).

```c
size_t buf_len(TYPE *);
```
Get the length of the data in the buffer.

```c
bool buf_alloc(TYPE **, size_t size);
```
Ensure that the buffer has enough space for some data. Return true for
success, false for failure.

```c
bool buf_put(TYPE **, const void *data, size_t size);
```
Put some data in the buffer. Return true on success, false on failure.

```c
bool buf_append(TYPE **, const void *data, size_t size);
```
Write the given data at the end of the buffer, expanding the buffer if
necessary. Return true on success, false on failure.

## License

MIT
