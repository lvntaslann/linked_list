#include <iostream>
using namespace std;

class Node {
    public:
    	//parametrelerimizi olu�turup constructor fonksiyonumuzu olu�turduk
        int key;
        Node* pNext;
        Node(int key) {
            this->key = key;
            pNext = NULL;
        }
};

//dizi boyutumuzu 10 belirlerdik
const int MAX = 10;

class HashTable {
    public:
    	//hash tablomuzun parametreleri ve fonksiyonlar�n� belirledik
    	//boyutu olan dizimiz pointer olarak bellekte yer tutcak
    	//ekleme ��kartma ve eleman getirme gibi fonksiyonlar� var
        Node* Data[MAX];
        HashTable();
        void add(int key);
        Node* get(int key);
        bool remove(int anahtar);
};

HashTable::HashTable() 
    // constructor fonskiyon ile dizinin t�m elemanlar�n� NULL olarak atad�k
    for(int index = 0; index < MAX; index++) {
        Data[index] = NULL;
    }
}

void HashTable::add(int key) {
	//yeni eleman i�in bellekte yer ay�rd�k
    Node* pNew = new Node(key);
    //eleman�n yerini belirlemek i�in gelen key de�erine g�re dizinin boyutuyla mod alma i�lemi yapt�k
    //key=32 ise dizi boyutu 10 burada verimiz dizideki 2.indise yerle�tirilirdi Data[2]
    int mod = key % MAX;
    
    //belirlenen indiste eleman yoksa direkt verimizi oraya koyuyoruz
    if(!Data[mod]) {
        Data[mod] = pNew;
        return;
    }
    
    //belirlenen indiste eleman varsa eleman�n g�sterdi�i adresle ayn� yeri g�steren bir pTemp olu�turuyoruz
    //pTemp koyulmas� gereken yerden sonra ilk buldu�u bo�lu�a koyularak ekleme i�lemi tamamlan�yor
    Node* pTemp = Data[mod];
    while(pTemp->pNext != NULL) {
        pTemp = pTemp->pNext;
    }
    pTemp->pNext = pNew;
}

Node* HashTable::get(int key) {
	//yine indis hesab� i�in bir mod alma i�lemi yap�l�yor
	//ve o indisteki eleman�n verisi yeni bir g�stericiye atan�yor pTemp
    int mod = key % MAX;
    Node* pTemp = Data[mod];
    
    //dizi i�erisinde girilen key de�eriyle pTempin i�erisindeki key de�eri e�it olana kadar pTemp ilerletiliyor
    //ayn� keye sahip eleman yoksa NULL olarak d�n�� yap�l�yor 
    while(pTemp != NULL) {
        if(pTemp->key == key) {
            return pTemp;
        }
        pTemp = pTemp->pNext;
    }
    return NULL;
}

bool HashTable::remove(int key) {
	//indis belirleme i�lemi yap�l�yor
    int mod = key % MAX;
    
    //b�yle bir veri yoksa false de�eri d�n�yor burada fonksiyon bool oldu�u i�in geri d�n�� olmal�
    //direkt get Fonksiyonumuza da y�nlendirebilirdik
    if(!Data[mod]) return false;
    
    
    //indisten sonra eleman olmayana kadar indisi ilerletiyoruz
    //e�er e�le�me varsa ilk olarak ayr�lan yeri siliyoruz
    //daha sonra i�erisindeki veriyi
    //ve true de�eri d�nd�r�yoruz e�er yoksa false;
    if(!Data[mod]->pNext) {
        if(Data[mod]->key == key) {
            delete Data[mod];
            Data[mod] = NULL;
            return true;
        }
        return false;
    }
    
    //gelen key bilgisiyle indisteki key verisi e�it ise
    //yeni bir g�sterici olu�turuyoruz ve o bulunan indisin bir sonraki indisini g�steriyor
    //bulunan indisin bellekten silip i�eri�ini yeni g�stericiye at�yoruz ve true d�n��� yap�l�yor
    //burada silme i�leminde �rne�in 5 ile 15 ayn� key de�erlerine sahip ikisi de 5 
    //ve 5 silinmek isteniyor olsun
    //normalde ekleme i�leminde 5 ten sonra 15 gelicekti indisler ayn� oldu�u i�in bir sonrakine ge�iyordu
    //bu y�zden ge�ici g�stericiyi 15e ta��d�k ve 5 k�sm�n� kald�rarak 15 i oraya ta��d�k 
    //15 silinmek istedi�inde yine 5. indise bak�laca�� i�in bu i�lemin yap�lmas� gerekiyor
    if(Data[mod]->key == key) {
        Node* pNextNode = Data[mod]->pNext;
        delete Data[mod];
        Data[mod] = pNextNode;
        return true;
    }
    
    //veri ile ayn� indisi g�steren bir g�sterici olu�turduk
    Node* pTemp = Data[mod];
    //dizi bitene kadar i�lem devam edicek
    while(pTemp->pNext != NULL) {
    	//dizi bitene kadar da hep sonraki ad�mla silmek istedi�i key e�it mi kontrol� yap�cak
        if(pTemp->pNext->key == key) {
        	// e�it ise yeni bir g�sterici olu�turyoruz ve bu silmemiz gereken yeri g�steriyor
        	//��nk� biz hep silmemiz gereken yerden bir ad�m geride gidiyorduk
        	//daha sonra bulundu�umuz konumun bir sonraki ad�m� normalde silmemiz gereken yeri g�steriyordu
        	//pTemp->pNext = pToDelete->pNext bui�lem ile iki sonras�n� g�stermesini sa�lad�k
        	//ve daha sonra silinmesi gereken yeri sildik
        	//k�sacas� ben 4.deyim ve 5.yi silicem 5. g�rd�kten sonra onu bir ge�ici g�stericiye at�yorum
        	//sonra  4 ten sonra 6 geliyormul gibi manip�le ediyorum 
        	//5in i�eri�ini silip devam ediyorum
            Node* pToDelete = pTemp->pNext;
            pTemp->pNext = pToDelete->pNext;
            delete pToDelete;
            return true;
        }
        //her d�ng�de pTempi ilerletmeyi de unutmayal�m yoksa sonsuz d�ng� olur
        pTemp = pTemp->pNext;
    }
    return false;
}

int main(int argc, char** argv) {
	//BURAYA BAKMAYAB�L�RS�N DENED���M KISIMLAR
    HashTable hashTable;
    hashTable.add(5);
    hashTable.add(15);
    Node* node = hashTable.get(5);
    if(node) {
        cout << "Node found with key: " << node->key << endl;
    } else {
        cout << "Node not found" << endl;
    }
    return 0;
}

