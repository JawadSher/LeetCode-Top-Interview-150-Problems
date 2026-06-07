// Solution 1: O(N log N)
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int n = citations.size();
        
       sort(citations.begin(), citations.end(), greater<int>());

        for(int i=0; i < n; i++){
            if(citations[i] < i+1) return i;
        }

        return n;
    }
};

// Solution 2: O(N)2
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int n = citations.size();

        for(int h = 1; h <= n; h++){
            int cites = 0;
            for(int j = 0; j < n; j++){
                if(citations[j] >= h) cites++;
            }

            if(cites < h) return h-1;
        }

        return n;
    }
};
