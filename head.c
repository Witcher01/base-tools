#define _POSIX_C_SOURCE 200809L

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "args.h"
#include "util.h"

void head(FILE *, size_t);

char *argv0;

void
usage()
{
	fail("usage: %s [option]... [file]...", argv0);
}

void
head(FILE *in, size_t n)
{
	int i = 0;
	char *lineptr = NULL;
	size_t len = 0;
	ssize_t size = 0;

	while (i < n && (size = getline(&lineptr, &len, in)) > 0) {
		fwrite(lineptr, 1, size, stdout);
		++i;
	}
	free(lineptr);
}

int
main(int argc, char *argv[])
{
	int ret = EXIT_SUCCESS;
	int c;
	/* print 10 lines by default */
	int lines = 10;
	FILE *file;

	argv0 = *argv;

	while ((c = getopt(argc, argv, "+v")) != -1) {
		switch (c) {
		case 'n':
			lines = atoi(optarg);
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
		file = stdin;
	} else {
		file = fopen(argv[optind], "r");
	}

	head(file, lines);

	/* should be okay to close stdin at the end */
	if (fclose(file) != 0) {
		fail("fclose:");
	}

	return ret;
}
