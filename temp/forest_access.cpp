#include<iostream>
#include<vector>

using namespace std;

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

bool has_f(vector<vector<int>>& grid, int i, int j)
{
    for(int k = -3; k<3; k++)
    {
        for(int l = -3; l < 3; l++)
        {
            if (grid[i+k][j+l] == 2)
            {
                return true;
            }
                        
        }
    }
    return false;
}

//ez azt returnoli hogy van e erő accesse egy residentnek
void f(vector<vector<int>>& grid)
{
    
    for(int i = 0; i<grid.size(); i++)
    {
        for (int j = 0; j < grid[0].size(); j++)
        {
            if(grid[i][j] == 1)
            {
                cout<<has_f(grid, i,j)<<endl;
            }
        }
    }
}

int main()
{
    vector<vector<int>> grid;
    //1 lesz a ház
    //2 az erdő
    //a szélén még seg_fault van
    grid = {{2,2,2,2,0,0,0},   
            {0,0,0,0,0,0,0},  
            {0,0,0,0,0,0,0}, 
            {1,1,1,1,0,0,0},
            {0,0,0,1,1,1,1},
            {0,0,0,1,0,0,0},
            {0,0,0,0,0,0,0},
            {0,0,0,0,0,0,1}};

    f(grid);

    return 0;
}
