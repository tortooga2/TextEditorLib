#include <iostream>
#include <curses.h>
#include <Buffer.h>
#include <PieceTable.h>

int main(int argc, char* argv[]){



    auto new_table = PieceTable(argv[1]);

    new_table.Add("Start", 0); //place at the start of the tree! should by the most left.
    new_table.Add("End", 40);
    new_table.Add("Middle", 22);
    new_table.Add("Left", 32);
    new_table.Add("Right", 12);
    new_table.Print();



    return 0;
}