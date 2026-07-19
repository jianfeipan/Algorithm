class UnionFind {
public:
  UnionFind(size_t n) {
     root.resize(n);
     for (int i = 0; i < n; ++i) root[i] = i;
  }
  
  int findRoot(int x) {
     int finalRoot;
     int toSearch = x;
     while(root[toSearch] != toSearch) toSearch = root[toSearch];
     finalRoot = saerch;
    
     //should update the roots to finalRoot--> most famous
     int currentRoot;
     int toUpdate = x;
     while(root[toUpdate] != toUpdate) {
        currentRoot = root[toUpdate]; 
        root[toUpdate] = finalRoot;
        toUpdate = currentRoot; 
     }
    
     return finalRoot; 
  }

  void merge(int x, int y) {
     int r0 = findRoot(x), r1 = findRoot(y);
     if (r0 == r1) return;
     root[r1] = r0;
  }
  
private:
   vector<int> root;
};
