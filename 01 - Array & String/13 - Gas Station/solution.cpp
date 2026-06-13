class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int tank = 0;
        int index = 0;
        int n = gas.size();
        int i = 0;
        int total = 0;
        
        while (i < n ){
            total += gas[i] - cost[i]; 
            tank  += gas[i] - cost[i];
            if(tank < 0){
                index = i+1;
                tank = 0;
            }
            i++;
        }

        if(total < 0) return -1;

        return index;
    }
};
