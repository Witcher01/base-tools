#ifndef ARGS_H
#define ARGS_H

/* macros for parsing commandline arguments */
/* programs only ever accept one-char flags */
/* after calling ARGSBEGIN and ARGSEND, argv will point after the flags */

#define ARGSBEGIN	for (argv0 = *argv, argv++, argc--; \
						argv[0] && argv[0][0] == '-' && argv[0][1];\
						argv++, argc--) {\
						if (argv[0][1] == '-' && argv[0][2] == '\0') {\
							argv++;\
							argc--;\
							break;\
						}\
						switch(argv[0][1])

#define ARGSEND		}

/* name of the executed program */
extern char *argv0;

#endif /* ARGS_H */
