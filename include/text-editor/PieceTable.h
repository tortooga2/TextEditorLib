#pragma once
#include <iostream>
#include <string>
#include <Buffer.h>


// TODO I need three data structures, my buffers, my table, and then a tree to let me walk through my table and find the entries that need to be updated quickly


struct PTNode{
    PieceTable::BufferType bufferType = PieceTable::BufferType::OG; //This will consist of two possible types, either the "Add" or "Original" Buffer
    
    size_t start_index; // This is the start of the new 
    size_t length;

    size_t subtree_len = 0;

    PTNode *parent = nullptr;
    PTNode *left = nullptr;
    PTNode *right = nullptr;

    PieceTable::Color color = PieceTable::Color::Red;
};

class PieceTable{
    private:
        Buffer original;
        Buffer add;
        PTNode* root;



    public:

        enum class BufferType {OG, ADD};
        enum class Color {Red, Black};

        PieceTable(const char* filename);

        void Add(std::string edit, size_t document_location);

        void RBInsert(PTNode* new_node, PTNode* current_node, size_t p);

        Buffer GetOriginalBuffer();

        void DebugShowDetails();
};