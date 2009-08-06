
#include "cspec.h"

static int nbefore = 0;
static int nbefore_each = 0;
static int nafter = 0;
static int nafter_each = 0;

describe "CSpec before"
  before
    ++nbefore;
  end
  
  after
    ++nafter;
  end
  
  it "should be called before each suite"
    expect(nbefore == 1);
  end
  
  it "should not be called before each spec"
    expect(nbefore == 1);
  end
end

describe "CSpec after"
  it "should be called after each suite"
    expect(nafter == 1);
  end
  
  it "should not be called after each spec"
    expect(nafter == 1);
  end
end

describe "CSpec before_each"
  before_each
    ++nbefore_each;
  end
  
  it "should be called before each spec"
    expect(nbefore_each == 1);
  end
  
  it "should be called before each spec"
    expect(nbefore_each == 2);
  end
end

describe "CSpec after_each"
  after_each
    ++nafter_each;
  end
  
  it "should be called after each spec"
    expect(nafter_each == 0);
  end
  
  it "should be called after each spec"
    expect(nafter_each == 1);
  end
end