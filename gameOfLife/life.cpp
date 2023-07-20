#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <fstream>
#include <exception>

using std::cout, std::vector, std::string;

struct Cell {
        char mark;
        unsigned int age;
};

struct GridMap {
        vector<Cell> grid;
        int x;
        int y;
};

void greet();
GridMap parseFile(const string& filename);
vector<Cell> makeRandomGrid(int x, int y);

vector<Cell> advance(const vector<Cell> &grid, int x, int y);
int n_neighbors(const vector<Cell>& grid, int x, int y, int dx, int dy);
Cell nextGen(const Cell& c, int neighbors);

void printMap(const vector<Cell> &grid, int x, int y);

int main()
{
        greet();
        cout << "Game start!\n\n";
        string filename = "grid.txt";

        //int x = 5;
        //int y = 5;

        //vector<Cell> grid = makeRandomGrid(5, 5);
        GridMap g_map = parseFile(filename);

        printMap(g_map.grid, g_map.x, g_map.y);

        vector<Cell> grid = g_map.grid;
        int x = g_map.x;
        int y = g_map.y;
        for (int i = 0; i < 5; i++) {
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

GridMap parseFile(const string& filename)
{
        std::ifstream file(filename);
        if (!file) {
                throw std::runtime_error("There is no file " + filename);
        }

        int x;
        int y;
        file >> x >> y >> std::ws;
        vector<Cell> grid(x * y, {'-', 0});

        string s;
        for (int i = 0; i < x; ++i) {
                std::getline(file, s);
                for (int j = 0; j < y; ++j) {
                        if (s[j] == 'X') {
                                grid[i * y + j] = Cell{'x', 1};
                        }
                }
        }

        GridMap g_map = {grid, x, y};
        file.close();
        return g_map;
}

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