#include <iostream>

using namespace std;

template<class Item>
class BST_node{
    private:
        Item key_field;
        BST_node *left_child;
        BST_node *right_child;
    public:
        BST_node();
        void insert(Item);
        void inorder_traverse();
};

template<class Item>
BST_node<Item>::BST_node(){
    BST_node* left_child = NULL;
    BST_node* right_child = NULL;
}

template<class Item>
void BST_node<Item>::insert(Item word){
    BST_node* current_node = this;

    if( word > current_node->key_field ){
        if( current_node->right_child == NULL ){
            // if NULL, then create new node and insert to the right
            current_node->right_child = new BST_node;
            current_node->right_child->key_field = word;
            current_node->right_child->left_child = NULL;
            current_node->right_child->right_child = NULL;
        } else {
            //recursive call, go right
            current_node = current_node->right_child;
            current_node->insert(word);
 
        }
    } else if( word < current_node->key_field ){
        if( current_node->left_child == NULL ){
            // if NULL, then create new node and insert to the left
            current_node->left_child = new BST_node;
            current_node->left_child->key_field = word;
            current_node->left_child->left_child = NULL;
            current_node->left_child->right_child = NULL;
         } else {
            // recursive call, go left
            current_node = current_node->left_child;
            current_node->insert(word);
        }
    }
} // end method insert

template<class Item>
void BST_node<Item>::inorder_traverse(){
    BST_node* current_node = this;
    
    if( current_node != NULL ){
        // traverses left subtree until NULL
        current_node->left_child->inorder_traverse();

        // prints leftmost member
        cout << current_node->key_field << endl;

        // traverses right subtree after left
        current_node->right_child->inorder_traverse();
    }
}

int main(){

    BST_node<string>* tree = new BST_node<string>;

    // edit this text to be any sentence
    string text = "Data structures is one of the most important courses in computer science";

    // takes string, and finds each word
    int i;
    string word = "";
    for( i = 0; text[i] != '\0'; i++ ){ 
        // if a space is not encountered
        if( text[i] != ' ' ){
            word = word + text[i];
        } else {
            tree->insert(word);
            // if a space is encountered, then word is reset 
            word = "";
        }
    }
    tree->insert(word);

    cout << "Inorder traverse: ";
    tree->inorder_traverse();
    return 0;
}
