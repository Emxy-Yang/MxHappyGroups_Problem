#include <iostream>
#include "Normal_DFS.hpp"
#include "Memo_DFS.hpp"

std::vector<int> groups;
int n , m;
int mode;

int ans;

int main() {
    std::cin>>n>>m;
    groups.resize(n,0);
    for (auto &i : groups)
        std::cin>>i;

    std::cin>>mode;

    switch (mode) {
        case 1:      //normal DFS
            Normal_DFS normal_dfs_ans;
            ans = n - normal_dfs_ans.maxHappyGroups(m , groups);
            break;
        case 2:
            Memo_DFS memo_dfs_ans;
            ans = n - memo_dfs_ans.maxHappyGroups(m,groups);
            break;

        default:
            break;
    }



    std::cout<<ans<<std::endl;

    return 0;
}