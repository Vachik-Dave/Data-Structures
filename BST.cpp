/*
This is simple binary search tree program with basic operations such as insertion, deletion and all three way of travarsal.

Here, I added sucessor of current node is maintained as a part of tree_node structure. All operations on the BST support to maintain this sucessor value.

Author: Vachik Dave
*/


#include <iostream>
#include <cstdlib>
using namespace std;

class BinarySearchTree
{
    private:
        struct tree_node
        {
		tree_node* left;
		tree_node* right;
		int data;
		tree_node* suc;
        };
        tree_node* root;
    
    public:
        BinarySearchTree()
        {
		root = NULL;
        }
        void insert(int);
        void remove(int);
        bool isEmpty() const { return root==NULL; }
        void print_inorder();
        void inorder(tree_node*);
        void print_preorder();
        void preorder(tree_node*);
        void print_postorder();
        void postorder(tree_node*);
	tree_node* Tree_max(tree_node* curr)
	{
		struct tree_node* ret= curr;
		if(curr == NULL)
			return ret;
		while(ret->right != NULL)
			ret = ret->right;
	
		return ret;
	}
	tree_node* Predecessor(tree_node* curr)
	{

		if(curr->left != NULL)
			return Tree_max(curr->left);


		// find the last right
		tree_node* r = NULL;
		int d  = curr->data;
		tree_node* temp = root;
		while(temp != NULL)
		{
			if(temp == curr)
			{
				break;
			}
			else
			{
				if(d > temp->data) 
				{
					r = temp;
					temp = temp->right;
				}
				else 
					temp = temp->left;
			}
		}
		// last right is predecessor
		return r;
	}

};

// Smaller elements go left
// larger elements go right
void BinarySearchTree::insert(int d)
{
	tree_node* t = new tree_node;
	tree_node* parent;
	t->data = d;
	t->left = NULL;
	t->right = NULL;
	parent = NULL;
	tree_node* curr;
	curr = this->root;

	// keeping address of the node where last left and last right is taken
	tree_node *l, *r;
	l = NULL;
	r = NULL;

	while(curr)
	{
		parent = curr;
		if(d < curr->data)
		{
			l = curr;
			curr = curr->left;
		}
		else
		{
			r = curr;
			curr = curr->right;
		}
	}
	
	// last left would be sucessor of current new node
	t->suc = l;
	// new node would be sucessor of the last right 
	if(r != NULL)
		r->suc = t;
	if(parent == NULL)
		this->root = t;
	else if(d < parent->data)
		parent->left = t;
	else
		parent->right = t;
	
}

void BinarySearchTree::remove(int d)
{
	//Locate the element
	bool found = false;
	if(isEmpty())
	{
		cout<<" This Tree is empty! "<<endl;
		return;
	}

	// search the node with the value

	tree_node* curr;
	tree_node* parent;

	curr = root;

	while(curr != NULL)
	{
		if(curr->data == d)
		{
			found = true;
			break;
		}
		else
		{
			parent = curr;
			if(d > curr->data) 
			{
				curr = curr->right;
			}
			else 
				curr = curr->left;
		}
	}
	if(!found)
	{
		cout<<" Data not found! "<<endl;
		return;
	}

	tree_node* pred = Predecessor(curr);


		 // 3 cases :
	// 1. We're removing a leaf node
	// 2. We're removing a node with a single child
	// 3. we're removing a node with 2 children

	//We're looking at a leaf node
	if( curr->left == NULL && curr->right == NULL)
	{
		if(parent->left == curr) 
			parent->left = NULL;
		else 
			parent->right = NULL;

		if(pred != NULL)
			pred->suc = curr->suc;

		delete curr;
		return;
	}

	// Node with single child
	if((curr->left == NULL && curr->right != NULL)|| (curr->left != NULL && curr->right == NULL))
	{
		if(curr->left == NULL && curr->right != NULL)
		{
			if(pred != NULL)
				pred->suc = curr->suc;
			if(parent->left == curr)
			{
				parent->left = curr->right;
				delete curr;
			}
			else
			{
				parent->right = curr->right;
				delete curr;
			}
		}
		else // left child present, no right child
		{
			if(pred != NULL)
				pred->suc = curr->suc;

			if(parent->left == curr)
			{
				parent->left = curr->left;
				delete curr;
			}
			else
			{
				parent->right = curr->left;
				delete curr;
			}
		}
		return;
	}



	//Node with 2 children
	// replace node with smallest value in right subtree
	if (curr->left != NULL && curr->right != NULL)
	{
		// here in all cases program is finding sucessor as regular BST tree node idea
		// however we can user curr->suc to get that node in current special case
		
		tree_node* chkr;
		chkr = curr->right;
		// right child is a leaf
		if((chkr->left == NULL) && (chkr->right == NULL))
		{
			// copy(overwrite) data of sucessor node
			curr->data = chkr->data;
			curr->suc = chkr->suc;

			// delete sucessor node (values are copied)
			delete chkr;

			curr->right = NULL;
		}
		else // right child has children
		{
			//if the node's right child has a left child
			// Move all the way down left to locate smallest element
			if((curr->right)->left != NULL)
			{
				tree_node* lcurr;
				tree_node* lcurrp;
				lcurrp = curr->right;
				lcurr = (curr->right)->left;
				while(lcurr->left != NULL)
				{
					lcurrp = lcurr;
					lcurr = lcurr->left;
				}
				// copy(overwrite) data of sucessor node
				curr->data = lcurr->data;
				curr->suc = lcurr->suc;

				// set link for right subtree of the sucessor
				lcurrp->left = lcurr->right;

				// delete sucessor node (values are copied)
				delete lcurr;
			}
			else
			{
				tree_node* tmp;
				tmp = curr->right;

				// copy(overwrite) data of sucessor node
				curr->data = tmp->data;
				curr->right = tmp->right;
				curr->suc = tmp->suc;
				// delete sucessor node (values are copied)
				delete tmp;
			}

		}
		return;
	}

}

