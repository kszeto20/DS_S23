/* ASSUMPTIONS:
1. When a node must be split and has an odd number of keys, the extra key will go to the new right-hand node.
2. There will never be a duplicate key passed to insert.
*/

#include <vector>
#include <algorithm>

#ifndef DS_BPLUSTREE
#define DS_BPLUSTREE

///////////////////////////////////////////////////////////////////////////////
//DO NOT CHANGE THIS CODE
///////////////////////////////////////////////////////////////////////////////

//Do not implement the class here, this is a forward declaration. Implement at
//the bottom of the .h file
template <class T> class BPlusTree; 

template <class T>
class BPlusTreeNode{
    public:
    BPlusTreeNode() : parent(NULL) {};
	bool is_leaf();
	bool contains(const T& key);

	//For grading only. This is bad practice to have, because
	//it exposes a private member variable.
	BPlusTreeNode* get_parent() { return parent; } 

	//We need this to let BPlusTree access private members
	friend class BPlusTree<T>; 
    private:
	bool contains(const T& key,std::size_t low,std::size_t high);
	std::vector<T> keys;
	std::vector<BPlusTreeNode*> children;
	BPlusTreeNode* parent;
};

template <class T>
bool BPlusTreeNode<T>::is_leaf(){
	for(unsigned int i=0; i<children.size(); i++){
		if(children[i]){
			return false;
		}
	}
	return true;
}

template <class T>
bool BPlusTreeNode<T>::contains(const T& key){
	return contains(key,0,keys.size()-1);
}

//Private method takes advantage of the fact keys are sorted
template <class T>
bool BPlusTreeNode<T>::contains(const T& key,std::size_t low,std::size_t high){
	if(low>high){
		return false;
	}
	if(low==high){
		return key == keys[low];
	}
	std::size_t mid = (low+high)/2;
	if(key<=keys[mid]){
		return contains(key,0,mid);
	}
	else{
		return contains(key,mid+1,high);
	}
}

///////////////////////////////////////////////////////////////////////////////////////
//Your BPlusTree implementation goes below this point.
///////////////////////////////////////////////////////////////////////////////////////

template <class T>
class BPlusTree {
    public:
    // CONSTRUCTOR
    BPlusTree() : root_(NULL), size_(0) {}
    BPlusTree(int size_wanted) : root_(NULL), size_(size_wanted) {};
    BPlusTree(const BPlusTree<T>& old) : size_(old.size_) { 
        root_ = this->copy_tree(old.root_,NULL);
    }
    // DESTRUCTOR
    ~BPlusTree() {
        this->destroy_tree(root_);
        root_ = NULL;
    }

    // OVERLOAD
    BPlusTree& operator=(const BPlusTree<T>& old) {
        if (&old != this) {
            this->destroy_tree(root_);
            root_ = this->copy_tree(old.root_,NULL);
            size_ = old.size_;
        }
        return *this;
    }

    // ACCESSORS
    int size() const { return size_; }

    // NEW FUNCTIONS

    // FIND, INSERT & ERASE
    BPlusTreeNode<T>* find(const T& key_value) { return find_recursive(key_value, root_); }
    void insert(T const& key_value) { return insert_recursive(key_value, root_, NULL); }
    int erase(T const& key_value) { return erase(key_value, root_); }

    // OUTPUT & PRINTING
    void print_sideways(std::ostream& ostr) { print_as_sideways_tree(ostr, root_, 0); }
    void print_BFS(std::ostream& ostr);

    private:
    // REPRESENTATION
    BPlusTreeNode<T>* root_;
    int size_;

    // PRIVATE HELPER FUNCTIONS
    BPlusTreeNode<T>*  copy_tree(BPlusTreeNode<T>* old_root, BPlusTreeNode<T>* the_parent);
    void destroy_tree(BPlusTreeNode<T>* p);    
    BPlusTreeNode<T>* find_recursive(const T& key_value, BPlusTreeNode<T>* p);
    void resize_recursive(BPlusTreeNode<T>*& node_in, BPlusTreeNode<T>*& the_parent);
    void insert_recursive(const T& key_value, BPlusTreeNode<T>*& node_in, BPlusTreeNode<T>* the_parent);

