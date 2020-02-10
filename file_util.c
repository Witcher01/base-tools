#include <stdio.h>
#include <unistd.h>

#include "file_util.h"
#include "util.h"

/*
 * Return values:
 *  0: correct execution
 * -1: read failed
 * -2: write failed
 */
int
concatenate(int fd1, int fd2)
{
	char buf[BUFSIZ];
	ssize_t n;

	while((n = read(fd1, buf, sizeof(buf))) > 0) {
		if (write(fd2, buf, n) < 0) {
			efail("write:");
			return -2;
		}
	}

	/* read error occured */
	if (n < 0) {
		efail("read:");
		return -1;
	}

	return 0;
}
