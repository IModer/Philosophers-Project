#include <iostream>
#include <vector>
//fight me
using namespace std;

void dfs(vector<vector<int>>& grid, int i, int j) {
    int m = grid.size();
    int n = grid[0].size();
    if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] != 1) {
        return;
    }
    grid[i][j] = 2;
    dfs(grid, i + 1, j);
    dfs(grid, i - 1, j);
    dfs(grid, i, j + 1);
    dfs(grid, i, j - 1);
}

void connected(vector<vector<int>>& grid) {
    dfs(grid, 0, 0);
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

void init(vector<vector<int>> &ints, int num1, int num2)
{
    for(int i = 0; i<num1; i++)
    {
        vector<int> temp;
        for (int j = 0; j < num2; j++)
        {
            temp.push_back(0);
        }
        ints.push_back(temp);
    }

    ints[0][0] = 1;
}

void res(vector<vector<int>>& grid)
{
    for(int i = 0; i<grid.size(); i++)
    {
        vector<int> temp;
        for (int j = 0; j < grid[0].size(); j++)
        {
            if(grid[i][j] > 0)
            {
                grid[i][j] = 1;
            }
        }
    }
}

void insert(vector<vector<int>> &ints, int i, int j)
{
    //ez nem biztos hogy kell mert csak jó helyre lehet utat rakni.
    //lehet, hogy a negatív indexek miatt szar lesz -> sőt biztos
    if(i >= ints.size() || j >= ints[0].size())
    {
        cerr<<"Will result in segfault"<<endl;
    }
    else{ints[i][j] = 1;}
}

void addAndConnect(vector<vector<int>> &ints, int i, int j)
{
    //res(ints);
    insert(ints, i, j);
    connected(ints);
    pr(ints);
    res(ints);
}

int main() {
    
    vector<vector<int>> grid;
    init(grid,5,5);
    addAndConnect(grid, 1, 0);
    addAndConnect(grid, 2, 0);
    addAndConnect(grid, 4, 0);
    addAndConnect(grid, 3, 0);
    addAndConnect(grid, 0, 1);
    addAndConnect(grid, 10, 0);
    
    return 0;
}
