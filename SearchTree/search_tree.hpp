#pragma once

#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <algorithm>
#include <iomanip>

/*AVL search tree*/
template<typename T>
class SearchTree final{
	struct Node_{
		explicit Node_(const T& data) : value_(data) {}
		
		T value_;
		int height_ = 1;
		Node_* right_ = nullptr,* left_ = nullptr;
	};
	
	Node_* root_ = nullptr;  //tree roots
	int get_height__(Node_* node) const noexcept;  //get the height value from node
	int get_balance__(Node_* node) const noexcept;  //get the balance factor from node

	Node_* single_right_rotation__(Node_* &node);  //explanation of the principle before definition
	Node_* single_left_rotation__(Node_* &node);  //explanation of the principle before definition
	Node_* double_left_rotation__(Node_* &node);  //explanation of the principle before definition
	Node_* double_right_rotation__(Node_* &node);  //explanation of the principle before definition
  
	void inorder_traversal__(Node_* node = nullptr, int indent = 0) const noexcept;  //printing a tree with the in-order crawl
	Node_* search__(Node_* node, T data) const noexcept;  //search for a Node_ by its content
	Node_* push__(Node_* node, T data);  //add an element with data content to the tree
	Node_* remove__(Node_* node, T data) noexcept;  //delete an element with the data content from the tree
	void make_empty__() noexcept;  //deletes a tree
	
public:
	SearchTree();
	SearchTree(const SearchTree<T>& rhs);
	SearchTree<T>& operator=(const SearchTree<T>& rhs);
	~SearchTree() noexcept;

	Node_* get_root() const noexcept;  //getting an immutable tree root
	bool is_balanced() const;  //checking if tree is balanced
	
	void inorder_print(int indent = 0) const noexcept;  //auxiliary function for in-order crawl tree printing

	Node_* search(T data) const noexcept;  //auxiliary function for searching a Node_ by its content
	bool exists(T data) const noexcept;  //is tree has data content?

