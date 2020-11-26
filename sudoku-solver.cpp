#include <iostream>
#include <fstream>
#include <string>

struct InputData
{
    int argc;
    char *argv;
};

bool loadData(InputData &input, unsigned short data[9][9]);
bool correctLengthOfFile(std::ifstream &file);
bool correctNumber(std::string &token, unsigned short &number);

bool numberInCol(unsigned short data[9][9], unsigned short &number, unsigned short &col);
bool numberInRow(unsigned short data[9][9], unsigned short &number, unsigned short &row);
bool numberInBox(unsigned short data[9][9], unsigned short &number, unsigned short rowBox, unsigned short colBox);
bool findEmptyCell(unsigned short data[9][9], unsigned short &row, unsigned short &col);
bool isValidCell(unsigned short data[9][9], unsigned short &number, unsigned short &row, unsigned short &col);

bool solveSudoku(unsigned short data[9][9]);

void printSudoku(unsigned short data[9][9]);
void printFancySudoku(unsigned short data[9][9]);

int main(int argc, char **argv)
{
    InputData dataStruct{argc, argv[1]};
    unsigned short sudokuData[9][9];

    if (!loadData(dataStruct, sudokuData))
    {
        return -1;
    }

    if (solveSudoku(sudokuData))
    {
        //printSudoku(sudokuData);
        printFancySudoku(sudokuData);
    }
    else
    {
        std::cout << "NO SOLUTION EXISTS" << std::endl;
    }

    return 0;
}

bool loadData(InputData &input, unsigned short data[9][9])
{
    std::string token;
    unsigned short number;

    //input from file
    if (input.argc > 1)
    {
        std::ifstream file(input.argv);

        if (!file.is_open())
        {
            std::cout << "error: could not read file " << input.argv << std::endl;
            return false;
        }

        if (!correctLengthOfFile(file))
        {
            std::cout << "error: input data has incorrect number of items " << std::endl;
            return false;
        }

        for (auto row = 0; row < 9; ++row)
        {
            for (auto col = 0; col < 9; ++col)
            {
                file >> token;
                if (!correctNumber(token, number))
                {
                    std::cout << "error: input data is incorrect " << token << std::endl;
                    return false;
                }
                data[row][col] = number;
            }
        }

        file.close();
    }

    //input from console
    else
    {
        for (auto row = 0; row < 9; ++row)
        {
            for (auto col = 0; col < 9; ++col)
            {
                std::cin >> token;
                if (!correctNumber(token, number))
                {
                    std::cout << "error: input data is incorrect " << token << std::endl;
                    return false;
                }
                data[row][col] = number;
            }
        }
    }

    std::cout << "Data successfully loaded" << std::endl
              << std::endl;
    return true;
}

bool correctLengthOfFile(std::ifstream &file)
{
    file.seekg(0, file.end);
    auto length = file.tellg();
    file.seekg(0, file.beg);

    if (length != 161 && length != 162)
    {
        return false;
    }
    return true;
}

bool correctNumber(std::string &token, unsigned short &number)
{
    try
    {
        number = std::stoi(token);
    }
    catch (...)
    {
        return false;
    }

    if (!(number >= 0 || number <= 9))
    {
        return false;
    }

    return true;
}

void printSudoku(unsigned short data[9][9])
{
    for (auto row = 0; row < 9; ++row)
    {
        for (auto col = 0; col < 9; ++col)
        {
            std::cout << data[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

void printFancySudoku(unsigned short data[9][9])
{
    for (auto row = 0; row < 9; ++row)
    {
        for (auto col = 0; col < 9; ++col)
        {
            if (col == 3 || col == 6)
            {
                std::cout << "| ";
            }
            std::cout << data[row][col] << " ";
        }
        if (row == 2 || row == 5)
        {
            std::cout << std::endl;
            std::cout << std::string(21, '-');
        }
        std::cout << std::endl;
    }
}

bool numberInCol(unsigned short data[9][9], unsigned short &number, unsigned short &col)
{
    for (auto row = 0; row < 9; ++row)
    {
        if (data[row][col] == number)
        {
            return true;
        }
    }
    return false;
}

bool numberInRow(unsigned short data[9][9], unsigned short &number, unsigned short &row)
{
    for (auto col = 0; col < 9; ++col)
    {
        if (data[row][col] == number)
        {
            return true;
        }
    }
    return false;
}

bool numberInBox(unsigned short data[9][9], unsigned short &number, unsigned short rowBox, unsigned short colBox)
{
    for (auto row = 0; row < 3; ++row)
    {
        for (auto col = 0; col < 3; ++col)
        {
            if (data[row + rowBox][col + colBox] == number)
            {
                return true;
            }
        }
    }
    return false;
}

bool findEmptyCell(unsigned short data[9][9], unsigned short &row, unsigned short &col)
{
    for (row = 0; row < 9; ++row)
    {
        for (col = 0; col < 9; ++col)
        {
            if (data[row][col] == 0)
            {
                return true;
            }
        }
    }
    return false;
}

bool isValidCell(unsigned short data[9][9], unsigned short &number, unsigned short &row, unsigned short &col)
{
    if (!numberInRow(data, number, row) && !numberInCol(data, number, col) && !numberInBox(data, number, row - row % 3, col - col % 3))
    {
        return true;
    }
    return false;
}

bool solveSudoku(unsigned short data[9][9])
{
    unsigned short row = 0;
    unsigned short col = 0;

    if (!findEmptyCell(data, row, col))
    {
        return true;
    }
    for (unsigned short number = 1; number <= 9; ++number)
    {
        if (isValidCell(data, number, row, col))
        {
            data[row][col] = number;
            if (solveSudoku(data))
            {
                return true;
            }
            data[row][col] = 0;
        }
    }
    return false;
}