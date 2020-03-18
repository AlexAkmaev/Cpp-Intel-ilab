#pragma once

#include <iostream>
#include <string>
#include <iomanip>

/*All methods of the class SearchTree are recursive*/
template<typename T>
class SearchTree{
	struct _Node{
		explicit _Node() = delete;
		explicit _Node(const T& data) : _value(data) {}
		
		T _value;
		_Node* _right = nullptr,* _left = nullptr;
	};
	
	_Node* _root = nullptr;  //tree roots
  
	void __inorder_traversal__(_Node* node = nullptr, int indent = 0) const;  //printing a tree with the in-order crawl
	_Node* __search__(_Node* node, T data) const;  //search for a _Node by its content
	_Node* __push__(_Node* node, T data);  //add an element with data content to the tree
	_Node* __remove__(_Node* node, T data);  //delete an element with the data content from the tree
  
public:
	explicit SearchTree();  //ctor
	SearchTree(const SearchTree<T>& rhs);  //copy ctor
	SearchTree<T>& operator=(const SearchTree<T>& rhs);  //op=
	~SearchTree();  //dtor
	
	_Node* get_root() const;  //getting an immutable tree root
	
	void inorder_print(int indent = 0) const;  //auxiliary function for in-order crawl tree printing

	_Node* search(T data) const;  //auxiliary function for searching a _Node by its content
	bool exists(T data) const;  //is tree has data content?

	_Node* minimum(_Node* node) const;  //searches for the minimum in a subtree with the given root
	_Node* maximum(_Node* node) const;  //searches for the maximum in a subtree with the given root
	
	void push(T data);  //auxiliary function for adding an element with data content to the tree
	
	template<typename U>
	friend void __add__(SearchTree<U>& rhs, typename SearchTree<U>::_Node* node);  //auxiliary function for op+, op= and copy ctor
	
	_Node* remove(T data);  //auxiliary function for deleting an element with the data content from the tree

};

template<typename T>
SearchTree<T>::SearchTree() = default;

template<typename T>
SearchTree<T>::SearchTree(const SearchTree& rhs) {
	__add__(*this, rhs.get_root());
}

template<typename T>
SearchTree<T>& SearchTree<T>::operator=(const SearchTree<T>& rhs) {
	if (rhs.get_root() != _root) {
		__add__(*this, rhs.get_root());
	}
	return *this;
}

template<typename T>
typename SearchTree<T>::_Node* SearchTree<T>::get_root() const{
  return _root;
}

template< typename T >
void SearchTree<T>::__inorder_traversal__(_Node* node, int indent) const{
  if(node) {
		if(node->_right) {
		  __inorder_traversal__(node->_right, indent + 4);
		}
		if (indent) {
		  std::cout << std::setw(indent) << ' ';
		}
		if (node->_right) std::cout<<" /\n" << std::setw(indent) << ' ';
		  std::cout<< node->_value << "\n ";
		if(node->_left) {
		  std::cout << std::setw(indent) << ' ' << " \\\n";
		  __inorder_traversal__(node->_left, indent + 4);
		}
  }
}

template< typename T >
void SearchTree<T>::inorder_print(int indent) const{
	if (!_root) {
		std::cout << "Empty tree:(" << std::endl;
	} else {
	  __inorder_traversal__(_root, indent);
	}
}

/*
 * Recursively searches for the necessary node,
 * comparing the value in each node with the date,
 * and if the date is greater than the value in the node,
 * it goes to the right, otherwise to the left.
*/
template< typename T >
typename SearchTree<T>::_Node* SearchTree<T>::__search__(_Node* node, T data) const{
  if (!node || data == node->_value)
    return node;
  if (data < node->_value)
    return __search__(node->_left, data);
  else
    return __search__(node->_right, data);
}

template< typename T >
typename SearchTree<T>::_Node* SearchTree<T>::search(T data) const{
  if (!_root) {
  	std::cout << "Nothing to search:(" << std::endl;
  	return nullptr;
  } else {
  	return __search__(_root, data);
  }
}

template< typename T >
bool SearchTree<T>::exists(T data) const{
  if (search(data))
  	return true;
 	return false;
}

template< typename T >
typename SearchTree<T>::_Node* SearchTree<T>::minimum(_Node* node) const{
  if (!node->_left)
    return node;
  else
    return minimum(node->_left);
}

template< typename T >
typename SearchTree<T>::_Node* SearchTree<T>::maximum(_Node* node) const{
  if (!node->_right)
    return node;
  else
    return maximum(node->_right);
}

/*
 * Recursively searches for the desired node,
 * after which you can add an element with 
 * the date content and leave the tree balanced
 */
template< typename T >
typename SearchTree<T>::_Node* SearchTree<T>::__push__(_Node* node, T data){
	_Node* tmp = new _Node(data);
	if(!_root) {
		_root = tmp;
		return _root;
	} else {
  	if(!node) {
      return tmp;
  	}
  	else if(data < node->_value)
      node->_left = __push__(node->_left, data);
  	else if(data > node->_value)
      node->_right = __push__(node->_right, data);
  	delete tmp;
  	return node;
  }
}

template< typename T >
void SearchTree<T>::push(T data){
	__push__(_root, data);
}

template< typename T >
void __add__(SearchTree<T>& rhs, typename SearchTree<T>::_Node* node) {
	if (node){
    rhs.push(node->_value);
    __add__(rhs, node->_left);
    __add__(rhs, node->_right);
  }
}

template<typename T>
SearchTree<T> operator+(const SearchTree<T>& rhs, const SearchTree<T>& lhs) {  //operation of adding the rhs tree to the current one
	SearchTree<T> ans = rhs;
	__add__(ans, lhs.get_root());
	return ans;
}

/*
 * Recursively searches for the node to delete
 * and replaces it with the minimum node in the
 * right subtree to keep the entire tree balanced
*/
template< typename T >
typename SearchTree<T>::_Node* SearchTree<T>::__remove__(_Node* node, T data){
  if(!node)
    return node;
  if (data < node->_value)
    node->_left = __remove__(node->_left, data);
  else if (data > node->_value)
    node->_right = __remove__(node->_right, data);
  else if (node->_left && node->_right){
    node->_value = minimum(node->_right)->_value;
    node->_right = __remove__(node->_right, node->_value);
  }
  else{
    if (node->_left)
      node = node->_left;
    else if (node->_right)
      node = node->_right;
    else
      node = nullptr;
  }
  return node;
}

template< typename T >
typename SearchTree<T>::_Node* SearchTree<T>::remove(T data){
	if (!_root) {
  	std::cout << "Nothing to remove:(" << std::endl;
  	return nullptr;
  } else {
	  return __remove__(_root, data);
  }
}

template<typename T>
SearchTree<T>::~SearchTree(){
	_Node* temp = _root;
	while(_root){
		_root = remove(_root->_value);
	}
}
