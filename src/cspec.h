
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

typedef void (*callback)();

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
} Suite;

void
expect(int expr, char *source);

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

#endif
