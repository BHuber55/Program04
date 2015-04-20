#if !defined (NULL)
#define NULL 0
#endif

#if !defined (AVLTREE_H)
#define AVLTREE_H

#include "Drawable.h"
#include "AVLTreeIterator.h"
#include "Line.h"

#include "Text.h"
using CSC2110::String;

#include <iostream>
using namespace std;

template < class T >
class AVLTree : public Drawable
{
   
private:
	AVLTreeNode<T>* root;
	bool avlFlag;
	int sze;

	int (*compare_items) (T* item_1, T* item_2); 
	int(*compare_keys) (String* key, T* item);
	 
		//Pre:	Must pass valid, non-Null value.
		//Post: Sets private value root as tNode.
	void setRootNode(AVLTreeNode<T>* tNode); //you can get by without using these methods, refer to root directly
		//Pre:  
		//Post: Returns the private value root.
	AVLTreeNode<T>* getRootNode();
		//Pre:  Must pass valid, non-Null value.
		//Post: Returns height of the tree from the node passed in.
	int getHeight(AVLTreeNode<T>* tNode);  //from lab
		//Pre:  Must pass valid, non-Null value.
		//Post: Returns true if tree is balanced, else returns false.
	bool isBalanced(AVLTreeNode<T>* tNode);
		//Pre:  Must pass valid, non-Null value.
		//Post: Deletes tree from the root passed in.
	void destroyItem(AVLTreeNode<T>* tNode); 
		//Pre:  
		//Post: Begins to delete nodes.
	void destroy();
		//Pre:  Must pass valid, non-Null value.
		//Post: Returns the node passed after insertion and balancing.
	AVLTreeNode<T>* insertItem(AVLTreeNode<T>* tNode, T* item);
		//Pre:  Must pass valid, non-Null value.
		//Post: Returns a new node after a rotation to the left has occured.
	AVLTreeNode<T>* rotateLeft(AVLTreeNode<T>* tNode);
		//Pre:  Must pass valid, non-Null value.
		//Post: Returns a new node after a rotation to the right has occured.
	AVLTreeNode<T>* rotateRight(AVLTreeNode<T>* tNode);
		//Pre:  Must pass valid, non-Null value.
		//Post: Returns a new node, after a double rotation to the left then the right has occured.
	AVLTreeNode<T>* rotateLeftRight(AVLTreeNode<T>* tNode);
		//Pre:  Must pass valid, non-Null value.
		//Post: Returns a new node, aftera double rotation to the right then left has occured.
	AVLTreeNode<T>* rotateRightLeft(AVLTreeNode<T>* tNode);




		//Pre:  
		//Post: 
	AVLTreeNode<T>* avlFixAddLeft(AVLTreeNode<T>* tNode);
		//Pre:  
		//Post: 
	AVLTreeNode<T>* avlFixAddRight(AVLTreeNode<T>* tNode);

    virtual void drawRec(AVLTreeNode<T>* tNode, Cairo::RefPtr<Cairo::Context> cr, Line* line, int x_parent, int x_curr, int y_curr);

public:
	//Constructor
		//Pre:  Must pass valid, non-Null value.
		//Post: 
	AVLTree(int (*comp_items) (T* item_1, T* item_2), int (*comp_keys) (String* key, T* item));
	//Destructor	
		//Pre: 
		//Post: Deletes all nodes
	~AVLTree();
		//Pre:  
		//Post: Returns the number of items in the AVLtree.
	int size();
		//Pre:  Must pass valid, non-Null value. If item is a duplicate, will not do anything.
		//Post: Inserts the item into the correct location of the tree. 
	void insert(T* item);
		//Pre:  Must pass valid, non-Null value.
		//Post: Returns the item, if it exists.
	T* retrieve(String* sk);
		//Pre: 	
		//Post: Returns true if AVLtree is empty, else will return false.
	bool isEmpty();
		//Pre: 		
		//Post: Returns the item at the root of the AVLtree
	T* getRootItem();
		//Pre: 
		//Post: Returns an iterator for the AVLtree.
	AVLTreeIterator<T>* iterator();
		//Pre: 	
		//Post: Returns the height of the tree.
	int getHeight();
		//Pre: 
		//Post: Returns true if tree is balanced, else will return false.
	bool isBalanced();

