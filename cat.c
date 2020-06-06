#define _POSIX_C_SOURCE 2

#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "args.h"
#include "file_util.h"
#include "util.h"

char *argv0;

void
usage()
{
	fail("usage: %s [file ...]", argv0);
}

int
main(int argc, char *argv[])
{
	int fd, ret = EXIT_SUCCESS;
	int c;
	int index;

	argv0 = *argv;

	while ((c = getopt(argc, argv, "+v")) != -1) {
		switch (c) {
		case 'v':
			fail("%s: version 0.1", argv[0]);
			break;
		default:
			usage();
		}
	}

	/* no arguments are given */
	if (argc == optind) {
		/* pass STDIN to STDOUT */
		concatenate(STDIN_FILENO, STDOUT_FILENO);
	}

	/* argv points after flags */
	for (index = optind; index < argc; ++index) {
		/* "-" means stdin */
		if (!(strcmp(argv[index], "-"))) {
			fd = STDIN_FILENO;
		} else if (!(fd = open(argv[index], O_RDONLY))) {
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
		if (strcmp(argv[index], "-") != 0) {
			close(fd);
		}
	}

	return ret;
}
