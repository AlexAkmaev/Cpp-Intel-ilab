#include "search_tree.hpp"

int main(){
	SearchTree<int> mytree;
	mytree.push(100);
	mytree.push(50);
	mytree.push(200);
	mytree.push(30);
	mytree.push(10);
	mytree.push(40);
	mytree.push(80);
	mytree.push(70);
	mytree.push(90);
	mytree.push(170);
	mytree.push(180);
	mytree.push(300);
	mytree.push(250);
	
	SearchTree<int> histree;
	histree.push(20);
	histree.push(45);
	histree.push(120);
	histree.push(33);
	histree.push(71);
	histree.push(94);
	histree.push(8);
	histree.push(7);

	std::cout << "\n***inorder_print  mytree***\n";
	mytree.inorder_print();
	std::cout << "\n***inorder_print  histree***\n";
	histree.inorder_print();
	
	SearchTree<int> ourtree = mytree + histree;
	std::cout << "\n***inorder_print  ourtree***\n";
	ourtree.inorder_print();
	
	if (ourtree.exists(50))
	  std::cout << "50 exists!" << std::endl;
  ourtree.remove(50);
	std::cout << "\n***after remove  ourtree***\n";
	ourtree.inorder_print();
	
	if (!ourtree.exists(50))
	  std::cout << "50 doesn't exists" << std::endl;
	
	return 0;
}