    void print_as_sideways_tree(std::ostream& ostr, BPlusTreeNode<T>*& node_in, int level) const;
};

// purpose: copy the tree
// parameters: node to copy, parent of node to copy

template <class T>
BPlusTreeNode<T>*  BPlusTree<T>::copy_tree(BPlusTreeNode<T>* old_root, BPlusTreeNode<T>* the_parent) {
    if (old_root == NULL) { // if the tree is empty, nothing to copy
        return NULL;
    }

    BPlusTreeNode<T> *answer = new BPlusTreeNode<T>(); // create new node
    answer->keys = old_root->keys; // transfer keys
    for (unsigned int i = 0; i < old_root->children.size(); i++) { // transfer children with their children transferred
        // recursive call
        answer->children.push_back(copy_tree(old_root->children[i], answer));
    }
    answer->parent = the_parent; // update parent
    return answer;
}

// purpose: destruct tree without memory leaks
// parameters: node to destroy

template <class T>
void BPlusTree<T>::destroy_tree(BPlusTreeNode<T>* p) {
    if (!p) return; // if already empty don't do anything

    for (unsigned int i = 0; i < p->children.size(); i++) { // for each child
        destroy_tree(p->children[i]); // destroy all of its children (recursive call)
    }

    delete p; // destroy self last
}

// purpose: find where the item with that value is
// parameters: value to search for, node to start search at

template <class T>
BPlusTreeNode<T>* BPlusTree<T>::find_recursive(const T& key_value, BPlusTreeNode<T>* p) {
    if (p == NULL) { return NULL; } // empty tree
    if (p->is_leaf()) { return p; } // if it is a leaf then it has to be there because there no other children to traverse through

    for (int i = 0; i < p->keys.size(); i++) { // for each key
        // find first key it is less than
        if (key_value < p->keys[i]) {
            // return find of child to the "left" 
            return find_recursive(key_value, p->children[i]);
        }
    }
    // if >= all the keys, look in the last child
    return find_recursive(key_value, p->children[p->keys.size()]);
}

template <class T>
void BPlusTree<T>::resize_recursive(BPlusTreeNode<T>*& node_in, BPlusTreeNode<T>*& the_parent) {
    if (node_in == NULL) { // Case 1: ? if ever a null Node
        return;
    }
    if (node_in->keys.size() < this->size_) { // Case 2: no resize actually needed
        return;
    }
    else { // Case 3: resize needed
        // Case 3a: 
        int split_ind, second;
        split_ind = node_in->keys.size() / 2;
        second = node_in->keys.size() - split_ind;
        if (node_in->is_leaf()) {

            bool at_top = false;
            if (the_parent == NULL) {
                the_parent = new BPlusTreeNode<T>();
                node_in->parent = the_parent;
                the_parent->children.push_back(node_in);
                at_top = true;
            }

            // make right child 
            BPlusTreeNode<T>* right_child = new BPlusTreeNode<T>();
            for (int i = 0; i < second; i++) {
                right_child->keys.insert(right_child->keys.begin(), node_in->keys.back());
                node_in->keys.pop_back();
            }

            // add correct to the key to the correct position in the parent keys
            int counter = 0;
            for (int i = 0; i < the_parent->keys.size(); i++, counter++) {
                // if no parent keys or find first key less than
                if (right_child->keys[0] < the_parent->keys[i]) {
                    break;
                }
            }
            typename std::vector<T>::iterator itr = the_parent->keys.begin();
            the_parent->keys.insert(itr + counter, right_child->keys[0]);

            // insert children in the correct place
            the_parent->children.insert(the_parent->children.begin() + counter + 1, right_child);

            right_child->parent = the_parent;
            if (at_top) {
                this->root_ = the_parent;
            }
            
            return resize_recursive(the_parent, the_parent->parent);
        }
        else {
            second--; // split value should not be duplicated in "child"

            // check for null parent -- if null copy over right side into new node
            bool at_top = false;
            if (the_parent == NULL) {
                the_parent = new BPlusTreeNode<T>();
                node_in->parent = the_parent;
                the_parent->children.push_back(node_in);
                at_top = true;
            }

            // make a right side node 
            BPlusTreeNode<T>* right_child = new BPlusTreeNode<T>();
            // for up to second # of keys, move the keys from the back to the front of the right_child keys
            for (int i = 0; i < second; i++) {
                right_child->keys.insert(right_child->keys.begin(), node_in->keys.back());
                node_in->keys.pop_back();
            }
            right_child->parent = the_parent; // fix right_child parent

             // add correct to the key to the correct position in the parent keys
            int counter = 0;
            for (int i = 0; i < the_parent->keys.size(); i++, counter++) {
                // if no parent keys or find first key less than
                if (node_in->keys[node_in->keys.size() - 1] < the_parent->keys[i]) {
                    break;
                }
            }
            // insert into the_parent keys vector
            typename std::vector<T>::iterator itr = the_parent->keys.begin();
            the_parent->keys.insert(itr + counter, node_in->keys[node_in->keys.size() - 1]);
            node_in->keys.pop_back();
            
            // inset the right_child into the proper position in parent children vector
            for (int i = 0; i < the_parent->children.size(); i++) {
                if (the_parent->children[i] == node_in) { // once node_in is found, insert right behind it
                    the_parent->children.insert(the_parent->children.begin() + i + 1, right_child);
                    break;
                }
            }

            // split the children properly
            for (int i = 0; i < second + 1; i++) { // right child gets second + 1 # of children
                right_child->children.insert(right_child->children.begin(), node_in->children.back());
                // after moving children over -- adjust children parent
                node_in->children.back()->parent = right_child;
                node_in->children.pop_back(); // remove form node_in children vector
            }
            
            if (at_top) { // adjust root if necessary
                this->root_ = the_parent;
            }   

            return resize_recursive(the_parent, the_parent->parent);
        }
    }
}


