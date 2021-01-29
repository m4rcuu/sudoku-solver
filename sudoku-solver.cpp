#include <iostream>
#include <fstream>
#include <string>

class Sudoku
{
public:
    struct Exception
    {
        Exception(const std::string &r) : reason(r)
        {
        }

        std::string what() const
        {
            return reason;
        }

    private:
        std::string reason;
    };

    Sudoku();

    void loadData(int argc, const char *argv);
    bool solve();

    void print();
    void printFancy();

private:
    int data[9][9];

    void correctLenghtOfFile(std::ifstream &file);
    int correctNumber(const std::string &token);

    void readFromFile(const char *argv);
    void readFromConsole();

    bool numberInCol(int number, int col);
    bool numberInRow(int number, int row);
    bool numberInBox(int number, int rowBox, int colBox);

    bool findEmptyCell(int &row, int &col);
    bool isValidCell(int number, int row, int col);
};

//public

Sudoku::Sudoku()
{
    for (auto row = 0; row != 9; ++row)
    {
        for (auto col = 0; col != 9; ++col)
        {
            data[row][col] = 0;
        }
    }
}

void Sudoku::loadData(int argc, const char *argv)
{
    if (argc > 1)
    {
        this->readFromFile(argv);
    }
    else
    {
        std::cout<<"Enter data:\n";
        readFromConsole();
    }

    std::cout << "Data successfully loaded\n";
}

bool Sudoku::solve()
{
    int row = 0;
    int col = 0;

    if (!findEmptyCell(row, col))
    {
        return true;
    }

    for (auto number = 1; number <= 9; ++number)
    {
        if (isValidCell(number, row, col))
        {
            data[row][col] = number;
            if (solve())
            {
                return true;
            }
            data[row][col] = 0;
        }
    }
    return false;
}

void Sudoku::print()
{
    for (auto row = 0; row != 9; ++row)
    {
        for (auto col = 0; col != 9; ++col)
        {
            std::cout << data[row][col] << " ";
        }
        std::cout << "\n";
    }
}

void Sudoku::printFancy()
{
    for (auto row = 0; row != 9; ++row)
    {
        for (auto col = 0; col != 9; ++col)
        {
            if (col == 3 || col == 6)
            {
                std::cout << "| ";
            }
            std::cout << data[row][col] << " ";
        }
        if (row == 2 || row == 5)
        {
            std::cout << "\n"
                      << std::string(21, '-');
        }
        std::cout << "\n";
    }
}

//private

void Sudoku::correctLenghtOfFile(std::ifstream &file)
{
    auto length = file.tellg();
    file.seekg(0, file.beg);

    if (length != 161 && length != 162)
    {
        throw Exception("input data has incorrect number of items");
    }
}

int Sudoku::correctNumber(const std::string &token)
{
    int number = 0;
    try
    {
        number = std::stoi(token);
    }
    catch (...)
    {
        throw Exception("input data is incorrect");
    }

    if (!(number >= 0 || number <= 9))
    {
        throw Exception("input data is incorrect");
    }

    return number;
}

void Sudoku::readFromFile(const char *argv)
{
    std::string token;
    int number;

    std::ifstream file(argv, std::ifstream::ate);

    if (!file.is_open())
    {
        throw Exception("could not read file");
    }

    this->correctLenghtOfFile(file);

    for (auto row = 0; row != 9; ++row)
    {
        for (auto col = 0; col != 9; ++col)
        {
            file >> token;
            number = this->correctNumber(token);

            data[row][col] = number;
        }
    }

    file.close();
}

void Sudoku::readFromConsole()
{
    std::string token;
    int number;

    for (auto row = 0; row != 9; ++row)
    {
        for (auto col = 0; col != 9; ++col)
        {
            std::cin >> token;
            number = this->correctNumber(token);

            data[row][col] = number;
        }
    }
}

bool Sudoku::numberInCol(int number, int col)
{
    for (auto row = 0; row != 9; ++row)
    {
        if (data[row][col] == number)
        {
            return true;
        }
    }
    return false;
}

bool Sudoku::numberInRow(int number, int row)
{
    for (auto col = 0; col != 9; ++col)
    {
        if (data[row][col] == number)
        {
            return true;
        }
    }
    return false;
}

bool Sudoku::numberInBox(int number, int rowBox, int colBox)
{
    for (auto row = 0; row != 3; ++row)
    {
        for (auto col = 0; col != 3; ++col)
        {
            if (data[row + rowBox][col + colBox] == number)
            {
                return true;
            }
        }
    }
    return false;
}

bool Sudoku::findEmptyCell(int &row, int &col)
{
    for (row = 0; row != 9; ++row)
    {
        for (col = 0; col != 9; ++col)
        {
            if (data[row][col] == 0)
            {
                return true;
            }
        }
    }
    return false;
}

bool Sudoku::isValidCell(int number, int row, int col)
{
    if (!numberInRow(number, row) && !numberInCol(number, col) && !numberInBox(number, row - row % 3, col - col % 3))
    {
        return true;
    }
    return false;
}

//main

int main(int argc, char **argv)
{
    Sudoku sudoku;

    try
    {
        sudoku.loadData(argc, argv[1]);
    }
    catch (Sudoku::Exception e)
    {
        std::cerr << e.what() << '\n';
        return -1;
    }

    if (sudoku.solve())
    {
        sudoku.printFancy();
    }
    else
    {
        std::cout << "NO SOLUTION EXISTS\n";
    }

    return 0;
}