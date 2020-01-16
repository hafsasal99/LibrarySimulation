#pragma once
#include<iostream>
#include<string>
using namespace std;

template<class T>
class dlist;

class book
{
	int ISSN;
	string Title;
	string* Authors;
	int numOfAuthors;
	int refCopies;
	int issuableCopies;
	book * next;
	book * prev;
public:
	book() 
	{ 
		next = prev = nullptr; 
		
	}
	book(int i,string t,int size,string* a,int r, int c,book* n=0,book*p=0)
	{
		ISSN = i;
		Title = t;
		numOfAuthors = size;
		Authors = new string[size];
		for (int x = 0; x < size; x++)
		{
			Authors[x] = a[x];
		}
		refCopies = r;
		issuableCopies = c;
		next = n;
		prev = p;
	}
	~book()
	{
		if(Authors!=0)
			delete[] Authors;
	}
	void print()
	{
		cout << "ISSN :\t\t\t" << ISSN << endl;
		cout << "Title:\t" << Title << endl;
		cout << "No Of Reference Copies:\t" << refCopies<<endl;
		cout << "No Of Issuable Copies:\t" << issuableCopies<<endl;
		cout << "Authors:\t";
		for (int j = 0; j < numOfAuthors; j++)
		{
			cout << Authors[j];
			cout << endl << "\t\t";
		}
		cout << endl;
	}
	void setTitle(string t)
	{
		Title = t;
	}
	void setRefCopies(int r)
	{
		refCopies = r;
	}
	void setIssuableCopies(int i)
	{
		issuableCopies = i;
	}
	void setAuthors(int count, string* a)
	{
		numOfAuthors = count;
		delete[] Authors;
		Authors = new string[count];
		for (int s = 0; s < count; s++)
		{
			Authors[s] = a[s];
		}
	}
	friend class library;
	friend class avl;
};

class library
{
	book* head; 
	class dlistiterator
	{
		book* curr;
	public:
		friend class avl;


		dlistiterator(book* n = nullptr)
		{
			curr = n;
		}
		dlistiterator& operator++()
		{
			if (curr != nullptr)
				curr = curr->next;
			return *this;
		}
		dlistiterator& operator--()
		{
			if (curr != 0 && curr->prev != 0)
				curr = curr->prev;
			return *this;
		}
		bool operator!=(dlistiterator& it)
		{
			return(curr != it.curr);
		}
		int operator*()
		{
			return(curr->ISSN);
		}
		book* getcurr()
		{
			return curr;
		}

	};
public:
	typedef dlistiterator diterator;
	friend class avl;
	dlistiterator begin()
	{
		dlistiterator obj(head);
		return obj;
	}
	dlistiterator end()
	{
		dlistiterator obj;
		return obj;
	}

	library() { head= nullptr; }


	void insertatstart(int i, string t, int size, string* a, int r, int c, book* n, book*p)
	{
		book* temp = new book(i, t, size, a, r, c);
		temp->next = head;
		temp->prev = 0;
		if (head!= 0)
			temp->next->prev = temp;
		head = temp;
	}
	void insertatend(int i, string t, int size, string* a, int r, int c, book* n, book*p)
	{
		book* ptr = new book(i, t, size, a, r, c);
		book* temp = head;
		if (head != nullptr)
		{
			while (temp->next != nullptr)
				temp = temp->next;
			ptr->prev = temp;
		}
		else
			head = ptr;

	}
	void insertSorted(int i, string t, int size, string* a, int r, int c, book* n=0, book*p=0)
	{
		book* curr = head;
		book* previous = 0;
		while (curr != nullptr && curr->ISSN < i)
		{
			previous = curr;
			curr = curr->next;
		}
		book* ptr = new book(i, t, size, a, r, c, curr, previous);
		if (previous != nullptr)
			previous->next = ptr;
		else
			head = ptr;
		if (curr != 0)
			curr->prev = ptr;
	}
	bool isEmpty()
	{
		return (head == nullptr);
	}
	book* Search(int i)
	{
		book* temp = head;
		while (temp != nullptr && temp->ISSN != i)
			temp = temp->next;
		return temp;
	}
	~library()
	{
		book* curr = head;
		while (curr != nullptr)
		{
			head = head->next;
			delete curr;
			curr = head;
		}
	}
	
