class UnionFind {
public:
  UnionFind(size_t n) {
     root.resize(n);
     for (int i = 0; i < n; ++i) root[i] = i;
  }
  
  int findRoot(int x) {
     int r, y = x, t;
     while(root[x] != x) x = root[x];
     r = x;
     while(root[y] != y) {
        t = root[y]; root[y] = r; y = t; 
     }
     return r; 
  }

  void merge(int x, int y) {
     int r0 = findRoot(x), r1 = findRoot(y);
     if (r0 == r1) return;
     root[r1] = r0;
  }
  
private:
   vector<int> root;
};

class Solution {
public:
    /**
     * @param graph: graph edge value
     * @return: return the minium length of graph
     */


     //Idea: sort edges from max to min, remove them one by one, util we could not have two group 
    int getMiniumValue(vector<vector<int>> &graph) {
       const int n = graph.size();
       
       vector<tuple<int, int, int>> edges; 
        {//sort edges by distance maxToMin
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (i >= j) continue; // dedup
                    edges.emplace_back(make_tuple(i, j, graph[i][j]));
                }
            }

            sort(edges.begin(), edges.end(), [](auto& l, auto& r) -> bool {
                return get<2>(l) > get<2>(r);
            });
        }

       /*
       the difficulty is how to know we have two complete groups
       we scan all edges from max to min, in the mean whil, we need to merge the nodes while we remove an edge : 
        ex:if we remove an edge from 0 to 1 then we remove an edge from 0 to 2, that means we need to merge 1 and 2 in the same group, 
        so if we got to have the max edge to move is from 1 to 2, in this case that means the two groups {0...} and {1,2 ...} 's max inner edge is the edge from 1 to 2

        how to do that ? 
            we can se union find to see if two nodes are alreayd made in the same group
            we need a set per node to note the node in the other group of this node : vector<unordered_set<int>> apartFrom(n);
       
       */
       UnionFind uf(n);
       vector<unordered_set<int>> apartFrom(n);

        /*
            cut edge means we want to remove this curent max edge, and the consiquence is :
                 the other node in the edge should be noted in the set, then to be unioned with other nodes in the set
        */
       auto cutEdge = [&](int i, int j, int w) -> int {
           cout<<"cutEdge"<<i<<","<<j<<endl;
          if (!apartFrom[i].count(j)) {
             for (auto& k : apartFrom[i]) {
                uf.merge(k, j);
                std::cout<< "merge "<<k<<","<<j<<endl;
                break;
             }
             apartFrom[i].insert(j);
          }
          /*
          here we need this return to avoid the case that we have only one node in a group
          in the description "The number of points in each group should not be less than 2"
          */
          return (apartFrom[i].size() == n - 1) ? w : INT_MIN;
       };

       for (auto& edge : edges) {
          int i = get<0>(edge), j = get<1>(edge), w = get<2>(edge); 
          cout<<"uf "<<i<<","<<j<<endl;
          if (uf.findRoot(i) == uf.findRoot(j)) {
              return w;
          }

          int res = cutEdge(i, j, w);
          if (res != INT_MIN) return res;

          res = cutEdge(j, i, w);
          if (res != INT_MIN) return res;
       }

       return 0;
    }
};
