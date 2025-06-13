#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<queue>
#include<algorithm>
#include<limits>
#include<cctype>

using namespace std;

// Login section
bool login() {
    string username, password;
    const string User = "admin";
    const string Pass = "12345";

    cout << "=======SISTEM LOGIN=======" << endl;
    cout << "Username : ";
    getline(cin, username);
    cout << "Password : ";
    getline(cin, password);

    if(username == User && password == Pass) {
        cout << "Login berhasil" << endl;
        return true;
    } else {
        cout << "Login gagal. Username atau Password salah" << endl;
        return false;
    }
}

// tipe data_1
struct Pasien {
    string nik;
    string nama;
    int usia;
    string keluhan;
};

queue<Pasien> daftarAntrian;

// validasi NIK
bool cekNIK(string nik) {
    if(nik.length() != 16) return false;
    for(char c : nik) {
        if(!isdigit(c)) return false;
    }
    return true;
}

// validasi nama
bool cekHurufspasi(string teks) {
    for(char c : teks) {
        if(!isalpha(c) && !isspace(c)) {
            return false;
        }
    }
    return true;
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
        } else {
            cin.ignore();
            return angka;
        }
    }
}

// ambil data dari file
Pasien* ambilData(int &jumlah) {
    ifstream file("data_pasien.txt");
    Pasien* list = nullptr;
    jumlah = 0;
    string baris;

    while (getline(file, baris)) {
        Pasien p;
        size_t a = baris.find("|");
        size_t b = baris.find("|", a+1);
        size_t c = baris.find("|", b+1);
        p.nik = baris.substr(0,a);
        p.nama = baris.substr(a+1, b-a-1);
        p.usia = stoi(baris.substr(b+1,c-b-1));
        p.keluhan = baris.substr(c+1);

        Pasien* temp = new Pasien[jumlah+1];
        for(int i=0; i<jumlah; i++) {
            temp[i] = list[i];
        }
        temp[jumlah] = p;
        delete[] list;
        list = temp;
        jumlah++;
    }
    return list;
}

// simpan data ke file
void simpanData(Pasien* list, int jumlah) {
    ofstream file("data_pasien.txt");
    for(int i=0; i<jumlah; i++) {
        file << list[i].nik << "|" << list[i].nama << "|" << list[i].usia << "|" << list[i].keluhan << endl;
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
    } while (!cekNIK(pasienBaru.nik));

    do {
        cout << "Nama Pasien : ";
        getline(cin, pasienBaru.nama);
        if(!cekHurufspasi(pasienBaru.nama)) {
            cout << "Nama tidak valid." << endl;
        }
    } while (!cekHurufspasi(pasienBaru.nama));

    pasienBaru.usia = ambilAngka("Umur Pasien : ");

    do {
        cout << "Keluhan : ";
        getline(cin, pasienBaru.keluhan);
        if(!cekHurufspasi(pasienBaru.keluhan)) {
            cout << "Keluhan tidak valid." << endl;
        }
    } while (!cekHurufspasi(pasienBaru.keluhan));

    ofstream file("data_pasien.txt", ios::app);
    file << pasienBaru.nik << "|" << pasienBaru.nama << "|" << pasienBaru.usia << "|" << pasienBaru.keluhan << endl;
    cout << "Data berhasil disimpan" << endl;
    daftarAntrian.push(pasienBaru);
}

// tampilkan semua data pasien
void tampilkanSemua(Pasien* data, int jumlah) {
    if(jumlah == 0) {
        cout << "Belum ada data pasien.\n";
        return;
    }

    cout << left << setw(6) << "No" << setw(18) << "NIK" << setw(20) << "Nama" << setw(6) << "Usia" << setw(30) << "Keluhan" << endl;
    cout << string(80, '-') << endl;

    for(int i = 0; i < jumlah; i++) {
        cout << left << setw(6) << (i+1) << setw(18) << data[i].nik << setw(20) << data[i].nama << setw(6) << data[i].usia << setw(30) << data[i].keluhan << endl;
    }
}

// ubah data pasien
void ubahDataPasien() {
    int total;
    Pasien* data = ambilData(total);
    string nik;
    cout << "Masukkan NIK yang mau diubah: ";
    getline(cin, nik);

    for (int i = 0; i < total; i++) {
        if (data[i].nik == nik) {
            string input; 
            cout << "Nama baru (" << data[i].nama << "): ";
            getline(cin, input);
            if (!input.empty() && cekHurufspasi(input)) data[i].nama = input;

            cout << "Umur baru (" << data[i].usia << "): ";
            getline(cin, input);
            if (!input.empty()) {
                try {
                    data[i].usia = stoi(input);
                } catch (...) {
                    cout << "Input umur tidak valid.\n";
                }
            }

            cout << "Keluhan baru (" << data[i].keluhan << "): ";
            getline(cin, input);
            if (!input.empty() && cekHurufspasi(input)) data[i].keluhan = input;

            simpanData(data, total);
            cout << "Data berhasil diperbarui.\n";
            delete[] data;
            return;
        }
    }

    cout << "Data pasien tidak ditemukan.\n";
    delete[] data;
}

// hapus data pasien

// mencari data pasien berdasarkan NIK

// urutkan data pasien berdasarkan NIK
void urutkanPasien() {
    int jumlah;
    Pasien* data = ambilData(jumlah);
    sort(data, data + jumlah, [](Pasien a, Pasien b) {
        return a.nik < b.nik;
    });
    tampilkanSemua(data, jumlah);
    delete[] data;
}

// panggil antrian pasien

// tampilan menu
int getMenu() {
    int input;
    cout << "\nProgram CRUD Data Antrian Pasien Klinik Sehat" << endl;
    cout << "================================================" << endl;
    cout << "1. Tambah Data Pasien" << endl;
    cout << "2. Tampilkan Data Pasien" << endl;
    cout << "3. Ubah Data Pasien" << endl;
    cout << "4. Hapus Data Pasien" << endl;
    cout << "5. Cari Data Pasien" << endl;
    cout << "6. Urutkan Pasien" << endl;
    cout << "7. Panggil Antrian" << endl;
    cout << "8. Keluar" << endl;
    cout << "================================================" << endl;
    cout << "Pilih [1-8] : ";
    cin >> input;
    cin.ignore(); // agar getline setelah cin tidak bermasalah
    return input;
}

// main program
int main() {
    if(!login()) return 0;

    int pilihan;
    do {
        pilihan = getMenu();
        switch(pilihan){
            case 1:
                tambahPasien();
                break;
            case 2: {
                int jumlah;
                Pasien* data = ambilData(jumlah);
                tampilkanSemua(data, jumlah);
                delete[] data;
                break;
            }
            case 3:
                ubahDataPasien();
                break;
            case 4:
                hapusDataPasien();
                break;
            case 5:
                cariDatapasien();
                break;
            case 6:
                urutkanPasien();
                break;
            case 7:
                panggilPasien();
                break;
            case 8:
                cout << "Selesai. Terima Kasih!" << endl;
                break;
            default:
                cout << "Pilihan tidak ditemukan" << endl;
                break;
        }
    } while (pilihan != 8);

    return 0;
}
