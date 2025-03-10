#include <iostream>
using namespace std;

class Node {
    public:
    	//parametrelerimizi oluþturup constructor fonksiyonumuzu oluþturduk
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
    	//hash tablomuzun parametreleri ve fonksiyonlarýný belirledik
    	//boyutu olan dizimiz pointer olarak bellekte yer tutcak
    	//ekleme çýkartma ve eleman getirme gibi fonksiyonlarý var
        Node* Data[MAX];
        HashTable();
        void add(int key);
        Node* get(int key);
        bool remove(int anahtar);
};

HashTable::HashTable() 
    // constructor fonskiyon ile dizinin tüm elemanlarýný NULL olarak atadýk
    for(int index = 0; index < MAX; index++) {
        Data[index] = NULL;
    }
}

void HashTable::add(int key) {
	//yeni eleman için bellekte yer ayýrdýk
    Node* pNew = new Node(key);
    //elemanýn yerini belirlemek için gelen key deðerine göre dizinin boyutuyla mod alma iþlemi yaptýk
    //key=32 ise dizi boyutu 10 burada verimiz dizideki 2.indise yerleþtirilirdi Data[2]
    int mod = key % MAX;
    
    //belirlenen indiste eleman yoksa direkt verimizi oraya koyuyoruz
    if(!Data[mod]) {
        Data[mod] = pNew;
        return;
    }
    
    //belirlenen indiste eleman varsa elemanýn gösterdiði adresle ayný yeri gösteren bir pTemp oluþturuyoruz
    //pTemp koyulmasý gereken yerden sonra ilk bulduðu boþluða koyularak ekleme iþlemi tamamlanýyor
    Node* pTemp = Data[mod];
    while(pTemp->pNext != NULL) {
        pTemp = pTemp->pNext;
    }
    pTemp->pNext = pNew;
}

Node* HashTable::get(int key) {
	//yine indis hesabý için bir mod alma iþlemi yapýlýyor
	//ve o indisteki elemanýn verisi yeni bir göstericiye atanýyor pTemp
    int mod = key % MAX;
    Node* pTemp = Data[mod];
    
    //dizi içerisinde girilen key deðeriyle pTempin içerisindeki key deðeri eþit olana kadar pTemp ilerletiliyor
    //ayný keye sahip eleman yoksa NULL olarak dönüþ yapýlýyor 
    while(pTemp != NULL) {
        if(pTemp->key == key) {
            return pTemp;
        }
        pTemp = pTemp->pNext;
    }
    return NULL;
}

bool HashTable::remove(int key) {
	//indis belirleme iþlemi yapýlýyor
    int mod = key % MAX;
    
    //böyle bir veri yoksa false deðeri dönüyor burada fonksiyon bool olduðu için geri dönüþ olmalý
    //direkt get Fonksiyonumuza da yönlendirebilirdik
    if(!Data[mod]) return false;
    
    
    //indisten sonra eleman olmayana kadar indisi ilerletiyoruz
    //eðer eþleþme varsa ilk olarak ayrýlan yeri siliyoruz
    //daha sonra içerisindeki veriyi
    //ve true deðeri döndürüyoruz eðer yoksa false;
    if(!Data[mod]->pNext) {
        if(Data[mod]->key == key) {
            delete Data[mod];
            Data[mod] = NULL;
            return true;
        }
        return false;
    }
    
    //gelen key bilgisiyle indisteki key verisi eþit ise
    //yeni bir gösterici oluþturuyoruz ve o bulunan indisin bir sonraki indisini gösteriyor
    //bulunan indisin bellekten silip içeriðini yeni göstericiye atýyoruz ve true dönüþü yapýlýyor
    //burada silme iþleminde örneðin 5 ile 15 ayný key deðerlerine sahip ikisi de 5 
    //ve 5 silinmek isteniyor olsun
    //normalde ekleme iþleminde 5 ten sonra 15 gelicekti indisler ayný olduðu için bir sonrakine geçiyordu
    //bu yüzden geçici göstericiyi 15e taþýdýk ve 5 kýsmýný kaldýrarak 15 i oraya taþýdýk 
    //15 silinmek istediðinde yine 5. indise bakýlacaðý için bu iþlemin yapýlmasý gerekiyor
    if(Data[mod]->key == key) {
        Node* pNextNode = Data[mod]->pNext;
        delete Data[mod];
        Data[mod] = pNextNode;
        return true;
    }
    
    //veri ile ayný indisi gösteren bir gösterici oluþturduk
    Node* pTemp = Data[mod];
    //dizi bitene kadar iþlem devam edicek
    while(pTemp->pNext != NULL) {
    	//dizi bitene kadar da hep sonraki adýmla silmek istediði key eþit mi kontrolü yapýcak
        if(pTemp->pNext->key == key) {
        	// eþit ise yeni bir gösterici oluþturyoruz ve bu silmemiz gereken yeri gösteriyor
        	//çünkü biz hep silmemiz gereken yerden bir adým geride gidiyorduk
        	//daha sonra bulunduðumuz konumun bir sonraki adýmý normalde silmemiz gereken yeri gösteriyordu
        	//pTemp->pNext = pToDelete->pNext buiþlem ile iki sonrasýný göstermesini saðladýk
        	//ve daha sonra silinmesi gereken yeri sildik
        	//kýsacasý ben 4.deyim ve 5.yi silicem 5. gördükten sonra onu bir geçici göstericiye atýyorum
        	//sonra  4 ten sonra 6 geliyormul gibi manipüle ediyorum 
        	//5in içeriðini silip devam ediyorum
            Node* pToDelete = pTemp->pNext;
            pTemp->pNext = pToDelete->pNext;
            delete pToDelete;
            return true;
        }
        //her döngüde pTempi ilerletmeyi de unutmayalým yoksa sonsuz döngü olur
        pTemp = pTemp->pNext;
    }
    return false;
}

int main(int argc, char** argv) {
	//BURAYA BAKMAYABÝLÝRSÝN DENEDÝÐÝM KISIMLAR
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

