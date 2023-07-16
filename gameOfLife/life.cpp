#include <iostream>
#include <vector>

using std::cout, std::vector;

void greet();
void printMap(vector<vector<char>> &grid);


int main()
{
        vector<vector<char>> grid(3, vector<char>(4, '-'));
        greet();
        printMap(grid);
}

void greet()
{
        cout << "Welcome to the Game of life\n";
}

void printMap(vector<vector<char>> &grid)
{
        int x = grid.size();
        int y = grid[0].size(); 
        for (int i = 0; i < x; ++i) {
                for (int j = 0; j < y; ++j) {
                        cout << grid[i][j];
                }
                cout << '\n';
        }
}