	void print()
	{
		cout << "\nISSN\t\tTitle\t\tNoOfRefCopies\tNoOfIssuableCopies Authors" << endl;
		book* curr = head;
		while (curr != nullptr)
		{
			cout << curr->ISSN << " " << curr->Title <<"\t"<< curr->refCopies << "\t" << curr->issuableCopies << '\t';
			for (int i = 0; i < curr->numOfAuthors;i++)
			{
				cout << curr->Authors[i] << ',';
			}
			cout << endl;
			curr = curr->next;
		}
	}
	void remove(book* ptr)
	{
		book* temp = ptr->prev;
		if (ptr == head)
			head = ptr->next;
		if (ptr->prev != nullptr)
			ptr->prev->next = ptr->next;
		if (ptr->next != nullptr)
			ptr->next->prev = temp;
		delete ptr;
	}
};
class tnode
{
private:
	int height;
	tnode* right;
	tnode* left;
	int data;
	book* attributes;
public:
	tnode(int d,library::diterator& a, tnode* r = 0, tnode* l = 0)
	{
		right = r;
		left = l;
		attributes =a.getcurr();
		data = d;
		if (right == nullptr && left == nullptr)
			height = 0;
		else if (right != nullptr && left != nullptr)
		{
			if (right->height > left->height)
				height = right->height + 1;
			else
				height = left->height + 1;
		}
		else if (right != nullptr)
		{
			height = right->height + 1;
		}
		else if (left != nullptr)
		{
			height = left->height + 1;
		}
	}
	friend class avl;
};
class avl
{
private:
	tnode* root;
public:
	
