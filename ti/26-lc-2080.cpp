class RangeFreqQuery {
private:
    unordered_map<int,vector<int>> pos;
    /*
        unordered_map底层是哈希表，map底层是红黑树
    */
public:
    RangeFreqQuery(vector<int>& arr) {
        for(int i=0;i<arr.size();i++)
        {
            pos[arr[i]].push_back(i);
        }
    }
    
    int query(int left, int right, int value) {
        auto it = pos.find(value);//得到value对应的下标数组

        if(it==pos.end())//如果原来的数组中根本没有要找的value
        {
            return 0;
        }

        auto& a = it->second;
        //it->first是value，it->second是对应的下标数组或者说位置数组
        return ranges::upper_bound(a,right)-ranges::lower_bound(a,left);
        //lower_bound(a,left)是在a数组中找到第一个大于等于left的位置
        //upper_bound(a,right)是在a数组中找到第一个大于right的位置
    }
};

/**
 * Your RangeFreqQuery object will be instantiated and called as such:
 * RangeFreqQuery* obj = new RangeFreqQuery(arr); //实例化，obj为实例
 * int param_1 = obj->query(left,right,value);
 */