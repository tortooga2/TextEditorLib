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

    size_t subtree_len;

    PTNode *parent;
    PTNode *left;
    PTNode *right;

    Color color = Color::Red;

    void SetLeft(PTNode* x) {left = x;}
    void SetRight(PTNode* x) {right = x;}
    PTNode* GetParent() {return parent;}
    


    void Print(std::string content){
        std::cout << "PTNode: " << this << ", Color: " << (color == Color::Black ? "Black" : "Red") << ", Start Index: " << start_index 
        << ", Length: " << length  << ", subtree length: " << subtree_len
        <<", parent: " << parent << ", Content: " << content << std::endl;
    };

   
};

class PieceTable{
    private:
        Buffer original;
        
        PTNode* root;
        PTNode* NIL;

        void RotateLeft(PTNode* x);
        void RotateRight(PTNode* x);
        void RBInsertFixup(PTNode* z);

        void RBInsert(PTNode* new_node, PTNode* current_node, size_t p);

        void SplitNode(PTNode *currentNode, size_t p);
        
        void DisplayTree(PTNode* currentNode);

        void calcSubtreeLength(PTNode* n){
            if(!n || n == NIL) return;

            size_t new_subtree = 0;
            if( n->left != NIL){
                new_subtree += n->left->subtree_len;
            }
            
            if( n->right != NIL){
                new_subtree += n->right->subtree_len;
            }
            new_subtree += n->length;
            
            n->subtree_len = new_subtree;
            
            if(n->parent != NIL){
                calcSubtreeLength(n->parent);
            }
            
        }



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