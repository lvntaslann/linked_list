#include <iostream>
using namespace std;

class QueueNode{
	public:
		int data;
		QueueNode* next;
		QueueNode(const int& data=0, QueueNode* next=NULL)
		: data(data), next(next){	}
};


class Queue{
	QueueNode* root;
	int length=0;
	public:
		Queue():root(NULL),length(0){}
		bool isEmpty(){ return root==NULL;}
		void enqueue(const int& value){
			if(isEmpty())
				root= new QueueNode(value);
			else {
				QueueNode* tmp=root;
				while(tmp->next!=NULL)
					tmp=tmp->next;
				tmp->next=new QueueNode(value);
			}
			length++;
		}
		
		void printQueueElements(){
			if(isEmpty()) return;
			
			QueueNode* tmp=root;
			while(tmp!=NULL){
				cout<<tmp->data<<endl;
				tmp=tmp->next;
			}
			
		}
		
		void dequeue(){
			if(isEmpty()) return;
			
			QueueNode* tmp=root;
			root=root->next;
			delete tmp;	
			length--;
		}
		
		int sizequeue(){
			return length;
			
			/*
			int size=0;
			QueueNode* tmp=root;
			while(tmp!=NULL){
				tmp=tmp->next;
				size++;
			}
			cout<<"Size: "<<size<<endl;
			*/
		}
};



int main(int argc, char** argv) {
	Queue queue;
	cout<<queue.isEmpty()<<endl;
	queue.enqueue(10);
	queue.enqueue(15);
	queue.enqueue(20);
	queue.enqueue(25);
	cout<<"Size:"<<queue.sizequeue()<<endl;
	cout<<queue.isEmpty()<<endl;
	queue.printQueueElements();
	queue.dequeue();
	queue.printQueueElements();
	queue.dequeue();
	queue.dequeue();
	queue.dequeue();
	cout<<"Size:"<<queue.sizequeue()<<endl;
	return 0;
}
