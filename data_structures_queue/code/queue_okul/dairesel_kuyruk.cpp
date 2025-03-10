#include <iostream>
using namespace std;

const int KUYRUK_MAX=10;

class DaireselKuyruk{
	public:
		DaireselKuyruk();
		bool ekle(int item);
		int cikar();
		bool bosMu();
		bool doluMu();
		void yazdir();
		int D[KUYRUK_MAX];
		int kuyrukSonu;
		int kuyrukBasi;
};

DaireselKuyruk::DaireselKuyruk() {
	kuyrukSonu=-1;
	kuyrukBasi=-1;
}

bool DaireselKuyruk::bosMu() {
	return(kuyrukBasi==-1);
}

bool DaireselKuyruk::doluMu() {
	//kuyruk sonu dizide geçerli bir indise çevrilerek kuyrukbasina esit mi deðil mi kontrol ediliyor
	return((kuyrukSonu+1)%KUYRUK_MAX==kuyrukBasi);
}

bool DaireselKuyruk::ekle(int item) {
	if(doluMu()) return false;
	
	if(bosMu()) kuyrukBasi=0;
	
	kuyrukSonu=(kuyrukSonu+1)%KUYRUK_MAX;
	D[kuyrukSonu]=item;
	return true;
}

DaireselKuyruk::cikar() {
	if(bosMu()) return -1;
	
	int item=D[kuyrukBasi];
	
	if(kuyrukBasi==kuyrukSonu)
	{
		//tek eleman varsa direkt içeriðini NULL yapýyoruz
		kuyrukBasi=-1;
		kuyrukSonu=-1;
	}else {
		//birden fazla eleman varsa ilk elemaný çýkartmabilmek için
		// ilk elemanýn sonrakini indisini itema atýyoruz ver çýkartma iþlemi gerçekleþiyor
		kuyrukBasi=(kuyrukBasi+1)%KUYRUK_MAX;
	}
	return item;
}


void DaireselKuyruk::yazdir() {
	if(bosMu()) {
		cout<<"Kuyruk bos"<<endl;
		return;
	}
	
	int index =kuyrukBasi;
	while(index!=kuyrukSonu){
		cout<<D[index]<<endl;
		index=(index+1)%KUYRUK_MAX;
	}
	//kuyruk sonuna kadar gittiðimiz için ek olarak sonuncu elemaný da yazdýrmalýyýz
	cout<<D[kuyrukSonu]<<endl;
}

int main(int argc, char** argv) {
	DaireselKuyruk daireselKuyruk;
    cout << daireselKuyruk.bosMu() << endl;
    daireselKuyruk.ekle(10);
    daireselKuyruk.ekle(20);
    daireselKuyruk.ekle(30);
    daireselKuyruk.yazdir();
    daireselKuyruk.cikar();
    daireselKuyruk.yazdir();
    return 0;
}