	Node_* minimum(Node_* node) const noexcept;  //searches for the minimum in a subtree with the given root
	Node_* maximum(Node_* node) const noexcept;  //searches for the maximum in a subtree with the given root
	
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
typename SearchTree<T>::Node_* SearchTree<T>::get_root() const noexcept{
  return root_;
}

template<typename T>
int SearchTree<T>::get_height__(Node_* node) const noexcept{
	return (!node ? 0 : node->height_);
}

template< typename T >
int SearchTree<T>::get_balance__(Node_* node) const noexcept{
	return !node ? 0 : get_height__(node->left_) - get_height__(node->right_);  
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
	if(node->left_) {
		Node_* lfnode = node->left_;
		node->left_ = lfnode->right_;
		lfnode->right_ = node;
		node->height_ = std::max(get_height__(node->left_), get_height__(node->right_)) + 1;
		lfnode->height_ = std::max(get_height__(lfnode->left_), node->height_) + 1;
		return lfnode;
	}
	return node;
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
	if(node->right_) {
		Node_* rhnode = node->right_;
		node->right_ = rhnode->left_;
		rhnode->left_ = node;
		node->height_ = std::max(get_height__(node->left_), get_height__(node->right_)) + 1;
		rhnode->height_ = std::max(get_height__(node->right_), node->height_) + 1 ;
		return rhnode;
	}
	return node;
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
bool SearchTree<T>::is_balanced() const{
	Node_* node = root_;
	std::stack<Node_*> tree_stack;
	tree_stack.push(node);
	while(!tree_stack.empty()) {
		node = tree_stack.top();
		tree_stack.pop();
		if(abs(get_height__(node->left_) - get_height__(node->right_)) > 1)
			return false;
		if(node->right_)
			tree_stack.push(node->right_);
		if(node->left_)
			tree_stack.push(node->left_);
	}
	return true;
}


template<typename T>
void SearchTree<T>::inorder_traversal__(Node_* node, int indent) const noexcept{
  if(node) {
		if(node->right_) {
		  inorder_traversal__(node->right_, indent + 4);
		}
		if(indent) {
		  std::cout << std::setw(indent) << ' ';
		}
		if(node->right_) std::cout<<" /\n" << std::setw(indent) << ' ';
		  std::cout<< node->value_ << "\n ";
		if(node->left_) {
		  std::cout << std::setw(indent) << ' ' << " \\\n";
		  inorder_traversal__(node->left_, indent + 4);
		}
  }
}

template< typename T >
void SearchTree<T>::inorder_print(int indent) const noexcept{
	if(!root_) {
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
typename SearchTree<T>::Node_* SearchTree<T>::search__(Node_* node, T data) const noexcept{
	bool found = false;
	while(node && !found) {
		if(data == node->value_) { 
			found = true;
			break; 
		} else if(data < node->value_) {
			if(!node->left_) break;
			node = node->left_;
		} else {
			if(!node->right_) break; 
			node = node->right_;
		}
	}
	
	if(found) 
		return node;
	else 
		return nullptr;
}

template< typename T >
typename SearchTree<T>::Node_* SearchTree<T>::search(T data) const noexcept{
  if(!root_) {
  	std::cout << "Nothing to search:(" << std::endl;
  	return nullptr;
  } else {
  	return search__(root_, data);
  }
}

template< typename T >
bool SearchTree<T>::exists(T data) const noexcept{
 	return search(data);
}

template< typename T >
typename SearchTree<T>::Node_* SearchTree<T>::minimum(Node_* node) const noexcept{
	if(!node)
		return nullptr;
	else if(!node->left_)
		return node;
	else
		return minimum(node->left_);
}

template< typename T >
typename SearchTree<T>::Node_* SearchTree<T>::maximum(Node_* node) const noexcept{
  if(!node->right_)
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
SearchTree<T> operator+(const SearchTree<T>& rhs, const SearchTree<T>& lhs) {  //operation of adding the lhs tree to the rhs
	SearchTree<T> ans(rhs);
	if(!ans.get_root() && !lhs.get_root())
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
typename SearchTree<T>::Node_* SearchTree<T>::remove__(Node_* head, T data) noexcept{
	if(!head)
		return head;
	
	if(data < head->value_) {
		head->left_ = remove__(head->left_, data);
	}else if(data > head->value_) {
		head->right_ = remove__(head->right_, data);
	}else {
		if(!head->left_ || !head->right_) {
			Node_ *tmp = head->left_ ? head->left_ : head->right_;
			if (!tmp) {
				tmp = head;
				head = nullptr;
			}else{
				*head = *tmp;
			}
			delete tmp;
		}else{
		    Node_* tmp = minimum(head->right_);
		    head->value_ = tmp->value_;
		    head->right_ = remove__(head->right_, tmp->value_);
		}
	}
	if (!head)
		return head;
	  
	head->height_ = std::max(get_height__(head->left_), get_height__(head->right_)) + 1;
	
	int balance = get_balance__(head);
	
	if (balance > 1 && get_balance__(head->left_) >= 0)
		return single_right_rotation__(head);
	if (balance > 1 && get_balance__(head->left_) < 0)
		return double_right_rotation__(head);
	if (balance < -1 && get_balance__(head->right_) <= 0)
		return single_left_rotation__(head);
	if (balance < -1 && get_balance__(head->right_) > 0)
		return double_left_rotation__(head);
	
	return head;
}

template< typename T >
void SearchTree<T>::remove(T data){
	if(!root_) {
  	std::cout << "Nothing to remove:(" << std::endl;
  } else {
	  root_ = remove__(root_, data);
  }
}

template<typename T>
void SearchTree<T>::make_empty__() noexcept{
	if (!root_) 
		return;

	std::queue<Node_*> tree_queue; 
	tree_queue.push(root_); 
	while(!tree_queue.empty()) { 
		Node_* node = tree_queue.front(); 
		tree_queue.pop();
		
		if(node->left_) 
			tree_queue.push(node->left_); 
		if(node->right_) 
			tree_queue.push(node->right_);
		delete node; 
	}
	
	root_ = nullptr;
}

template<typename T>
SearchTree<T>::~SearchTree() noexcept{
	make_empty__();
}
