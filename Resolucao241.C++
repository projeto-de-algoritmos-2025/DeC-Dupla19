class Solution {
public:
    vector<int> diffWaysToCompute(string expression) {
        unordered_map<string, vector<int>> memo; // memoização
        return compute(expression, memo);
    }

private:
    vector<int> compute(const string& expr, unordered_map<string, vector<int>>& memo) {
        // Se já foi calculado antes, retorna do cache
        if (memo.count(expr)) return memo[expr];

        vector<int> res;
        for (int i = 0; i < expr.size(); ++i) {
            char c = expr[i];
            // Se o caractere é um operador, divide a expressão
            if (c == '+' || c == '-' || c == '*') {
                string left = expr.substr(0, i);
                string right = expr.substr(i + 1);

                // Divide e conquista: resolve as duas partes recursivamente
                vector<int> leftVals = compute(left, memo);
                vector<int> rightVals = compute(right, memo);

                // Combina os resultados das duas metades
                for (int a : leftVals) {
                    for (int b : rightVals) {
                        if (c == '+') res.push_back(a + b);
                        else if (c == '-') res.push_back(a - b);
                        else if (c == '*') res.push_back(a * b);
                    }
                }
            }
        }

        // Caso base: se a string contém apenas um número
        if (res.empty()) {
            res.push_back(stoi(expr));
        }

        // Armazena no cache antes de retornar
        memo[expr] = res;
        return res;
    }
};
