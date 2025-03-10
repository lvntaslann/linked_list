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
    
    //aþaðý ve yukarý düzeltme iþlemleri için fonksiyonlar
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
	//ebeveyn indexi bulunurken küsuratlý çýkarsa integer kýsým alýnýyor sadece çünkü type integer
    return (index - 1) / 2;
}

bool HeapSort::ekle(int ekle) {
    //dizimiz sabit olduðu için geniþletme yapmadýk(yapýlabilirde)
    if(elemanSayisi == MAX) return false;
    //gelen veriyi diziye ekleyerek eleman sayýsýný bir arttýrýyoruz
    veriler[elemanSayisi] = ekle;
    elemanSayisi++;
    //gelen veri atasýndan büyük olmalý bu yüzden kontrol için HeapifyUp fonksiyonumuza gönderiyoruz
    HeapifyUp(elemanSayisi - 1);
    return true;
}

void HeapSort::HeapifyUp(int index) {
    if(index == 0) return; //eleman yoksa iþleme gerek yok 
    //parametreyle gelen elemanýn ebeveyni bulunuyor
    int ebeveynIndex = ebeveynIndexGetir(index);
    
    //heapte her zaman ata büyük deðerde olacaðý için bu durumda yer deðiþtirmeli
    if(veriler[ebeveynIndex] > veriler[index]) {
        //ebeveyn ile eklenen verinin yer deðiþtirme iþlemi
        int temp = veriler[index];
        veriler[index] = veriler[ebeveynIndex];
        veriler[ebeveynIndex] = temp;
        //eklenen eleman ebeyn fonksiyonla yer deðiþtirdði için rekursif olarak doðru iþlem olana kadar tekrarlýyoruz
        HeapifyUp(ebeveynIndex);    
    }
}

bool HeapSort::cikar() {
    if(elemanSayisi == 0) return false;
    
    //eleman çýkartmak için dizinin son sýrasýndaki elemaný dizinin ilk sýrasýna alýyoruz
    veriler[0] = veriler[elemanSayisi - 1];
    elemanSayisi--;
    HeapifyDown(0); //düzeltmeye en kökten baþlýyoruz
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
    } else if(veriler[solIndex] < veriler[sagIndex]) { //sol elman sað elemandan küçükse
        min = solIndex;
    } else {
        min = sagIndex;
    }
    
    //çocuklarýn en küçük elemaný bulunduktan sonra gelen index ile karþýlaþtýrýlýyor
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

    cout << "Eleman mevcut deðil" <<endl;
}


int main(int argc, char** argv) {
    HeapSort heap; //nesne oluþturduk
    heap.ekle(10);//veriler[3]
    heap.ekle(5);//veriler[2]
    heap.ekle(20);//veriler[1]
    heap.ekle(1); //veriler[0]

    cout << "Min: " << heap.minGetir() <<endl; // Çýktý: Min: 1

    heap.cikar(); //hep kökten çýkartýldýðý için minumum deðiþiyor
    cout << "Min: " << heap.minGetir() <<endl; // Çýktý: Min: 5

    return 0;
}

