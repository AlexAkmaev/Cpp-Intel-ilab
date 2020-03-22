#pragma once

#include <iostream>
#include <string>
#include <stack>
#include <algorithm>
#include <iomanip>

/*AVL search tree*/
template<typename T>
class SearchTree{
	struct Node_{
		explicit Node_() = delete;
		explicit Node_(const T& data) : value_(data) {}
		
		T value_;
		int height_ = 1;
		Node_* right_ = nullptr,* left_ = nullptr;
	};
	
	Node_* root_ = nullptr;  //tree roots
	int get_height__(Node_* node) const;  //get the height value from node

	Node_* single_right_rotation__(Node_* &node);  //explanation of the principle before definition
	Node_* single_left_rotation__(Node_* &node);  //explanation of the principle before definition
	Node_* double_left_rotation__(Node_* &node);  //explanation of the principle before definition
	Node_* double_right_rotation__(Node_* &node);  //explanation of the principle before definition
	int is_balanced__(Node_* root, bool isBalanced) const;  //checks if tree is balanced
  
	void inorder_traversal__(Node_* node = nullptr, int indent = 0) const;  //printing a tree with the in-order crawl
	Node_* search__(Node_* node, T data) const;  //search for a Node_ by its content
	Node_* push__(Node_* node, T data);  //add an element with data content to the tree
	Node_* remove__(Node_* node, T data);  //delete an element with the data content from the tree
	void makeEmpty(Node_* node); //deletes a tree
	void make_empty__();  //auxiliary function for deleting a tree
	
public:
	explicit SearchTree();  //ctor
	SearchTree(const SearchTree<T>& rhs);  //copy ctor
	SearchTree<T>& operator=(const SearchTree<T>& rhs);  //op=
	~SearchTree();  //dtor

	Node_* get_root() const;  //getting an immutable tree root
	bool is_balanced() const;  //auxiliary function for checking if tree is balanced
	
	void inorder_print(int indent = 0) const;  //auxiliary function for in-order crawl tree printing

	Node_* search(T data) const;  //auxiliary function for searching a Node_ by its content
	bool exists(T data) const;  //is tree has data content?

	Node_* minimum(Node_* node) const;  //searches for the minimum in a subtree with the given root
	Node_* maximum(Node_* node) const;  //searches for the maximum in a subtree with the given root
	
	void push(T data); //auxiliary function for adding an element with data content to the tree
	
	template<typename U>
	friend void merge__(SearchTree<U>& rhs, typename SearchTree<U>::Node_* node);  //auxiliary function for op+, op= and copy ctor
	
	void remove(T data);  //auxiliary function for deleting an element with the data content from the tree

};

template<typename T>
SearchTree<T>::SearchTree() = default;

template<typename T>
SearchTree<T>::SearchTree(const SearchTree& rhs) {
	merge__(*this, rhs.get_root());
}

template<typename T>
SearchTree<T>& SearchTree<T>::operator=(const SearchTree<T>& rhs) {
	if (rhs.get_root() == root_)
		return *this;

	make_empty__();
	merge__(*this, rhs.get_root());
	return *this;
}

template<typename T>
typename SearchTree<T>::Node_* SearchTree<T>::get_root() const{
  return root_;
}

template<typename T>
int SearchTree<T>::get_height__(Node_* node) const {
	return (!node ? 0 : node->height_);
}

/*
             ***single right rotation***
         node                            lfnode
        /   \                            /   \
    lfnode   C     -------------->      A    node
    /   \                                    /  \
   A    B                                   B   C
*/
template<typename T>
typename SearchTree<T>::Node_* SearchTree<T>::single_right_rotation__(Node_* &node) {
	Node_* lfnode = node->left_;
	node->left_ = lfnode->right_;
	lfnode->right_ = node;
	node->height_ = std::max(get_height__(node->left_), get_height__(node->right_)) + 1;
	lfnode->height_ = std::max(get_height__(lfnode->left_), node->height_) + 1;
	return lfnode;
}

