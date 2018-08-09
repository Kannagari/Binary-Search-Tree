#include <iostream>
#include <random>

using namespace std;

//Structure of the different nodes (or leaves) of the tree
//Containing data and pointers to left/right children if present
struct Node {
	int data; 
	Node *left;
	Node *right;
};

class BinTree
{
public:
	BinTree(); //Constructor to initialize root to NULL
	~BinTree(); //Destructor to help delete the tree when needed
	bool isEmpty(); //Checking if tree is empty
	Node* createNode(int x); //Function passed a data value, to be turned into a node
	Node* insert(int x); //Function that will insert node into a tree, calls createNode from within
	void search(int x); //Search the tree for the passed value
	void PreOrderPrint(); //Print tree in PreOrder traversal
	void InOrderPrint(); //Print tree in InOrder traversal
	void PostOrderPrint(); //Print tree in PostOrder traversal
	int getMax(); //Function to find max value in the tree and return it
	int getMin(); //Function to find the minimum value in the tree and return it
	int getSize(); //Function to get the size of the tree
	int maxHeight(); //Function to calculate the max height of the tree
	Node* remove(int x); //Function to delete a node with passed value from the tree

private:
	Node* root;
	int size;


	Node* destroyTreeHelper(Node* n)
	{

		//If the node passed doesnt exist, return
		if (n == nullptr)
			return n;

		//Recursively call destroyTreeHelper on both the left and right subtrees before deleting the current Node
		else
		{
			destroyTreeHelper(n->left);
			destroyTreeHelper(n->right);
			delete n;


		}
		//Set size to 0, root to nullptr, and return
		size = 0;
		root = nullptr;
		return root;


	}

	void insertHelper(Node* n, int x)
	{
		//If the value you want to insert is smaller than the root
		if (x < n->data)
		{
			//Check if a left child exists
			//Inserting the new node there if a left child is not present
			if (!n->left)
				n->left = createNode(x);
			//If a left child is present
			//Slide left and recursively check using the left child's data
			else
				insertHelper(n->left, x);

		}
			
		//If the value you want to insert is bigger than the root
		else
		{
			//Check if a right child exists
			//Inserting the new node there if a right child is not present
			if (!n->right)
				n->right = createNode(x);
			//If a right child is present
			//Slide right and recursively check using the right child's data
			else
				insertHelper(n->right, x);
		}
			


	}

	bool searchHelper(Node* n, int x)
	{
		//If we reach a point where the current node doesnt exist, we failed to find the value
		//Return false
		if (n == nullptr)
			return false;

		//If the current nodes data is what we're looking for
		//Return true
		if (n->data == x)
			return true;

		//If the value we want is less than the current nodes data
		//Recursively search the left subtree
		if (x < n->data)
			searchHelper(n->left, x);

		//Else, we know the value we want must be bigger than the current node
		//Hence, we recursively search the right subtree
		else
			searchHelper(n->right, x);


	}

	void PreOrderHelper(Node* n)
	{
		//PreOrder is Node, Left, Right

		//If the node passed does not exist, return
		if (n == nullptr)
			return;

		//Print the Nodes data, then recursively check the left, then right, subtrees
		cout << n->data << " ";
		PreOrderHelper(n->left);
		PreOrderHelper(n->right);

	}
	
	void InOrderHelper(Node* n)
	{
		//Inorder is Left, Node, Right

		//Make sure the node passed exists, return if not
		if (n == nullptr)
			return;

		//Check recursively if the left child exists, then print nodes data, then check right child
		InOrderHelper(n->left);
		cout << n->data << " ";
		InOrderHelper(n->right);

	}

	void PostOrderHelper(Node* n)
	{
		//PostOrder is Left, Right, Node

		//Make sure the node being passed exists, return if it doesnt
		if (n == nullptr)
			return;

		//Check recursively the left child, then the right child, then print the nodes data
		PostOrderHelper(n->left);
		PostOrderHelper(n->right);
		cout << n->data << " ";

	}

	int maxHelper(Node* n)
	{
		int max;
		//If this is as far right as you can go
		//Thats the max value, return it
		if (n->right == nullptr)
		{
			max = n->data;
			return max;
		}
			
		//Else, keep going right
		else
			maxHelper(n->right);

	}

	int minHelper(Node* n)
	{
		int min;

		//If thats as far left as you can go
		//Thats the minimum value, return it
		if (n->left == nullptr)
		{
			min = n->data;
			return min;

		}
		//Else, keep going left
		else
			minHelper(n->left);


	}

	int sizeHelper()
	{
		//Return private class value size
		return size;

	}

	int maxHeightHelper(Node* n)
	{
		//If the root does not exist, the height is 0
		if (n == nullptr)
			return 0;

		//Else, recursively calculate the height of the left and right subtrees
		else
		{
			int leftHeight = maxHeightHelper(n->left);
			int rightHeight = maxHeightHelper(n->right);

			if (leftHeight > rightHeight)
				return leftHeight + 1;
			else
				return rightHeight + 1;

		}


	}

	Node* minNodeFinder(Node* n)
	{
		//Find the leftmost node and return it
		if (n->left == nullptr)
			return n;
		else
			minNodeFinder(n->left);

	}

