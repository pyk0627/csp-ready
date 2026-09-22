class Solution {
    string digits;
    vector<string> str={"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
    vector<string> ans;
    string path;
    void dfs(string digits,int depth)
    {
        if(depth==digits.size())
        {
            ans.push_back(path);
            return;
        }
        int num=digits[depth]-'0';
        for(int i=0;i<str[num].size();i++)
        {
            path[depth]=str[num][i];
            dfs(digits,depth+1);
        }
    }
public:
    vector<string> letterCombinations(string digits) {
        this->digits=digits;
        path.resize(digits.size());
        dfs(digits,0);
        return ans;
    }
};