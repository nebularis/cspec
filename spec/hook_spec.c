
#include "cspec.h"

static int nbefore = 0;
static int nbefore_each = 0;
static int nafter = 0;
static int nafter_each = 0;

describe "CSpec"
  before
    ++nbefore;
  end
  
  after
    ++nafter;
  end
  
  describe "before"
    it "should be called before each suite"
      expect(nbefore == 1);
    end
    
    it "should not be called before each spec"
      expect(nbefore == 1);
    end
  end
  
  describe "after"
    it "should be called after each suite"
      expect(nafter == 1);
    end 
    
    it "should not be called after each spec"
      expect(nafter == 1);
    end
  end
  
  describe "before_each"
    before_each
      ++nbefore_each;
    end
    
    after_each
      ++nafter_each;
    end
    
    it "should be called before / after each spec"
      expect(nbefore_each == 1);
      expect(nafter_each == 0);
    end
    
    it "should be called before / after each spec"
      expect(nbefore_each == 2);
      expect(nafter_each == 1);
    end
  end
  
end
