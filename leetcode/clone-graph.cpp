#include <queue>
#include <unordered_map>
#include "leetcode.h"

class SolutionV2 {
public:
  unordered_set<int> visited;
  unordered_map<int, UndirectedGraphNode *> nodes;

  UndirectedGraphNode *dfs(UndirectedGraphNode *node) {
    if (node == NULL) return NULL;

    if ( visited.find(node->label) != visited.end() )
      return nodes[node->label];

    auto &node_clone = nodes[node->label];
    if (!node_clone)
      node_clone = new UndirectedGraphNode(node->label);

    for (UndirectedGraphNode *nbr : node->neighbors) {
      auto &nbr_clone = nodes[nbr->label];
      if (!nbr_clone) {
        nbr_clone = dfs(nbr);
      }
      node_clone->neighbors.push_back(nbr_clone);
    }
    visited.insert(node->label);
    return node_clone;
  }

  UndirectedGraphNode *bfs(UndirectedGraphNode *node) {
    if (node == NULL) return NULL;

    nodes[node->label] = new UndirectedGraphNode(node->label);
    queue<UndirectedGraphNode *> q;
    q.push(node);

    while (!q.empty()) {
      UndirectedGraphNode *nd = q.front();
      q.pop();
      if (visited.find(nd->label) != visited.end()) {
        continue;
      }

      auto &node_clone = nodes[nd->label];
      if (!node_clone)
        node_clone = new UndirectedGraphNode(nd->label);
      visited.insert(nd->label);
      
      for (UndirectedGraphNode *nbr : nd->neighbors) {
        auto &nbr_clone = nodes[nbr->label];
        if (!nbr_clone) {
          nbr_clone = new UndirectedGraphNode(nbr->label);
        }
        node_clone->neighbors.push_back(nbr_clone);
        if (visited.find(nbr->label) == visited.end()) {
          q.push(nbr);
        }
      }
    }

    return nodes[node->label];
  }

  UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
    visited.clear();
    nodes.clear();
    return bfs(node);
  }
};

class Solution {
  std::unordered_map<int, UndirectedGraphNode *> clone;
  std::unordered_set<int> visited;
public:
  UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
    if (node == NULL) return NULL;
    std::queue<UndirectedGraphNode *> myqueue;
    myqueue.push(node);

    while ( !myqueue.empty() ) {
      UndirectedGraphNode *p = myqueue.front();
      myqueue.pop();

      // already visited this node
      if ( visited.find(p->label) != visited.end() )
        continue;

      visited.insert(p->label);
      UndirectedGraphNode *cur = clone[p->label];

      if (cur == NULL)
        cur = clone[p->label] = new UndirectedGraphNode(p->label);

      for (auto nbr : p->neighbors) {
        UndirectedGraphNode *clone_nbr = clone[nbr->label];

        if (clone_nbr == NULL) {
          clone_nbr = clone[nbr->label] = new UndirectedGraphNode(nbr->label);
        }

        if ( visited.find(nbr->label) == visited.end() )
          myqueue.push(nbr);

        cur->neighbors.push_back(clone_nbr);
      }
    } // while

    return clone[node->label];
  }
};

int main() {
  Solution sol;
  string graph = "0,1,2#1,2#2,2";
  UndirectedGraphNode *node = deserialize_graph(graph);
  serialize_graph(cout, node);

  auto nn = sol.cloneGraph(node);
  serialize_graph(cout, nn);

  return 0;
}