	avl(tnode* temp=0)
	{
		root = temp;
	}
	tnode* search(int i)
	{
		return search(root, i);
	}
	tnode* search(tnode* r, int i)
	{
		if (r == 0 || r->data == i)
			return r;
		else
		{
			if (i > r->data)
				return search(r->right, i);
			else
				return search(r->left, i);
		}
	}
	tnode* searchRange(tnode* r, int s,int e)
	{
		if (r==0||(r->data >= s &&r->data <= e))
			return r;
	
		
		else
		{
			if (r->data<s)
				return searchRange(r->right, s,e);
			else
				return searchRange(r->left, s,e);
		}
	}
	void rotateRight(tnode* &x)
	{
		tnode*y = x->left;
		x->left = y->right;
		y->right=x;
		x = y;
		//updating heights
		int hleft, hright;
		if (x->left == 0)
			hleft = -1;
		else
			hleft = x->left->height;
		if (x->right == 0)
			hright = -1;
		else
			hright = x->right->height;
		if (hleft > hright)
			x->height = hleft + 1;
		else
			x->height = hright+1;
		//computing y's new height;
		if (y->left == 0)
			hleft = -1;
		else
			hleft = y->left->height;
		if (y->right == 0)
			hright = -1;
		else
			hright = y->right->height;
		if (hleft > hright)
			y->height = hleft + 1;
		else
			y->height = hright+ 1;
	}
	void rotateLeft(tnode*& x)
	{
		tnode* y = x->right;
		x->right = y->left;
		y->left = x;
		x = y;
		//updating heights
		int hleft, hright;
		if (x->left == 0)
			hleft = -1;
		else
			hleft = x->left->height;
		if (x->right == 0)
			hright = -1;
		else
			hright = x->right->height;
		if (hleft > hright)
			x->height = hleft + 1;
		else
			x->height = hright + 1;
		//computing y's new height;
		if (y->left == 0)
			hleft = -1;
		else
			hleft = y->left->height;
		if (y->right == 0)
			hright = -1;
		else
			hright = y->right->height;
		if (hleft > hright)
			y->height = hleft + 1;
		else
			y->height = hright + 1;
	}
	void DoubleRotateLeft(tnode*& x)
	{
		rotateRight(x->right);
		rotateLeft(x);
	}
	void DoubleRotateRight(tnode*&x)
	{
		rotateLeft(x->left);
		rotateRight(x);
	}
	void insert(int ISSN,library::diterator it)
	{
		insert(ISSN, it, root);
	}
	void insert(int ISSN, library::diterator& it, tnode*& r)
	{
		if (r == 0)
		{
			r = new tnode(ISSN, it);
			return;
		}
		else
		{
			int hleft, hright;
			if (ISSN < r->data)
			{
				insert(ISSN,it,r->left);
				
				if (r->left == 0)
					hleft = -1;
				else
					hleft = r->left->height;
				if (r->right == 0)
					hright = -1;
				else
					hright = r->right->height;
				if (hleft-hright== 2)
				{
					if (ISSN < r->left->data)
						rotateRight(r);
					else
						DoubleRotateRight(r);
				}

			}
			else
			{
				insert(ISSN, it, r->right);
				
				if (r->left == 0)
					hleft = -1;
				else
					hleft = r->left->height;
				if (r->right == 0)
					hright = -1;
				else
					hright = r->right->height;
				if (hleft - hright == -2)
				{
					if (ISSN > r->right->data)
						rotateLeft(r);
					else
						DoubleRotateLeft(r);
				}

			}
			if (hleft > hright)
				r->height = hleft + 1;
			else
				r->height = hright + 1;
		}

	}
	void insert(int ISSN, tnode*& r, library::diterator it,book*& parent,tnode*& newNode)
	{
		if (r == 0)
		{
			r = new tnode(ISSN, it);
			newNode = r;
			return;
		}
		else
		{
			int hleft, hright;
			
			if (ISSN < r->data)
			{
				insert(ISSN,r->left,0,parent,newNode);
				if (r->left == newNode)//if true then r is parent
				{
					parent = r->attributes;
				}
				if (r->left == 0)
					hleft = -1;
				else
					hleft = r->left->height;
				if (r->right == 0)
					hright = -1;
				else
					hright = r->right->height;
				if (hleft - hright == 2)
				{
					if (ISSN < r->left->data)
						rotateRight(r);
					else
						DoubleRotateRight(r);
				}

			}
			else
			{
				insert(ISSN, r->right, 0, parent, newNode);

				if (r->right == newNode)//if true then r is parent
				{
					parent = r->attributes;
				}
				if (r->left == 0)
					hleft = -1;
				else
					hleft = r->left->height;
				if (r->right == 0)
					hright = -1;
				else
					hright = r->right->height;
				if (hleft - hright == -2)
				{
					if (ISSN > r->right->data)
						rotateLeft(r);
					else
						DoubleRotateLeft(r);
				}

			}
			if (hleft > hright)
				r->height = hleft + 1;
			else
				r->height = hright + 1;
		}

	}
	void printSorted()
	{
		printSorted(root);
	}

	void printSorted(tnode* r)
	{
		if (r != nullptr)
		{
			printSorted(r->left);
			cout << r->data << "  ";
			printSorted(r->right);
		}
	}
	void view(int i)
	{
		tnode* temp = search(i);
		if (temp == 0)
			cout << "Sorry the entered ISSN was not found in the library" << endl;
		else
		{
			temp->attributes->print();
		}
	}

