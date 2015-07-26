#include <iostream>

using namespace std;

class BST_node{
    private:
        string key_field;
        BST_node *left_child;
        BST_node *right_child;
    public:
        BST_node();
        void insert(string);
        void inorder_traverse();
};

BST_node::BST_node(){
    BST_node* left_child = NULL;
    BST_node* right_child = NULL;
}

void BST_node::insert(string word){
    BST_node* current_node = this;

    if( word < current_node->key_field ){
        if( current_node->left_child != NULL ){
            // recursive call, go left
            current_node = current_node->left_child;
            current_node->insert(word);
        } else {
            // if NULL, then create new node and insert to the left
            current_node->left_child = new BST_node;
            current_node->left_child->key_field = word;
            current_node->left_child->left_child = NULL;
            current_node->left_child->right_child = NULL;

            //cout << "insert: " << word << endl;
        }
    } else if ( word > current_node->key_field ){
        if( current_node->right_child != NULL ){
            //recursive call, go right
            current_node = current_node->right_child;
            current_node->insert(word);
        } else {
            // if NULL, then create new node and insert to the right
            current_node->right_child = new BST_node;
            current_node->right_child->key_field = word;
            current_node->right_child->left_child = NULL;
            current_node->right_child->right_child = NULL;

            //cout << "insert: " << word << endl;
        }
    }
} // end method insert

void BST_node::inorder_traverse(){
    BST_node* current_node = this;
    if( current_node ){
        current_node->left_child->inorder_traverse();
        cout << current_node->key_field << endl;
        current_node->right_child->inorder_traverse();
    }
}

int main(){

    BST_node* tree = new BST_node;

    string text_to_insert = "Data structures is one of the most important courses in computer science";


    // takes string, and finds each word
    int i;
    string word = "";
    for( i = 0; text_to_insert[i] != '\0'; i++ ){ 
        // if a space is not encountered
        if( text_to_insert[i] != ' ' ){
            word =  word + text_to_insert[i];
        } else {
            tree->insert(word);
            // if a space is encountered, then word is reset 
            word = "";
        }
    }
    tree->insert(word);

    tree->inorder_traverse();
    return 0;
}
