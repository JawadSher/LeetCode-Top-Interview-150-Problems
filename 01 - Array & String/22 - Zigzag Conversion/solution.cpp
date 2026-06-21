class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1) return s;

        vector<string> rows(numRows);
        bool goingDown = false;
        int currRow = 0;

        for(char c : s){
            rows[currRow] += c;

            if(currRow == 0 || currRow == numRows - 1) goingDown = !goingDown;

            currRow += goingDown ? 1 : -1;
        }

        string result = "";
        for(string &row: rows) result += row;

        return result;
        
    }
};
