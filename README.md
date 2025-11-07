## 一道 LeetCode 经典题的思考与启发
 > 原题参考：https://leetcode.cn/problems/maximum-number-of-groups-getting-fresh-donuts/description/
 
* 分析： 一道最优规划题，因该有 dp 解不过本人还没学， 暂时给出三种解法：
* 1、暴力DFS
* 2、基于hash(玄学) 实现的优化DFS
* 3、真正的玄学：随机算法（退火）

 
#### 1、Naive DFS Method
* 没什么好说的，主要实现累计的思路

#### 2、Memo DFS Method
* 优化1 ： 取模操作简化运算，方便以后实现
* 优化2 ： 优先处理```2-groups```拼车的情况,底层剪枝
* ##### 核心优化：  记忆化剪枝，记忆化什么特征 ？ 哈希实现（有点玄学）
```c++
// hash state of the whole cnt vector
unsigned long long hash_state(long long current_sum) {
    unsigned long long h = current_sum;
    for (long long i = 0; i < bs; i++)
        h = (h << 6) + cnt[i];    //和ACM_OJ智斗了半小时得出的最优hash
    return h;
}
```
```c++
std::unordered_map<unsigned long long , int> memo_mp;
//in function dfs
    unsigned long long hs = hash_state(current_sum);
    if (memo_mp.count(hs)) { 
        return memo_mp[hs]; 
    }
``` 

#### 3、Random ALG
> 我的代码死活通不过OJ最后三个点，希望有大佬指正
 
* 思路：整体随机打乱 + 随机交换 + 检查（若随即交换结果差则撤销，否则保留）