/*
           ***single left rotation***
    node                                rhnode
   /   \                                /   \
  A   rhnode      ------------->      node   C
       /  \                          /  \
      B   C                         A   B
*/
template<typename T>
typename SearchTree<T>::Node_* SearchTree<T>::single_left_rotation__(Node_* &node) {
	Node_* rhnode = node->right_;
	node->right_ = rhnode->left_;
	rhnode->left_ = node;
	node->height_ = std::max(get_height__(node->left_), get_height__(node->right_)) + 1;
	rhnode->height_ = std::max(get_height__(node->right_), node->height_) + 1 ;
	return rhnode;
}

template<typename T>
typename SearchTree<T>::Node_* SearchTree<T>::double_left_rotation__(Node_* &node) {
	node->right_ = single_right_rotation__(node->right_);
	return single_left_rotation__(node);
}

template<typename T>
typename SearchTree<T>::Node_* SearchTree<T>::double_right_rotation__(Node_* &node) {
	node->left_ = single_left_rotation__(node->left_);
	return single_right_rotation__(node);
}

template<typename T>
int SearchTree<T>::is_balanced__(Node_* root, bool isBalanced) const {
	if (!root || !isBalanced)
		return 0;
	
	int left_height = is_balanced__(root->left_, isBalanced);
	int right_height = is_balanced__(root->right_, isBalanced);
	
	// tree is unbalanced if absolute difference between height of
	// its left subtree and right subtree is more than 1
	if (abs(left_height - right_height) > 1)
		isBalanced = false;
	
	// return height of subtree rooted at current node
	return std::max(left_height, right_height) + 1;
}

template<typename T>
bool SearchTree<T>::is_balanced() const {
	bool isBalanced = true;
	is_balanced__(root_, isBalanced);
	return isBalanced;
}

template<typename T>
void SearchTree<T>::inorder_traversal__(Node_* node, int indent) const{
  if(node) {
		if(node->right_) {
		  inorder_traversal__(node->right_, indent + 4);
		}
		if (indent) {
		  std::cout << std::setw(indent) << ' ';
		}
		if (node->right_) std::cout<<" /\n" << std::setw(indent) << ' ';
		  std::cout<< node->value_ << "\n ";
		if(node->left_) {
		  std::cout << std::setw(indent) << ' ' << " \\\n";
		  inorder_traversal__(node->left_, indent + 4);
		}
  }
}

template< typename T >
void SearchTree<T>::inorder_print(int indent) const{
	if (!root_) {
		std::cout << "Empty tree:(" << std::endl;
	} else {
	  inorder_traversal__(root_, indent);
	  std::cout << std::endl;
	}
}

/*
 * Nonrecursively searches for the necessary node,
 * comparing the value in each node with the date,
 * and if the date is greater than the value in the node,
 * it goes to the right_, otherwise to the left_.
*/
template< typename T >
typename SearchTree<T>::Node_* SearchTree<T>::search__(Node_* node, T data) const{
	bool found = false;
	while (node && !found) {
		if (data == node->value_) { 
			found = true;
			break; 
		} else if (data < node->value_) {
			if (!node->left_) break;
			node = node->left_;
		} else {
			if (!node->right_) break; 
			node = node->right_;
		}
	}
	
	if (found) 
		return node;
	else 
		return nullptr;
}

template< typename T >
typename SearchTree<T>::Node_* SearchTree<T>::search(T data) const{
  if (!root_) {
  	std::cout << "Nothing to search:(" << std::endl;
  	return nullptr;
  } else {
  	return search__(root_, data);
  }
}

template< typename T >
bool SearchTree<T>::exists(T data) const{
  if (search(data))
  	return true;
 	return false;
}

template< typename T >
typename SearchTree<T>::Node_* SearchTree<T>::minimum(Node_* node) const{
	if (!node)
		return nullptr;
	else if(!node->left_)
		return node;
	else
		return minimum(node->left_);
}

template< typename T >
typename SearchTree<T>::Node_* SearchTree<T>::maximum(Node_* node) const{
  if (!node->right_)
    return node;
  else
    return maximum(node->right_);
}

