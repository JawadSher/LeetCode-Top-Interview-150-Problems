class Solution {
public:
    string reverseWords(string s) {
        string sentence = "";
        stringstream ss(s);
        string word;

        while (ss >> word){
            if(sentence.empty()){
                sentence = word;
            }else{
                sentence = word + ' ' + sentence;
            }
        }

        return sentence;
    }
};
