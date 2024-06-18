#include <iostream>
using namespace std;

class Node {
public:
    // data düðümlerin verisini tutacak
    // node göstericisi ile kendinden sonra gelen elemana eriþim için next oluþturuldu
    int data;
    Node* next;

    // constructor fonksiyon ile parametrelerin ilk deðeri atandý ve buradaki deðerlere eþitlendi
    Node(const int& data = 0, Node* next = NULL) : data(data), next(next) {}
};

// elemanlara ulaþým için bir liste oluþturuldu
class list {
    // listenin kökünde root tutarak tüm elemanlara ulaþýlmak amaçlandý
    Node* root;
public:
    // constructor
    list() : root(NULL) {}

    // listenin baþlangýcýný ve sonunu göstermek için özel fonksiyonlar oluþturuldu
    Node* begin() const { return root; }
    Node* end() const { return NULL; }

    // Listenin içeriðinin boþ mu olduðunu kontrol etmek için isEmpty fonksiyonu
    bool isEmpty() const { return begin() == end(); }

    // Listeye eleman ekleme fonksiyonu (listenin sonuna ekler)
    void pushBack(const int& value) {
        if (isEmpty()) {
            // liste boþsa yeni bir node oluþtur ve gelen value'yu ata
            root = new Node(value);
        } else {
            // eðer liste doluysa baþlangýcý gösteren bir tmp göstericisi oluþtur
            // ve tmp null deðer görene kadar next'e geçiþ iþlemi yap
            // null gördükten sonra yeni bir node oluþturarak gelen value'yu ata
            Node* tmp = begin();
            while (tmp->next != end()) {
                tmp = tmp->next;
            }
            tmp->next = new Node(value);
        }
    }

    // Listeye eleman ekleme fonksiyonu (listenin baþýna ekler)
    void pushFront(const int& value) {
        Node* tmp = new Node(value);
        tmp->next = root;
        root = tmp;
    }

    // Belirli bir pozisyona eleman ekleme fonksiyonu
    void insert(int position, const int& value) {
    	//liste boþ ise baþa eleman ekle
        if ( position<=0) {
            pushFront(value);
            return;
        }
		
		//bir gösterici oluþtur baþlangýcý göstersin
		//eklenicek pozisyondan bir öncesine  gelene kadar(gösterici null olmayacak) göstericiyi ilerlet
        Node* tmp = begin();
        for (int i = 0; tmp != end() && i < position - 1; ++i) {
            tmp = tmp->next;
        }
		
		//gösterici eklenecek kýsýmdan 1 önceki adýmý gösterdiði için
		//göstericinin nexti boþ ise sona eleman ekleyecek
        if (tmp == end()) {
            pushBack(value);
        } else {
        	//null deðilse yeni bir node oluþturacak
        	/*	
        		7 ile 5 arasýnda ekleyeceksek
        		tmp eklenecek adýmdan öncesini gösteriyor
        		99 ekleyeceðiz örneðin
        		yeni oluþan node'un içerisine value olarak 99 verdik ve göstericisine tmp->next verdik
        		tmp normalde 7 yi gösteriyordu nexti 5 i gösteriyor böyle eleman kaybetmeden araya ekledik
        		daha sonrada tmpnin normal göstericisini valuesi 99 olan node'mýza baðladýk
        		
				[3] -> [6] -> [7] -> [5] -> [4]
            				 ^
            				 tmp

				Yeni düðüm: [99]
        	*/
            Node* newNode = new Node(value, tmp->next);
            tmp->next = newNode;
        }
    }

    // Belirli bir pozisyondan eleman çýkarma fonksiyonu
    void remove(int position) {
        if (isEmpty()) {
            cout << "Liste boþ" << endl;
            return;
        }
		
		//girilen pozisyon 0 ise baþtan eleman çýkartýyordur bu yüzden popFront fonksiyonu kullandýk
        if (position == 0) {
            popFront();
            return;
        }
		
		//daha sonra yeni bir gösterici oluþturduk ve rootu gösteriyor
		//tmpyi çýkarýlacak elemandan bir öncesine kadar ilerlettik bir sonraki adým null olmayacak þekilde(null deðiþse bir sonraki adýma geçmesi için)
        Node* tmp = begin();
        for (int i = 0; tmp->next != end() && i < position - 1; ++i) {
            tmp = tmp->next;
        }
		
		//örneðin 4 eleman var listede ve pozisyon olarak kullanýcý 5 girdi tmp->next 5. olucak ve içerisi null olduðu için daha doðrusu böyle bir kýsým olmadýðý için bir hata döndürecek
        if (tmp->next == end()) {
            cout << "Pozisyon listede mevcut deðil" << endl;
        } else {
        	/*
        	örneðin 99 elemanýný çýkarýcaz
        	tmp çýkarýlacak elemandan öncekini gösteriyordu
        	yeni bir node oluþturduk ve tmpnin nextini atadýk yani 99unu gösteriyor 
        	daha sonra yeni nodun yani çýkarýlacak olan elemandan sonraki gelen elamný tmp->next = nodeToRemove->next bu iþlemi yaparak tmp ye tanýttýk
        	artýk 7 ile 99 arasýnda baðlantý kalmadýðý için 99u bellekten tahsis ettik
        	[3] -> [6] -> [7] -> [99] -> [5] -> [4]
            			 ^      ^
             			tmp   tmp->next (çýkarýlacak düðüm)

			Çýkarýlacak düðüm: [99]
			*/
            Node* nodeToRemove = tmp->next;
            tmp->next = nodeToRemove->next;
            delete nodeToRemove;
        }
    }

