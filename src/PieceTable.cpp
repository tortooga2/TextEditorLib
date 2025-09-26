#include <PieceTable.h>



PieceTable::PieceTable(const char* filename){
    original = Buffer(filename);
    add = Buffer();

    root = new PTNode;
    root->color = Color::Black;
    root->start_index=0;
    root->length = original.GetLength();
    root->subtree_len=original.GetLength();
}

void PieceTable::Add(std::string edit, size_t document_location)
{
    size_t start_index = add.GetLength();
    size_t length = edit.length();
    add.Append(edit);
    size_t subtree_len = 0;

    PTNode* new_node = new PTNode;
    new_node->bufferType = BufferType::ADD;
    new_node->color = Color::Red;
    new_node->length = length;
    new_node->start_index = start_index;
}



void PieceTable::RBInsert(PTNode* new_node, PTNode* current_node ,size_t p)
{
    if(current_node == nullptr){
        return;
    }

    size_t L = current_node->left ? current_node->left->subtree_len : 0;
    size_t R = L + current_node->length;

    if(p < L){
        if(!current_node->left){
            new_node->parent = current_node;
            new_node->subtree_len = new_node->length;
            current_node->left = new_node;
            //bubbleFixUp;
            //rbInsertFixup;
            return;
        }
        RBInsert(new_node, current_node->left, p);
    }
    else if(p >= R){
        size_t new_p = p - R;
        if(!current_node->right){
            new_node->parent = current_node;
            new_node->subtree_len = new_node->length;
            current_node->right = new_node;
            //bubbleFixUp;
            //rbInsertFixup;
            return; 
        }
        RBInsert(new_node, current_node->right, new_p);
    }
    else{
        //TODO Finish up the split action!

    }
}

Buffer PieceTable::GetOriginalBuffer()
{
    return original;
}

void PieceTable::DebugShowDetails()
{
    std::cout << root->start_index << " " << root->length << std::endl;
}
