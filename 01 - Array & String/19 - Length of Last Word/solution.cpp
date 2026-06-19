// Optimized: O(N)
class Solution {
public:
    int lengthOfLastWord(string s) {
        int count = 0;
        
        for(int i = s.length()-1; i >= 0; i--){
            if(s[i] == ' ' && count > 0) return count;
            if(s[i] != ' ') count++;
        }
        return count;
    }
};

// Un-Optimized: O(N + N)
class Solution {
public:
    string trimAllExtraSpaces(const string &str) {
        istringstream stream(str);
        string word;
        string result;

        while (stream >> word) {
            if (!result.empty()) {
                result += " ";
            }
            result += word;
        }
        return result;
    }

    int lengthOfLastWord(string s) {
        int count = 0;
        string sentence = trimAllExtraSpaces(s);
        
        for(int i = sentence.length()-1; i >= 0; i--){
            if(sentence[i] == ' ') return count;
            count++;
        }
        return count;
    }
};
