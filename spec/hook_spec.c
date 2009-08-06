
#include "cspec.h"

static int nbefore = 0;
static int nbefore_each = 0;
static int nafter = 0;
static int nafter_each = 0;

static int foo()  { return 4; }
static int bar(n) { return n * n; }

describe "CSpec before"
  before
    ++nbefore;
  end
  
  after
    ++nafter;
  end
  
  it "should be called before each suite"
    nbefore should equal 1;
  end
  
  it "should not be called before each spec"
    nbefore should equal 1;
  end
end

describe "CSpec after"
  it "should be called after each suite"
    nafter should equal 1;
  end
  
  it "should not be called after each spec"
    nafter should equal 1;
  end
end

describe "CSpec before_each"
  before_each
    ++nbefore_each;
  end
  
  it "should be called before each spec"
    nbefore_each should equal 1;
  end
  
  it "should be called before each spec"
    nbefore_each should equal 2;
  end
end

describe "CSpec after_each"
  after_each
    ++nafter_each;
  end
  
  it "should be called after each spec"
    nafter_each should equal 0;
  end
  
  it "should be called after each spec"
    nafter_each should equal 1;
  end
end

describe "CSpec assertions"
  it "should work without semicolons"
    int foo = 1;
    foo should equal 1
  end
  
  it "should work with ids"
    int foo = 1;
    foo should equal 1;
  end
  
  it "should work with underscored ids"
    char *foo_bar = "test";
    foo_bar should equal "test";
  end
  
  it "should work with structures"
    struct { int x, y; } point = { 0, 1 };
    point.x should equal 0;
    point.y should equal 1;
  end
  
  it "should work with pointers to structures"
    Suite *foo = Suite_new("Something");
    foo->description should equal "Something";
  end
  
  it "should work with function calls"
    foo() should equal 4;
    bar(2) should equal 4;
  end
end