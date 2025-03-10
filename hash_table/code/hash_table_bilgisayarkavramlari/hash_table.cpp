#include <iostream>
using namespace std;

typedef struct veri {
    int key;
    int value;
} veri;

veri a[27];

int hash(int x) {
    // Burada ax+b format�ndaki denklemde a ve b aralar�nda asal olmal�d�r.
    // Mod alma i�leminin sonucunun s�rekli b de�eri ��kmas�n�n �n�ne ge�mi� oluyoruz.
    return x % 27; // �rnek fonksiyon: 8*x+5 mod 27
}

int put(veri data) {
    // Dizide eklenece�i yer bo�sa ekleme i�lemi yap�l�r.
    // Bo� de�ilse indisi artt�rarak dizi boyunca bo�luk aramaya devam eder.
    int index = hash(data.key);
    int donusSayisi = 0;
    if (a[index].key == -1) {
        a[index] = data;
        return 1;
    } else {
        // Dizideki index bo�ken ve gelen value e�it de�ilken
        while (a[index].key != data.key && a[index].key!=-1 ) {
        	cout << "Key: " << a[index].key << " Value: " << a[index].value << " Index: " << index << endl;
            index++;
            if (index >= 27) {
                index = index % 27;
                donusSayisi++;
                if (donusSayisi >= 1) {
                    cout << "Hash table dolu" << endl;
                    return -1;
                }
            }
        }
        
        a[index].value = data.value;
        a[index].key = data.key;
        return 1;
    }
}

int arrayItems() {
    for (int index = 0; index < 27; index++) {
        cout << "Index: " << index << " Key: " << a[index].key << " Value: " << a[index].value << endl;
    }
    return 0;
}

int get(int key) {
    int donusSayisi = 0;
    int index = hash(key); // Ba�lang�� indeksi
    while (a[index].key != key && a[index].key != -1) {
        index++;
        if (index >= 27) {
            index = index % 27;
            donusSayisi++;
            if (donusSayisi >= 1) {
                cout << "Hash tableda bulunumad�" << endl;
                return -1;
            }
        }
    }
    return a[index].value;
}


int main(int argc, char** argv) {
    for (int i = 0; i < 27; i++) {
        a[i].key = -1;
    }

    veri data;
    
    //hash table dolu hatas�n� almak i�in 30 eleman ekledik
    for(int index = 0;index<30;index++){
    data.key = index;
    data.value = index*23;
    put(data);
	}

    data.key = 10;
    data.value = 42342;
    put(data);

    data.key = 100;
    data.value = 343434;
    put(data);

    data.key = 1;
    data.value = 66666;
    put(data);

    data.key = 5;
    data.value = 55555;
    put(data);
 

    cout << get(10) << endl;
    cout << get(1) << endl;
    cout << get(5) << endl;
    cout << get(3) << endl;
    cout<<get(31)<<endl;
    arrayItems();

    return 0;
}

