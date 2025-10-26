//
// Created by Yang Jibin on 2025/10/26.
//

#include "Memo_DFS.hpp"
#include <vector>
#include <iostream>
#include <unordered_map>

//How to realize the Memo part ? Hash Function!!
//optimize by using mod_num to replace the initial num
//use unordered_map to store the mod vector(cnt)
//remember to optimize the func by pre_processing the situation of one/two match full

static int bs,size;
std::vector<int> cnt;

//hash state of the whole cnt vector
unsigned long long hash_state(long long current_sum) {
    unsigned long long h = current_sum;
    for (long long i = 0; i < bs; i++)
        h = (h << 6) + cnt[i];    //和ACM_OJ智斗了半小时得出的最优hash
    return h;
}

bool empty() {
    for (auto x : cnt)
        if (x) return false;
    return true;
}

std::unordered_map<unsigned long long , int> memo_mp;

int dfs(int depth , int current_sum) {
    if (empty()) { return 0; }
    unsigned long long hs = hash_state(current_sum);
    if (memo_mp.count(hs)) { return memo_mp[hs]; }

    int ans = 0 , ok = (current_sum==0);
    for (int i = 0 ; i < bs ; ++i) {
        if (cnt[i] == 0) continue;
        cnt[i]--;

        ans = std::max(ans , ok + dfs(depth+1, (current_sum + i) % bs));

        cnt[i]++;
    }

    return memo_mp[hs] = ans;
}




int Memo_DFS::maxHappyGroups(int batchSize, std::vector<int> &groups) {
    bs = batchSize;
    size = groups.size();
    cnt.resize(batchSize,0);

    for (const auto & i :groups) {
        cnt[i % batchSize] ++;
    }

    int pre_happy = cnt[0];
    cnt[0] = 0;

    //pre_process the situation of 1/2 group fill a batch
    if (batchSize % 2 == 0) {
        pre_happy += cnt[batchSize/2] / 2;
        cnt[batchSize/2] %= 2;
    }
    for (int i = 1; i < batchSize /2 ; ++i) {
        int t = std::min(cnt[i] , cnt[batchSize-i]);
        pre_happy += t;
        cnt[i] -= t;
        cnt[batchSize-i] -= t;
    }

    int ans = dfs(0 , 0) + pre_happy;

    return ans;

}
