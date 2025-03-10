#include <iostream>
using namespace std;
int faktoriyel(int n){
	if(n==0)
		return 1;
	else 
		return n*faktoriyel(n-1);
}

int toplam(int n){
	if(n==1)
		return 1;
	else
		return n+toplam(n-1);
}


void binary(int n){
	if(n>1)
		binary(n/2);
		
	cout<<n%2;
	
}


template<class type>
class Node{
	public:
		type data;
		Node<type>*next;
		Node(const type&data=type(),Node<type>*next=NULL):data(data),next(next){}
};

Node<int>*root=NULL;

template<class type>
void print(Node<type>*begin){
	if(begin){
		cout<<begin->data<<endl;
		print(begin->next);
	}
}


template<class type>
Node<type>* addLast(const type& data,Node<type>*begin){
	if(begin){
		begin->next=addLast(data,begin->next);
	}
	else return new Node<type>(data);
}
int main(int argc, char** argv) {
	//faktoriyel
	cout<< faktoriyel(5)<<endl;
	//toplam
	cout<<toplam(100)<<endl;
	//sayilarin binary gösterilmesi
	 binary(10);
	 cout<<""<<endl;
	 
	 //listeyi rekürsif olarak oluþturma
	 root=new Node<int>(5);
	 root->next=new Node<int>(10);
	 addLast(11,root);
	 print(root);
	return 0;
}
