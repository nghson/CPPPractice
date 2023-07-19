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
vector<vector<Cell>> parseFile(string fileName);
vector<Cell> makeRandomGrid(int x, int y);
vector<Cell> advance(const vector<Cell> &grid);
void printMap(const vector<Cell> &grid, int x, int y);

void testPrintGrid(void (*printer)(const vector<Cell>&, int, int))
{
        vector<Cell> grid(3 * 3, {'-', 0});
        vector<int> points = {0, 1, 2, 3, 7};
        for (int num : points) {
                grid[num].mark = 'X';
        }
        string expected = "XXX\nX--\n-X-";
        cout << "Expected: " << '\n';
        cout << expected << '\n';
        cout << "Result: " << '\n';
        printer(grid, 3, 3);
}

int main()
{
        vector<Cell> grid = makeRandomGrid(5, 5);
        greet();
        printMap(grid, 5, 5);
        //for (int i = 0; i < 3; i++) {
        //        grid = advance(grid);
        //        printMap(grid);
        //}
}

void greet()
{
        cout << "Welcome to the Game of life\n\n";
}

void printMap(const vector<Cell>& grid, int x, int y)
{
        for (int i = 0; i < x; ++i) {
                for (int j = 0; j < y; ++j) {
                        Cell cell = grid[i * y + j];
                        cout << cell.mark;
                }
                cout << '\n';
        }
}

//vector<vector<Cell>> parseFile(string fileName)
//{
//
//}

vector<Cell> makeRandomGrid(int x, int y)
{
        vector<Cell> grid(x * y, {'-', 0});
        std::default_random_engine e;
        std::uniform_real_distribution<double> u(0, 1);
        for (int i = 0; i < x; ++i) {
                for (int j = 0; j < y; ++j) {
                        if (u(e) > 0.5) {
                                grid[i * y + j].mark = 'X';
                        }
                }
        }
        return grid;
}

//vector<Cell> advance(const vector<Cell> &grid)
//{
//
//}