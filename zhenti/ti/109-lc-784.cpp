class Solution {
    string s;
    vector<string> ans;
    string temp;
    void dfs(int depth)
    {
        if(depth==s.size())
        {
            ans.push_back(temp);
            return;
        }
        if('a'<=s[depth]&&s[depth]<='z')
        {
            temp+=s[depth];
            dfs(depth+1);
            temp.erase(temp.size()-1);

            s[depth]=s[depth]-'a'+'A';
            temp+=s[depth];
            dfs(depth+1);
            temp.erase(temp.size()-1);
        }else if('A'<=s[depth]&&s[depth]<='Z')
        {
            temp+=s[depth];
            dfs(depth+1);
            temp.erase(temp.size()-1);

            s[depth]=s[depth]-'A'+'a';
            temp+=s[depth];
            dfs(depth+1);
            temp.erase(temp.size()-1);
        }else
        {
            temp+=s[depth];
            dfs(depth+1);
            temp.erase(temp.size()-1);
        }

    }
public:
    vector<string> letterCasePermutation(string s) {
        this->s=s;
        dfs(0);
        return ans;
    }
};