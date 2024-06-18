#include <iostream>
using namespace std;

class Node {
public:
    // data düğümlerin verisini tutacak
    // node göstericisi ile kendinden sonra gelen elemana erişim için next oluşturuldu
    int data;
    Node* next;

    // constructor fonksiyon ile parametrelerin ilk değeri atandı ve buradaki değerlere eşitlendi
    Node(const int& data = 0, Node* next = NULL) : data(data), next(next) {}
};

// elemanlara ulaşım için bir liste oluşturuldu
class list {
    // listenin kökünde root tutarak tüm elemanlara ulaşılmak amaçladık
    Node* root;
public:
    // constructor
    list() : root(NULL) {}

    // listenin başlangıcını ve sonunu göstermek için özel fonksiyonlar oluşturuldu
    Node* begin() const { return root; }
    Node* end() const { return NULL; }

    // Listenin içeriğinin boş mu olduğunu kontrol etmek için isEmpty fonksiyonu
    bool isEmpty() const { return begin() == end(); }

    // Listenin sonuna eleman ekleme
    void pushBack(const int& value) {
        if (isEmpty()) {
            // liste boşsa yeni bir node oluştur ve gelen value'yu ata
            root = new Node(value);
        } else {
            // eğer liste doluysa başlangıcı gösteren bir tmp göstericisi oluştur
            // ve tmp null değer görene kadar next'e geçiş işlemi yap
            // null gördükten sonra yeni bir node oluşturarak gelen value'yu ata
            Node* tmp = begin();
            while (tmp->next != end()) {
                tmp = tmp->next;
            }
            tmp->next = new Node(value);
        }
    }

    // Listenin başına eleman ekleme
    void pushFront(const int& value) {
        Node* tmp = new Node(value);
        tmp->next = root;
        root = tmp;
    }

    // Belirli bir pozisyona eleman ekleme fonksiyonu
    void insert(int position, const int& value) {
    	//liste boş ise başa eleman ekle
        if ( position<=0) {
            pushFront(value);
            return;
        }
		
	//başlangıcı gösterecek şekilde tmp göstericisini oluşturduk
	//eklenicek pozisyondan bir öncesine  gelene kadar(gösterici null olmayacak) göstericiye kadar ilerleticek döngüyu hazırladık
        Node* tmp = begin();
        for (int i = 0; tmp != end() && i < position - 1; ++i) {
            tmp = tmp->next;
        }
		
	//gösterici eklenecek kısımdan 1 önceki adımı gösterdiği için
	//göstericinin nexti boş ise sona eleman ekleyecek
        if (tmp == end()) {
            pushBack(value);
        } else {
        	//null değilse yeni bir node oluşturacak
        	/*	
        		7 ile 5 arasında ekleyeceksek
        		tmp eklenecek adımdan öncesini gösteriyor
        		99 ekleyeceğiz örneğin
        		yeni oluşan node'un içerisine value olarak 99 verdik ve göstericisine tmp->next verdik
        		tmp normalde 7 yi gösteriyordu nexti 5 i gösteriyor böyle eleman kaybetmeden araya ekledik
        		daha sonrada tmpnin normal göstericisini valuesi 99 olan node'mıza bağladık
        		
				[3] -> [6] -> [7] -> [5] -> [4]
            				 ^
            				 tmp

				Yeni düğüm: [99]
        	*/
            Node* newNode = new Node(value, tmp->next);
            tmp->next = newNode;
        }
    }

    // Belirli bir pozisyondan eleman çıkarma fonksiyonu
    void remove(int position) {
        if (isEmpty()) {
            cout << "Liste boş" << endl;
            return;
        }
		
		//girilen pozisyon 0 ise baştan eleman çıkartıyordur bu yüzden popFront fonksiyonu kullandık
        if (position == 0) {
            popFront();
            return;
        }
		
		//daha sonra yeni bir gösterici oluşturduk ve rootu gösteriyor
		//tmpyi çıkarılacak elemandan bir öncesine kadar ilerlettik bir sonraki adım null olmayacak şekilde(null değişse bir sonraki adıma geçmesi için)
        Node* tmp = begin();
        for (int i = 0; tmp->next != end() && i < position - 1; ++i) {
            tmp = tmp->next;
        }
		
		//örneğin 4 eleman var listede ve pozisyon olarak kullanıcı 5 girdi tmp->next 5. olucak ve içerisi null olduğu için daha doğrusu böyle bir kısım olmadığı için bir hata döndürecek
        if (tmp->next == end()) {
            cout << "Pozisyon listede mevcut değil" << endl;
        } else {
        	/*
        	örneğin 99 elemanını çıkarıcaz
        	tmp çıkarılacak elemandan öncekini gösteriyordu
        	yeni bir node oluşturduk ve tmpnin nextini atadık yani 99unu gösteriyor 
        	daha sonra yeni nodun yani çıkarılacak olan elemandan sonraki gelen elamnı tmp->next = nodeToRemove->next bu işlemi yaparak tmp ye tanıttık
        	artık 7 ile 99 arasında bağlantı kalmadığı için 99u bellekten tahsis ettik
        	[3] -> [6] -> [7] -> [99] -> [5] -> [4]
            			 ^      ^
             			tmp   tmp->next (çıkarılacak düğüm)

			Çıkarılacak düğüm: [99]
			*/
            Node* nodeToRemove = tmp->next;
            tmp->next = nodeToRemove->next;
            delete nodeToRemove;
        }
    }

