#include <iostream>
#include <vector>
#include <string>
#include <random>

using std::cout, std::vector, std::string;

struct Cell {
        char mark;
        unsigned int age;
};

void greet();
void parseFile(string fileName, vector<vector<Cell>> &grid);
vector<vector<Cell>> makeRandomGrid(int x, int y);
void printMap(const vector<vector<Cell>> &grid);
vector<vector<Cell>> advance(const vector<vector<Cell>> &grid);


int main()
{
        vector<vector<Cell>> grid = makeRandomGrid(5, 5);
        greet();
        for (int i = 0; i < 3; i++) {
                grid = advance(grid);
                printMap(grid);
        }
}

void greet()
{
        cout << "Welcome to the Game of life\n\n";
}

void printMap(const vector<vector<Cell>> &grid)
{
        int x = grid.size();
        int y = grid[0].size(); 
        for (int i = 0; i < x; ++i) {
                for (int j = 0; j < y; ++j) {
                        Cell cell = grid[i][j];
                        cout << cell.mark;
                }
                cout << '\n';
        }
}

void parseFile(string filename, vector<vector<Cell>> &grid)
{

}

vector<vector<Cell>> makeRandomGrid(int x, int y)
{
        vector<vector<Cell>> grid(x, vector<Cell>(y, {'-', 0}));
        std::default_random_engine e;
        std::uniform_real_distribution<double> u(0, 1);
        for (int i = 0; i < x; ++i) {
                for (int j = 0; j < y; ++j) {
                        if (u(e) > 0.5) {
                                grid[i][j].mark = 'X';
                        }
                }
        }
        return grid;
}

vector<vector<Cell>> advance(const vector<vector<Cell>> &grid)
{

}