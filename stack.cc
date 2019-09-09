/*
stack.cc
Alessandro Sacchetti
9/25/2018
Stack class file
*/

#include <cstdlib>
#include <iostream>

using namespace std;

template <typename T> class stack{

private:
	struct node{
		T data;
		node *next;
	};

	size_t _size;
	node *_top;




public:
	stack();//A 0 parameter constructor that initializes all private variables appropriately,

	~stack();//A destructor


	void push(T newdata); //- places d in a node at the top of the stack,

	void pop(); //- removes and deletes the top node of the stack. Returns nothing,

	T top() const; //- returns the value stored in the top node. Does not change the object structure.

	size_t size() const; //- returns the size of the stack. Does not change the object structure.

	bool empty() const; //- returns a boolean value - whether the stack is empty. Does not change the object structure.

	void print(); //- prints out a representation of the stack: “[1, 2, 3, 2]”  where 1 is top. Does not change the object structure.


};

template <typename T> stack<T>::stack(){
	_size=0;
	_top=NULL;
}

template <typename T> stack<T>::~stack(){
	//uses the _top pointer as the pointer that goes through the entire linked list

	while(_top){//loops through the stack until the pointer is NULL
		node *aboutToBeDeleted;//make a temp variable so that we are able to move on in the array while also deleting the current one
		aboutToBeDeleted=_top;

		_top = _top -> next;//move to the next node in the stack
		delete aboutToBeDeleted;
	}

}

template <typename T> void stack<T>::push(T newdata){

	node *tasty;
	tasty = new node;//dynamically allocates a new node somewhere in ram 

	tasty-> data = newdata;//stores the input data into the new node
	tasty-> next = _top; //sets the next variable of this new node to the previous top variable -adding it on top

	_top = tasty; //move that new node to the top

	_size++;
}

template <typename T> void stack<T>::pop(){

	if(!empty()){//if there is something to pop

		node *tasty;
		tasty = _top->next;//make a temp pointer and point to the next node in the stack

		delete _top;//delete the node at the top
		_top=tasty;//set the top node to the next node
		_size--;
	}
}

template <typename T> T stack<T>::top() const{
	return _top->data; //returns the data at the top of the stack
}

template <typename T> size_t stack<T>::size() const{
	return _size; //returns the size of the linked list
}

template <typename T> bool stack<T>::empty() const{
	return !_top; //returns true if the stack is empty
}

template <typename T> void stack<T>::print(){
	cout<<"[";

	node *tasty=_top;
	while(tasty){//loops through the stack until the pointer is NULL

		cout << (*tasty).data;

		if( (tasty->next) ){//if it is not the last node
			cout<<", ";
		}
		tasty = tasty -> next;//move to the next node in the stack
		
	}
	cout<<"]"<<endl;
}

