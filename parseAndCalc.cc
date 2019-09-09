/*
parseAndCalc.cc
Alessandro Sacchetti
12/13/2018
parse and calc file
*/
#include "stack.cc"
#include <cstdlib>
#include <iostream>

using namespace std;


//Tree node - left and right pointers + data
struct node {
  char data;
  node *left;
  node *right;
  node(char data, node *left, node *right): 
  data(data), left(left), right(right) {}
};
//Tree stuff
void printTree(node * tree, size_t depth = 0){
// right to left inorder traversal
  if (tree == NULL)
    return;

  printTree(tree -> right, depth + 1);
  for (size_t i = 0; i < depth; i++)
    cout << "   ";

  cout << tree -> data << endl;
  printTree(tree -> left, depth + 1);
}

bool isOperator(char c){
	return c=='+' or c=='-' or c=='*' or c=='/' or c=='%';
}

int charToInt(char c){
	return c-'0';
}

//input is in reverse polish notation - if the function returns NULL as the node it was not able to make one
node* MakeBinExpressionTree(string input){
	stack<node*> treeStack;
	int i(0);
	while(input[i]){//didnt use for each loop b/c stupid warnings
		if(input[i] != ' '){
			if(!isOperator(input[i])){//if its not an operator

				if('0'>input[i] or input[i]>'9'){//there are other symbols besides nums and operators
					return NULL;
				}

				treeStack.push(new node(input[i], NULL, NULL));
			}else{

				if(treeStack.size()<2){//not enough numbers before an operator
					return NULL;
				}
				node* tempNode1 = treeStack.top();
				treeStack.pop();
				node* tempNode2 = treeStack.top();
				treeStack.pop();

				treeStack.push(new node(input[i], tempNode2, tempNode1));
			}
		}
		i++;
	}

	if(treeStack.size()!=1){//there must have been left over numbers without operations
		return NULL;
	}else{
		return treeStack.top();
	}
}

void printPreFix(node* tree, bool first=true){//created from wikipedia pseudo code https://en.wikipedia.org/wiki/Binary_expression_tree
	if(tree){
		cout<<tree->data;
		printPreFix(tree->left,false);
		printPreFix(tree->right,false);
		if(first) cout<<endl;
	}
}

void printInfix(node* tree, bool first=true){//created from wikipedia pseudo code https://en.wikipedia.org/wiki/Binary_expression_tree
	if(tree){
		if(isOperator(tree->data) and !first){
			cout<<"(";
		}
		printInfix(tree->left,false);
		cout<<tree->data;
		printInfix(tree->right,false);
		if(isOperator(tree->data) and !first){
			cout<<")";
		}
		if(first) cout<<endl;
	}
}

int reversePolishNotationCalc(string in, bool & divideByZero){
	stack<int> numStack;
	int i(0);
	while(in[i]){
		if(isOperator(in[i])){//do that operation and put the ans back on stack
			int b = numStack.top();
			numStack.pop();
			int a = numStack.top();
			numStack.pop();
			int ans = 0;

			if(in[i] == '+'){
				ans = a+b;
			}else if(in[i] == '-'){
				ans = a-b;
			}else if(in[i] == '*'){
				ans = a*b;
			}else if(in[i] == '/'){
				if(b==0){
					divideByZero=true;//if it would /0
					return 0;
				}else{
					ans = a/b;
				}
			}else if(in[i] == '%'){
				ans = a%b;
			}

			numStack.push(ans);
		}else if(in[i]!=' '){
			numStack.push(charToInt(in[i]));//put numbers on stack
		}

		i++;
	}
	return numStack.top();
}

int main(){
	string input="";

	while(true){
		cout<<"INPUT: ";
		getline(cin,input);
		if(input!="q"){
			cout<<"~~~~~~~~~~~~~~~~~"<<endl;
			//The part of the program that actually does stuff
			node* n = MakeBinExpressionTree(input);
			if(n){// if the node exist the tree is possible
				bool divideByZero = false;//is true if the calculation would contain a num/0
				int answer = reversePolishNotationCalc(input, divideByZero);

				if(!divideByZero){
					printTree(n);
					cout<<"Infix Notation: ";
					printInfix(n);
					cout<<"PreFix Notation: ";
					printPreFix(n);
					cout<<"Answer: " << answer<<endl;
				}else{
					cout<<"Cannot Divide By Zero!"<<endl;
				}

			}else{
				cout<<"NOT A VALID POSTFIX NOTATION"<<endl;
			}
			cout<<"~~~~~~~~~~~~~~~~~"<<endl;

		}else{
			break;
		}
	}
}