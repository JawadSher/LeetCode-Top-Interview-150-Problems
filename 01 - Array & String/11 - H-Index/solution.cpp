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
