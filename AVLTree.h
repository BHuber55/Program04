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

	//if false do not check.
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
AVLTree::AVLTree(int(*comp_items) (T* item_1, T* item_2), int(*comp_keys) (String* key, T* item))
{
	compare_items = comp_item;
	compare_keys = comp_keys;

	sze == 0;
	avlflag = false;
	root = NULL;
}

template < class T >
AVLTree::~AVLTree()
{
	destroy();
}

template < class T >
int AVLTree::size()
{
	return sze;
}

template < class T >
void AVLTree::insert(T* item)
{

}

template < class T >
T* AVLTree::retrieve(String* sk)
{

}

template < class T >
bool AVLTree::isEmpty()
{
	return sze == 0;
}

template < class T >
T* AVLTree::getRootItem()
{
	if (root != NULL)
	{
		return root->getItem();
	}

	return NULL;
}

template < class T >
AVLTreeIterator<T>* AVLTree::iterator()
{
	AVLTreeIterator<T>* iter = new AVLTreeIterator<T>(root);
	return iter;
}

template < class T >
int AVLTree::getHeight()
{
	int height;
	height = getHeight(root);
	return height;

}

template < class T >
bool AVLTree::isBalanced()
{
	bool balanced;
	balanced = isBalanced(root);
	return balanced;
}

template < class T >
AVLTreeNode<T>* AVLTree::avlFixAddLeft(AVLTreeNode<T>* tNode)
{

}

template < class T >
AVLTreeNode<T>* AVLTree::avlFixAddRight(AVLTreeNode<T>* tNode)
{

}

template < class T >
int AVLTree::getHeight(AVLTreeNode<T>* tNode)  //from lab
{
	int LeftHeight;
	int RightHeight;
	if (tNode == NULL)
	{
		return 0;
	}

	LeftHeight = getHeight(tNode->getLeft());
	RightHeight = getHeight(tNode->getRight());

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
bool AVLTree::isBalanced(AVLTreeNode<T>* tNode)
{
	if (tNode == NULL)
	{
		return true;
	}
	else
	{
		TreeNode<T>* left = tNode->getLeft();
		TreeNode<T>* right = tNode->getRight();
		bool leftBalanced = isBalanced(left);
		bool rightBalanced = isBalanced(right);

		if (leftBalanced == false || rightBalanced == false)
		{
			return false;
		}

		else
		{
			int leftHeight = getHeight(left);
			int rightHeight = getHeight(right);
			int x = abs(rightHeight - leftHeight);

			if (x < 2)
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
void AVLTree::destroyItem(AVLTreeNode<T>* tNode)
{
	if (tNode == NULL)
	{
		destoryItem(tNode->getLeft());
		destoryItem(tNode->getRight());
		delete tNode;
	}
}

template < class T >
void AVLTree::destroy()
{
	destroyItems(root);
	sze = 0;
	avlflag = false;
	root = NULL;
}

template < class T >
AVLTreeNode<T>* AVLTree::insertItem(AVLTreeNode<T>* tNode, T* item)
{

}

template < class T >
AVLTreeNode<T>* AVLTree::rotateLeft(AVLTreeNode<T>* tNode)
{

}

template < class T >
AVLTreeNode<T>* AVLTree::rotateRight(AVLTreeNode<T>* tNode)
{

}

template < class T >
AVLTreeNode<T>* AVLTree::rotateLeftRight(AVLTreeNode<T>* tNode)
{

}

template < class T >
AVLTreeNode<T>* AVLTree::rotateRightLeft(AVLTreeNode<T>* tNode)
{

}

template < class T >
void AVLTree::setRootNode(AVLTreeNode<T>* tNode) //you can get by without using these methods, refer to root directly
{

}

template < class T >
AVLTreeNode<T>* AVLTree::getRootNode()
{
	return root;
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
