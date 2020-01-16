#include<iostream>
#include<fstream>
#include "header.h"
using namespace std;
void main()
{
	library MyLibrary;
	fstream f1;
	fstream f2;
	f1.open("records.txt");
	f2.open("authors.txt");
	int noOfBooks;
	char key;
	string title;
	string* listOfAuthors;
	int countOfAuthors;
	int CopiesRef;
	int CopiesIssuable;
	f1 >> noOfBooks;
	char buffer[80];
	int pk;
	f1.getline(buffer, 80);
	f1.getline(buffer, 80);
	for (int i = 0; i < noOfBooks; i++)
	{
		

		f1 >> pk;
	
		f1 >> countOfAuthors;
		listOfAuthors = new string[countOfAuthors];
		/*for (int x = 0; x < 15; x++)
		{
			f1.get(key);
		}*/
		f1 >> CopiesRef;
		/*f1.get(key);
		f1.get(key);
		f1.get(key);*/
		f1 >> CopiesIssuable;
		f1.getline(buffer, 80);
		title = buffer;
		for (int j = 0; j < countOfAuthors; j++)//reads author names from a diff file
		{
			f2.getline(buffer, 80);
			listOfAuthors[j] = buffer;
		}
		MyLibrary.insertSorted(pk, title, countOfAuthors,listOfAuthors,CopiesRef,CopiesIssuable);
		delete[] listOfAuthors;
	}
	f2.close();
	f1.close();

	//MyLibrary.print();
	avl lib;
	for (library::diterator it = MyLibrary.begin(); it != MyLibrary.end(); ++it)
	{
		lib.insert(*it, it);
	}
	//cout << "AVL TREE " << endl;
	//lib.printSorted();
	cout << "--------------------------------------------LIBRARY SIMULATION--------------------------------------------" << endl;
	cout << "To view a book record,hit R" << endl;
	cout << "To update a book record hit U" << endl;
	cout << "To create a new record hit C" << endl;
	cout << "To remove a record hit D" << endl;
	cout << "To view all records within a particular range hit E" << endl;
	char choice;
	cin >> choice;
	if (choice == 'R' || choice == 'r')
	{
		cout << "Enter ISSBN Of a book to view its records" << endl;
		cin >> pk;
		lib.view(pk);
	}
	else if (choice == 'U' || choice == 'u')
	{
		cout << "Enter ISSBN of a book to update its records" << endl;
		cin >> pk;
		lib.update(pk);
	}
	else if (choice == 'C' || choice == 'c')
	{
		lib.create();
		cout << "The AVl after insertion of new record" << endl;
		MyLibrary.print();
		cout << "The linked List after insertion of new record" << endl;
		lib.printSorted();
	}
	else if (choice == 'D'|| choice=='d')
	{
		cout << "Enter ISSBN of a book to delete its records" << endl;
		cin >> pk;
		
		lib.remove(pk,MyLibrary);
		cout << "AVL:" << endl;
		MyLibrary.print();
		cout << "Linked List:" << endl;
		lib.printSorted();
	}
	else if (choice == 'E' || choice == 'e')
	{
		cout << "Enter range of ISSBN :" << endl;
		cout << "Enter starting value" << endl;
		cin >> pk;
		cout << "Enter ending value" << endl;
		int c;
		cin >> c;
		lib.printRange(pk, c,MyLibrary);
	}
	else
	{
		cout << "Invalid key press" << endl;
	}
	system("pause");
}