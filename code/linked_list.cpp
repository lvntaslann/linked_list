#include <iostream>
using namespace std;

class Node {
public:
    // data d���mlerin verisini tutacak
    // node g�stericisi ile kendinden sonra gelen elemana eri�im i�in next olu�turuldu
    int data;
    Node* next;

    // constructor fonksiyon ile parametrelerin ilk de�eri atand� ve buradaki de�erlere e�itlendi
    Node(const int& data = 0, Node* next = NULL) : data(data), next(next) {}
};

// elemanlara ula��m i�in bir liste olu�turuldu
class list {
    // listenin k�k�nde root tutarak t�m elemanlara ula��lmak ama�land�
    Node* root;
public:
    // constructor
    list() : root(NULL) {}

    // listenin ba�lang�c�n� ve sonunu g�stermek i�in �zel fonksiyonlar olu�turuldu
    Node* begin() const { return root; }
    Node* end() const { return NULL; }

    // Listenin i�eri�inin bo� mu oldu�unu kontrol etmek i�in isEmpty fonksiyonu
    bool isEmpty() const { return begin() == end(); }

    // Listeye eleman ekleme fonksiyonu (listenin sonuna ekler)
    void pushBack(const int& value) {
        if (isEmpty()) {
            // liste bo�sa yeni bir node olu�tur ve gelen value'yu ata
            root = new Node(value);
        } else {
            // e�er liste doluysa ba�lang�c� g�steren bir tmp g�stericisi olu�tur
            // ve tmp null de�er g�rene kadar next'e ge�i� i�lemi yap
            // null g�rd�kten sonra yeni bir node olu�turarak gelen value'yu ata
            Node* tmp = begin();
            while (tmp->next != end()) {
                tmp = tmp->next;
            }
            tmp->next = new Node(value);
        }
    }

    // Listeye eleman ekleme fonksiyonu (listenin ba��na ekler)
    void pushFront(const int& value) {
        Node* tmp = new Node(value);
        tmp->next = root;
        root = tmp;
    }

    // Belirli bir pozisyona eleman ekleme fonksiyonu
    void insert(int position, const int& value) {
    	//liste bo� ise ba�a eleman ekle
        if ( position<=0) {
            pushFront(value);
            return;
        }
		
		//bir g�sterici olu�tur ba�lang�c� g�stersin
		//eklenicek pozisyondan bir �ncesine  gelene kadar(g�sterici null olmayacak) g�stericiyi ilerlet
        Node* tmp = begin();
        for (int i = 0; tmp != end() && i < position - 1; ++i) {
            tmp = tmp->next;
        }
		
		//g�sterici eklenecek k�s�mdan 1 �nceki ad�m� g�sterdi�i i�in
		//g�stericinin nexti bo� ise sona eleman ekleyecek
        if (tmp == end()) {
            pushBack(value);
        } else {
        	//null de�ilse yeni bir node olu�turacak
        	/*	
        		7 ile 5 aras�nda ekleyeceksek
        		tmp eklenecek ad�mdan �ncesini g�steriyor
        		99 ekleyece�iz �rne�in
        		yeni olu�an node'un i�erisine value olarak 99 verdik ve g�stericisine tmp->next verdik
        		tmp normalde 7 yi g�steriyordu nexti 5 i g�steriyor b�yle eleman kaybetmeden araya ekledik
        		daha sonrada tmpnin normal g�stericisini valuesi 99 olan node'm�za ba�lad�k
        		
				[3] -> [6] -> [7] -> [5] -> [4]
            				 ^
            				 tmp

				Yeni d���m: [99]
        	*/
            Node* newNode = new Node(value, tmp->next);
            tmp->next = newNode;
        }
    }

    // Belirli bir pozisyondan eleman ��karma fonksiyonu
    void remove(int position) {
        if (isEmpty()) {
            cout << "Liste bo�" << endl;
            return;
        }
		
		//girilen pozisyon 0 ise ba�tan eleman ��kart�yordur bu y�zden popFront fonksiyonu kulland�k
        if (position == 0) {
            popFront();
            return;
        }
		
		//daha sonra yeni bir g�sterici olu�turduk ve rootu g�steriyor
		//tmpyi ��kar�lacak elemandan bir �ncesine kadar ilerlettik bir sonraki ad�m null olmayacak �ekilde(null de�i�se bir sonraki ad�ma ge�mesi i�in)
        Node* tmp = begin();
        for (int i = 0; tmp->next != end() && i < position - 1; ++i) {
            tmp = tmp->next;
        }
		
		//�rne�in 4 eleman var listede ve pozisyon olarak kullan�c� 5 girdi tmp->next 5. olucak ve i�erisi null oldu�u i�in daha do�rusu b�yle bir k�s�m olmad��� i�in bir hata d�nd�recek
        if (tmp->next == end()) {
            cout << "Pozisyon listede mevcut de�il" << endl;
        } else {
        	/*
        	�rne�in 99 eleman�n� ��kar�caz
        	tmp ��kar�lacak elemandan �ncekini g�steriyordu
        	yeni bir node olu�turduk ve tmpnin nextini atad�k yani 99unu g�steriyor 
        	daha sonra yeni nodun yani ��kar�lacak olan elemandan sonraki gelen elamn� tmp->next = nodeToRemove->next bu i�lemi yaparak tmp ye tan�tt�k
        	art�k 7 ile 99 aras�nda ba�lant� kalmad��� i�in 99u bellekten tahsis ettik
        	[3] -> [6] -> [7] -> [99] -> [5] -> [4]
            			 ^      ^
             			tmp   tmp->next (��kar�lacak d���m)

			��kar�lacak d���m: [99]
			*/
            Node* nodeToRemove = tmp->next;
            tmp->next = nodeToRemove->next;
            delete nodeToRemove;
        }
    }

