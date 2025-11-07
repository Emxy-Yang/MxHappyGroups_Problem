//
// Created by Yang Jibin on 2025/11/7.
//
#include<iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include "Random_ALG.hpp"
#include <vector>

#include <shared_mutex>


constexpr int RANDOM_TIMES_01 = 100;
constexpr int RANDOM_TIMES_02 = 500;

const int RANDOM_SEED = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937 rng(RANDOM_SEED);

int randint(int l, int r) {
    return int(rng() % (r - l + 1) + l);
}

int rand_ans = 0;

inline int check(int batchSize, std::vector<int> &groups) {
    int temp_ans = 0;
    int current_sum = 0;
    for (auto i : groups) {
        if (current_sum == 0) {
            ++temp_ans;
        }
        current_sum = (current_sum + i) % batchSize;
    }
    rand_ans = std::max(rand_ans , temp_ans);
    return temp_ans;
}

int Random_ALG::maxHappyGroups(int batchSize, std::vector<int> &groups) {
    check(batchSize , groups);
    for (int outwards_times = 0 ; outwards_times < RANDOM_TIMES_01 ; ++outwards_times) {
        std::shuffle(groups.begin() , groups.end() , rng);
        int temp_idx = check(batchSize , groups);
        for (int inwards_times = 0 ; inwards_times < RANDOM_TIMES_02 ; ++inwards_times) {
            int idx_1 = randint(0 , groups.size()-1);
            int idx_2 = randint(0 , groups.size()-1);
            while (idx_2 == idx_1) {
                idx_2 = randint(0 , groups.size()-1);
            }
            std::swap(groups[idx_1] , groups[idx_2]);
            int temp_ans = check(batchSize , groups);
            if (temp_ans < temp_idx) {
                std::swap(groups[idx_1] , groups[idx_2]);
            }else {
                temp_idx = temp_ans;
            }
        }
    }

    return rand_ans;
}
