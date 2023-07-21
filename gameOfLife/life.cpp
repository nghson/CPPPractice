#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <fstream>
#include <exception>

using std::cout, std::cin, std::vector, std::string;

struct Cell {
        char mark;
        unsigned int age;
};

struct GridMap {
        vector<Cell> grid;
        int x;
        int y;
};

void initMap(char source, const string& filename, int x, int y, GridMap& g_map);
void parseFile(const string& filename, GridMap& g_map);
vector<Cell> makeRandomGrid(int x, int y);

void advance(vector<Cell> &grid, vector<Cell>& newGrid, int x, int y);
int n_neighbors(const vector<Cell>& grid, int x, int y, int dx, int dy);
void updateCell(int age, int neighbors, Cell& new_c);

void printMap(const vector<Cell> &grid, int x, int y);

int main()
{
        cout << "Welcome to the Game of life\nGame start!\n\n";

        char source;
        string filename;
        int x;
        int y;
        //cout << "Read from (f)ile, or (r)andom? ";
        //cin >> source;
        //if (source == 'f') {
        //        cout << "Grid input file name? ";
        //        cin  >> filename;
        //} else if (source == 'r') {
        //        cout << "How many rows? ";
        //        cin >> x;
        //        cout << "How many columns? ";
        //        cin >> y;
        //} else {
        //        cout << "Unknown option, try again";
        //}

        GridMap g_map;
        //initMap(source, filename, x, y, g_map);
        initMap('f', "grid.txt", x, y, g_map);

        printMap(g_map.grid, g_map.x, g_map.y);

        vector<Cell>& grid = g_map.grid;
        x = g_map.x;
        y = g_map.y;
        vector<Cell> newGrid(x * y, {'-', 0});

        for (int i = 0; i < 20; i++) {
                advance(grid, newGrid, x, y);
                cout << "Round " << i + 1 << '\n';
                printMap(grid, x, y);
        }
}

void initMap(char source, const string& filename, int x, int y, GridMap& g_map)
{
        if (source == 'f') {
                parseFile(filename, g_map);
        }
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

void parseFile(const string& filename, GridMap& g_map)
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

        g_map = {grid, x, y};
        file.close();
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

void advance(vector<Cell>& grid, vector<Cell>& newGrid, int x, int y)
{
        for (int i = 0; i < x; ++i) {
                for (int j = 0; j < y; ++j) {
                        Cell c = grid[i * y + j];
                        int neighbors = n_neighbors(grid, x, y, i, j);

                        updateCell(c.age, neighbors, newGrid[i * y + j]);
                }
        }

        grid = newGrid;
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

void updateCell(int age, int neighbors, Cell& new_c)
{
        if (age >= 10 || neighbors <= 1 || neighbors >= 4 || (neighbors == 2 && age == 0)) {
                new_c.mark = '-';
                new_c.age = 0;
        } else {
                new_c.age = age + 1;
                new_c.mark = age >= 4 ? 'X' : 'x';
        }
}