    // Listenin ilk eleman�n� yazd�rma fonksiyonu
    void frontDataPrint() {
        if (isEmpty()) {
            cout << "Liste bo�" << " ";
        } else {
            cout << "Listenin ilk elemani: " << begin()->data << endl;
        }
    }

    // Listenin son eleman�n� yazd�rma fonksiyonu
    void backDataPrint() {
        Node* tmp = begin();
        if (isEmpty()) {
            cout << "Liste bo�" << " ";
        } else {
            while (tmp->next != NULL) {
                tmp = tmp->next;
            }
            cout << "Listenin son elemani: " << tmp->data << endl;
        }
    }

    // Listenin son eleman�n� ��karma fonksiyonu
    void popBack() {
        if (isEmpty()) {
            cout << "Liste bo�" << " ";
        } else if (begin()->next == end()) {
        	//burada liste tek elemandan olu�uyosa ba�lang�c� da sonuda o olaca�� i�in o eleman� sildik yani root ba�lang�c� g�sterdi�i i�in rootu bellekten silip null yapt�k
            delete root;
            root = NULL;
        } else {
        	//birden fazla eleman varsada yeni bir node olu�turduk ve ilk elemandan ba�latt�k
        	//tmp her seferinden kendin 2 sonrakini kontrol ediyor yani 3-4-5 olarak 3 eleman olsa 3 e kadar gelicek 3�n nextinin nexti dolu oldu�u i�in 4 e ge�icek daha sonras� null oldu�u i�in burada kal�cak
        	//buna bakarken d�ng�de hep tmpyi kayd�r�yoruz
        	//daha sonra 4 sondan bir �nceki ad�m� g�sterdi�i i�in 4�n bir sonrakini yani 5. elemani siliyoruz
            Node* tmp = begin();
            while (tmp->next->next != NULL) {
                tmp = tmp->next;
            }
            delete tmp->next;
            tmp->next = NULL;
        }
    }

    // Listenin ilk eleman�n� ��karma fonksiyonu
    void popFront() {
        if (isEmpty()) {
            cout << "Liste Bo�" << endl;
        } else {
        	//yeni node ba�lang�c� g�steriyor
        	//rootta ba�lang�c� g�steriyordu onu 2.elemana ald�k
        	//ve tmpyi sildik
            Node* tmp = begin();
            root = tmp->next;
            delete tmp;
        }
    }

    // Listenin t�m elemanlar�n� yazd�rma fonksiyonu
    void printData() {
    	//yeni node tmp olu�turduk
    	//root ile ayn� yer olan ba�lang�c� g�steriyor
    	//tmp null de�erini g�rene kadar datas�n� yazd�rd�k ve bir ad�m ileriye aktard�k
        Node* tmp = begin();
        while (tmp != end()) {
            cout << tmp->data << endl;
            tmp = tmp->next;
        }
    }
};

int main(int argc, char** argv) {
	
	/*
	
	
	BU KISIM FONKS�YONLARI TEST ETT���M KISIM BURAYI �OK KAALE ALMANA GEREK YOK
	
	*/
    // Node s�n�f�n�n nesnesi olu�turuldu
    // b�ylece bellekte alan tahsis edilmi� oldu ve 3 de�eri atand�
    Node* n1 = new Node(3);

    // n2 node da olu�turuldu 
    Node* n2 = new Node(5);

    // n3 node da olu�turuldu 
    Node* n3 = new Node(10);

    // n1 ile g�sterici i�lemleri yap�ld� 3--->5--->10 diye gidiyor s�ra
    n1->next = n2;
    n2->next = n3;

    // ba�lang�c�m�z n1 oldu�u i�in ba�lang�c� g�stericek bir tmp de�i�keni i�in alan tahsisi ger�ekle�tirildi
    Node* tmp = n1;
    while (tmp != NULL) {
        // temp'in bir sonraki ad�m� null olana kadar yani 3.node'a gidene kadar elemanlar ekrana yazd�r�ld�
        cout << tmp->data << endl;
        tmp = tmp->next;
    }

    // Liste s�n�f�n�n nesnesi olu�turuldu
    list liste;
    cout << liste.isEmpty() << endl;

    // Listeye elemanlar eklendi
    liste.pushFront(5);
    liste.pushFront(6);
    liste.pushFront(7);
    liste.pushBack(4);
    liste.pushFront(3);
    liste.printData();

    // Listenin son ve ilk elemanlar� yazd�r�ld�
    liste.backDataPrint();
    liste.frontDataPrint();

    // Belirli bir pozisyona eleman eklendi
    liste.insert(2, 99);
    liste.printData();

    // Belirli bir pozisyondan eleman ��kar�ld�
    liste.remove(3);
    liste.printData();

    // Listenin son eleman� ��kar�ld�
    liste.popBack();
    liste.printData();

    // Listenin ilk eleman� ��kar�ld�
    liste.popFront();
    liste.printData();
}

