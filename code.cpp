#include<iostream>   //untuk input-output
#include<fstream>    //untuk file handling(ifstream.ofstream)
#include<string>     //untuk tipe data string
#include<iomanip>    //untuk format tampilan (setw,left)
#include<queue>      //untuk struktur data queue(antrian)
#include<algorithm>  //untuk sort
#include<limits>     //untuk membersihkan cin saat input salah
#include<cctype>     //untuk cek karakter (isalpha,isdigit,isspace)

using namespace std;

// -------------------- LOGIN SECTION --------------------
bool login() {
    string username, password;                             //menyimpan inputan pengguna
    const string User = "admin";
    const string Pass = "12345";

    cout << "=======SISTEM LOGIN=======" << endl;
    cout << "Username : ";
    getline(cin, username);
    cout << "Password : ";
    getline(cin, password);

    if(username == User && password == Pass) {             //pengecekan login
        cout << "Login berhasil" << endl;
        return true;
    } else {
        cout << "Login gagal. Username atau Password salah" << endl;
        return false;
    }
}

// tipe data
struct Pasien {
    string nik;
    string nama;
    int usia;
    string keluhan;
};

queue<Pasien> daftarAntrian; //antrian, prinsip FIFO

// validasi NIK
bool cekNIK(string nik) {
    if(nik.length() != 16) return false;                   //cek panjang string
    for(char c : nik) {
        if(!isdigit(c)) return false;                     //cek karakter harus angka
    }
    return true;
}

// validasi nama
bool cekHurufspasi(string teks) {
    for(char c : teks) {
        if(!isalpha(c) && !isspace(c)) {                 //cek huruf dan spasi
            return false;
        }
    }
    return true;
}

// ambil inputan angka
int ambilAngka(string teks) {
    int angka;
    while(true) {                                       //ulangi sampai inputan user benar
        cout << teks;
        cin >> angka;
        if(cin.fail()) {                                //cek apakah input gagal dibaca sebagai angka
            cin.clear();                                //kalau input gagal,fungsi ini akan menghapus status eror dari cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n');   //membersihkan sisa input yang salah dari buffer
            cout << "Input harus angka, coba lagi.\n";
        } else {
            cin.ignore();
            return angka;                               //keluarkan nilai ke program utama
        }
    }
}

// ambil data dari file
Pasien* ambilData(int &jumlah) {                       //ambil data dari file untuk masuk ke array
    ifstream file("data_pasien.txt");                  //buka file untuk dibaca
    Pasien* list = nullptr;
    jumlah = 0;
    string baris;

    while (getline(file, baris)) {                    //ambil tiap baris dari file
        Pasien p;
        size_t a = baris.find("|");
        size_t b = baris.find("|", a+1);
        size_t c = baris.find("|", b+1);
        p.nik = baris.substr(0,a);
        p.nama = baris.substr(a+1, b-a-1);
        p.usia = stoi(baris.substr(b+1,c-b-1));
        p.keluhan = baris.substr(c+1);

        Pasien* temp = new Pasien[jumlah+1];          //tambahkan ke array
        for(int i=0; i<jumlah; i++) {
            temp[i] = list[i];
        }
        temp[jumlah] = p;
        delete[] list;
        list = temp;
        jumlah++;                                     //update list
    }
    return list;
}

// simpan data ke file
void simpanData(Pasien* list, int jumlah) {          //simpan array ke dalam file pagi
    ofstream file("data_pasien.txt");                //buka file untuk ditulis ulang
    for(int i=0; i<jumlah; i++) {                    //ulangi semua data dalam array, lalu tulis ke file dengan format nik|nama|usia|keluhan
        file << list[i].nik << "|" << list[i].nama << "|" << list[i].usia << "|" << list[i].keluhan << endl;
    }
}

// tambah data pasien
void tambahPasien() {
    Pasien pasienBaru;                              //variabel pasienBaru untuk menampung data input

    do {
        cout << "Input NIK (16 digit) : ";
        getline(cin, pasienBaru.nik);              //cek nik
        if(!cekNIK(pasienBaru.nik)) {              
            cout << "Format NIK salah." << endl;
        }
    } while (!cekNIK(pasienBaru.nik));

    do {
        cout << "Nama Pasien : ";
        getline(cin, pasienBaru.nama);
        if(!cekHurufspasi(pasienBaru.nama)) {     //cek huruf dan spasi
            cout << "Nama tidak valid." << endl;
        }
    } while (!cekHurufspasi(pasienBaru.nama));

    pasienBaru.usia = ambilAngka("Umur Pasien : ");   //validasi input adalah angka

    do {
        cout << "Keluhan : ";
        getline(cin, pasienBaru.keluhan);
        if(!cekHurufspasi(pasienBaru.keluhan)) {      //cek agar input hanya huruf dan spasi
            cout << "Keluhan tidak valid." << endl;
        }
    } while (!cekHurufspasi(pasienBaru.keluhan));

    ofstream file("data_pasien.txt", ios::app);      //simpan data ke file
    file << pasienBaru.nik << "|" << pasienBaru.nama << "|" << pasienBaru.usia << "|" << pasienBaru.keluhan << endl;
    cout << "Data berhasil disimpan" << endl;
    daftarAntrian.push(pasienBaru);                 //menambahkan pasien baru ke antrian (struktur data queue)
}

