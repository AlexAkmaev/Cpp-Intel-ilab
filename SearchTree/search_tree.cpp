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
	histree.push(19);
	histree.push(18);
	histree.push(17);
	histree.push(16);
	histree.push(15);
	histree.push(10);
	histree.push(101);
	histree.push(20);
	histree.push(45);
	histree.push(120);
	histree.push(33);
	histree.push(71);
	histree.push(94);
	histree.push(8);
	histree.push(7);
	histree.push(7);
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
	ourtree.remove(300);
	ourtree.remove(200);
	ourtree.remove(101);
	ourtree.remove(250);
	ourtree.remove(170);
	std::cout << "\n***after remove  ourtree***\n";
	ourtree.inorder_print();
	
	if (!ourtree.exists(50))
	  std::cout << "50 doesn't exists" << std::endl;
	
	return 0;
}
