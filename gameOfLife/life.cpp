#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

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

void testNeighbors()
{
        vector<Cell> grid(3 * 3, {'-', 0});
        vector<int> points = {0, 1, 2, 3, 7};
        for (int num : points) {
                grid[num].mark = 'x';
        }

        vector<int> expected = {2, 3, 1, 3, 5, 3, 2, 1, 1};
        cout << "E: ";
        for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                        cout << expected[i * 3 + j] << ' ';
                }
        }
        cout << '\n';

        cout << "R: ";
        for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                        cout << n_neighbors(grid, 3, 3, i, j) << ' ';
                }
        }
        cout << '\n';
}

void testPrintGrid()
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
        printMap(grid, 3, 3);
}

void testNextGen()
{
        Cell young = {'x', 2};
        Cell old = {'X', 9};
        Cell very_old = {'X', 10};
        Cell empty = {'-', 0};

        Cell n_young = nextGen(young, 2);
        Cell n_old = nextGen(old, 3);
        Cell n_very_old = nextGen(very_old, 3);
        Cell n_emp_3 = nextGen(empty, 3);
        Cell n_emp_2 = nextGen(empty, 2);

        cout << "Young cell with 2 neighbors:\n";
        cout << "Expected:\n";
        cout << 'x' << ", " << 3 << '\n';
        cout << "Result:\n";
        cout << n_young.mark << ", " << n_young.age << "\n\n";

        cout << "Old cell with 3 neighbors:\n";
        cout << "Expected:\n";
        cout << 'X' << ", " << 10 << '\n';
        cout << "Result:\n";
        cout << n_old.mark << ", " << n_old.age << "\n\n";

        cout << "Empty cell with 2 neighbors:\n";
        cout << "Expected:\n";
        cout << '-' << ", " << 0 << '\n';
        cout << "Result:\n";
        cout << n_emp_2.mark << ", " << n_emp_2.age << "\n\n";

        cout << "Empty cell with 3 neighbors:\n";
        cout << "Expected:\n";
        cout << 'x' << ", " << 1 << '\n';
        cout << "Result:\n";
        cout << n_emp_3.mark << ", " << n_emp_3.age << "\n\n";

        cout << "Very old cell with 3 neighbors:\n";
        cout << "Expected:\n";
        cout << '-' << ", " << 0 << '\n';
        cout << "Result:\n";
        cout << n_very_old.mark << ", " << n_very_old.age << "\n\n";
}

int main()
{
        int x = 5;
        int y = 5;
        vector<Cell> grid = makeRandomGrid(5, 5);
        greet();
        cout << "Game start!\n\n";
        printMap(grid, x, y);
        for (int i = 0; i < 3; i++) {
                grid = advance(grid, x, y);
                cout << "Round " << i + 1 << '\n';
                printMap(grid, x, y);
        }
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
                cout << "\n";
        }
        cout << "\n";
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

        int low_x = std::max(0, dx - 1);
        int hi_x = std::min(x - 1, dx + 1);
        int low_y = std::max(0, dy - 1);
        int hi_y = std::min(y - 1, dy + 1);

        for (int i = low_x; i <= hi_x; ++i) {
                for (int j = low_y; j <= hi_y; ++j) {
                        if (grid[i * y + j].mark != '-') {
                                ++neighbors;
                        }
                }
        }

        if (grid[dx * y + dy].mark != '-') {
                --neighbors;
        }

        return neighbors;
}

Cell nextGen(const Cell& c, int neighbors)
{
        Cell new_c = {'-', 0};
        if (c.age >= 10) {
                return new_c;
        }

        if (neighbors <= 1 || neighbors >= 4 || (neighbors == 2 && c.age == 0)) {
                return new_c;
        }

        if (neighbors == 2) {
                new_c.age = c.age > 0 ? c.age + 1 : c.age;
                new_c.mark = c.age > 3 ? 'X' : 'x';
        } else {
                new_c.age = c.age + 1;
                new_c.mark = c.age > 3 ? 'X' : 'x';
        }

        return new_c;
}