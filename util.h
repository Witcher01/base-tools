#ifndef UTIL_H
#define UTIL_H

/* define some standard macros */
#define MIN(A, B) ((A) < (B) ? (A) : (B))
#define MAX(A, B) ((A) > (B) ? (A) : (B))

void *emalloc(size_t);
void *ecalloc(size_t, size_t);
void fail(const char *, ...);
void efail(const char *, ...);

#endif /* UTIL_H */
