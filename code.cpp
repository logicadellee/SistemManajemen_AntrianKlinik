#include<iostream>
#include<string>

using namespace std;

// tipedata_1
struct Pasien {
    int nomorAntrian;
    string nama;
    long long nik;
    int usia;
    string Keluhan;
    string waktuDaftar;
};

// fungsi tampilan
int getMenu() {
    int input;
    system("cls");
    cout << "\nProgram CRUD Data Antrian Pasien Klinik Sehat" << endl;
    cout << "================================================" <<endl;
    cout << "1. Tambah Data Pasien" << endl;
    cout << "2. Tampilkan Data Pasien" << endl;
    cout << "3. Ubah Data Pasien" << endl;
    cout << "4. Hapus Data Pasien" << endl;
    cout << "5. Selesai" << endl;
    cout << "================================================" <<endl;
    cout << "Pilih [1-5] : ";
    cin >> input;
    return input;

}

// Menambahkan Pasien
// void tambahPasien(string nama, long long nik, int usia, string keluhan,string waktuDaftar,int prioritas) {
//     pasien p = {nomorAntrian++,nama, nik, usia, keluhan, waktuDaftar, prioritas};
//     antrian.push(p);
//     semuaPasien.pushBack(p);
//     cout << "Pasien " << nama << " Berhasil ditambahkan ke antrian.\n";
// }

// Menampilkan Antrian
// void tampilkanAntrian() {
    
// }

int main() {
    int pilihan = getMenu();
    char is_continue;

    enum menu{CREATE=1,READ, UPDATE, DELETE, FINISH};

    while(pilihan != FINISH) {
        switch(pilihan){
            case CREATE : 
                cout << "Menambah data pasien" << endl;
                break;
            case READ :
                cout << "Tampilkan data pasien" << endl;
                break;
            case UPDATE :
                cout << "Ubah data pasien" << endl;
                break;
            case DELETE :
                cout << "Hapus data pasien" << endl;
                break;
            default :
                cout << "Pilihan tidak ditemukan" << endl;
                break;
        }

        label_continue :

        cout << "Lanjutkan? (y/n) : ";
        cin >> is_continue;
        if((is_continue == 'y') | (is_continue == 'Y')) {
            pilihan = getMenu();
        } else if((is_continue == 'n') | (is_continue == 'N')) {
            break;
        } else {
            goto label_continue;
        }
    }
    cout << "akhir dari program" << endl;
    cin.get();
    return 0;
}