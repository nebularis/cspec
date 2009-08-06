
// 
// cspec.c
// 
// (c) 2009 TJ Holowaychuk <tj@vision-media.ca> (MIT Licensed)
//

#include "cspec.h"

Suite *current_suite = NULL;
Block *current_spec = NULL;

Block *
Block_new(blockType type, char *description, callback func) {
  INIT(Block);
  self->type = type;
  self->description = description;
  self->func = func;
  return self;
}

Suite *
Suite_new(char *description) {
  INIT(Suite);
  self->description = description;
  self->blocks = NULL;
  self->suites = NULL;
  self->nblocks = 0;
  self->nsuites = 0;
  self->parent = NULL;
  return self;
}

void
Suite_run(Suite *self) {
  current_suite = self;
  if (Suite_spec_length(self))
    printf("\n\033[1;01m  %s\033[0m", Suite_description(self));
  Suite_run_blocks(self, blockTypeBefore);
  for (int i = 0; i < self->nblocks; ++i) 
    if (self->blocks[i]->type == blockTypeSpec)
      Suite_run_spec(self, self->blocks[i]);
  printf("\n");
  Suite_run_blocks(self, blockTypeAfter);
  for (int i = 0; i < self->nsuites; ++i)
    Suite_run(self->suites[i]);
}

void
Suite_run_spec(Suite *self, Block *spec) {
  current_spec = spec;
  printf("\n\033[0;32m    %s\033[0m ", spec->description);
  Suite_run_blocks(self, blockTypeBeforeEach);
  spec->func();
  Suite_run_blocks(self, blockTypeAfterEach);
}

int
Suite_spec_length(Suite *self) {
  int len = 0;
  for (int i = 0; i < self->nblocks; ++i) 
    if (self->blocks[i]->type == blockTypeSpec)
      ++len;
  return len;
}

char *
Suite_description(Suite *self) {
  return self->description;
}

void
Suite_run_blocks(Suite *self, blockType type) {
  for (int i = 0; i < self->nblocks; ++i)
    if (self->blocks[i]->type == type)
      if (self->blocks[i]->func)
        self->blocks[i]->func();
}

void
Suite_push_block(Suite *self, Block *block) {
  REALLOC(blocks, Block *);
  self->blocks[self->nblocks-1] = block;
}

void
Suite_push_suite(Suite *self, Suite *suite) {
  REALLOC(suites, Suite *);
  self->suites[self->nsuites-1] = suite;
  suite->parent = self;
}

void
CSpec_stats() {
  printf("\n  \033[1;01mPasses:\033[0m \033[1;32m%d\033[0m \033[1;01mFailures:\033[0m \033[1;31m%d\033[0m\n\n", 
    CSpec.passes, CSpec.failures);
}