    // Listenin ilk elemanını yazdırma fonksiyonu
    void frontDataPrint() {
        if (isEmpty()) {
            cout << "Liste boş" << " ";
        } else {
            cout << "Listenin ilk elemani: " << begin()->data << endl;
        }
    }

    // Listenin son elemanını yazdırma fonksiyonu
    void backDataPrint() {
        Node* tmp = begin();
        if (isEmpty()) {
            cout << "Liste boş" << " ";
        } else {
            while (tmp->next != NULL) {
                tmp = tmp->next;
            }
            cout << "Listenin son elemani: " << tmp->data << endl;
        }
    }

    // Listenin son elemanını çıkarma fonksiyonu
    void popBack() {
        if (isEmpty()) {
            cout << "Liste boş" << " ";
        } else if (begin()->next == end()) {
        	//burada liste tek elemandan oluşuyosa başlangıcı da sonuda o olacağı için o elemanı sildik yani root başlangıcı gösterdiği için rootu bellekten silip null yaptık
            delete root;
            root = NULL;
        } else {
        	//birden fazla eleman varsada yeni bir node oluşturduk ve ilk elemandan başlattık
        	//tmp her seferinden kendin 2 sonrakini kontrol ediyor yani 3-4-5 olarak 3 eleman olsa 3 e kadar gelicek 3ün nextinin nexti dolu olduğu için 4 e geçicek daha sonrası null olduğu için burada kalıcak
        	//buna bakarken döngüde hep tmpyi kaydırıyoruz
        	//daha sonra 4 sondan bir önceki adımı gösterdiği için 4ün bir sonrakini yani 5. elemani siliyoruz
            Node* tmp = begin();
            while (tmp->next->next != NULL) {
                tmp = tmp->next;
            }
            delete tmp->next;
            tmp->next = NULL;
        }
    }

    // Listenin ilk elemanını çıkarma fonksiyonu
    void popFront() {
        if (isEmpty()) {
            cout << "Liste Boş" << endl;
        } else {
        	//yeni node başlangıcı gösteriyor
        	//rootta başlangıcı gösteriyordu onu 2.elemana aldık
        	//ve tmpyi sildik
            Node* tmp = begin();
            root = tmp->next;
            delete tmp;
        }
    }

    // Listenin tüm elemanlarını yazdırma fonksiyonu
    void printData() {
    	//yeni node tmp oluşturduk
    	//root ile aynı yer olan başlangıcı gösteriyor
    	//tmp null değerini görene kadar datasını yazdırdık ve bir adım ileriye aktardık
        Node* tmp = begin();
        while (tmp != end()) {
            cout << tmp->data << endl;
            tmp = tmp->next;
        }
    }
};

int main(int argc, char** argv) {
	
	/*
	
	
	BU KISIM FONKSİYONLARI TEST ETTİĞİM KISIM BURAYI ÇOK KAALE ALMANA GEREK YOK
	
	*/
    // Node sınıfının nesnesi oluşturuldu
    // böylece bellekte alan tahsis edilmiş oldu ve 3 değeri atandı
    Node* n1 = new Node(3);

    // n2 node da oluşturuldu 
    Node* n2 = new Node(5);

    // n3 node da oluşturuldu 
    Node* n3 = new Node(10);

    // n1 ile gösterici işlemleri yapıldı 3--->5--->10 diye gidiyor sıra
    n1->next = n2;
    n2->next = n3;

    // başlangıcımız n1 olduğu için başlangıcı göstericek bir tmp değişkeni için alan tahsisi gerçekleştirildi
    Node* tmp = n1;
    while (tmp != NULL) {
        // temp'in bir sonraki adımı null olana kadar yani 3.node'a gidene kadar elemanlar ekrana yazdırıldı
        cout << tmp->data << endl;
        tmp = tmp->next;
    }

    // Liste sınıfının nesnesi oluşturuldu
    list liste;
    cout << liste.isEmpty() << endl;

    // Listeye elemanlar eklendi
    liste.pushFront(5);
    liste.pushFront(6);
    liste.pushFront(7);
    liste.pushBack(4);
    liste.pushFront(3);
    liste.printData();

    // Listenin son ve ilk elemanları yazdırıldı
    liste.backDataPrint();
    liste.frontDataPrint();

    // Belirli bir pozisyona eleman eklendi
    liste.insert(2, 99);
    liste.printData();

    // Belirli bir pozisyondan eleman çıkarıldı
    liste.remove(3);
    liste.printData();

    // Listenin son elemanı çıkarıldı
    liste.popBack();
    liste.printData();

    // Listenin ilk elemanı çıkarıldı
    liste.popFront();
    liste.printData();
}

