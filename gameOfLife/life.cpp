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
vector<Cell> advance(const vector<Cell> &grid, int x, int y);
void printMap(const vector<Cell> &grid, int x, int y);
int n_neighbors(const vector<Cell>& grid, int x, int y, int dx, int dy);
Cell nextGen(const Cell& c, int neighbors);

void testPrintGrid(void (*printer)(const vector<Cell>&, int, int))
{
        vector<Cell> grid(3 * 3, {'-', 0});
        vector<int> points = {0, 1, 2, 3, 7};
        for (int num : points) {
                grid[num].mark = 'x';
        }
        string expected = "xxx\nx--\n-x-";
        cout << "Expected: " << '\n';
        cout << expected << '\n';
        cout << "Result: " << '\n';
        printer(grid, 3, 3);
}

//void testNextGen(Cell (*f)(const Cell&, int))
//{
//        
//}

int main()
{
        int x = 5;
        int y = 5;
        vector<Cell> grid = makeRandomGrid(5, 5);
        greet();
        printMap(grid, x, y);
        //for (int i = 0; i < 3; i++) {
        //        grid = advance(grid, x, y);
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
                                Cell& c = grid[i * y + j];
                                c.mark = 'x';
                                c.age = 1;
                        }
                }
        }
        return grid;
}

vector<Cell> advance(const vector<Cell> &grid, int x, int y)
{
        vector<Cell> new_grid(x * y, {'-', 0});
        for (int i = 0; i < x; ++i) {
                for (int j = 0; j < x; ++j) {
                        Cell c = grid[i * y + j];
                        int neighbors = n_neighbors(grid, x, y, i, j);

                        Cell new_c = nextGen(c, neighbors);
                        new_grid[i * y + j] = new_c;
                }
        }

        return new_grid;
}

int n_neighbors(const vector<Cell>& grid, int x, int y, int dx, int dy)
{
        int neighbors = 0;

        return neighbors;
}

Cell nextGen(const Cell& c, int neighbors)
{
        Cell new_c = {'-', 0};
        if (c.age >= 10) {
                return new_c;
        }

        if (neighbors <= 1 || neighbors >= 4) {
                return new_c;
        } else if (neighbors == 2) {
                new_c = c;
                new_c.age = c.age > 0 ? c.age + 1 : c.age;
        } else {
                new_c.age = c.age + 1;
                new_c.mark = c.age > 3 ? 'X' : 'x';
        }

        return new_c;
}