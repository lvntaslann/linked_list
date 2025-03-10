#include <iostream>
using namespace std;
class TreeNode{
	public:
		int data;
		TreeNode*left;
		TreeNode*right;
		TreeNode(int data=0,TreeNode*left=NULL,TreeNode*right=NULL):data(data),left(left),right(right){	}
};


enum MODE{PREORDER,INORDER,POSTORDER};
class BinarySearchTree{
	
	TreeNode* insert(TreeNode* start, int data){
		if(start){
			if(data<start->data){
				start->left=insert(start->left,data);
			}else start->right=insert(start->right,data);	 
		}else return new TreeNode(data);
		
		return start;
	}
	
	
	TreeNode* find(TreeNode* start,int data){
		if(start){
			if(data<start->data){
				return find(start->left,data);
			}else if(data>start->data){
				return find(start->right,data);
			}
		}
		return start;
	}
	
	
	TreeNode* getMin(TreeNode* start){
		while(start&&start->left)
			start=start->left;
		return start;
	}
	
	
	
	TreeNode* getMax(TreeNode* start){
		while(start&&start->right)
			start=start->right;
		return start;
	}
	
	TreeNode* remove(TreeNode*start, TreeNode*deleted){
		if(start){
			if(deleted->data < start->data){
				start->left=remove(start->left,deleted);
			}else if(deleted->data > start->data){
				start->right=remove(start->right,deleted);
			}else if(start==deleted){
				TreeNode* temp=NULL;
				if(start->left && start->right){//hem sol hem sað çocuk varsa
				//silinecek olan elamanýn sað çocuðundan sonraki en küçük elemaný bulup yer deðiþtrime yapýyor
					temp=getMin(start->right);
					remove(start,temp);
					temp->left=start->left;
					temp->right=start->right;
					
				}else if(start->left){//sadece sol çocuk varsa
					temp=start->left;
				}else if(start->right){//sadece sað çocuk varsa
					temp=start->right;
				} return temp;//hiç çocuk yoksa
				
			}else start->right=remove(start->right,deleted);
		}
		return start;
	}
	
	public:
	TreeNode* root;
	BinarySearchTree( TreeNode*root=NULL ):root(root){}
	bool isEmpty()const{return root==NULL;}
	TreeNode* getRoot()const{return root;}//roota dýþarýdan ulaþýlabilmesi için
	
	
	TreeNode* find(int data){
		return find(root,data);
	}
	
	
	void insert(int data){
		root=insert(root,data);
	}
	

	
	TreeNode* getMin(){
		return getMin(root);
	}
	
	

	
	TreeNode* getMax(){
		return getMax(root);
	}
	
	void remove(TreeNode* node){
		if(node){
			root=remove(root,node);
			delete node;
		}
	}
	
	void remove(int data){
		remove(find(data));
	}
	int height(TreeNode* node){
		//aðacýn yüksekliði saðdan ve soldan en uzak uzaklýðýn bulunmasýyla oluyor
		if(node){
		
		int left= height(node->left);
		int right=height(node->right);
		return 1+max(left,right);//sað ve solun maxýna bakýp her adýmda arttýrýyoruz yolu göstericimiz null dönene kadar
    	}
		else return -1;//aðacta hiçbir veri yoksa null döndürecek yükseklik hesaplanamaz çünkü
	
	}
	
	int depth(TreeNode* start, TreeNode* finish){
		if(start){
			if(start==finish)
				return 0;
			int left=depth(start->left,finish);
			int right=depth(start->right,finish);
			return 1+max(left,right);
			
		}
		else return INT_MIN;
	}
	
	
	//depth fonksiyonunu override ettik tek paramatre gelirse köke göre derinlik ölçücek
	int depth(TreeNode* finish){
		return depth(root,finish);
	}
	
	
	
	void preOrder(TreeNode* start){
		if(start){
			cout<<start->data<<"  ";
			preOrder(start->left);
			preOrder(start->right);
		}
	}
	
	
	void inOrder(TreeNode* start){
		if(start){
			inOrder(start->left);
			cout<<start->data<< "  ";
			inOrder(start->right);
		}
	}
	
	
	void postOrder(TreeNode* start){
		if(start)
		{
			postOrder(start->left);
			postOrder(start->right);
			cout<<start->data<<"  ";
		}
	}
	
	
	void print(MODE mode)
	{
		switch(mode){
			case PREORDER:
				preOrder(root);
				break;
			case INORDER:
				inOrder(root);
				break;
			case POSTORDER:
				postOrder(root);
				break;
		}
		if(!isEmpty()){
			cout<<endl;
		}
	}
	
};
int main(int argc, char** argv) {
	BinarySearchTree tree;
	tree.insert(15);
	tree.insert(20);
	tree.insert(5);
	tree.insert(12);
	tree.insert(13);
	tree.insert(14);
	//cout<<tree.isEmpty()<<endl;
	cout<<"Preorder: ";
	tree.print(PREORDER);
	cout<<"Inorder: ";
	tree.print(INORDER);
	cout<<"Postorder:  ";
	tree.print(POSTORDER);
	cout<<tree.find(12)->data<<endl;
	cout<<"Max:"<<tree.getMax()->data<<endl;
	cout<<"Min:"<<tree.getMin()->data<<endl;
	
	tree.remove(5);
	cout<<"Inorder: "; //5 elemaný kaldýrýldýktan sonra
	tree.print(INORDER);
	cout<<"Max:"<<tree.getMax()->data<<endl;
	cout<<"Min:"<<tree.getMin()->data<<endl;
	return 0;
}
