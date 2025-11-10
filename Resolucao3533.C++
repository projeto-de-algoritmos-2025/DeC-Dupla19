class Solution {
public:
    vector<int> concatenatedDivisibility(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end()); // garantir a menor permutação 
        int n = nums.size();

        vector<int> mods(n), pow10(n);
        for (int i = 0; i < n; ++i) {
            mods[i] = nums[i] % k;
            int len = to_string(nums[i]).size();
            long long p = 1;
            for (int j = 0; j < len; ++j)
                p = (p * 10) % k;
            pow10[i] = p;
        }

        // memo[mask][mod] = -1 (não visitado), 0 (falso), 1 (verdadeiro)
        vector<vector<int>> memo(1 << n, vector<int>(k, -1));
        vector<vector<int>> nextChoice(1 << n, vector<int>(k, -1));

    }
};
