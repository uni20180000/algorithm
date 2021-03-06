// very tricky problem, the following has a very clear code
// http://oj.leetcode.com/discuss/1722/spoiler-alert-java-gas-station-solution-what-you-guys-think
//
// Two observations:
// 1. if sum(gas) >= sum(cost), there must be a solution (proof)?
// 2. if we travel from A to B and gas becomes negative, starting from any station between them will fail too.
//    this gives us a linear time solution, we can visit it only one pass to examine all the possibilities of starting point.

#include "leetcode.h"

class SolutionV2 {
public:
  int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
    int n = gas.size();
    if (n == 0) return -1;

    int lapse = 0;
    int cur = gas[0] - cost[0], start = 0;
    int i = 0;
    while (lapse < 2*n) {
      i = (i+1) % n;
      ++lapse;
      if (cur < 0) {
        cur = gas[i] - cost[i];
        start = i;
      } else if (start == i) {
        return start;
      } else {
        cur = cur + gas[i] - cost[i];
      }
    }
    return -1;
  }
};

class Solution {
public:
  int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
    // compute the delta and sum the cost
    int n = gas.size();
    if (n == 1) 
      return gas[0] - cost[0] >= 0 ? 0 : -1;
    vector<int> delta(n);
    int sum = 0;
    int idx = -1;
    int pos_start = -1;
    for (int i = 0; i < n; ++i) {
      delta[i] = gas[i] - cost[i];
      // special case
      int prev_delta = (i-1 >= 0) ? delta[i-1] : (gas[n-1] - cost[n-1]);
      if (delta[i] >= 0 && prev_delta < 0)
        pos_start = i;
      else if (delta[i] < 0)
        pos_start = -1;

      sum += delta[i];
      if (sum >= 0 && idx == -1)
        idx = pos_start;
      else if (sum < 0)
        idx = -1;
      // printf ("i=%d, delta=%d, sum=%d, idx=%d\n", i, delta[i], sum, idx);
    }

    return idx;
  }
};

int main() {
  Solution sol;
  vector<vector<int> > gas {
    {5, 0, 4, 0},
    {5, 0, 2},
    {2, 0, 2, 0},
    {5, 1, 3},
    {1, 2, 3},
    {1, 2, 3, 4, 5},
    {5},
    {5, 1},
    {1, 5},
  };

  vector<vector<int> > cost {
    {3, 3, 0, 3},
    {3, 3, 1},
    {0, 3, 0, 1},
    {3, 2, 4},
    {2, 3, 2},
    {3, 4, 5, 1, 2},
    {4},
    {6, 0},
    {0, 6},
  };

  for (int i = 0; i < gas.size(); ++i)
  {
    printf("%d\n", sol.canCompleteCircuit(gas[i], cost[i]));
  }
  
  return 0;
}