    // Listenin ilk elemanýný yazdýrma fonksiyonu
    void frontDataPrint() {
        if (isEmpty()) {
            cout << "Liste boþ" << " ";
        } else {
            cout << "Listenin ilk elemani: " << begin()->data << endl;
        }
    }

    // Listenin son elemanýný yazdýrma fonksiyonu
    void backDataPrint() {
        Node* tmp = begin();
        if (isEmpty()) {
            cout << "Liste boþ" << " ";
        } else {
            while (tmp->next != NULL) {
                tmp = tmp->next;
            }
            cout << "Listenin son elemani: " << tmp->data << endl;
        }
    }

    // Listenin son elemanýný çýkarma fonksiyonu
    void popBack() {
        if (isEmpty()) {
            cout << "Liste boþ" << " ";
        } else if (begin()->next == end()) {
        	//burada liste tek elemandan oluþuyosa baþlangýcý da sonuda o olacaðý için o elemaný sildik yani root baþlangýcý gösterdiði için rootu bellekten silip null yaptýk
            delete root;
            root = NULL;
        } else {
        	//birden fazla eleman varsada yeni bir node oluþturduk ve ilk elemandan baþlattýk
        	//tmp her seferinden kendin 2 sonrakini kontrol ediyor yani 3-4-5 olarak 3 eleman olsa 3 e kadar gelicek 3ün nextinin nexti dolu olduðu için 4 e geçicek daha sonrasý null olduðu için burada kalýcak
        	//buna bakarken döngüde hep tmpyi kaydýrýyoruz
        	//daha sonra 4 sondan bir önceki adýmý gösterdiði için 4ün bir sonrakini yani 5. elemani siliyoruz
            Node* tmp = begin();
            while (tmp->next->next != NULL) {
                tmp = tmp->next;
            }
            delete tmp->next;
            tmp->next = NULL;
        }
    }

    // Listenin ilk elemanýný çýkarma fonksiyonu
    void popFront() {
        if (isEmpty()) {
            cout << "Liste Boþ" << endl;
        } else {
        	//yeni node baþlangýcý gösteriyor
        	//rootta baþlangýcý gösteriyordu onu 2.elemana aldýk
        	//ve tmpyi sildik
            Node* tmp = begin();
            root = tmp->next;
            delete tmp;
        }
    }

    // Listenin tüm elemanlarýný yazdýrma fonksiyonu
    void printData() {
    	//yeni node tmp oluþturduk
    	//root ile ayný yer olan baþlangýcý gösteriyor
    	//tmp null deðerini görene kadar datasýný yazdýrdýk ve bir adým ileriye aktardýk
        Node* tmp = begin();
        while (tmp != end()) {
            cout << tmp->data << endl;
            tmp = tmp->next;
        }
    }
};

int main(int argc, char** argv) {
	
	/*
	
	
	BU KISIM FONKSÝYONLARI TEST ETTÝÐÝM KISIM BURAYI ÇOK KAALE ALMANA GEREK YOK
	
	*/
    // Node sýnýfýnýn nesnesi oluþturuldu
    // böylece bellekte alan tahsis edilmiþ oldu ve 3 deðeri atandý
    Node* n1 = new Node(3);

    // n2 node da oluþturuldu 
    Node* n2 = new Node(5);

    // n3 node da oluþturuldu 
    Node* n3 = new Node(10);

    // n1 ile gösterici iþlemleri yapýldý 3--->5--->10 diye gidiyor sýra
    n1->next = n2;
    n2->next = n3;

    // baþlangýcýmýz n1 olduðu için baþlangýcý göstericek bir tmp deðiþkeni için alan tahsisi gerçekleþtirildi
    Node* tmp = n1;
    while (tmp != NULL) {
        // temp'in bir sonraki adýmý null olana kadar yani 3.node'a gidene kadar elemanlar ekrana yazdýrýldý
        cout << tmp->data << endl;
        tmp = tmp->next;
    }

    // Liste sýnýfýnýn nesnesi oluþturuldu
    list liste;
    cout << liste.isEmpty() << endl;

    // Listeye elemanlar eklendi
    liste.pushFront(5);
    liste.pushFront(6);
    liste.pushFront(7);
    liste.pushBack(4);
    liste.pushFront(3);
    liste.printData();

    // Listenin son ve ilk elemanlarý yazdýrýldý
    liste.backDataPrint();
    liste.frontDataPrint();

    // Belirli bir pozisyona eleman eklendi
    liste.insert(2, 99);
    liste.printData();

    // Belirli bir pozisyondan eleman çýkarýldý
    liste.remove(3);
    liste.printData();

    // Listenin son elemaný çýkarýldý
    liste.popBack();
    liste.printData();

    // Listenin ilk elemaný çýkarýldý
    liste.popFront();
    liste.printData();
}

