#include <PieceTable.h>

using namespace std;

PieceTable::PieceTable(const char* filename){
    original = Buffer(filename);
    add = Buffer();

    NIL = new PTNode;
    NIL->color = Color::Black;

    root = new PTNode;
    root->color = Color::Black;
    root->start_index=0;
    root->length = original.GetLength();
    root->subtree_len=original.GetLength();
    root->right = NIL;
    root->left = NIL;
}

void PieceTable::Add(std::string edit, size_t document_location)
{
    size_t start_index = add.GetLength();
    size_t length = edit.length();
    add.Append(edit);
    

    PTNode* new_node = new PTNode;
    new_node->bufferType = BufferType::ADD;
    new_node->color = Color::Red;
    new_node->length = length;
    new_node->start_index = start_index;
    new_node->subtree_len = edit.length();
    new_node->left = NIL;
    new_node->right = NIL;
    

    RBInsert(new_node, root, document_location);

}

std::string PieceTable::GetNodesString(PTNode *node)
{
    if(node->bufferType == BufferType::OG){
        return PieceTable::original.GetString(node->start_index, node->length);
    }else{
        return PieceTable::add.GetString(node->start_index, node->length);
    }
}

void PieceTable::RBInsert(PTNode* new_node, PTNode* currentNode ,size_t p)
{
    //First we need to find the node where 0 < p < subtree_len or nil
    //Step 1: Check if p is within subtree length
    //we have three things to check.

    currentNode->Print("current node");
    new_node->Print("new node");
    
    size_t L = currentNode->left != NIL ? currentNode->left->subtree_len : 0;
    size_t R = L + currentNode->length;
    cout << "Got my shit!"  << endl;

    if(p <= L){
        cout << "Flag first condition" << endl;
        size_t local_p = p;
        if(currentNode->left != NIL) RBInsert(new_node, currentNode->left, local_p);
        else if(currentNode->left == NIL){
            cout << "ELSE/IF 1" << endl;
            currentNode->left = new_node;
            
            new_node->parent = currentNode;
            cout << "ELSE/IF 2" << endl;
            
            calcSubtreeLength(new_node);
            cout << "ELSE/IF 3" << endl;
            
            return;
        }
        
    }else if(p >= R){
        cout << "Flag second condition" << endl;
        size_t local_p = p - R;
        if(currentNode->right != NIL) RBInsert(new_node, currentNode->right, local_p);
        else if(currentNode->right == NIL){
            currentNode->right = new_node;
            new_node->parent = currentNode;
            calcSubtreeLength(new_node);
            return;
        }
        
    }else{
        
        size_t k         = p - L;                    // 1 <= k <= old_len-1
        size_t old_len   = currentNode->length;
        size_t old_start = currentNode->start_index;
        auto old_buf   = currentNode->bufferType;

        currentNode->length = k;                     // left piece
        // currentNode->start_index stays old_start

        size_t right_node_len   = old_len - k;
        size_t right_startIndex = old_start + k;

        cout << "This all worked so far" << endl;

        PTNode* right_node = new PTNode;
        right_node->length = right_node_len;
        right_node->start_index = right_startIndex;
        right_node->right = NIL;
        right_node->left = NIL;
        right_node->bufferType = currentNode->bufferType;
        right_node->color = Color::Red;

        size_t right_local_p = p + new_node->length;
        size_t new_local_p = p;

        

        RBInsert(new_node, currentNode, new_local_p);
        RBInsert(right_node, currentNode, right_local_p);
    }

    calcSubtreeLength(currentNode);

}

void PieceTable::SplitNode(PTNode *currentNode, size_t p)
{
    
}



void PieceTable::RBInsertFixup(PTNode* z)
{

}


void PieceTable::RotateLeft(PTNode* x) {

}

void PieceTable::RotateRight(PTNode *x)
{

}

void PieceTable::DisplayTree(PTNode *currentNode)
{
    
    currentNode->Print(GetNodesString(currentNode));
    if(currentNode->left != NIL){DisplayTree(currentNode->left);}
    if(currentNode->right != NIL){DisplayTree(currentNode->right);}
}

void PieceTable::Print()
{
    DisplayTree(root);
}

Buffer PieceTable::GetOriginalBuffer()
{
    return original;
}

void PieceTable::DebugShowDetails()
{
    std::cout << root->start_index << " " << root->length << std::endl;
}
