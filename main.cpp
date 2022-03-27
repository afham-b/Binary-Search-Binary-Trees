//Afham Bashir 
//Assignment 6 
#include <iostream>
#include <string>
#include <vector> 
using namespace std;

class BSTree {
private:

	// Sub-class to represent nodes within the tree
	class node {
	public:
		string data;
		node* left;
		node* right;
		node () { left = right = nullptr; }
	};

	// Pointer to the root node, initially NULL
	node* root;

	// Finds a node in a given subtree. Returns true/false to indicate if
	//	node with given string is in the subtree.
	bool find (const string& s, node* p) const {
		// Given: p is a pointer to an existing node
		if (s == p->data)
			return true;
		if (s < p->data)
			return p->left && find(s, p->left);
		return p->right && find(s, p->right);
	}

	// Inserts a new node into the subtree at the given pointer.
	void insert (const string& s, node* p) {
		// Given: p is a pointer to an existing node (root of a subtree)
		if (s < p->data) { // Insert into left subtree
			if (p->left) // Left subtree exists
				insert(s, p->left);
			else { // No left subtree, insert the new node
				p->left = new node;
				p->left->data = s;
			}
		}
		else if (s > p->data) { // Insert into right subtree
			if (p->right)
				insert(s, p->right);
			else {
				p->right = new node;
				p->right->data = s;
			}
		}
	}

	// Performs an inorder traversal of the subtree at node p. For each node
	//	prints the string stored at that node.
	void print_inorder (node* p) const {
		// Print all values in subtree, in order
		if (p) {
			print_inorder(p->left);
			cout << p->data << endl;
			print_inorder(p->right);
		}
	}

	// Perform a preorder traversal of the subtree at node p, also given the
	//	depth at node p. For each node, prints the string stored at the node
	//	with prefix showing the depth.
	void print_preorder (node* p, size_t depth) const {
		if (p) {
			for (size_t i = 0; i < depth; i++)
				cout << '-';
			cout << p->data << endl;
			print_preorder(p->left, depth + 1);
			print_preorder(p->right, depth + 1);
		}
	}

public:

	// Constructor - Sets the root node to NULL
	BSTree() { root = nullptr; }

	// Find a string in the tree. Returns true/false to indicate if the given
	//	string is in the tree.
	bool find (const string& s) const {
		return root && find(s, root);
	}

	// Inserts a string into the tree. If the string already exists in the
	//	tree, does nothing.
	void insert (const string& s) {
		// Is tree empty?
		if (!root) {
			root = new node;
			root->data = s;
		}
		else if (s < root->data) {
			// New node goes on left side of root
			if (root->left) // If there is a left subtree
				insert(s, root->left);
			else { // No left subtree, create node
				root->left = new node;
				root->left->data = s;
			}
		}
		else if (s > root->data) {
			if (root->right)
				insert(s, root->right);
			else {
				root->right = new node;
				root->right->data = s;
			}
		}
	}

	// Perform an inorder traversal on the tree. The traversal simply prints
	//	the string stored at each node.
	void print_inorder () const { print_inorder(root); }

	// Perform a preorder traversal, printing strings stored at each node
	//	while showing tree structure.
	void print_preorder () const { print_preorder(root, 0); }

	// TODO: Implement these functions...

  // Returns the height of the tree (longest path from root to a leaf)
  size_t height() const { return (heights(root)); } //driver function for heights 
	int heights (node* node) const {    //constant function takes node and recursively find height

    if (node == nullptr) { // if the tree is empty 
      return -1; // no height, height is zero at one node
    }
    else   
      // recursively calls the heights function which finds the max of the two heights of each sub tree. 
      return 1+max(heights(node->left), heights(node->right));  
  } 


  size_t leaves () const {return leaves (root); }  //driver function
	// Returns the number of leaf nodes in the tree
	size_t leaves (node* node) const {
   if (!node) { // if the tree is empty 
       return 0;// no leaves;
   } 
  
  if( node->left == NULL && node->right == NULL ) //there are no child nodes. 
   return 1; 
  else {
      return leaves(node->left) + leaves(node->right) ; // adds leafs from left subtree and right subtree 
    }
   } 


  
	// Returns the string stored in the parent node of the node with the
	//	given string. If the given string does not exist in the tree, or
	//	exists in the root, returns an empty string.
	string parent (const string& s) const { 
    if( s == root->data)
      return "";  // this is the root node
    if ( !find(s))  
      return ""; // string doesnt exist in tree. 

    node* parentlocation = new node;   //pointer to parent node
    node* stringlocation = new node;   //pointer to string's node
    node* temp = new node;             //temporary node. 
    temp = root; 

    while ( temp!= NULL) {     //loops untill the node reaches null
      if(s == temp->data){           
          stringlocation = temp;   // if the node data matches the string, the string location becomes that node
      }
      else if ( temp->data > s ) { // if the data of the node is greater than the inputed node
        parentlocation = temp;    // the parent node become the last node, before temp goes into subtree
        temp = temp->left;       //the node goes into the left subtree 
        } 
        else { 
           parentlocation = temp;
          temp = temp-> right; // goes into right right child node 
    }
  } 
  return parentlocation->data; } //return string at parent node. 


	// Returns the string stored in the sibling node of the node with the
	//	given string. If the given string does not exist in the tree, or
	//	exists in a node that has no sibling node, returns an empty string.
	string sibling (const string& s) const { 
    if ( !find(s))
      return " No Sibling"; // string doesnt exist in tree. 
    if ( s == root->data)
      return " No Sibling"; //string is at the root node 

  node* siblingLocation = new node; 
  node* parentlocation = new node; 
  node* stringlocation = new node; 
  node* temp = new node;  
  temp = root; 

  while ( temp!= NULL) {    //loop searchs for node location of the string
      if(s == temp->data){
          stringlocation = temp; 
      }
      else if ( temp->data > s ) { //looks into left subtree
        parentlocation = temp;
        temp = temp->left;
        } 
        else { 
           parentlocation = temp; //goes into right subtree
          temp = temp-> right; 
    }
  } 

  //using the parent node, look for sibling node
  if( parentlocation->right->data == s) { 
    //if the string is at the right node, check if the left node exists, and output data if it does
    if( parentlocation->left ) {      
      return parentlocation->left->data;} 
      else return "Node has no Siblings"; } //left node DNE 
  if ( parentlocation->left->data == s) { 
    //if the string is at the left node, check if the right node exists, and output data if it does
    if( parentlocation->right ) { 
      return parentlocation->right->data;} 
      else return "Node has no Siblings"; } //right node DNE

    return "";}  
};

int main () {
	BSTree tree;
	string s;

	cout << "Enter strings to insert into the binary search tree.\n";
	cout << "When finished, press ENTER.\n\n";
	cout << "> ";
	getline(cin, s);
	while (s.size()) {
		tree.insert(s);
		cout << "> ";
		getline(cin, s);
	}

	cout << "\nAn inorder traversal:\n";
	tree.print_inorder();

	cout << "\nA preorder traversal:\n";
	tree.print_preorder();

  cout << "\nheight is " << tree.height() << endl; 
  cout << "Number of leaf node in tree is " << tree.leaves() <<endl; 
  cout << "Enter String to find the Parent Node and Sibling Node: " ; 
  getline(cin, s); 
  cout << " The Parent Node is: " << tree.parent(s) << endl; 
  cout << " The Sibling Node is:"  << tree.sibling(s) <<endl; 

	return 0;
}