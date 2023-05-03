#include<iostream>
#include<vector>

using namespace std;

void dfs(vector<vector<int>>& grid, int i, int j) {
    //az i,j azok a koordináták ami a root
    int m = grid.size();
    int n = grid[0].size();
    //akkor működik ha az id >= 2 vagyis minden ami nem út és nem üres
    if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] < 2) {
        return;
    }
    //ekkor -1re állítja mert ilyen id biztos, hogy nincs
    grid[i][j] = -1;
    dfs(grid, i + 1, j);
    dfs(grid, i - 1, j);
    dfs(grid, i, j + 1);
    dfs(grid, i, j - 1);
}

//ez itt lényegében redundáns
void connected(vector<vector<int>>& grid, int i, int j) {
    dfs(grid, i, j);
}

void pr(vector<vector<int>>& grid)
{
    cout<<"------------------------------------------------"<<endl;
    for (auto& row : grid) {
        for (int cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
    cout<<"------------------------------------------------"<<endl;
}

//a main bemutatja a funkcionalitást
int main()
{
    vector<vector<int>> grid;
    grid = {{2,2,2,2},
            {2,1,1,1},
            {1,1,2,2},
            {3,0,0,0}};

    connected(grid, 0, 0);
    connected(grid, 3, 0);
    pr(grid);
    return 0;
}
