class Solution {
public:
    bool isPalindrome(string s) {
        string word = "";

        for(int i = 0; i < s.length(); i++){
            if(isalnum(s[i])) word += tolower(s[i]);
        }

        int start = 0;
        int end = word.length() -1;
        while(start < end){
            if(word[start] != word[end]) return false;

            start++;
            end--;
        }


        return true;
    }
};
