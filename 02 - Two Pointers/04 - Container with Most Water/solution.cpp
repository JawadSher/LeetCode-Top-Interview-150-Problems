class Solution {
public:
    int maxArea(vector<int>& height) {
        int n = height.size();
        int j = n-1;
        int i = 0;
        int area = 0;
        while (i < j){
            int width = j - i;
            int h = min(height[i], height[j]);
            area = max(area, width * h);

            if(height[i] < height[j]) i++;
            else j--;
        }

        return area;
    }
};
