#pragma once
#include <iostream>
#include <string>
#include <Buffer.h>
#include <vector>


// TODO I need three data structures, my buffers, my table, and then a tree to let me walk through my table and find the entries that need to be updated quickly


enum class Color {Red, Black};


struct PTNode{
    
    BufferType bufferType = BufferType::OG; //This will consist of two possible types, either the "Add" or "Original" Buffer
    
    size_t start_index; // This is the start of the new 
    size_t length;

    size_t subtree_len = 0;

    PTNode *parent = nullptr;
    PTNode *left = nullptr;
    PTNode *right = nullptr;

    Color color = Color::Red;



    void Print(std::string content){
        std::cout << "PTNode: " << this << ", Color: " << (color == Color::Black ? "Black" : "Red") << ", Start Index: " << start_index 
        << ", Length: " << length  << ", subtree length: " << subtree_len
        <<", parent: " << parent << ", Content: " << content << std::endl;
    };

    void calcSubtreeLength(){
        subtree_len = left->subtree_len + length + right->subtree_len;
        if(parent){
            parent->calcSubtreeLength();
        }
    }
};

class PieceTable{
    private:
        Buffer original;
        
        PTNode* root;

        void RotateLeft(PTNode* x);
        void RotateRight(PTNode* x);
        void RBInsertFixup(PTNode* z);

        void RBInsert(PTNode* new_node, PTNode* current_node, size_t p);

        void SplitNode(PTNode *currentNode, PTNode *leftNode, PTNode *rightNode, size_t p);
        
        void DisplayTree(PTNode* currentNode);



    public:
        Buffer add;

        PTNode* getRoot(){
            return root;
        }


        PieceTable(const char* filename);

        void Add(std::string edit, size_t document_location);

        std::string GetNodesString(PTNode* node);

        void Print();

        Buffer GetOriginalBuffer();

        void DebugShowDetails();
};