    void draw(Cairo::RefPtr<Cairo::Context> cr, int width, int height);
    void mouseClicked(int x, int y);

};

template < class T >
AVLTree<T>::AVLTree(int(*comp_items) (T* item_1, T* item_2), int(*comp_keys) (String* key, T* item))
{
	compare_items = comp_items;
	compare_keys = comp_keys;

	sze == 0;
	avlFlag = false;
	root = NULL;
}

template < class T >
AVLTree<T>::~AVLTree()
{
	destroy();
}

template < class T >
int AVLTree<T>::size()
{
	return sze;
}

template < class T >
bool AVLTree<T>::isEmpty()
{
	return sze == 0;
}

template < class T >
void AVLTree<T>::setRootNode(AVLTreeNode<T>* tNode) //you can get by without using these methods, refer to root directly
{
	root = tNode;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::getRootNode()
{
	return root;
}

template < class T >
T* AVLTree<T>::getRootItem()
{
	if (root != NULL)
	{
		return root->getItem();
	}

	return NULL;
}

template < class T >
AVLTreeIterator<T>* AVLTree<T>::iterator()
{
	AVLTreeIterator<T>* iter = new AVLTreeIterator<T>(root);
	return iter;
}


template < class T >
int AVLTree<T>::getHeight(AVLTreeNode<T>* tNode)  //from lab
{
	//base case.
	if (tNode == NULL)
	{
		return 0;
	}

	int LeftHeight = getHeight(tNode->getLeft());
	int RightHeight = getHeight(tNode->getRight());

	if (LeftHeight > RightHeight)
	{
		return LeftHeight + 1;
	}

	else
	{
		return RightHeight + 1;
	}
}

template < class T >
int AVLTree<T>::getHeight()
{
	int height;
	height = getHeight(root);
	return height;

}

template < class T >
bool AVLTree<T>::isBalanced(AVLTreeNode<T>* tNode)
{
	//base case.
	if (tNode == NULL)
	{
		return true;
	}
	else
	{
		AVLTreeNode<T>* l = tNode->getLeft();
		AVLTreeNode<T>* r = tNode->getRight();
		bool l_b = isBalanced(left);
		bool r_b = isBalanced(right);

		if (l_b == false || r_b == false)
		{
			return false;
		}

		else
		{
			int l_h = getHeight(l);
			int r_h = getHeight(r);
			int h = abs(r_h - l_h);

			if (h < 2)
			{
				return true;
			}

			else
			{
				return false;
			}
		}
	}
}

template < class T >
bool AVLTree<T>::isBalanced()
{
	bool balanced;
	balanced = isBalanced(root);
	return balanced;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::insertItem(AVLTreeNode<T>* tNode, T* item)
{
	//base case
	if (tNode == NULL)
	{
		AVLTreeNode<T>* new_node = new AVLTreeNode<T>(item);
		sze++;
		avlFlag = true;
		return new_node;
	}

	int comp = (*compare_items)(item, tNode->getItem());

	if (comp == 0)
	{
		//we aren't allowing duplicates in here..
		//so just return it.
		return tNode;
	}
	else if (comp < 0)
	{
		AVLTreeNode<T>* l = tNode->getLeft();
		tNode->setLeft(insertItem(l, item));
		if (avlFlag)
		{
			tNode = avlFixAddLeft(tNode);
		}
	}
	else
	{
		AVLTreeNode<T>* r = tNode->getRight();
		if (avlFlag)
		{
			tNode = avlFixAddRight(tNode);
			tNode->setRight(insertItem(r, item));
		}
	}

	return tNode;

}

template < class T >
void AVLTree<T>::insert(T* item)
{
	root = insertItem(root, item);
	avlFlag = false;
}

template < class T >
T* AVLTree<T>::retrieve(String* sk)
{
	AVLTreeNode<T>* curr = root;
	int comp;

	while (curr != NULL)
	{
		comp = (*compare_keys)(sk, curr->getItem());

		if (comp == 0)
		{
			return curr->getItem();
		}
		else if (comp < 0)
		{
			curr = curr->getLeft();
		}
		else
		{
			curr = curr->getRight();
		}
	}

	return NULL;
}

template < class T >
void AVLTree<T>::destroyItem(AVLTreeNode<T>* tNode)
{
	//cant remove something that isnt there..
	if (tNode != NULL)
	{
		destroyItem(tNode->getLeft());
		destroyItem(tNode->getRight());
		delete tNode;
	}
}

template < class T >
void AVLTree<T>::destroy()
{
	//get rid of all the things.
	destroyItem(root);
	sze = 0;
	avlFlag = false;
	root = NULL;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::avlFixAddLeft(AVLTreeNode<T>* tNode)
{
	tNode->insertLeft();
	AVL bf = tNode->getBalanceFactor();

	if (bf == BALANCED)
	{
		avlFlag = false;
		return tNode;
	}
	else if (bf == LEFT_HEAVY || bf == RIGHT_HEAVY)
	{
		//keep going
		return tNode;
	}
	else
	{
		if (bf == LEFT_UNBALANCED)
		{
			AVLTreeNode<T>* left = tNode->getLeft();
			AVL bf_l = left->getBalanceFactor();
			if (bf_l == RIGHT_HEAVY)
			{
				//Double left then right
				tNode = rotateLeftRight(tNode);
			}
			else
			{
				//single right
				tNode = rotateRight(tNode);
			}
		}
		else
		{
			AVLTreeNode<T>* right = tNode->getRight();
			AVL bf_r = right->getBalanceFactor();
			if (bf_r == LEFT_HEAVY)
			{
				//double right then left
				tNode = rotateRightLeft(tNode);
			}
			else
			{
				//single left
				tNode = rotateLeft(tNode);
			}
		}

		avlFlag = false;
		return tNode;
	}
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::avlFixAddRight(AVLTreeNode<T>* tNode)
{
	tNode->insertRight();
	AVL bf = tNode->getBalanceFactor();

	if (bf == BALANCED)
	{
		avlFlag = false;
		return tNode;
	}
	else if (bf == LEFT_HEAVY || bf == RIGHT_HEAVY)
	{
		//keep going
		return tNode;
	}
	else
	{
		if (bf == LEFT_UNBALANCED)
		{
			AVLTreeNode<T>* left = tNode->getLeft();
			AVL bf_l = left->getBalanceFactor();
			if (bf_l == RIGHT_HEAVY)
			{
				//Double left then right
				tNode = rotateLeftRight(tNode);
			}
			else
			{
				//single right
				tNode = rotateRight(tNode);
			}
		}
		else
		{
			AVLTreeNode<T>* right = tNode->getRight();
			AVL bf_r = right->getBalanceFactor();
			if (bf_r == LEFT_HEAVY)
			{
				//double right then left
				tNode = rotateRightLeft(tNode);
			}
			else
			{
				//single left
				tNode = rotateLeft(tNode);
			}
		}

		avlFlag = false;
		return tNode;
	}
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::rotateLeft(AVLTreeNode<T>* tNode)
{
	//All the nodes I need for rotation
	AVLTreeNode<T>* r = tNode->getRight();
	AVLTreeNode<T>* r_l = tNode->getRight();

	//actually rotating.
	r->setLeft(tNode);
	tNode->setRight(r_l);

	tNode->setBalanceFactor(BALANCED);
	r->setBalanceFactor(BALANCED);

	return r;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::rotateRight(AVLTreeNode<T>* tNode)
{
	//Declaring the nodes I will need for the rotation.
	AVLTreeNode<T>* l = tNode->getLeft();
	AVLTreeNode<T>* l_r = l->getRight();

	//Actually rotating them.
	l->setRight(tNode);
	tNode->setLeft(l_r);

	tNode->setBalanceFactor(BALANCED);
	l->setBalanceFactor(BALANCED);

	return l;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::rotateLeftRight(AVLTreeNode<T>* tNode)
{
	//All the nodes you need for a double rotation.
	AVLTreeNode<T>* l = tNode->getLeft();
	AVLTreeNode<T>* l_r = l->getRight();
	AVLTreeNode<T>* l_r_l = l_r->getLeft();
	AVLTreeNode<T>* l_r_r = l_r->getRight();
	AVLTreeNode<T>* r = tNode->getRight();

	//actually rotating the nodes. Drew myself a picture to make this easier.
	l_r->setRight(tNode);
	l_r->setLeft(l);
	tNode->setLeft(l_r_r);
	l->setRight(l_r_l);

	//check flags or whateverrrr.....DOUBLE CHECK THIS.............
	
	AVL lf = l_r->getBalanceFactor();
	l_r->setBalanceFactor(BALANCED);
	l->setBalanceFactor(BALANCED);
	if (lf == LEFT_HEAVY)
	{
		tNode->setBalanceFactor(RIGHT_HEAVY);
	}
	else
	{
		tNode->setBalanceFactor(BALANCED);
	}

	if (r != NULL)
	{
		AVL rf = r->getBalanceFactor();
		if (rf == RIGHT_HEAVY && lf == RIGHT_HEAVY)
		{
			r->setBalanceFactor(LEFT_HEAVY);
		}
	}



	return l_r;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::rotateRightLeft(AVLTreeNode<T>* tNode)
{
	//All the nodes you need for a double rotation.
	AVLTreeNode<T>* r = tNode->getRight();
	AVLTreeNode<T>* r_l = r->getLeft();
	AVLTreeNode<T>* r_l_r = r_l->getRight();
	AVLTreeNode<T>* r_l_l = r_l->getLeft();
	AVLTreeNode<T>* l = tNode->getLeft();

	r_l->setLeft(tNode);
	r_l->setRight(r);
	r->setLeft(r_l_r);
	tNode->setRight(r_l_l);

	//check flags....... DOUBLE CHECK THIS.............
	/*
	AVL rf = r_l->getBalanceFactor();
	r_l->setBalanceFactor(BALANCED);
	r->setBalanceFactor(BALANCED);
	if (rf == RIGHT_HEAVY)
	{
		tNode->setBalanceFactor(LEFT_HEAVY);
	}
	else
	{
		tNode->setBalanceFactor(BALANCED);
	}
	if (l != NULL)
	{
		AVL lf = l->getBalanceFactor();
		if (lf == LEFT_HEAVY && rf == LEFT_HEAVY)
		{
			l->setBalanceFactor(RIGHT_HEAVY);
		}
	}
	*/

	return r_l;
}

//the below GUI-related methods have been completed for you
template < class T >
void AVLTree<T>::draw(Cairo::RefPtr<Cairo::Context> cr, int width, int height)
{
   Line line(new Color(0, 0, 0), 5.0);
   drawRec(getRootNode(), cr, &line, width, width/2, 20);
}

template < class T >
void AVLTree<T>::drawRec(AVLTreeNode<T>* tNode, Cairo::RefPtr<Cairo::Context> cr, Line* line, int x_parent, int x_curr, int y_curr)
{

   //traversal to draw the entire binary tree
   if (tNode != NULL)
   {
      //computing the location of the current node's two children
      //the distance between a node's two children is the same as the horizontal distance between
      //the current node and the current node's parent
      //need to do this first as the drawing is from the bottom to the top
      int separation = abs(x_curr - x_parent);

      //need to make sure that the children are symmetrically placed with respect to the parent
      int x_left = x_curr - separation/2;  //the location of the left child
      int x_right = x_left + separation;   //the location of the right child

      //compute the vertical location of the current node's parent
      //and the current node's two children
      int y_parent = y_curr - 50;
      int y_children = y_curr + 50;

      //draw the line connecting the current node to its parent
      if (tNode != root)
      {
         line->draw(cr, x_curr, y_curr, x_parent, y_parent);
      }

      //draw the children
      drawRec(tNode->getLeft(), cr, line, x_curr, x_left, y_children);
      drawRec(tNode->getRight(), cr, line, x_curr, x_right, y_children);

      //draw tNode
      tNode->draw(cr, x_curr, y_curr);
   }
}

template < class T >
void AVLTree<T>::mouseClicked(int x, int y) {}

#endif
