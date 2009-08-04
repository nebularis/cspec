
#include "cspec.h"

static int nbefore = 0;
static int nbefore_each = 0;
static int nafter = 0;
static int nafter_each = 0;


 void block_0_callback() {
    ++nbefore;
 
}
  
 void block_1_callback() {
    ++nafter;
 
}
  
  
    void block_2_callback() {

      expect(nbefore == 1);
   
}
    
    void block_3_callback() {

      expect(nbefore == 1);
   
}
   
  
    void block_4_callback() {

      expect(nafter == 1);
   
}

    
    void block_5_callback() {

      expect(nafter == 1);
   
}
   
  
   void block_6_callback() {
      ++nbefore_each;
   
}
    
   void block_7_callback() {
      ++nafter_each;
   
}
    
    void block_8_callback() {

      expect(nbefore_each == 1);
      expect(nafter_each == 0);
   
}
    
    void block_9_callback() {

      expect(nbefore_each == 2);
      expect(nafter_each == 1);
   
}
   int main() {

Suite *suite_0 = Suite_new("CSpec");

 
Block *block_0 = Block_new(blockTypeBefore, NULL, &block_0_callback);

Suite_push_block(suite_0, block_0);

Block *block_1 = Block_new(blockTypeAfter, NULL, &block_1_callback);

Suite_push_block(suite_0, block_1);

Suite *suite_1 = Suite_new("before");

Suite_push_suite(suite_0, suite_1);

Block *block_2 = Block_new(blockTypeSpec, "should be called before each suite", &block_2_callback);

Suite_push_block(suite_1, block_2);

Block *block_3 = Block_new(blockTypeSpec, "should not be called before each spec", &block_3_callback);

Suite_push_block(suite_1, block_3);

Suite *suite_2 = Suite_new("after");

Suite_push_suite(suite_1, suite_2);

Block *block_4 = Block_new(blockTypeSpec, "should be called after each suite", &block_4_callback);

Suite_push_block(suite_2, block_4);

Block *block_5 = Block_new(blockTypeSpec, "should not be called after each spec", &block_5_callback);

Suite_push_block(suite_2, block_5);

Suite *suite_3 = Suite_new("before_each");

Suite_push_suite(suite_2, suite_3);

Block *block_6 = Block_new(blockTypeBeforeEach, NULL, &block_6_callback);

Suite_push_block(suite_3, block_6);

Block *block_7 = Block_new(blockTypeAfterEach, NULL, &block_7_callback);

Suite_push_block(suite_3, block_7);

Block *block_8 = Block_new(blockTypeSpec, "should be called before / after each spec", &block_8_callback);

Suite_push_block(suite_3, block_8);

Block *block_9 = Block_new(blockTypeSpec, "should be called before / after each spec", &block_9_callback);

Suite_push_block(suite_3, block_9);

Suite_run(suite_0);
return 0;
}


