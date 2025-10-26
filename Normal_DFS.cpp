//
// Created by Yang Jibin on 2025/10/26.
//

#include "Normal_DFS.hpp"
#include <iostream>
#include <vector>

//a normal DFS solve to the quest
//with o(n!) time complexity

int bs;
std::vector<bool> IsVst;

int dfs(int depth , int current_sum , std::vector<int> &groups ) {
    if (depth == groups.size()) { return 0; }

    int ans = 0;
    int ok = (current_sum == 0) ;   //ok stands for Is the batch of people get empty car

    for (int i = 0; i < groups.size() ; ++i) {
        if (!IsVst[i]) {
            IsVst[i] = true;

            ans = std::max(ans, ok + dfs(depth+1 , (current_sum + groups[i]) % bs , groups));
            //max sum of the branch

            IsVst[i] = false;
        }
    }

    return ans;
}


int Normal_DFS::maxHappyGroups(int batchSize, std::vector<int> &groups) {
    bs = batchSize;
    IsVst.resize(groups.size(),false);

    int ans = dfs(0 , 0, groups);

    return ans;
}
