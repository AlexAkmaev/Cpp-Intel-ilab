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
	
	Node_* singleRightRotate__(Node_* &node);
	Node_* singleLeftRotate__(Node_* &node);
	Node_* doubleLeftRotate__(Node_* &node);
	Node_* doubleRightRotate__(Node_* &node);
  
	void inorder_traversal__(Node_* node = nullptr, int indent = 0) const;  //printing a tree with the in-order crawl
	Node_* search__(Node_* node, T data) const;  //search for a Node_ by its content
	Node_* push__(Node_* node, T data);  //add an element with data content to the tree
	Node_* remove__(Node_* node, T data);  //delete an element with the data content from the tree
	void make_empty__();  //deletes a tree
	void makeEmpty(Node_* node);
	
public:
	explicit SearchTree();  //ctor
	SearchTree(const SearchTree<T>& rhs);  //copy ctor
	SearchTree<T>& operator=(const SearchTree<T>& rhs);  //op=
	~SearchTree();  //dtor
	
	Node_* get_root() const;  //getting an immutable tree root
	int get_height(Node_* node) const;
	
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
int SearchTree<T>::get_height(Node_* node) const {
	return (!node ? -1 : node->height_);
}

template< typename T >
typename SearchTree<T>::Node_* SearchTree<T>::singleRightRotate__(Node_* &node) {
	Node_* lfnode = node->left_;
	node->left_ = lfnode->right_;
	lfnode->right_ = node;
	node->height_ = std::max(get_height(node->left_), get_height(node->right_))+1;
	lfnode->height_ = std::max(get_height(lfnode->left_), node->height_)+1;
	return lfnode;
}

template< typename T >
typename SearchTree<T>::Node_* SearchTree<T>::singleLeftRotate__(Node_* &node) {
	Node_* lfnode = node->right_;
	node->right_ = lfnode->left_;
	lfnode->left_ = node;
	node->height_ = std::max(get_height(node->left_), get_height(node->right_))+1;
	lfnode->height_ = std::max(get_height(node->right_), node->height_)+1 ;
	return lfnode;
}

template< typename T >
typename SearchTree<T>::Node_* SearchTree<T>::doubleLeftRotate__(Node_* &node) {
	node->right_ = singleRightRotate__(node->right_);
	return singleLeftRotate__(node);
}

template< typename T >
typename SearchTree<T>::Node_* SearchTree<T>::doubleRightRotate__(Node_* &node) {
	node->left_ = singleLeftRotate__(node->left_);
	return singleRightRotate__(node);
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
 * the date content and leave the tree balanced
 */
//template< typename T >
//typename SearchTree<T>::Node_* SearchTree<T>::push__(Node_* node, T data){
//	if (!node) 
//		return new Node_(data);
//	if (data < node->value_)
//		node->left_ = push__(node->left_, data);
//	else
//		node->right_ = push__(node->right_, data);
//	return balance_the_tree__(node);
//}
//template< typename T >
//typename SearchTree<T>::Node_* SearchTree<T>::push__(Node_* node, T data){
//	Node_* tmp = new Node_(data);
//	if(!root_) {
//		root_ = tmp;
//		return root_;
//	} else {
//  	if(!node) {
//      return tmp;
//  	}
//  	else if(data < node->value_)
//      node->left_ = push__(node->left_, data);
//  	else if(data > node->value_)
//      node->right_ = push__(node->right_, data);
//  	delete tmp;
//  	return balance_the_tree__(node);
//  }
//}
template< typename T >
typename SearchTree<T>::Node_* SearchTree<T>::push__(Node_* node, T data) {
	if(!node) {
		node = new Node_(data);
	} else if(data < node->value_) {
		node->left_ = push__(node->left_, data);
		if(get_height(node->left_) - get_height(node->right_) == 2) {
			if(data < node->left_->value_)
				node = singleRightRotate__(node);
			else
				node = doubleRightRotate__(node);
		}
	} else if(data > node->value_) {
		node->right_ = push__(node->right_, data);
		if(get_height(node->right_) - get_height(node->left_) == 2) {
			if(data > node->right_->value_)
				node = singleLeftRotate__(node);
			else
				node = doubleLeftRotate__(node);
		}
	}
	
	node->height_ = std::max(get_height(node->left_), get_height(node->right_)) + 1;
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
	merge__(ans, lhs.get_root());
	return ans;
}

/*
 * Recursively searches for the node to delete
 * and replaces it with the minimum node in the
 * right_ subtree to keep the entire tree balanced
*/
template< typename T >
typename SearchTree<T>::Node_* SearchTree<T>::remove__(Node_* node, T data) {
	Node_* temp;
	if(!node)
		return node;
	
	else if(data < node->value_)
		node->left_ = remove__(node->left_, data);
	else if(data > node->value_)
		node->right_ = remove__(node->right_, data);
	else if(node->left_ && node->right_) {
		temp = minimum(node->right_);
		node->value_ = temp->value_;
		node->right_ = remove__(node->right_, node->value_);
	} else {
		temp = node;
		if(!node->left_)
			node = node->right_;
		else if(!node->right_)
			node = node->left_;
		delete temp;
	}
	if(!node)
		return node;
	
	node->height_ = std::max(get_height(node->left_), get_height(node->right_)) + 1;
	
	//if node is unbalanced
	if(get_height(node->left_) - get_height(node->right_) == 2) {
		if(get_height(node->left_->left_) - get_height(node->left_->right_) == 1)
			return singleLeftRotate__(node);
		else
			return doubleLeftRotate__(node);
	} else if(get_height(node->right_) - get_height(node->left_) == 2) {
		if(get_height(node->right_->right_) - get_height(node->right_->left_) == 1)
			return singleRightRotate__(node);
		else
			return doubleRightRotate__(node);
	}
	
	return node;
}

//template< typename T >
//typename SearchTree<T>::Node_* SearchTree<T>::remove__(Node_* node, T data){
//  if(!node)
//    return node;
//  if (data < node->value_)
//    node->left_ = remove__(node->left_, data);
//  else if (data > node->value_)
//    node->right_ = remove__(node->right_, data);
//  else if (node->left_ && node->right_){
//    node->value_ = minimum(node->right_)->value_;
//    node->right_ = remove__(node->right_, node->value_);
//  }
//  else{
//    if (node->left_)
//      node = node->left_;
//    else if (node->right_)
//      node = node->right_;
//    else
//      node = nullptr;
//  }
//  return (node);
//}

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
