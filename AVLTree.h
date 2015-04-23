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
		//Post: Begins to delete everything.
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
		//Pre:  Must pass valid, non-Null value.
		//Post: Returns the 'root' node after all the necessary rotation have been applied in order to make the tree a valid AVL tree. (fixes if there was an insertion to the left)
	AVLTreeNode<T>* avlFixAddLeft(AVLTreeNode<T>* tNode);
		//Pre:  Must pass valid, non-Null value.
		//Post: Returns the 'root' node after all the necessary rotation have been applied in order to make the tree a valid AVL tree. (fixes if there was an insertion to the right)
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
		T* item = root->getItem();
		return item;
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
	//Declaring local variables.
	AVLTreeNode<T>* l = tNode->getLeft();
	AVLTreeNode<T>* r = tNode->getRight();

	int LeftHeight = getHeight(l);
	int RightHeight = getHeight(r);

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
	int height = getHeight(root);
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
	//Declaring local variables.
	AVLTreeNode<T>* l = tNode->getLeft();
	AVLTreeNode<T>* r = tNode->getRight();
	bool l_b = isBalanced(l);
	bool r_b = isBalanced(r);

	if (!l_b || !r_b)
	{
		return false;
	}

	int l_h = getHeight(l);
	int r_h = getHeight(r);
	int h = abs(r_h - l_h);

	if (h < 2)
	{
		return true;
	}
		
	return false;
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
	if(tNode == NULL)
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
		AVLTreeNode<T>* subtree = insertItem(l, item);
		tNode->setLeft(subtree);
		if(avlFlag)
		{
			tNode->insertLeft();
		}
	}
	else if (comp > 0)
	{
		AVLTreeNode<T>* r = tNode->getRight();
		AVLTreeNode<T>* subtree = insertItem(r, item);
		tNode->setRight(subtree);
		if (avlFlag)
		{
			tNode->insertRight();
		}
	}
	
	//Need to set the flag to false on all of these.
	if (tNode->getBalanceFactor() == BALANCED)
	{
		avlFlag = false;
	}
	else if (tNode->getBalanceFactor() == LEFT_UNBALANCED)
	{
		tNode = avlFixAddLeft(tNode);
		avlFlag = false;
	}
	else if (tNode->getBalanceFactor() == RIGHT_UNBALANCED)
	{
		tNode = avlFixAddRight(tNode);
		avlFlag = false;
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
		T* item = curr->getItem();
		comp = (*compare_keys)(sk, item);

		if (comp == 0)
		{
			return item;
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
		AVLTreeNode<T>* l = tNode->getLeft();
		AVLTreeNode<T>* r = tNode->getRight();
		destroyItem(l);
		destroyItem(r);
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
	//Declaring local variables.
	AVLTreeNode<T>* subtree;
	AVLTreeNode<T>* left = tNode->getLeft();
	AVL bf = left->getBalanceFactor();

	if (bf == LEFT_HEAVY)
	{
		subtree = rotateRight(tNode);
	}
	else
	{
		AVLTreeNode<T>* left_right = left->getRight();
		AVL bf_lr = left_right->getBalanceFactor();

		tNode->setLeft(rotateLeft(left));
		subtree = rotateRight(tNode);

		if (bf_lr == LEFT_HEAVY)
		{
			tNode->setBalanceFactor(RIGHT_HEAVY);
			left->setBalanceFactor(BALANCED);
			left_right->setBalanceFactor(BALANCED);
		}
		else if (bf_lr == RIGHT_HEAVY)
		{
			tNode->setBalanceFactor(BALANCED);
			left->setBalanceFactor(LEFT_HEAVY);
			left_right->setBalanceFactor(BALANCED);
		}
		else
		{
			tNode->setBalanceFactor(BALANCED);
			left->setBalanceFactor(BALANCED);
			left_right->setBalanceFactor(BALANCED);
		}
	}

	return subtree;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::avlFixAddRight(AVLTreeNode<T>* tNode)
{
	AVLTreeNode<T>* subtree;
	AVLTreeNode<T>* right = tNode->getRight();
	AVL bf = right->getBalanceFactor();

	if (bf == RIGHT_HEAVY)
	{
		subtree = rotateLeft(tNode);
	}
	else
	{
		AVLTreeNode<T>* right_left = right->getLeft();
		AVL bf_rl = right_left->getBalanceFactor();

		tNode->setRight(rotateRight(right));
		subtree = rotateLeft(tNode);

		if (bf_rl == LEFT_HEAVY)
		{
			tNode->setBalanceFactor(RIGHT_HEAVY);
			right->setBalanceFactor(BALANCED);
			right_left->setBalanceFactor(BALANCED);
		}
		else if (bf_rl == RIGHT_HEAVY)
		{
			tNode->setBalanceFactor(BALANCED);
			right->setBalanceFactor(LEFT_HEAVY);
			right_left->setBalanceFactor(BALANCED);
		}
		else
		{
			tNode->setBalanceFactor(BALANCED);
			right->setBalanceFactor(BALANCED);
			right_left->setBalanceFactor(BALANCED);
		}
	}

	return subtree;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::rotateLeft(AVLTreeNode<T>* tNode)
{
	//All the nodes I need for rotation
	AVLTreeNode<T>* p = tNode;
	AVLTreeNode<T>* r = p->getRight();
	AVLTreeNode<T>* r_l = r->getLeft();

	//actually rotating.
	r->setLeft(p);
	p->setRight(r_l);

	p->setBalanceFactor(BALANCED);
	r->setBalanceFactor(BALANCED);

	return r;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::rotateRight(AVLTreeNode<T>* tNode)
{
	//Declaring the nodes I will need for the rotation.
	AVLTreeNode<T>* p = tNode;
	AVLTreeNode<T>* l = p->getLeft();
	AVLTreeNode<T>* l_r = l->getRight();

	//Actually rotating them.
	l->setRight(p);
	p->setLeft(l_r);

	p->setBalanceFactor(BALANCED);
	l->setBalanceFactor(BALANCED);

	return l;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::rotateLeftRight(AVLTreeNode<T>* tNode)
{
	//All the nodes you need for a double rotation.
	AVLTreeNode<T>* l = tNode->getLeft();
	AVLTreeNode<T>* r = tNode->getRight();
	AVLTreeNode<T>* l_r = l->getRight();
	AVLTreeNode<T>* l_r_l = l_r->getLeft();
	AVLTreeNode<T>* l_r_r = l_r->getRight();

	//actually rotating the nodes. Drew myself a picture to make this easier.
	l->setRight(l_r_l);
	tNode->setLeft(l_r_r);
	l_r->setLeft(l);
	l_r->setRight(tNode);
	

	//Checking the balance factors..
	AVL l_rf = l_r->getBalanceFactor();
	l_r->setBalanceFactor(BALANCED);
	l->setBalanceFactor(BALANCED);

	//modifying the balance factors
	if (l_rf == LEFT_HEAVY)
	{
		tNode->setBalanceFactor(RIGHT_HEAVY);
	}
	else if (l_rf == RIGHT_HEAVY)
	{
		l->setBalanceFactor(LEFT_HEAVY);
	}
	else
	{
		tNode->setBalanceFactor(BALANCED);
	}

	return l_r;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::rotateRightLeft(AVLTreeNode<T>* tNode)
{
	//All the nodes you need for a double rotation.
	AVLTreeNode<T>* r = tNode->getRight();
	AVLTreeNode<T>* l = tNode->getLeft();
	AVLTreeNode<T>* r_l = r->getLeft();
	AVLTreeNode<T>* r_l_r = r_l->getRight();
	AVLTreeNode<T>* r_l_l = r_l->getLeft();

	tNode->setRight(r_l_l);
	r->setLeft(r_l_r);
	r_l->setLeft(tNode);
	r_l->setRight(r);

	
	//check flags....... DOUBLE CHECK THIS.............
	AVL r_lf = r_l->getBalanceFactor();
	r_l->setBalanceFactor(BALANCED);
	r->setBalanceFactor(BALANCED);

	//modifying the balance factors.
	if (r_lf == RIGHT_HEAVY)
	{
		tNode->setBalanceFactor(LEFT_HEAVY);
	}
	else if (r_lf == LEFT_HEAVY)
	{
		r->setBalanceFactor(RIGHT_HEAVY);
	}
	else
	{
		tNode->setBalanceFactor(BALANCED);
	}

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
