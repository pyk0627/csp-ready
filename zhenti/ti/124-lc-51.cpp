class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        vector<int> queens(n);
        vector<uint8_t> col(n,false),diag1(n*2-1,false),diag2(n*2-1,false);
        auto dfs=[&](this auto&& dfs,int r)->void
        {
            if(r==n)
            {
                vector<string> board(n);
                for(int i=0;i<n;i++)
                {
                    board[i]=string(queens[i],'.')+'Q'+string(n-queens[i]-1,'.');
                }
                ans.push_back(board);
                return;
            }
            for(int c=0;c<n;c++)
            {
                int rc=r-c+n-1;
                if(!col[c]&&!diag1[r+c]&&!diag2[rc])
                {
                    col[c]=diag1[r+c]=diag2[rc]=true;
                    queens[r]=c;
                    dfs(r+1);
                    col[c]=diag1[r+c]=diag2[rc]=false;
                }
            }
        };
        dfs(0);
        return ans;
    }
};