#include <iostream>
using namespace std;
const int KUYRUK_MAX=10;
class DogrusalKuyruk{
	public:
		DogrusalKuyruk();
		bool ekle(int item);
		int cikar();
		bool bosMu();
		void yazdir();
		int D[KUYRUK_MAX];
		int kuyrukSonu;
		int kuyrukBasi;
		
};

DogrusalKuyruk::DogrusalKuyruk(){
	kuyrukSonu=-1;
	kuyrukBasi=-1;
}

bool DogrusalKuyruk::bosMu(){
	if(kuyrukSonu==-1 && kuyrukBasi==-1)
			return true;
	return false;
}

bool DogrusalKuyruk::ekle(int item){
	// kuyruk dolu ise
	if(kuyrukSonu>=KUYRUK_MAX-1) 
		return false;
	
	//kuyruk bo� ise
	if(bosMu())
		kuyrukBasi++;
		
	//kuyruk bo� ya da dolu de�ilse kuyru�u bir artt�r�p i�erisini eleman� ekliyoruz
	kuyrukSonu++;
	D[kuyrukSonu]=item;
	return true;
} 	

int DogrusalKuyruk::cikar(){
	if(bosMu()) return -1;
	
	int index, item=D[kuyrukBasi];
	kuyrukSonu--;
	for(index=0;index<=kuyrukSonu;index++){
		//kuyruk sonuna gidene kadar kuyrukta bir ad�m kayd�rma i�lemi yapt�k ve ilk eleman silinmi� oldu
		D[index]=D[index+1];
	}
	return item;
}

void DogrusalKuyruk::yazdir(){
	for(int index=0;index<=kuyrukSonu;index++){
		cout<<D[index]<<endl;
	}
}


int main(int argc, char** argv) {
	DogrusalKuyruk dogrusalKuyruk;
	cout<<dogrusalKuyruk.bosMu()<<endl;
	dogrusalKuyruk.ekle(10);
	dogrusalKuyruk.ekle(20);
	dogrusalKuyruk.ekle(30);
	dogrusalKuyruk.yazdir();
	dogrusalKuyruk.cikar();
	dogrusalKuyruk.yazdir();
	return 0;
}
