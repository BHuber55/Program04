#include "AVLTree.h"
#include "AVLTreeIterator.h"
#include "ListArray.h"
using CSC2110::ListArray;
#include "ListArrayIterator.h"
using CSC2110::ListArrayIterator;
#include "CD.h"
using CSC2110::CD;

#include <iostream>
using namespace std;

void deleteCDs(ListArray<CD>* list)
{
	ListArrayIterator<CD>* iter = list->iterator();

	while (iter->hasNext())
	{
		CD* cd = iter->next();
		delete cd;
	}

	delete iter;
}

int main()
{
	//the unsorted ListArray of cds
	ListArray<CD>* cds = CD::readCDs("cds.txt");
	int numItems = cds->size();
	cout << numItems << endl;
	cout << endl;

	//test the binary search tree
	//insert all of the cds
	ListArrayIterator<CD>* iter = cds->iterator();
	BinarySearchTree<CD>* avl = new AVLTree<CD>(&CD::compare_items, &CD::compare_keys);
	while (iter->hasNext())
	{
		CD* cd = iter->next();
		avl->insert(cd);
	}
	delete iter;

	AVLTreeIterator<CD>* avl_iter = avl->iterator();
	avl_iter->setInorder();  //takes a snapshot of the data
	while (avl_iter->hasNext())
	{
		CD* cd = avl_iter->next();
		cd->displayCD();
	}
	delete avl_iter;




	//PROBABLY WILL HAVE TO DO MORE HERE.


	deleteCDs(cds);
	delete cds;
	return 0;
}