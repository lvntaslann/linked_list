#include <iostream>
#include <stdexcept>
using namespace std;
const int MAX = 100;

//minHeap
class HeapSort {
public:
    HeapSort();
    bool ekle(int ekle);
    int minGetir();
    bool cikar();
    int solIndexGetir(int index);
    int sagIndexGetir(int index);
    int ebeveynIndexGetir(int index);
    void elemanAra(int aranacakEleman);
    
    int veriler[MAX];
    int elemanSayisi;
    
    //a�a�� ve yukar� d�zeltme i�lemleri i�in fonksiyonlar
    void HeapifyUp(int index);
    void HeapifyDown(int index);
};

HeapSort::HeapSort() {
    elemanSayisi = 0;
}

int HeapSort::solIndexGetir(int index) {
    return 2 * index + 1;
}

int HeapSort::sagIndexGetir(int index) {
    return 2 * index + 2;
}

int HeapSort::ebeveynIndexGetir(int index) {
	//ebeveyn indexi bulunurken k�suratl� ��karsa integer k�s�m al�n�yor sadece ��nk� type integer
    return (index - 1) / 2;
}

bool HeapSort::ekle(int ekle) {
    //dizimiz sabit oldu�u i�in geni�letme yapmad�k(yap�labilirde)
    if(elemanSayisi == MAX) return false;
    //gelen veriyi diziye ekleyerek eleman say�s�n� bir artt�r�yoruz
    veriler[elemanSayisi] = ekle;
    elemanSayisi++;
    //gelen veri atas�ndan b�y�k olmal� bu y�zden kontrol i�in HeapifyUp fonksiyonumuza g�nderiyoruz
    HeapifyUp(elemanSayisi - 1);
    return true;
}

void HeapSort::HeapifyUp(int index) {
    if(index == 0) return; //eleman yoksa i�leme gerek yok 
    //parametreyle gelen eleman�n ebeveyni bulunuyor
    int ebeveynIndex = ebeveynIndexGetir(index);
    
    //heapte her zaman ata b�y�k de�erde olaca�� i�in bu durumda yer de�i�tirmeli
    if(veriler[ebeveynIndex] > veriler[index]) {
        //ebeveyn ile eklenen verinin yer de�i�tirme i�lemi
        int temp = veriler[index];
        veriler[index] = veriler[ebeveynIndex];
        veriler[ebeveynIndex] = temp;
        //eklenen eleman ebeyn fonksiyonla yer de�i�tird�i i�in rekursif olarak do�ru i�lem olana kadar tekrarl�yoruz
        HeapifyUp(ebeveynIndex);    
    }
}

bool HeapSort::cikar() {
    if(elemanSayisi == 0) return false;
    
    //eleman ��kartmak i�in dizinin son s�ras�ndaki eleman� dizinin ilk s�ras�na al�yoruz
    veriler[0] = veriler[elemanSayisi - 1];
    elemanSayisi--;
    HeapifyDown(0); //d�zeltmeye en k�kten ba�l�yoruz
    return true;
}

void HeapSort::HeapifyDown(int index) {
    int solIndex = solIndexGetir(index);
    int sagIndex = sagIndexGetir(index);
    int min;
    
    if(sagIndex >= elemanSayisi) { //sag eleman yoksa
        if(solIndex >= elemanSayisi) { //sol eleman yoksa
            return;
        } 
        else {
            min = solIndex; //sol eleman varsa
        }
    } else if(veriler[solIndex] < veriler[sagIndex]) { //sol elman sa� elemandan k���kse
        min = solIndex;
    } else {
        min = sagIndex;
    }
    
    //�ocuklar�n en k���k eleman� bulunduktan sonra gelen index ile kar��la�t�r�l�yor
    if(veriler[min] < veriler[index]) { 
        int temp = veriler[index];
        veriler[index] = veriler[min];
        veriler[min] = temp;
        HeapifyDown(min);
    }
}

int HeapSort::minGetir() {
    if(elemanSayisi != 0)
        return veriler[0];
    throw out_of_range("HeapSort::getir() - Eleman yok");
}

void HeapSort::elemanAra(int aranacakEleman) {
    for(int index = 0; index < elemanSayisi; index++) { 
        if(aranacakEleman == veriler[index]) {
            cout << "Eleman mevcut" <<endl;
            return; 
        }
    }

    cout << "Eleman mevcut de�il" <<endl;
}


int main(int argc, char** argv) {
    HeapSort heap; //nesne olu�turduk
    heap.ekle(10);//veriler[3]
    heap.ekle(5);//veriler[2]
    heap.ekle(20);//veriler[1]
    heap.ekle(1); //veriler[0]

    cout << "Min: " << heap.minGetir() <<endl; // ��kt�: Min: 1

    heap.cikar(); //hep k�kten ��kart�ld��� i�in minumum de�i�iyor
    cout << "Min: " << heap.minGetir() <<endl; // ��kt�: Min: 5

    return 0;
}

