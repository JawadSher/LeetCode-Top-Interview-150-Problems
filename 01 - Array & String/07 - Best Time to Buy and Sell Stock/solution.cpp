// Solution 1: O(N * N)
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int profit = 0;
        int buy = INT_MAX;
        int cell = INT_MIN;
        for(int i = 0; i < n; i++){
            if(prices[i] < buy){
                buy = prices[i];
                for(int j = i; j < n; j++){
                    int n_profit = prices[j] - buy;
                    if(n_profit > profit) profit = n_profit;
                }
            }
        }

        return profit;
    }
};

// Solution 2: O(N)
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int profit = 0;
        int buy = INT_MAX;
        int cell = INT_MIN;
        for(int i = 0; i < n; i++){
            if(prices[i] < buy && i+1 < n) {
                buy = prices[i];
                if((prices[i+1] - buy) > profit) profit = prices[i+1] - buy;
            }else {
                if((prices[i] - buy) > profit) profit = prices[i] - buy;
            }
            
        }

        return profit;
    }
};

// Solution 3: Recommended O(N)
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int mini = prices[0];
        int profit = 0;
        for(int i = 1; i < prices.size(); i++){
            int diff = prices[i] - mini;
            profit = max(profit, diff);
            mini = min(mini, prices[i]);
        }

        return profit;
    }
};
