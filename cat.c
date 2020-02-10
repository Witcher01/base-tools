#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "args.h"
#include "file_util.h"
#include "util.h"

void usage();

void
usage()
{
	fail("usage: %s [file ...]", argv0);
}

int
main(int argc, char *argv[])
{
	int fd, ret = 0;

	ARGSBEGIN {
	default:
		usage();
	} ARGSEND

	/* no arguments are given */
	if (argc < 1) {
		/* pass STDIN to STDOUT */
		concatenate(STDIN_FILENO, STDOUT_FILENO);
	}

	/* argv points after flags */
	for (; argv[0] && argc > 0; argv++, argc--) {
		/* "-" means stdin */
		if (!(strcmp(argv[0], "-"))) {
			fd = STDIN_FILENO;
		} else if (!(fd = open(argv[0], O_RDONLY))) {
			fail("open:");
		}

		switch (concatenate(fd, STDOUT_FILENO)) {
		case -1:
			/* read error, continue */
			ret = 1;
			break;
		case -2:
			/* write error, end */
			return 1;
		}

		/* fd is not stdin */
		if (strcmp(argv[0], "-") != 0) {
			close(fd);
		}
	}

	return ret;
}
