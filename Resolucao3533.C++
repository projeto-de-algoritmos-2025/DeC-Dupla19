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

        function<bool(int, int)> dfs = [&](int mask, int mod) -> bool {
            if (mask == (1 << n) - 1)
                return mod == 0;

            int &res = memo[mask][mod];
            if (res != -1) return res;

            for (int i = 0; i < n; ++i) {
                if (!(mask & (1 << i))) {
                    int newMod = (mod * pow10[i] + mods[i]) % k;
                    if (dfs(mask | (1 << i), newMod)) {
                        nextChoice[mask][mod] = i;
                        return res = 1;
                    }
                }
            }
            return res = 0;
        };

        if (!dfs(0, 0))
            return {};

        // reconstrução da resposta
        vector<int> ans;
        int mask = 0, mod = 0;
        while (mask != (1 << n) - 1) {
            int i = nextChoice[mask][mod];
            ans.push_back(nums[i]);
            int newMod = (mod * pow10[i] + mods[i]) % k;
            mask |= (1 << i);
            mod = newMod;
        }
        
        return ans;

    }
};