template <class T> 
void BPlusTree<T>::insert_recursive(const T& key_value, BPlusTreeNode<T>*& node_in, BPlusTreeNode<T>* the_parent) {

    if (node_in == NULL) { // Case 1: empty tree - must make new node
        BPlusTreeNode<T>* head = new BPlusTreeNode<T>();
        head->parent = the_parent;
        head->keys.push_back(key_value);
        node_in = head;
        return;
    }
    else if (node_in->is_leaf()) { // Case 2: at leaf, must insert key at this leaf/level
        // loop around to find correct position for insertion
        int counter = 0;
        for (int i = 0; i < node_in->keys.size(); i++, counter++) {
            if (key_value < node_in->keys[i]) {
                break;
            }
        }
        // insert after position found || if never found will append to end
        typename std::vector<T>::iterator itr = node_in->keys.begin();
        node_in->keys.insert(itr+counter, key_value);

        if (node_in->keys.size() >= this->size_) { // check key size for resize
            resize_recursive(node_in, node_in->parent);
        }
        return;
    }
    else { // Case 3: not at leaf yet, must keep recursing to find correct leaf for insertion
        // loop to find which child to go into
        for (int i = 0; i < node_in->keys.size(); i++) {
            if (key_value < node_in->keys[i]) {
                return insert_recursive(key_value, node_in->children[i], node_in);
            }
        }
        // if never found look in rightmost child
        return insert_recursive(key_value, node_in->children[node_in->keys.size()], node_in);
    }
    return;
}


// purpose print sideways

template <class T>
void BPlusTree<T>::print_as_sideways_tree(std::ostream& ostr, BPlusTreeNode<T>*& node_in, int level) const {
    if (node_in == NULL) {
        ostr << "Tree is empty." << std::endl;
        return;
    }
    else {
        // print left side children
        int left = node_in->children.size() / 2;
        for (int i = 0; i < left; i++) {
            print_as_sideways_tree(ostr, node_in->children[i], level+1); // recursion call
        }

        for (int i = 0; i < level; i++) {
            ostr << '\t';
        }
        ostr << std::endl;

        // print right side children
        int right = node_in->children.size() - left;
        for (int i = left; i < left + right; i++) {
            print_as_sideways_tree(ostr, node_in->children[i], level + 1); // recursion call
        }
        return;

    }
    return;
}

// didn;t finish print BFS
template <class T>
void BPlusTree<T>::print_BFS(std::ostream& ostr) {
    if (this->root_ == NULL) {
        ostr << "Tree is empty." << std::endl;
        return;
    }
}


#endif