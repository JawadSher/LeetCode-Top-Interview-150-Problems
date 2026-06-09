class RandomizedSet {
    vector<int> vec;
    unordered_map<int, int> mp;
public:
    RandomizedSet() {}
    bool insert(int val) {
        if(!mp.count(val)){
            vec.push_back(val);
            int index = vec.size() - 1;
            mp[val] = index;
            return true;
        }

        return false;
    }
    
    bool remove(int val) {
        if(mp.count(val)){
            int index = mp.find(val)->second; // [10, 20, 30, 40] val = 20 = 1
            mp[vec[vec.size()-1]] = index;
            swap(vec[index], vec[vec.size()-1]); // [10, 40, 30, 20]
            mp.erase(val);
            vec.pop_back();
            return true;
        }

        return false;
    }
    
    int getRandom() {
        return vec[rand() % vec.size()];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