	void removeMax(int& data, tnode*& r,library& lib,book*& newAttributes)
	{
		tnode* parent = r;
		while (r != nullptr)//finding max
		{
			parent = r;
			r = r->right;
			
		}
			data = parent->data;
			newAttributes = parent->attributes;

			delete parent;
		
	}
	void remove(int i, tnode*& r,library& lib,tnode*& parent)
	{
		tnode* temp=0;
		if (r!=0 && r->data != i)//ISSN to be deleted not found yet
		{
			if (i > r->data)
			{
				remove(i, r->right,lib, r);
				//r is X/unbalanced node
				//Y is r->left
				int hleft, hright;
				if (r->left == 0)
					hleft = -1;
				else
					hleft = r->left->height;
				if (r->right == 0)
					hright = -1;
				else
					hright = r->right->height;
			

				if (hright < hleft)//removal from a subtree that was already of a lower height so rotations required
				{
					int hright2; int hleft2;
					if (r->left != nullptr)
					{
						if (r->left->left == nullptr)
							hleft2 = -1;
						else
							hleft2 = r->left->left->height;
						if (r->left->right == nullptr)
							hright2 = -1;
						else
							hright2 = r->left->right->height;
					}
					if ((r->left->left == 0 && r->left->right == 0) || r->left->right->height == r->left->left->height)//BF of Y=0
					{
						rotateRight(r);
						
					}
					else if ((hleft2 - hright2) == (hleft-hright))//BF of Y=BF of X
					{
						rotateRight(r);
						
					}
					else if ((hleft2-hright2) ==( (hleft - hright)*-1))
					{
						DoubleRotateRight(r);
					}
				
				}
			

			}
			else
			{
				remove(i, r->left,lib, r);
				int hleft, hright;
				if (r->left == 0)
					hleft = -1;
				else
					hleft = r->left->height;
				if (r->right == 0)
					hright = -1;
				else
					hright = r->right->height;
				int hright2; int hleft2;//heights of subtrees of Y
				if (r->right != nullptr)
				{
					if (r->right->left == nullptr)
						hleft2 = -1;
					else
						hleft2 = r->right->left->height;
					if (r->right->right == nullptr)
						hright2 = -1;
					else
						hright2 = r->right->right->height;
				}
				if (hleft < hright)
				{

					if (hright2==hleft2)//BF of Y=0
					{
						rotateLeft(r);
						return;
					}
					else if ((hleft2 - hright2) == (hleft - hright))//BF of X=Y
					{
						rotateLeft(r);
						return;
					}
					else if ((hleft2-hright2) == ((hleft - hright)*-1))//BF of X=Bfof y*-1
					{
						DoubleRotateLeft(r);
						return;
					}
				
				}
				
			}
			int hleft, hright;
			if (r->left == 0)
				hleft = -1;
			else
				hleft = r->left->height;
			if (r->right == 0)
				hright = -1;
			else
				hright = r->right->height;
			if (hleft > hright)
				r->height = hleft + 1;
			else
				r->height = hright + 1;

		}
		else
		{
			if (r != nullptr)
			{
				if (r->left == nullptr && r->right == nullptr)//r is a leaf node
				{
					lib.remove(r->attributes);//removes from linked list
					if (parent->data > r->data)
						parent->left = nullptr;
					else
						parent->right = nullptr;
					
					delete r;
					return;

				}
				if (r->left == nullptr)//r has a right child only
				{
					lib.remove(r->attributes);//removes from linked list
					if (r->data > parent->data)
					{
						temp = r;

						parent->right = r->right;
					}
					else
						parent->left = r->right;
					delete temp;
					return;
				}
				if (r->right == nullptr)//r has a left child only
				{
					lib.remove(r->attributes);
					if (r->data > parent->data)
						parent->right = r->left;
					else
						parent->left = r->left;
					
					delete r;
					return;
				}
				else
				{
					int val=0;
					book* newAttributes = 0;
					removeMax(val, r->left, lib,newAttributes);//finds predecessor and deletes it
					lib.remove(r->attributes);
					r->attributes = newAttributes;
					r->data = val;
					return;
				}
				cout << "Record deleted successfully" << endl;
			}
			else
			{
				cout << "The entered ISSBN wasn't found" << endl;
			}
		
		}
	}
	void remove(int i, library& lib)
	{
		tnode* parent = 0;
		remove(i, root, lib, parent);
	}
	void update(int i)
	{
		cout << "Hit t to update title,a to update author,r to update reference copies and i to update issuable copies" << endl;
		tnode* temp = search(i);
		if (temp == 0)
			cout << "Sorry the entered ISSN was not found in the library" << endl;
		else
		{
			char choice;
			cin >> choice;
			if (choice == 't' || choice == 'T')
			{
				char buffer[80];
				cout << "Enter new title : " ;
				cin.ignore();
				cin.getline(buffer,80);
				string t = buffer;
				temp->attributes->setTitle(t);
				cout << "Record successfully updated" << endl;
				temp->attributes->print();
			}
			else if (choice == 'r' || choice == 'R')
			{
				cout << "Enter new number of reference copies" << endl;
				int num;
				cin >> num;
				temp->attributes->setRefCopies(num);
				cout << "Record successfully updated" << endl;
				temp->attributes->print();

			}
			else if (choice == 'i' || choice == 'I')
			{
				cout << "Enter new number of issuable copies" << endl;
				int num;
				cin >> num;
				temp->attributes->setIssuableCopies(num);
				cout << "Record successfully updated" << endl;
				temp->attributes->print();
			}
			else if (choice == 'a' || choice == 'A')
			{
				cout << "Enter new number of authors" << endl;
				int num;
				cin >> num;
				char buffer[80];
				string* s = new string[num];
				for (int x = 0; x < num; x++)
				{
					cout << "Enter name of new author" << endl;
					cin.ignore();
					cin.getline(buffer, 80);
					s[x] = buffer;
				}
				temp->attributes->setAuthors(num, s);
				cout << "Record successfully updated" << endl;
				temp->attributes->print();
			}
		}
		
	}
	void create()
	{
		int pk,CopiesRef, CopiesIssuable,count;
		string t;
		string* s;
		char buffer[80];
		cout << "Enter ISSBN the new book" << endl;
		cin >> pk;
		cout << "Enter the number of reference copies for new book" << endl;
		cin >> CopiesRef;
		cout << "Enter the number of reference copies for new book" << endl;
		cin >> CopiesIssuable;
		cout << "Enter the title for the new book" << endl;
		cin.ignore();
		cin.getline(buffer, 80);
		t = buffer;
		cout << "Enter number of authors for the new book" << endl;
		cin >> count;
		s = new string[count];
		for (int x = 0; x < count; x++)
		{
			cout << "Enter name of author for the new book" << endl;
			cin.ignore();
			cin.getline(buffer, 80);
			s[x] = buffer;
		}
		book* parent = 0;
		tnode* newNode=0;
		insert(pk,root,0,parent,newNode);
		book* newBook=new book(pk, t, count, s, CopiesRef, CopiesIssuable);
		if (parent->ISSN > pk)//parent successor
		{
			newBook->prev = parent->prev;
			if(newBook->prev!=nullptr)
				newBook->prev->next = newBook;
			newBook->next = parent;
			parent->prev = newBook;
		}
		else
		{
			newBook->next = parent->next;
			if(newBook->next!=nullptr)
				newBook->next->prev = newBook;
			parent->next = newBook;
			newBook->prev = parent;
		}
		newNode->attributes = newBook;
		cout << "Record Successfully Created" << endl;
	}



	void printRange(int s, int e,library& lib)
	{
		if (s <= e)
		{
			tnode* temp = searchRange(root, s, e);//Search Range searches for a value within the range.Simple Search wasn't used cause the starting index of range might not be in avl
			if (temp != 0)
			{
				cout << "The records of all books within these ranges are listed below:" << endl;
				book* curr = temp->attributes;

				while (curr != nullptr&&curr->ISSN > s)//as temp may or may not be the closest index in avl to s,linked list is traversed to find the first element that lies within s and e
				{
					if (curr != lib.head)
					{
						curr = curr->prev;
					}
					else
						break;
				}
				if (curr->ISSN < s)
					curr = curr->next;
				while (curr != nullptr && curr->ISSN <= e)
				{
					curr->print();
					curr = curr->next;
				}
			}
			else
				cout << "No records of books found within the given range" << endl;
		}
		else
			cout << "Starting index should be less than ending" << endl;
	}
};