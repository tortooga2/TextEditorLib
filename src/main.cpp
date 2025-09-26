#include <iostream>
#include <curses.h>
#include <Buffer.h>
#include <PieceTable.h>

int main(int argc, char* argv[]){



    auto new_table = PieceTable(argv[1]);

    new_table.GetOriginalBuffer().ShowBuffer();
    new_table.DebugShowDetails();


    return 0;
}