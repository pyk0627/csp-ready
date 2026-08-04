class Solution {
    int limit;
    vector<vector<int>> attribute;
    vector<int> materials;
    vector <vector<int>> cookbooks;
    int len;
    int ans = 0;
    int x = 0;
    int y = 0;
    void dfs(int depth) {
        if (depth == len) {
            if(y>=limit)
            {
                ans = max(ans, x);
            }
            return;
        }
        dfs(depth + 1);

        int f = 1;
        for (int i = 0; i < materials.size(); i++) {
            if (materials[i] < cookbooks[depth][i]) {
                f = 0;
                break;
            }
        }
        if (f) {
            for (int i = 0; i < materials.size(); i++) {
                materials[i] -= cookbooks[depth][i];
            }
            x += attribute[depth][0];
            y += attribute[depth][1];
            dfs(depth + 1);
            x -= attribute[depth][0];
            y -= attribute[depth][1];
            for (int i = 0; i < materials.size(); i++) {
                materials[i] += cookbooks[depth][i];
            }
        }
    }

public:
    int perfectMenu(vector<int>& materials, 
                    vector<vector<int>>& cookbooks,
                    vector<vector<int>>& attribute, 
                    int limit) 
    {
        this->attribute = attribute;
        this->materials = materials;
        this->limit = limit;
        this->cookbooks = cookbooks;
        len = attribute.size();
        dfs(0);
        if(ans==0)
        {
            return -1;
        }else
        {
            return ans;
        }
    }
};
