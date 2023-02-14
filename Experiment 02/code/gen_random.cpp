#include <fstream>
#include <iostream>

int random_int()
{
    return rand() % 100000 + 1;
}

int main()
{
    std::ofstream fout("random_numbers.txt");

    for (int i = 1; i <= 100000; i++)
    {
        fout << random_int() << "\n";
    }

    return 0;
}