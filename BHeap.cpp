#ifndef BHEAP_H
#define BHEAP_H
#include <iostream>
#include <string>

using namespace std;

template <typename keytype>
class BHeap {
	struct Node {
		Node* parent;
		Node* sibling;
		Node* child;
		keytype data;
		int degree;

		Node(keytype val) {
			data = val;
			degree = 0;
			parent= NULL;
			sibling= NULL;
			child= NULL;
		}
	};


	Node* head;
	Node* smallest;

public:
	BHeap(){
		head = NULL;
		smallest = NULL;
	}
	//constructor of BHeap with 1 node
	BHeap(keytype s) {
		Node* newN = new Node(s);
		head = newN;
		smallest = newN;
	}
	//constructor from array of data
	BHeap(keytype k[], int s) {
		head = NULL;
		smallest = NULL;
		for (int i = 0; i < s; i++) {
			insert(k[i]);
		}
	}

	BHeap(const BHeap& other) {

		head = copySubtree(other.head);
		smallest = findMin();
	}



	BHeap& operator= (const BHeap& rhs) {
		BHeap temp(rhs);


		//swap 
		this->head = temp.head;
		temp.head = NULL;
		this->smallest = temp.smallest;
		temp.smallest = NULL;

		return *this;
	}

	~BHeap() {
		while (head != NULL) {
			extractMin();
		}
	}

	keytype peekKey() {
		if (smallest == NULL)
			return keytype();
		return smallest->data;
	}

	keytype extractMin() {
		//node to be extracted
		Node* temp = smallest;
		
		//remove node's tree from roots
		if (smallest == head)
			head = smallest->sibling;
		else {
			//find parent
			Node* p = head;

			while (p->sibling != smallest) {
				p = p->sibling;
			}

			p->sibling = smallest->sibling;

			//parent pointer not working properly
			//smallest->parent->sibling = smallest->sibling;

		}
			
		//reverse order of node's children
		Node* current = temp->child;
		Node* prev = NULL;
		Node* next = NULL;
		while (current != NULL) {
			next = current->sibling;
			current->sibling = prev;
			prev = current;
			current = next;
		}
		current = prev;

		//merge 
		head = binomialHeapUnion(head, current);
		smallest = findMin();

		//return data
		keytype val(temp->data);
		delete temp;
		return val;
	}
	
	void insert(keytype k) {
		BHeap other(k);
		merge(other);
	}

	void merge(BHeap<keytype>& other) {
		head = binomialHeapUnion(head, other.head);
		other.smallest = NULL;
		other.head = NULL;
		smallest = findMin();
	}

	void printKey() {
		Node* current = head;
		while (current!= NULL) {
			cout << "B" << current->degree << "\n" << current->data << " ";
			printKeyHelper(current->child);
			cout << "\n\n";
			current = current->sibling;
		}
	}


private:
	//helper functions

	//find node with minimum data
	Node* findMin() {
		if (head == NULL)
			return NULL;
		if (head->sibling == NULL)
			return head;

		Node* min = head;
		Node* x = head->sibling;

		while (x != NULL) {
			if (x->data < min->data) {
				min = x;
			}
			x = x->sibling;
		}

		return min;
	}

	//merge first node to become child of 2nd node
	void binomialLink(Node* y, Node* z) {
		y->parent = z;
		y->sibling = z->child;
		z->child = y;
		z->degree++;
	}

	//combines 2 BHeap heads into 1 without merging, but in increasing degree
	Node* binomialHeapMerge(Node* h1, Node* h2) {
		Node* newHead;
		Node* current;

		//if 1 head is empty
		if (h1 == NULL) 
			return h2;
		if (h2 == NULL)
			return h1;

		//point head to the smaller starter node
		if (h1->degree <= h2->degree) {
			head = h1;
			h1 = h1->sibling;
		}
		else {
			head = h2;
			h2 = h2->sibling;
		}

		current = head;

		//keep going while both lists are not empty
		while (h1 != NULL && h2 != NULL) {
			if (h1->degree <= h2->degree) {
				current->sibling = h1;
				h1->parent = current;
				h1 = h1->sibling;
			}
			else {
				current->sibling = h2;
				h2->parent = current;
				h2 = h2->sibling;
			}
			current = current->sibling;
		}

		//add the rest of whichever list is not empty 
		if (h1 != NULL) {
			current->sibling = h1;
			h1->parent = current;
		}
		if (h2 != NULL) {
			current->sibling = h2;
			h2->parent = current;
		}
		return head;
	}

	//merges 2 BHeap heads into 1 Bheap head with merging
	Node* binomialHeapUnion(Node* h1, Node* h2) {

		Node* newHead = binomialHeapMerge(h1, h2);

		if (newHead == NULL)
			return newHead;

		Node* prev = NULL;
		Node* x = newHead;
		Node* next = x->sibling;

		while (next != NULL) {
			if ((x->degree != next->degree) || (next->sibling != NULL && next->sibling->degree == x->degree)) {
				prev = x;
				x = next;
			}
			else if (x->data <= next->data) {
				x->sibling = next->sibling;
				binomialLink(next, x);
			}
			else {

				if (prev == NULL) 
					newHead = next;
				else
					prev->sibling = next;
				binomialLink(x, next);
				x = next;
			}


			next = x->sibling;
		}

		return newHead;
	}

	//prints in order traversal
	void printKeyHelper(Node* n) {
		if (n == NULL)
			return;

		cout << n->data << " ";
		printKeyHelper(n->child);
		printKeyHelper(n->sibling);
	}


	//copies the subtree of a node, return the duplicate root node
	Node* copySubtree(Node* n) {
		if (n == NULL)
			return NULL;

		Node* temp = new Node(n->data);

		temp->child = copySubtree(n->child);
		if (temp->child != NULL)
			temp->child->parent = temp;
		temp->sibling = copySubtree(n->sibling);
		if (temp->sibling != NULL)
			temp->sibling->parent = temp;

		return temp;
	}
};

#endif