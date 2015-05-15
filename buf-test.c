#include "buf.h"

#include <assert.h>
#include <string.h>

int main(int argc, char **argv) {
	char *buf = NULL;
	assert(buf_len(buf) == 0);

	assert(buf_append(&buf, "foo", 3));
	assert(buf_len(buf) == 3);
	assert(strncmp(buf, "foo", 3) == 0);

	assert(buf_append(&buf, "bar", 3));
	assert(buf_len(buf) == 6);
	assert(strncmp(buf, "foobar", 6) == 0);

	assert(buf_append(&buf, "qux", 4));
	assert(buf_len(buf) == 10);
	assert(strcmp(buf, "foobarqux") == 0);

	assert(buf_put(&buf, "blah", 5));
	assert(strcmp(buf, "blah") == 0);

	char longstr[] = "qwertyuiopasdfghjklzxcvbnm,./";
	assert(buf_put(&buf, longstr, sizeof longstr));
	assert(buf_len(buf) == sizeof longstr);
	assert(strcmp(buf, longstr) == 0);

	buf_truncate(buf);
	assert(buf_len(buf) == 0);

	buf_free(&buf);
	assert(buf_len(buf) == 0);
	assert(buf == NULL);

	buf_append(&buf, "asdf", 4);
	buf_free(&buf);
	assert(buf_len(buf) == 0);
	assert(buf == NULL);

	return 0;
}
