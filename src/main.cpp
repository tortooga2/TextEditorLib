#include <iostream>
#include <curses.h>
#include <Buffer.h>
#include <PieceTable.h>

int main(int argc, char* argv[]){



    auto new_table = PieceTable(argv[1]);

    new_table.Add("Help!", 10); //This must SPLIT!
    new_table.Add("Okay!", 0); //place at the start of the tree! should by the most left.
    new_table.Add("Mhm!", 0); //place at the start of the tree! should by the most left.
    new_table.Add("Yup!", 0); //place at the start of the tree! should by the most left.

    new_table.Print();
    new_table.add.ShowBuffer();


    return 0;
}