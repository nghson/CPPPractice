#include <iostream>
#include <ios>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <exception>
#include <unordered_set>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <fstream>

using std::cout, std::cin, std::vector, std::string;

struct Cell {
        char mark;
        unsigned int age;
};

void takeInput(const string& prompt, const string& error_msg,
        string& input, bool (*criteria)(const string&));
bool checkFilename(const string& filename);
bool isNumber(const string& input);
bool checkPlayInput(const string& input);

void parseFile(const string& filename, vector<Cell>& grid, int& x, int& y);
void makeRandomGrid(vector<Cell>& grid, int x, int y);

void advance(vector<Cell> &grid, vector<Cell>& newGrid, int x, int y, bool wrap);
int n_neighbors(const vector<Cell>& grid, int x, int y, int dx, int dy, bool wrap);
void updateCell(int age, int neighbors, Cell& new_c);

void clear();
void animate(int rounds, vector<Cell>& grid, vector<Cell>& newGrid, int x, int y, bool wrap);

void screenshot(std::ostream& os, const vector<Cell>& grid, int x, int y);

void initMap(vector<Cell>& grid, int& x, int& y);
void play(vector<Cell>& grid, int x, int y);
void printMap(const vector<Cell> &grid, int x, int y);

int main()
{
        cout << "Welcome to the Game of life\nGame start!\n\n";

        int x;
        int y;
        vector<Cell> grid;
        bool quit = false;
        string input;

        while (!quit) {
                initMap(grid, x, y);

                play(grid, x, y);

                takeInput("Simulate another colony (y/n)? ", "Invalid choice. Try again.",
                        input, [](const string& s) { return s == "y" || s == "n"; });
                quit = input == "n" ? true : false;
        }

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

bool checkPlayInput(const string& input)
{
        std::unordered_set<string> acceptable_input = {"a", "t", "s", "q"};
        return acceptable_input.find(input) != acceptable_input.end();
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
        grid = vector<Cell>(x * y, {'-', 0});
        for (int i = 0; i < x; ++i) {
                std::getline(file, s);
                for (int j = 0; j < y; ++j) {
                        if (s[j] == 'X') {
                                Cell& c = grid[i * y + j];
                                c.mark = 'x';
                                c.age = 1;
                        }
                }
        }
        file.close();
}

void makeRandomGrid(vector<Cell>& grid, int x, int y)
{
        std::random_device rd;
        std::default_random_engine e(rd());
        std::uniform_real_distribution<double> u(0, 1);
        grid = vector<Cell>(x * y, {'-', 0});
        for (int i = 0; i < x; ++i) {
                for (int j = 0; j < y; ++j) {
                        if (u(e) > 0.5) {
                                Cell& c = grid[i * y + j];
                                c.mark = 'x';
                                c.age = 1;
                        }
                }
        }
}

void advance(vector<Cell>& grid, vector<Cell>& newGrid, int x, int y, bool wrap)
{
        for (int i = 0; i < x; ++i) {
                for (int j = 0; j < y; ++j) {
                        const Cell& c = grid[i * y + j];
                        int neighbors = n_neighbors(grid, x, y, i, j, wrap);
                        updateCell(c.age, neighbors, newGrid[i * y + j]);
                }
        }
        grid = newGrid;
}

int n_neighbors(const vector<Cell>& grid, int x, int y, int dx, int dy, bool wrap)
{
        int neighbors = 0;
        int low_x = wrap ? dx - 1 : std::max(0, dx - 1);
        int hi_x = wrap ? dx + 1 : std::min(x - 1, dx + 1);
        int low_y = wrap ? dy - 1 : std::max(0, dy - 1);
        int hi_y = wrap ? dy + 1 : std::min(y - 1, dy + 1);

        for (int r = low_x; r <= hi_x; ++r) {
                for (int c = low_y; c <= hi_y; ++c) {
                        int i = (r + x) % x;
                        int j = (c + y) % y;
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

void clear()
{
#if defined _WIN32
        system("cls");
        //clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        system("clear");
        //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
#elif defined (__APPLE__)
        system("clear");
#endif
}

void animate(int rounds, vector<Cell>& grid, vector<Cell>& newGrid, int x, int y, bool wrap)
{
        for (int i = 0; i < rounds; ++i) {
                clear();
                advance(grid, newGrid, x, y, wrap);
                printMap(grid, x, y);
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
}

void screenshot(std::ostream& os, const vector<Cell>& grid, int x, int y)
{
        for (int i = 0; i < x; ++i) {
                for (int j = 0; j < y; ++j) {
                        os << grid[i * y + j].mark;
                }
                os << '\n';
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
        string command;
        vector<Cell> newGrid(x * y, {'-', 0});
        takeInput("Should the simulation wrap around the grid (y/n)? ", "Invalid choice. Try again.",
                command, [](const string& s) { return s == "y" || s == "n"; });
        bool wrap = command == "y" ? true : false;
        printMap(grid, x, y);
        while (!quit) { 
                takeInput("a)nimate, t)ick, s)creenshot, q)uit? ", "Invalid choice. Try again.",
                        command, checkPlayInput);
                if (command == "t") {
                        advance(grid, newGrid, x, y, wrap);
                        printMap(grid, x, y);
                }
                else if (command == "q") {
                        quit = true;
                } else if (command == "s") {
                        cout << "Save to file? ";
                        std::getline(cin, command);
                        std::ofstream savefile(command);
                        if (!savefile) {
                                cout << "Can't create file.\n";
                        } else {
                                screenshot(savefile, grid, x, y);
                                savefile.close();
                        }
                } else if (command == "a") {
                        takeInput("How many frames? ", "Illegal integer format. Try again.",
                                command, isNumber);
                        int rounds = std::stoi(command);
                        animate(rounds, grid, newGrid, x, y, wrap);
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
