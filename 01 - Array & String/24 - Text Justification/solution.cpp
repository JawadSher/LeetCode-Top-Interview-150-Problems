class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        int n = words.size();
        vector<string> ans;
        int i = 0;

        while (i < n){
            int charsCount = words[i].length();
            int j = i + 1;
            int spacesBtwWords = 0;

            while(j < n && charsCount + spacesBtwWords + words[j].length() + 1 <= maxWidth){
                charsCount += words[j].length();
                spacesBtwWords++;
                j++;
            }

            int allSpacesInLine = maxWidth - charsCount;
            int eachSpaceTakesSpacesBtwWords = spacesBtwWords <= 0 ? 0 : allSpacesInLine / spacesBtwWords;
            int extraLeftSpace = spacesBtwWords <= 0 ? 0 : allSpacesInLine % spacesBtwWords;

            string line = "";
            bool isLastLine = (j == n);
            for(int k = i; k < j; k++){
                line += words[k];

                if(k == j-1) break;

                 if(isLastLine || spacesBtwWords == 0){
                    line += " ";
                }else{
                      for(int s = 0; s < eachSpaceTakesSpacesBtwWords; s++){
                        line += " ";

                        if(extraLeftSpace > 0){
                            line += " ";
                            extraLeftSpace--;
                        }
                    }
                }
            }

            if(isLastLine || spacesBtwWords  == 0) while(line.size() < maxWidth) line += " ";

            ans.push_back(line);

            i = j;
        }

        return ans;
    }
};