void BinarySearchTree::print_inorder()
{
  inorder(root);
}

void BinarySearchTree::inorder(tree_node* p)
{
    if(p != NULL)
    {
        if(p->left) inorder(p->left);
	if(p->suc != NULL)
		cout<<" "<<p->data<<"-"<<p->suc->data<<" ";
	else
		cout<<" "<<p->data<<"-"<<" ";
        if(p->right) inorder(p->right);
    }
    else return;
}

void BinarySearchTree::print_preorder()
{
    preorder(root);
}

void BinarySearchTree::preorder(tree_node* p)
{
    if(p != NULL)
    {
	if(p->suc != NULL)
		cout<<" "<<p->data<<"-"<<p->suc->data<<" ";
	else
		cout<<" "<<p->data<<"-"<<" ";
        if(p->left) preorder(p->left);
        if(p->right) preorder(p->right);
    }
    else return;
}

void BinarySearchTree::print_postorder()
{
    postorder(root);
}

void BinarySearchTree::postorder(tree_node* p)
{
    if(p != NULL)
    {
        if(p->left) postorder(p->left);
        if(p->right) postorder(p->right);
	if(p->suc != NULL)
		cout<<" "<<p->data<<"-"<<p->suc->data<<" ";
	else
		cout<<" "<<p->data<<"-"<<" ";

    }
    else return;
}

int main()
{
    BinarySearchTree b;
    int ch,tmp,tmp1;
    while(1)
    {
       cout<<endl<<endl;
       cout<<" Binary Search Tree Operations "<<endl;
       cout<<" ----------------------------- "<<endl;
       cout<<" 1. Insertion/Creation "<<endl;
       cout<<" 2. Removal "<<endl;
       cout<<" 3. In-Order Traversal "<<endl;
       cout<<" 4. Pre-Order Traversal "<<endl;
       cout<<" 5. Post-Order Traversal "<<endl;
       cout<<" 6. Exit "<<endl;
       cout<<" Enter your choice : ";
       cin>>ch;
       switch(ch)
       {
		case 1 : cout<<" Enter Number to be inserted : ";
			cin>>tmp;
			b.insert(tmp);
			break;
		case 2 : cout<<" Enter data to be deleted : ";
			cin>>tmp1;
			b.remove(tmp1);
			break;
		case 3 : cout<<endl;
			cout<<" In-Order Traversal "<<endl;
			cout<<" -------------------"<<endl;
			b.print_inorder();
			break;
		case 4 : cout<<endl;
			cout<<" Pre-Order Traversal "<<endl;
			cout<<" -------------------"<<endl;
			b.print_preorder();
			break;
		case 5 : cout<<endl;
			cout<<" Post-Order Traversal "<<endl;
			cout<<" --------------------"<<endl;
			b.print_postorder();
			break;
		case 6 : 
			return 0;
//		default:
//			return 0;

            
       }
    }
}

