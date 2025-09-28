#include <PieceTable.h>

using namespace std;

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
    

    PTNode* new_node = new PTNode;
    new_node->bufferType = BufferType::ADD;
    new_node->color = Color::Red;
    new_node->length = length;
    new_node->start_index = start_index;
    new_node->subtree_len = edit.length();
    

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

void PieceTable::RBInsert(PTNode* new_node, PTNode* current_node ,size_t p)
{

    if(current_node == nullptr){
        return;
    }


    size_t L = current_node->left ? current_node->left->subtree_len : 0;
    size_t R = L + current_node->length;

    if(p < L){
        //if the current node is a leaf
        if(!current_node->left){
            new_node->parent = current_node;
            new_node->subtree_len = new_node->length;
            current_node->left = new_node;
            RBInsertFixup(new_node);
            return;
        }
        RBInsert(new_node, current_node->left, p);
        
    }
    else if(p >= R){
        size_t new_p = p - R;

        //if the current node is a leaf
        if(!current_node->right){
            new_node->parent = current_node;
            new_node->subtree_len = new_node->length;
            current_node->right = new_node;
            RBInsertFixup(new_node);
            return; 
        }
        RBInsert(new_node, current_node->right, new_p);
        
    }
    else{

        //TODO Finish up the split action!
        PTNode* new_left = new PTNode;
        PTNode* new_right = new PTNode;


        //Replace current node with
        if(current_node->parent){
            if(current_node->parent->left && current_node->parent->left == current_node){
                current_node->parent->left = new_node;
            }else if(current_node->parent->right && current_node->parent->right == current_node){
                current_node->parent->right = new_node;
            }
            //Set new nodes parent to the 
            new_node->parent = current_node->parent;
        }else{
            //this is a root node;
            root = new_node;
            new_node->color = Color::Black;
            //Keep new_node's parent nullptr;
        }

        

        size_t local_L = current_node->left ? current_node->left->subtree_len : 0;
        size_t local = p - local_L; 
        //Now we create our left and right nodes after splitting our node.
        SplitNode(current_node, new_left, new_right, local);
        new_left->parent = new_node;
        new_right->parent = new_node;
        new_node->left = new_left;
        new_node->right = new_right;


        new_node->calcSubtreeLength();

        RBInsertFixup(new_node);
        RBInsertFixup(new_left);
        RBInsertFixup(new_right);
        delete current_node;
        

    }
    
}

void PieceTable::SplitNode(PTNode *currentNode, PTNode *leftNode, PTNode *rightNode, size_t p)
{
    //copy buffer type
    leftNode->bufferType = currentNode->bufferType;
    rightNode->bufferType = currentNode->bufferType;
    //copy child nodes
    leftNode->left = currentNode->left;
    rightNode->right = currentNode->right;

    if(currentNode->left)
    currentNode->left->parent = leftNode;
    if(currentNode->right)
    currentNode->right->parent = rightNode;

    leftNode->length = p;
    leftNode->start_index = currentNode->start_index;
    
    rightNode->length = currentNode->length - p;
    rightNode->start_index = currentNode->start_index + p;
    
    size_t l = (leftNode->left ? leftNode->left->subtree_len : 0);
    size_t r = (currentNode->right ? currentNode->right->subtree_len : 0);
    leftNode->subtree_len =  l + leftNode->length;
    rightNode->subtree_len = r + rightNode->length;

    // if(rightNode->length == 0){
    //     rightNode = rightNode->right;
    //     rightNode->parent = currentNode;
    // }

    // if(leftNode->length == 0){
    //     leftNode = leftNode->left;
    //     leftNode->parent = currentNode;
    // }


    
}



void PieceTable::RBInsertFixup(PTNode* z)
{
    if (!z) return;

    while (z->parent && z->parent->color == Color::Red) {
        PTNode* gp = z->parent->parent;

        // Parent is root → just recolor parent (root) black and stop.
        if (!gp) {
            z->parent->color = Color::Black;
            break;
        }

        if (z->parent == gp->left) {
            PTNode* uncle = gp->right;

            if (uncle && uncle->color == Color::Red) {
                z->parent->color = Color::Black;
                uncle->color     = Color::Black;
                gp->color        = Color::Red;
                z = gp;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    RotateLeft(z);
                }
                z->parent->color = Color::Black;
                gp->color        = Color::Red;
                RotateRight(gp);
            }
        } else {
            PTNode* uncle = gp->left;

            if (uncle && uncle->color == Color::Red) {
                z->parent->color = Color::Black;
                uncle->color     = Color::Black;
                gp->color        = Color::Red;
                z = gp;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    RotateRight(z);
                }
                z->parent->color = Color::Black;
                gp->color        = Color::Red;
                RotateLeft(gp);
            }
        }
    }

    if (root) root->color = Color::Black; // always enforce
}


void PieceTable::RotateLeft(PTNode* x) {
    PTNode* y = x->right;
    if (!y) return; // or assert(y)

    x->right = y->left;
    if (y->left) y->left->parent = x;

    y->parent = x->parent;
    if (!x->parent) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;

    x->calcSubtreeLength();
    y->calcSubtreeLength();
}

void PieceTable::RotateRight(PTNode *x)
{
    PTNode* y = x->left;
    if (!y) return; // or assert(y)

    // y's right subtree becomes x's left subtree
    x->left = y->right;
    if (y->right) y->right->parent = x;

    // link y to x's parent
    y->parent = x->parent;
    if (!x->parent) {
        root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }

    // put x on y's right
    y->right = x;
    x->parent = y;

    x->calcSubtreeLength();
    y->calcSubtreeLength();
}

void PieceTable::DisplayTree(PTNode *currentNode)
{
    
    currentNode->Print(GetNodesString(currentNode));
    if(currentNode->left){DisplayTree(currentNode->left);}
    if(currentNode->right){DisplayTree(currentNode->right);}
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