// tampilkan semua data pasien
void tampilkanSemua(Pasien* data, int jumlah) {    //pointer ke array dari struct pasien, jumlah adalah total data dalam array
    if(jumlah == 0) {                              //jika tidak ada data
        cout << "Belum ada data pasien.\n";
        return;
    }

    cout << left << setw(6) << "No" << setw(18) << "NIK" << setw(20) << "Nama" << setw(6) << "Usia" << setw(30) << "Keluhan" << endl;   //setw(n) membuat lebar kolom, left untuk menyusun teks rata kiri
    cout << string(80, '-') << endl;         //menampilkan garis pemisah dengan panjang 80 karakter          

    for(int i = 0; i < jumlah; i++) {
        cout << left << setw(6) << (i+1) << setw(18) << data[i].nik << setw(20) << data[i].nama << setw(6) << data[i].usia << setw(30) << data[i].keluhan << endl;
    }
}

// ubah data pasien
void ubahDataPasien() {
    int total;
    Pasien* data = ambilData(total);              //ambil data dari file dan menyimpannya dalam array data
    string nik;
    cout << "Masukkan NIK yang mau diubah: ";
    getline(cin, nik);

    for (int i = 0; i < total; i++) {            //pencarian data dalam array
        if (data[i].nik == nik) {
            string input; 
            cout << "Nama baru (" << data[i].nama << "): ";
            getline(cin, input);
            if (!input.empty() && cekHurufspasi(input)) data[i].nama = input;      //cek jika input tidak kosong dan valid (huruf dan spasi), update nama

            cout << "Umur baru (" << data[i].usia << "): ";
            getline(cin, input);
            if (!input.empty()) {                         //jika tidak kosong,coba konversi ke int(stoi)
                try {
                    data[i].usia = stoi(input);           
                } catch (...) {                          //kalau bukan angka, tampilkan pesan eror
                    cout << "Input umur tidak valid.\n";
                }
            }

            cout << "Keluhan baru (" << data[i].keluhan << "): ";
            getline(cin, input);
            if (!input.empty() && cekHurufspasi(input)) data[i].keluhan = input;

            simpanData(data, total);                   //simpan seluruh data kembali ke file
            cout << "Data berhasil diperbarui.\n";
            delete[] data;                            //hapus array dari memory            
            return;
        }
    }

    cout << "Data pasien tidak ditemukan.\n";
    delete[] data;
}

// hapus data pasien
void hapusDataPasien() {
    int jumlah;
    Pasien* data = ambilData(jumlah);                //ambil data dari file ke dalam array data
    string nik;
    cout << "NIK yang ingin dihapus: ";
    getline(cin, nik);

    bool ada = false;                               //cek apakah nik ditemukan
    Pasien* baru = new Pasien[jumlah];              //array baru untuk menyimpan data yang tidak dihapus
    int idx = 0;                                    //indeks array baru
    for (int i = 0; i < jumlah; i++) {                 
        if (data[i].nik != nik) {                   //nik tidak sama, simpan ke array baru
            baru[idx++] = data[i];
        } else {
            ada = true;                             //nik sama, data pasien dihapus
        }
    }

    if (ada) {
        simpanData(baru, idx);
        cout << "Data berhasil dihapus.\n";
    } else {
        cout << "NIK tidak ditemukan.\n";
    }

    delete[] data;
    delete[] baru;
}

// mencari data pasien berdasarkan NIK
void cariDataPasien() {
    int jumlah;
    Pasien* data = ambilData(jumlah);
    string nik;
    cout << "Cari NIK: ";
    getline(cin, nik);

    for (int i = 0; i < jumlah; i++) {                       //loop pencarian
        if (data[i].nik == nik) {                            //jika data ditemukan
            cout << "Pasien ditemukan:\n";          
            cout << "Nama: " << data[i].nama << "\nUmur: " << data[i].usia << "\nKeluhan: " << data[i].keluhan << "\n";
            delete[] data;
            return;
        }
    }

    cout << "Data tidak ditemukan.\n";                      //jika data tidak ditemukan
    delete[] data;
}

// urutkan data pasien berdasarkan NIK
void urutkanPasien() {                                       //mengurutkan data pasien berdasarkan nik secara ascending (kecil ke besar)
    int jumlah;
    Pasien* data = ambilData(jumlah);
    sort(data, data + jumlah, [](Pasien a, Pasien b) {      //mengurutkan array, [](pasien a, pasien b) fungsi kecil tanpa nama, yang membandingkan nik a dan nik b
        return a.nik < b.nik;
    });
    tampilkanSemua(data, jumlah);                           //tampilkan semua data pasien
    delete[] data;
}

// panggil antrian pasien
void panggilPasien() {
    if (daftarAntrian.empty()) {                            //cek apakah ada antrian pasien
        cout << "Antrian kosong.\n";
        return;
    }

    Pasien next = daftarAntrian.front();                   //mengambil pasien terdepan dalam antrian, tapi tidak menghapusnya dulu
    daftarAntrian.pop();                                   //hapus dari antrian, karena sudah dipanggil

    cout << "Memanggil: " << next.nama << " - Keluhan: " << next.keluhan << "\n";  

    ofstream file("riwayat_dilayani.txt", ios::app);      //buka file riwayat dan menambahkan data baru
    file << next.nik << "|" << next.nama << "|" << next.usia << "|" << next.keluhan << "|SUDAH DILAYANI\n";
}

// tampilan menu
int getMenu() {                                          //menampilkan daftar menu
    int input;
    cout << "\n===== MENU ANTRIAN PASIEN =====\n"<< endl;
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
    cin.ignore();
    return input;
}

// main program
int main() {
    if(!login()) return 0;                                 //cek login

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
                cariDataPasien();
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
