#include<iostream>
#include<string>
#include<iomanip>
#include<queue>
#include<algorithm>
#include<limits>
#include<cctype>

using namespace std;

// tipedata_1
struct Pasien {
    string nik;
    string nama;
    int usia;
    string keluhan;
};

queue<Pasien> daftarAntrian;

// validasi NIK
bool cekNIK(string nik) {
    if(nik.length() != 16) {
        return false;
    }
    for(char c : nik) {
        if(!isdigit(c)) {
            return false;
        }
    } return true;
}

// validasi nama
bool cekHurufspasi(string teks) {
    for(char c : teks) {
        if(!isalpha(c) && !isspace(c)) {
            return false;
        }
    } return true;
}

// ambil inputan angka
int ambilAngka(string teks) {
    int angka;
    while(true) {
        cout << teks;
        cin >> angka;
        if(cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input harus angka, coba lagi.\n";
        }else {
            cin.ignore();
            return angka;
        }
    }
}

// tambahPasien
void tambahPasien() {
    Pasien pasienBaru;

    do {
        cout << "Input NIK (16 digit) : ";
        getline(cin, pasienBaru.nik);
        if(!cekNIK(pasienBaru.nik)) {
            cout << "Format NIK salah." << endl;
        }
    }while (!cekNIK(pasienBaru.nik));

    pasienBaru.usia = ambilAngka("Umur Pasien : ");

    do {
        cout << "Nama Pasien : ";
        getline(cin, pasienBaru.nama);
        if(!cekHurufspasi(pasienBaru.nama)) {
            cout << "Nama tidak valid." << endl;
        }
    }while (!cekHurufspasi(pasienBaru.nama));

    do {
        cout << "Keluhan : ";
        getline(cin, pasienBaru.keluhan);
        if(!cekHurufspasi(pasienBaru.keluhan)) {
            cout << "Keluhan tidak valid." << endl;
        }
    }while (!cekHurufspasi(pasienBaru.keluhan));

}

// tampilkan data pasien
void tampilkanSemua(Pasien* data, int jumlah) {
    if(jumlah == 0) {
        cout << "Belum ada data pasien.";
        return;
    }

    cout << left << setw(6) << "No" << setw(18) << "NIK" << setw(20) << "Nama" << setw(6) << "Usia" << setw(30) << "Keluhan" << endl;
    cout << string(80, '-');
    cout << endl;

    for(int i=0; i<jumlah; i++) {
        cout << left << setw(6) << (i+1) << setw(18) << data[i].nik << setw(20) << data[i].nama << setw(6) << data[i].usia1 << setw(30) << data[i].keluhan << endl;
    }
}

// urutkan data pasien berdasarkan nik
void urutkanPasien() {
    int jumlah;
    
}

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