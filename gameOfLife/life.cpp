#include <iostream>
#include <ios>
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

void takeInput(const string& prompt, const string& error_msg,
        string& input, bool (*criteria)(const string&));
bool checkFilename(const string& filename);
bool isNumber(const string& input);

void parseFile(const string& filename, vector<Cell>& grid, int& x, int& y);
void makeRandomGrid(vector<Cell>& grid, int x, int y);

void advance(vector<Cell> &grid, vector<Cell>& newGrid, int x, int y);
int n_neighbors(const vector<Cell>& grid, int x, int y, int dx, int dy);
void updateCell(int age, int neighbors, Cell& new_c);

void initMap(vector<Cell>& grid, int& x, int& y);
void play(vector<Cell>& grid, int x, int y);
void printMap(const vector<Cell> &grid, int x, int y);

int main()
{
        cout << "Welcome to the Game of life\nGame start!\n\n";

        cout << "Read from (f)ile, or (r)andom? ";
        int x;
        int y;
        vector<Cell> grid;
        initMap(grid, x, y);

        printMap(grid, x, y);
        play(grid, x, y);
        cout << "Have a nice life!" << std::endl;
}

void takeInput(const string& prompt, const string& error_msg,
        string& input, bool (*criteria)(const string&))
{
        bool correct = false;
        while (!correct) {
                cout << prompt; 
                std::getline(cin, input);
                if (cin && criteria(input)) {
                        correct = true;
                } else {
                        cout << error_msg << std::endl;
                }
        }
}

bool checkFilename(const string& filename)
{
        std::ifstream file(filename);
        if (file) {
                return true;
        } else {
                return false;
        }
}

bool isNumber(const string& input)
{
        string::const_iterator it = input.begin();
        while (it != input.end() && std::isdigit(*it)) {
                ++it;
        }
        return !input.empty() && it == input.end();
}

void parseFile(const string& filename, vector<Cell>& grid, int& x, int& y)
{
        std::ifstream file(filename);
        if (!file) {
                throw std::runtime_error("There is no file " + filename);
        }

        string s;
        std::getline(file, s);
        x = std::stoi(s);
        std::getline(file, s);
        y = std::stoi(s);
        vector<Cell> n_grid(x * y, {'-', 0});
        for (int i = 0; i < x; ++i) {
                std::getline(file, s);
                for (int j = 0; j < y; ++j) {
                        if (s[j] == 'X') {
                                Cell& c = n_grid[i * y + j];
                                c.mark = 'x';
                                c.age = 1;
                        }
                }
        }
        grid = n_grid;

        file.close();
}

void makeRandomGrid(vector<Cell>& grid, int x, int y)
{
        std::default_random_engine e;
        std::uniform_real_distribution<double> u(0, 1);
        vector<Cell> n_grid(x * y, {'-', 0});
        for (int i = 0; i < x; ++i) {
                for (int j = 0; j < y; ++j) {
                        if (u(e) > 0.5) {
                                Cell& c = n_grid[i * y + j];
                                c.mark = 'x';
                                c.age = 1;
                        }
                }
        }
        grid = n_grid;
}

void advance(vector<Cell>& grid, vector<Cell>& newGrid, int x, int y)
{
        for (int i = 0; i < x; ++i) {
                for (int j = 0; j < y; ++j) {
                        const Cell& c = grid[i * y + j];
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
                        if (grid[i * y + j].mark != '-' && !(i == dx && j == dy)) {
                                ++neighbors;
                        }
                }
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

void initMap(vector<Cell>& grid, int& x, int& y)
{
        string input;
        takeInput("Read from (f)ile, or (r)andom? ", "Invalid choice, try again.",
                input, [](const string& s) { return (s == "f" || s == "r"); });
        if (input == "f") {
                takeInput("Grid input file name? ", "Unable to open that file. Try again.",
                        input, checkFilename);
                parseFile(input, grid, x, y);
        } else if (input == "r") {
                takeInput("How many rows? ", "Please put a valid nubmer.",
                        input, isNumber);
                x = std::stoi(input);
                takeInput("How many columns? ", "Please put a valid nubmer.",
                        input, isNumber);
                y = std::stoi(input);
                makeRandomGrid(grid, x, y);
        }
}

void play(vector<Cell>& grid, int x, int y)
{
        bool quit = false;
        char command;
        vector<Cell> newGrid(x * y, {'-', 0});
        while (!quit) { 
                cout << "a)nimate, t)ick, s)creenshot, q)uit? ";
                cin >> command;
                if (command == 't') {
                        advance(grid, newGrid, x, y);
                        printMap(grid, x, y);
                }
                else if (command == 'q') {
                        quit = true;
                } else {
                        cout << "Unknown option, try again\n";
                }
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
}
