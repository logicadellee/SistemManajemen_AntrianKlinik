#include<iostream>
using namespace std;

// tipedata_1
struct Pasien {
    int nomorAntrian;
    string nama;
    long long nik;
    int usia;
    string Keluhan;
    string waktuDaftar;
    int prioritas;
};

// Menambahkan Pasien
void tambahPasien(string nama, long long nik, int usia, string keluhan,string waktuDaftar,int prioritas) {
    pasien p = {nomorAntrian++,nama, nik, usia, keluhan, waktuDaftar, prioritas};
    antrian.push(p);
    semuaPasien.pushBack(p);
    cout << "Pasien " << nama << " Berhasil ditambahkan ke antrian.\n";
}

// Menampilkan Antrian
void tampilkanAntrian() {
    
}

int main() {

    return 0;
}