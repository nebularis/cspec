
int nbefore = 0;
int nbefore_each = 0;
int nafter = 0;
int nafter_each = 0;

describe 'CSpec'
  before
    ++nbefore;
  end
  
  after
    ++nafter;
  end
  
  describe 'before'
    it 'should be called before each suite'
      expect(nbefore == 1);
    end
    
    it 'should not be called before each spec'
      expect(nbefore == 1);
    end
  end
  
  describe 'after'
    it 'be called after each suite'
      expect(nafter == 1);
    end 
    
    it 'should not be called after each spec'
      expect(nafter == 1);
    end
  end
end