	Node* removeHelper(Node* n, int x)
	{
		Node* temp;

		//If the tree is empty or the desired node was not found
		if (n == nullptr)
		{
			cout << "A node with that value was not found in the tree.\n";
			return n;
		}
			

		//Recursively search for the node with your passsed data value
		if (x < n->data)
			n->left = removeHelper(n->left, x);

		else if (x > n->data)
			n->right = removeHelper(n->right, x);

		//If you found the node with the value you're looking for
		//And that node has two children
		else if (n->left && n->right)
		{
			//Find the smallest node in the right subtree of the node you want to delete
			temp = minNodeFinder(n->right);
			//Make current nodes data = the temp nodes data
			n->data = temp->data;
			//Recursively call remove helper to delete the node with desired value
			n->right = removeHelper(n->right, n->data);

			cout << "Node successfully deleted!\n";

			//Decrease size
			size--;


		}

		//Else, the desired node has 0 or 1 children/child
		else
		{

			temp = n;

			//If only the right child exists
			if (n->left == nullptr)
				n = n->right; //Move it to its parent's location

			//Else if only the left child exists
			else if (n->right == nullptr)
				n = n->left; //Move it to its parents location

			delete temp; //Delete the parent

			cout << "Node successfully deleted!\n";

			//Decrement size
			size--;

		}

		return n;
	}
};

BinTree::BinTree()
{
	//Constructor initializing root to null, and size to 0
	root == nullptr;
	size = 0;


}

BinTree::~BinTree()
{
	//Destructor calling destroyTreeHelper, passing the tree's root
	destroyTreeHelper(this->root);

}

bool BinTree::isEmpty()
{
	//Checking if the tree's root is null, meaning the tree would be empty
	return(root == nullptr);

}

Node* BinTree::createNode(int x)
{

	Node* n = new Node; // Allocate space for a new value of Node* type
	n->data = x; //Set the nodes data to the passed value
	n->left = nullptr; //Set left child to Null
	n->right = nullptr; //Set right child to Null

	//Print out the value of the node you successfully just created
	cout << "Successfully created a node with value: " << n->data << endl;
	//Increase the size of the tree
	size++;

	return n;


}

Node* BinTree::insert(int x)
{
	//If the tree is empty
	if (isEmpty()) 
	{
		//Set root equal to the new node you created
		root = createNode(x);
		return root;
	}

	//If the tree already has a root (it is not empty)
	//Call insert helper, passing it root and the value of the desired node
	else
		insertHelper(this->root, x);


}

void BinTree::search(int x)
{
	//If the value is found in the tree
	//Print that it was
	//Else, print that it wasn't
	if (searchHelper(this->root, x))
		cout << x << " was found in the tree!\n";
	else
		cout << x << " was not found in the tree\n";

	
}

void BinTree::PreOrderPrint()
{
	//Call PreOrderHelper, passing it root
	PreOrderHelper(this->root);
}

void BinTree::InOrderPrint()
{
	//Call InOrderHelper, passing it root
	InOrderHelper(this->root);
}

void BinTree::PostOrderPrint()
{
	//Call PostOrderHelper, passing it root
	PostOrderHelper(this->root);
}

int BinTree::getMax()
{
	//Pass maxHelper root, and return the max value that it passes back
	int max = maxHelper(this->root);
	return max;

}

int BinTree::getMin()
{
	//Pass minHelper the root of the tree and accept the min value it passes you back
	int min = minHelper(this->root);
	return min;


}

int BinTree::getSize()
{
	//Call sizeHelper and return the size
	int s = sizeHelper();
	return s;

}

int BinTree::maxHeight()
{
	int height = maxHeightHelper(this->root);
	return height;

}

Node* BinTree::remove(int x)
{
	if (isEmpty())
		return root;
	else
		removeHelper(this->root, x);

}

int main()
{
	//Create an instance of the Binary Search Tree Class and some variables for later
	BinTree Tree;
	int max;
	int min;
	int NumNodes;
	int height;
	srand(4); //Seed srand with a arbitrary value

	//Generate random numbers, creating nodes for them, and inserting them into the tree
	for (int i = 0; i < 10; i++)
		Tree.insert(rand() % 101);


	cout << "The values in PreOrder Traversal are: ";
	Tree.PreOrderPrint();
	cout << "\n\n";

	cout << "The values in InOrder Traversal are: ";
	Tree.InOrderPrint();
	cout << "\n\n";

	cout << "The values in PostOrder Traversal are: ";
	Tree.PostOrderPrint();
	cout << "\n\n";

	Tree.search(9);
	cout << "\n";
	Tree.search(87);
	cout << "\n";


	max = Tree.getMax();
	cout << "The max value within the tree is: " << max << endl;
	cout << "\n";

	min = Tree.getMin();
	cout << "The min value within the tree is: " << min << endl;
	cout << "\n";

	NumNodes = Tree.getSize();
	cout << "The number of nodes currently in the tree is: " << NumNodes << endl;
	cout << "\n";

	height = Tree.maxHeight();
	cout << "The maximum height of the tree is: " << height << endl;
	cout << "\n";

	cout << "Attempting to delete node with value 700\n";
	Tree.remove(700);
	cout << "\n";

	NumNodes = Tree.getSize();
	cout << "The number of nodes currently in the tree is: " << NumNodes << endl;
	cout << "\n";

	cout << "Attempting to delete node with value 9\n";
	Tree.remove(9);
	cout << "\n";

	NumNodes = Tree.getSize();
	cout << "The number of nodes currently in the tree is: " << NumNodes << endl;
	cout << "\n";

	cout << "Deleting the entire tree.\n";
	Tree.~BinTree();
	NumNodes = Tree.getSize();
	cout << "The number of nodes currently in the tree is: " << NumNodes << endl;

	

	system("pause");

	return 0;

}
