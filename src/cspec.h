
// 
// cspec.c
// 
// (c) 2009 TJ Holowaychuk <tj@vision-media.ca> (MIT Licensed)
//

#ifndef __CPSEC_H__
#define __CPSEC_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define ERROR(S, ...) fprintf(stderr, S "\n", __VA_ARGS__), exit(1)
#define MALLOC(T) (T *) malloc(sizeof(T))
#define REALLOC(F, T) self->F = (T *) realloc(self->F, ++self->n##F * sizeof(T))
#define INIT(T) T *self = MALLOC(T)
#define CSPEC_BUFFER_SIZE 5000

typedef void (*callback)();

#define expect(E) \
  if (E) printf("\033[1;32m%c\033[0m", '.'); \
  else printf("\n\033[0;31m      failed:\n        %s\033[0m\n", #E);

typedef enum {
  blockTypeNotImplemented = 1,
  blockTypeSpec,
  blockTypeBefore,
  blockTypeBeforeEach,
  blockTypeAfter,
  blockTypeAfterEach
} blockType;

typedef struct {
  char *description;
  callback func;
  blockType type;
} Block;

typedef struct _Suite {
  char *description;
  int nblocks;
  int nsuites;
  Block **blocks;
  struct _Suite **suites;
  struct _Suite *parent;
} Suite;

Block *
Block_new(blockType type, char *description, callback func);

Suite *
Suite_new(char *description);

void
Suite_run(Suite *self);

void
Suite_run_spec(Suite *self, Block *spec);

void
Suite_run_blocks(Suite *self, blockType type);

void
Suite_push_block(Suite *self, Block *block);

void
Suite_push_suite(Suite *self, Suite *suite);

int
Suite_spec_length(Suite *self);

char *
Suite_description(Suite *self);

#endif
