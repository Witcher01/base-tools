#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "util.h"

void *
emalloc(size_t size)
{
	void *ptr;

	/* no memory allocated */
	if (!(ptr = malloc(size))) {
		fail("malloc:");
	}

	return ptr;
}

void *
ecalloc(size_t nmemb, size_t size)
{
	void *ptr;

	/* no memory allocated */
	if (!(ptr = calloc(nmemb, size))) {
		fail("calloc:");
	}

	return ptr;
}

void
fail(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	/* print given string to stderr */
	vfprintf(stderr, fmt, ap);
	va_end(ap);

	/* if given string ends with a ':' print more info using perror */
	if (fmt[0] && fmt[strlen(fmt) - 1] == ':') {
		fputc(' ', stderr);
		perror(NULL);
	} else {
		fputc('\n', stderr);
	}

	exit(EXIT_FAILURE);
}

void
efail(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	/* print given string to stderr */
	vfprintf(stderr, fmt, ap);
	va_end(ap);

	/* if given string ends with a ':' print more info using perror */
	if (fmt[0] && fmt[strlen(fmt) - 1] == ':') {
		fputc(' ', stderr);
		perror(NULL);
	} else {
		fputc('\n', stderr);
	}
}
