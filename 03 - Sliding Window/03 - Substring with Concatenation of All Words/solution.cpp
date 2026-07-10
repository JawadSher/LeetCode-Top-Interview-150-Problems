// Un-optimized Solution - O(N)^2 - TLE Caused
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        unordered_map<string, int> freq, curr;
        vector<int> indices;
            
        int w_len = words[0].length();
        int w_size = words.size();
        int window = w_len * w_size;


        if ((int)s.length() < window)
            return indices;

        for(auto &word : words) freq[word]++;

        for (int i = 0; i <= s.length() - window; i++){
            curr = freq;
            bool isOk = true;
            for(int j = i; j < i + window; j+= w_len){
                string word = s.substr(j, w_len); 
                if(curr.find(word) == curr.end()) {
                    isOk = false;
                    break;
                }

                curr[word]--;

                if (curr[word] < 0) {
                    isOk = false;
                    break;
                }
            }
            
            if(isOk) indices.push_back(i);
        }   

        return indices;
    }
};