/*
 * Recursively searches for the desired node,
 * after which you can add an element with 
 * the date content and balances the tree if
 * the inserted node violated the tree's AVL balance.
 */
template< typename T >
typename SearchTree<T>::Node_* SearchTree<T>::push__(Node_* node, T data) {
	if(!node) {
		node = new Node_(data);
	} else if(data < node->value_) {
		node->left_ = push__(node->left_, data);
		if(get_height__(node->left_) - get_height__(node->right_) == 2) {
			if(data < node->left_->value_)
				node = single_right_rotation__(node);
			else
				node = double_right_rotation__(node);
		}
	} else if(data > node->value_) {
		node->right_ = push__(node->right_, data);
		if(get_height__(node->right_) - get_height__(node->left_) == 2) {
			if(data > node->right_->value_)
				node = single_left_rotation__(node);
			else
				node = double_left_rotation__(node);
		}
	}
	
	node->height_ = std::max(get_height__(node->left_), get_height__(node->right_)) + 1;
	return node;
}

template< typename T >
void SearchTree<T>::push(T data){
	root_ = push__(root_, data);
}

template< typename T >
void merge__(SearchTree<T>& rhs, typename SearchTree<T>::Node_* node) {
	using pnode_t = typename SearchTree<T>::Node_*;
	std::stack<pnode_t> tree_stack;
	tree_stack.push(node);
	while(!tree_stack.empty()) {
		node = tree_stack.top();
		tree_stack.pop();
		rhs.push(node->value_);
		if(node->right_)
			tree_stack.push(node->right_);
		if(node->left_)
			tree_stack.push(node->left_);
	}
}

template<typename T>
SearchTree<T> operator+(const SearchTree<T>& rhs, const SearchTree<T>& lhs) {  //operation of adding the rhs tree to the current one
	SearchTree<T> ans(rhs);
	if (!ans.get_root() && !lhs.get_root())
		return ans;
	merge__(ans, lhs.get_root());
	return ans;
}

/*
 * Recursively searches for the node to delete
 * and replaces it with the minimum node in the
 * right_ subtree to keep the entire tree data 
 * balanced and balances the tree if the deleted
 * node violated the tree's ABL height balance.
*/
template< typename T >
typename SearchTree<T>::Node_* SearchTree<T>::remove__(Node_* head, T data){
	if(!head) return head;
	if(data < head->value_){
		head->left_ = remove__(head->left_, data);
	}else if(data > head->value_) {
		head->right_ = remove__(head->right_, data);
	}else{
		Node_* rhnode = head->right_;
		if(head->right_== nullptr){
			Node_* lfnode = head->left_;
			delete(head);
			head = lfnode;
		}else if(!head->left_){
			delete(head);
			head = rhnode;
		}else{
			rhnode = minimum(head);
			head->value_ = rhnode->value_;
			head->right_ = remove__(head->right_, rhnode->value_);
		}
	}
	if(!head) return head;
	
	head->height_ = std::max(get_height__(head->left_), get_height__(head->right_)) + 1;
	int balance_indicator = get_height__(head->left_) - get_height__(head->right_);
	if(balance_indicator > 1) {
		if(data > head->left_->value_){
			return single_right_rotation__(head);
		}else{
			return double_right_rotation__(head);
		}
	}else if(balance_indicator < -1){
		if(data < head->right_->value_){
			return single_left_rotation__(head);
		}else{
			return double_left_rotation__(head);
		}
	}
	
	return head;
}

template< typename T >
void SearchTree<T>::remove(T data){
	if (!root_) {
  	std::cout << "Nothing to remove:(" << std::endl;
  } else {
	  root_ = remove__(root_, data);
  }
}

template<typename T>
void SearchTree<T>::makeEmpty(Node_* node) {
	if(!node)
		return;
	makeEmpty(node->left_);
	makeEmpty(node->right_);
	delete node;
}

template<typename T>
void SearchTree<T>::make_empty__() {
	makeEmpty(root_);
}

template<typename T>
SearchTree<T>::~SearchTree(){
	make_empty__();
}
