#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#define MAX_WISATA 100
#define MAX_BOOKING 100
#define MAX_AKUN 100

// TAMBAH WARNA
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN = "\033[36m";
const string RESET = "\033[0m";

typedef struct {
    string nama;
    string password;
    bool isAdmin;
} Akun;

struct Destinasi {
    string nama;
    string lokasi;
    string tanggal;
    string harga;
    int stok;
};

struct Booking {
    string destinasi;
    string lokasi;
    string tanggal;
    string harga;
    int jumlah;
    string username;
};

int validasiInput(const string& prompt, int min, int max) {
    int input;
    while (true) {
        cout << prompt;
        string temp;
        getline(cin, temp);
        
        if (temp.empty()) {
            cout << RED << "Input tidak boleh kosong.\n" << RESET;
            continue;
        }
        
        try {
            input = stoi(temp);
            if (input < min || input > max) {
                cout << RED << "Input harus antara " << min << " dan " << max << ".\n" << RESET;
                continue;
            }
            return input;
        } catch (...) {
            cout << RED << "Input harus berupa angka.\n" << RESET;
        }
    }
}

int validasiaAngka(const string& prompt, bool allowNegative = false) {
    int value;
    while (true) {
        cout << prompt;
        string input;
        getline(cin, input);
        
        if (input.empty()) {
            cout << RED << "Input tidak boleh kosong.\n" << RESET;
            continue;
        }
        
        try {
            size_t pos;
            value = stoi(input, &pos);
            
            if (pos != input.length()) {
                throw invalid_argument("Invalid input");
            }
            
            if (!allowNegative && value < 0) {
                cout << RED << "Input tidak boleh negatif.\n" << RESET;
                continue;
            }
            
            return value;
        } catch (...) {
            cout << RED << "Input harus berupa angka.\n" << RESET;
        }
    }
}

void goodbye() {
    cout << BLUE << R"(
                     _                       | 
                    (_| _  _  _|   |_  \/ _  | 
                    __|(_)(_)(_|   |_) / (/_ o 
    )" << RESET << endl;
}

void logoTiketTersedia() {
    cout << BLUE << R"(
                         _______  _ _        _     _______                     _ _       
                        |__   __ (_) |      | |   |__   __|                   | (_)      
                            | |   _| | _____| |_     | | ___ _ __ ___  ___  __| |_  __ _ 
                            | |  | | |/ / _ \ __|    | |/ _ \ '__/ __|/ _ \/ _` | |/ _` |
                            | |  | |   <  __/ |_     | |  __/ |  \__ \  __/ (_| | | (_| |
                            |_|  |_|_|\_\___|\__|    |_|\___|_|  |___/\___|\__,_|_|\__,_|
    )" << RESET << endl;
}

void logoWisaPan() {
    cout << CYAN << R"(
  _       _   __    __    ___    __    _     
 \ \    /| | ( (`  / /\  | |_)  / /\  | |\ | 
  \_\/\/ |_| _)_) /_/--\ |_|   /_/--\ |_| \| 
    )" << RESET << endl;
}

bool Login(int attempt, const int maxAttempt, Akun akun[], int Jumlahakun, string &user, string &pass) {
    if (attempt >= maxAttempt) {
        return false;
    }
    cout << BLUE << "\n==============================" << RESET;
    cout << "\n     Halo Selamat datang!" << endl;
    cout << "        Silahkan Login" <<endl;
    cout << BLUE << "==============================" << RESET << endl;
    cout << "Nama: ";
    getline(cin, user);
    cout << "Password: ";
    getline(cin, pass);
    for (int i = 0; i < Jumlahakun; i++) {
        if (user == akun[i].nama && pass == akun[i].password) {
            return true;
        }
    }
    cout << RED << "Login Gagal. Coba Lagi" << RESET << endl;
    return Login(attempt + 1, maxAttempt, akun, Jumlahakun, user, pass);
}

void tampilkan(Destinasi wisata[], int TotalDestinasi) {
    logoTiketTersedia();
    cout << "+-----+----------------------------+-------------------------+----------------------+------------+----------------+\n";
    cout << "| No  | Destinasi                  | Lokasi                  | Tanggal              |   Harga    | Tiket Tersedia |\n";
    cout << "+-----+----------------------------+-------------------------+----------------------+------------+----------------+\n";
    for (int i = 0; i < TotalDestinasi; i++) {
        cout << "| " << setw(3) << right << i + 1 << " "
             << "| " << setw(27) << left << wisata[i].nama
             << "| " << setw(24) << left << wisata[i].lokasi
             << "| " << setw(21) << left << wisata[i].tanggal
             << "| " << setw(10) << right << wisata[i].harga
             << " | " << setw(14) << right << wisata[i].stok << " |\n";
    }
    cout << "+-----+----------------------------+-------------------------+----------------------+------------+----------------+\n";
}

void tampilkanUserBooking(Booking bookings[], int TotalPesanan, const string &username) {
    cout << BLUE << "\n=====" << CYAN << " Tiket yang Dipesan " << BLUE << "=====\n" << RESET;
    cout << "+-----+----------------------------+-------------------------+----------------------+------------+--------+\n";
    cout << "| No  | Destinasi                  | Lokasi                  | Tanggal              |   Harga    | Jumlah |\n";
    cout << "+-----+----------------------------+-------------------------+----------------------+------------+--------+\n";
    int nomor = 1;
    for (int i = 0; i < TotalPesanan; i++) {
        if (bookings[i].username == username) {
            cout << "| " << setw(3) << right << nomor++ << " "
                << "| " << setw(27) << left << bookings[i].destinasi
                << "| " << setw(24) << left << bookings[i].lokasi
                << "| " << setw(21) << left << bookings[i].tanggal
                << "| " << setw(10) << right << bookings[i].harga
                << " | " << setw(6) << right << bookings[i].jumlah << " |\n";
        }
    }
    cout << "+-----+----------------------------+-------------------------+----------------------+------------+--------+\n";
    if (nomor == 1) {
        cout << RED << "Belum ada pesanan untuk akun ini.\n" << RESET;
    }
}

void tambahStok(Destinasi *d, int jumlah) {
    d->stok += jumlah;
}

void cetakBooking(Booking *b) {
    cout << BLUE << "\n=====" << CYAN << " Detail Tiket Booking " << BLUE << "=====\n" << RESET;
    cout << "Destinasi: " << b->destinasi << endl;
    cout << "Lokasi: " << b->lokasi << endl;
    cout << "Tanggal: " << b->tanggal << endl;
    cout << "Harga: Rp" << b->harga << endl;
    cout << "Jumlah Tiket: " << b->jumlah << endl;
    cout << BLUE << "================================" << RESET << endl;
}

void ListDestinasi(Destinasi wisata[], int TotalDestinasi) {
    for (int i = 0; i < TotalDestinasi; i++) {
        cout << i + 1 << ". " << wisata[i].nama << "\n";
    }
}

// Bubble Sort Nama, Destinasi (Descending Z - A)
void bubbleSortNamaDesc(Destinasi arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j].nama < arr[j + 1].nama) { // Z ke A
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Bubble Sort Angka, Harga (Ascending 0 - 9)
void bubbleSortHargaAsc(Destinasi arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (stoi(arr[j].harga) > stoi(arr[j+1].harga)) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

// Bubble Sort Angka, Stok Tiket (Ascending 0 - 9)
void bubbleSortStokAsc(Destinasi arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j].stok > arr[j + 1].stok) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void tampilkanStatistikBooking(Destinasi wisata[], int TotalDestinasi, Booking bookings[], int TotalPesanan) {
    if (TotalPesanan == 0) {
        cout << RED << "\nBelum ada data pemesanan.\n" << RESET;
        return;
    }
    // Hitung data
    int totalTiketTerjual = 0;
    for (int i = 0; i < TotalPesanan; i++) {
        totalTiketTerjual += bookings[i].jumlah;
    }

    int totalTiketTersedia = 0;
    for (int i = 0; i < TotalDestinasi; i++) {
        totalTiketTersedia += wisata[i].stok;
    }

    int totalTransaksi = TotalPesanan;

    // Fungsi mini untuk membuat bar
    auto bar = [](int jumlah, int scale = 1) {
        string b = "";
        for (int i = 0; i < jumlah / scale; i++) b += "[]";
        return b;
    };

    // Tampilkan UI Statistik
    cout << BLUE << "\n===================" << CYAN << " STATISTIK PEMESANAN (BAR CHART) " << BLUE << "===================\n" << RESET;
    cout << "Total Transaksi     : " << totalTransaksi << "\n";
    cout << GREEN << "  " << bar(totalTransaksi) << RESET << "\n";

    cout << "\nTotal Tiket Terjual : " << totalTiketTerjual << "\n";
    cout << GREEN << "  " << bar(totalTiketTerjual) << RESET << "\n";

    cout << "\nTiket Tersedia      : " << totalTiketTersedia << "\n";
    cout << YELLOW << "  " << bar(totalTiketTersedia / 8) << RESET << "\n";

    cout << BLUE << "=======================================================================\n" << RESET;
}

void menuSortirDestinasi(Destinasi wisata[], int TotalDestinasi) {
    cout << BLUE << "\nData Yang Ingin Disortir:\n" << RESET;
    cout << "1. Nama Destinasi (Z - A)\n";
    cout << "2. Harga Tiket (0 - 9)\n";
    cout << "3. Tiket Tersedia (0 - 9)\n";
    cout << YELLOW << "Pilih Data: " << RESET;
    int pildata;
    cin >> pildata;
    cin.ignore();

    switch (pildata) {
        case 1:
            bubbleSortNamaDesc(wisata, TotalDestinasi);
            cout << GREEN << "Berhasil sortir berdasarkan Nama (Z - A)\n" << RESET;
            tampilkan(wisata, TotalDestinasi);
            break;
        case 2:
            bubbleSortHargaAsc(wisata, TotalDestinasi);
            cout << GREEN << "Berhasil sortir berdasarkan Harga (0 - 9)\n" << RESET;
            tampilkan(wisata, TotalDestinasi);
            break;
        case 3:
            bubbleSortStokAsc(wisata, TotalDestinasi);
            cout << GREEN << "Berhasil sortir berdasarkan Tiket Tersedia (0 - 9)\n" << RESET;
            tampilkan(wisata, TotalDestinasi);
            break;
        default:
            cout << RED << "Opsi sorting tidak valid.\n" << RESET;
            break;
    }
}

void MenuAdmin(Destinasi wisata[], int &TotalDestinasi, Booking bookings[], int &TotalPesanan) {
    int optAdmin;
    while (true) {
        cout << BLUE << "\n==========" <<  CYAN << " Menu Admin " << BLUE << "==========\n" << RESET;
        cout << "1. Lihat Destinasi\n";
        cout << "2. Tambah Destinasi\n";
        cout << "3. Edit Destinasi\n";
        cout << "4. Hapus Destinasi\n";
        cout << "5. Sortir Data\n";
        cout << "6. Cari Data Pemesanan\n";
        cout << "7. Statistik Pemesanan\n";
        cout << "8. Logout\n";
        cout << BLUE << "================================\n" << RESET;
        optAdmin = validasiInput(YELLOW + "Pilih opsi: " + RESET, 1, 8);


        switch(optAdmin) {
            case 1:
                tampilkan(wisata, TotalDestinasi);
                break;
            case 2:
                if (TotalDestinasi < MAX_WISATA) {
                    cout << BLUE << "\n===" << CYAN << " Tambah Destinasi " << BLUE << "===\n" << RESET;
                    string nama, lokasi, tanggal, harga;
                    int stok;

                    cout << "Destinasi: ";
                    getline(cin, nama);
                    if (nama.empty()) {
                        cout << RED << "Nama destinasi tidak boleh kosong.\n" << RESET;
                        break;
                    }

                    cout << "Lokasi: ";
                    getline(cin, lokasi);
                    if (lokasi.empty()) {
                        cout << RED << "Lokasi tidak boleh kosong.\n" << RESET;
                        break;
                    }

                    cout << "Tanggal (format: YYYY-MM-DD): ";
                    getline(cin, tanggal);

                    if (tanggal.length() != 10 || tanggal[4] != '-' || tanggal[7] != '-') {
                        cout << RED << "Format tanggal salah. Gunakan format: YYYY-MM-DD.\n" << RESET;
                        break;
                    }

                    int tahun = stoi(tanggal.substr(0, 4));
                    if (tahun < 2025 || tahun > 2100) {
                        cout << RED << "Tahun tidak boleh kurang dari 2025 atau lebih dari 2100.\n" << RESET;
                        break;
                    }

                    int bulan = stoi(tanggal.substr(5, 2));
                    int hari = stoi(tanggal.substr(8, 2));
                    if (bulan < 1 || bulan > 12) {
                        cout << RED << "Bulan harus antara 01 dan 12.\n" << RESET;
                        break;
                    }
                    if (hari < 1 || hari > 31) {
                        cout << RED << "Hari harus antara 01 dan 31.\n" << RESET;
                        break;
                    }
                    
                    cout << "Harga Tiket: ";
                    getline(cin, harga);
                    if (harga.empty()) {
                        cout << RED << "Harga tiket tidak boleh kosong.\n" << RESET;
                        break;
                    }

                    stok = validasiaAngka("Stok Tiket: ");
                    if (stok < 0) {
                        cout << RED << "Stok tiket tidak boleh negatif.\n" << RESET;
                        break;
                    }

                    // Tambahkan dan urutkan berdasarkan tanggal (ascending)
                    Destinasi baru = {nama, lokasi, tanggal, harga, stok};
                    int pos = TotalDestinasi;
                    for (int i = 0; i < TotalDestinasi; i++) {
                        if (tanggal < wisata[i].tanggal) {
                            pos = i;
                            break;
                        }
                    }
                    for (int i = TotalDestinasi; i > pos; i--) {
                        wisata[i] = wisata[i - 1];
                    }
                    wisata[pos] = baru;
                    TotalDestinasi++;

                    cout << GREEN << "\nDestinasi berhasil ditambahkan dan diurutkan berdasarkan tanggal.\n" << RESET;
                } else {
                    cout << RED << "\nData destinasi penuh.\n" << RESET;
                }
                break;
            case 3: {
                cout << BLUE << "\nDaftar Destinasi:\n" << RESET;
                ListDestinasi(wisata, TotalDestinasi);
                cout << YELLOW << "Nomor destinasi yang ingin diedit: " << RESET;
                int nomor;
                cin >> nomor;
                cin.ignore();
                if (nomor >= 1 && nomor <= TotalDestinasi) {
                    int indeks = nomor - 1;
                    cout << BLUE << "\nBagian yang ingin diedit:\n" << RESET;
                    cout << "1. Destinasi\n";
                    cout << "2. Lokasi\n";
                    cout << "3. Tanggal\n";
                    cout << "4. Harga Tiket\n";
                    cout << "5. Stok Tiket\n";
                    cout << YELLOW << "Pilih opsi: " << RESET;
                    int editOpt;
                    cin >> editOpt;
                    cin.ignore();
                    if (editOpt >= 1 && editOpt <= 5) {
                        cout << "Masukkan data baru: ";
                        if (editOpt == 5) {
                            cin >> wisata[indeks].stok;
                            cin.ignore();
                        } else {
                            string dataBaru;
                            getline(cin, dataBaru);
                            if (editOpt == 1) wisata[indeks].nama = dataBaru;
                            else if (editOpt == 2) wisata[indeks].lokasi = dataBaru;
                            else if (editOpt == 3) wisata[indeks].tanggal = dataBaru;
                            else if (editOpt == 4) wisata[indeks].harga = dataBaru;
                        }
                        cout << GREEN << "Data berhasil diupdate.\n" << RESET;
                    } else {
                        cout << RED << "Opsi tidak valid.\n" << RESET;
                    }
                } else {
                    cout << RED << "Nomor tidak valid.\n" << RESET;
                }
                break;
            }
            case 4: {
                cout << BLUE << "\nDaftar Destinasi:\n" << RESET;
                ListDestinasi(wisata, TotalDestinasi);
                cout << YELLOW << "Nomor destinasi yang ingin dihapus: " << RESET;
                int nomor;
                cin >> nomor;
                cin.ignore();
                if (nomor >= 1 && nomor <= TotalDestinasi) {
                    for (int i = nomor - 1; i < TotalDestinasi - 1; i++) {
                        wisata[i] = wisata[i + 1];
                    }
                    TotalDestinasi--;
                    cout << GREEN << "\nDestinasi berhasil dihapus.\n" << RESET;
                } else {
                    cout << RED << "Nomor tidak valid.\n" << RESET;
                }
                break;
            }
            case 5: {
                menuSortirDestinasi(wisata, TotalDestinasi);
                break;
            }
            case 6: {
                if (TotalDestinasi == 0) {
                    cout << RED << "Belum ada data destinasi wisata.\n" << RESET;
                    break;
                }

                if (TotalPesanan == 0) {
                    cout << RED <<"Belum ada data pemesanan.\n" << RESET;
                    break;
                }

                cout << BLUE << "\n===" << CYAN << " Daftar Destinasi " << BLUE << "===\n" << RESET;
                for (int i = 0; i < TotalDestinasi; ++i) {
                    cout << i + 1 << ". " << wisata[i].nama << '\n';
                }

                cout << "Pilih nomor destinasi: ";
                int pilihan;
                if (!(cin >> pilihan) || pilihan < 1 || pilihan > TotalDestinasi) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << RED << "Input tidak valid.\n" << RESET;
                    break;
                }
                cin.ignore();

                string dicari = wisata[pilihan - 1].nama;
                bool ditemukan = false;
                // Linear Search
                for (int i = 0; i < TotalPesanan; ++i) {
                    if (bookings[i].destinasi == dicari) {
                        cetakBooking(&bookings[i]);
                        ditemukan = true;
                    }
                }

                if (!ditemukan) {
                    cout << RED << "Tidak ada pemesanan untuk destinasi tersebut.\n" << RESET;
                }
                break;
            }
            case 7:
                tampilkanStatistikBooking(wisata, TotalDestinasi, bookings, TotalPesanan);
                break;
            case 8:
                return;
            default:
                cout << RED << "Opsi tidak valid.\n" << RESET;
        }
    }
}


void MenuPengguna(Destinasi wisata[], int &TotalDestinasi, Booking bookings[], int &TotalPesanan, const string &username) {
    int opsiuser;
    while (true) {
        cout << BLUE << "\n==========" << CYAN << " Menu Pengguna " << BLUE << "==========\n" << RESET;
        cout << "1. Lihat Destinasi\n";
        cout << "2. Pesan Tiket Wisata\n";
        cout << "3. Lihat Tiket yang Dipesan\n";
        cout << "4. Batalkan Tiket Pesanan\n";
        cout << "5. Sortir Data\n";
        cout << "6. Logout\n";
        cout << BLUE << "=====================================\n" << RESET;
        opsiuser = validasiInput(YELLOW + "Pilih opsi: " + RESET, 1, 6);

        switch(opsiuser) {
            case 1:
                tampilkan(wisata, TotalDestinasi);
                break;
            case 2: {
                tampilkan(wisata, TotalDestinasi);
                cout << YELLOW << "Nomor destinasi yang ingin dipesan: " << RESET;
                int nomor;
                cin >> nomor;
                cin.ignore();
                if (nomor >= 1 && nomor <= TotalDestinasi) {
                    Destinasi *dipilih = &wisata[nomor - 1];
                    int jumlah = validasiaAngka(YELLOW + string("Jumlah tiket yang ingin dipesan: ") + RESET);
                    if (jumlah <= 0) {
                        cout << RED << "Jumlah tiket harus lebih dari 0.\n" << RESET;
                        break;
                    }
                    if (jumlah > dipilih->stok) {
                        cout << RED <<"Stok tiket tidak mencukupi.\n" << RESET;
                        break;
                    }
                    if (TotalPesanan >= MAX_BOOKING) {
                        cout << RED << "Kapasitas booking penuh.\n" << RESET;
                        break;
                    }
                    bookings[TotalPesanan] = {dipilih->nama, dipilih->lokasi, dipilih->tanggal, dipilih->harga, jumlah, username};
                    TotalPesanan++;
                    dipilih->stok -= jumlah;
                    cout << GREEN <<"Tiket berhasil dipesan. SELAMAT LIBURAN!\n" << RESET;
                } else {
                    cout << RED <<"Nomor tidak valid.\n" << RESET;
                }
                break;
            }
            case 3:
                tampilkanUserBooking(bookings, TotalPesanan, username);
                break;
            case 4: {
                int idxUser[MAX_BOOKING], count = 0;
                cout << BLUE << "\nDaftar Tiket yang Dipesan:\n" << RESET;
                cout << "+-----+----------------------------+-------------------------+----------------------+------------+--------+\n";
                cout << "| No  | Destinasi                  | Lokasi                  | Tanggal              |   Harga    | Jumlah |\n";
                cout << "+-----+----------------------------+-------------------------+----------------------+------------+--------+\n";
                for (int i = 0; i < TotalPesanan; i++) {
                    if (bookings[i].username == username) {
                        idxUser[count] = i;
                        cout << "| " << setw(3) << right << count + 1 << " "
                            << "| " << setw(27) << left << bookings[i].destinasi
                            << "| " << setw(24) << left << bookings[i].lokasi
                            << "| " << setw(21) << left << bookings[i].tanggal
                            << "| " << setw(10) << right << bookings[i].harga
                            << " | " << setw(6) << right << bookings[i].jumlah << " |\n";
                        count++;
                    }
                }
                cout << "+-----+----------------------------+-------------------------+----------------------+------------+--------+\n";
                if (count == 0) {
                    cout << RED << "Tidak ada pesanan untuk dibatalkan.\n" << RESET;
                    break;
                }
                cout << YELLOW << "Nomor pesanan yang ingin dibatalkan: ";
                int nomor;
                cin >> nomor;
                cin.ignore();
                if (nomor >= 1 && nomor <= count) {
                    int indeks = idxUser[nomor - 1];
                    // Kembalikan stok
                    for (int j = 0; j < TotalDestinasi; j++) {
                        if (wisata[j].nama == bookings[indeks].destinasi) {
                            tambahStok(&wisata[j], bookings[indeks].jumlah);
                            break;
                        }
                    }
                    cetakBooking(&bookings[indeks]);
                    for (int i = indeks; i < TotalPesanan - 1; i++) {
                        bookings[i] = bookings[i + 1];
                    }
                    TotalPesanan--;
                    cout << GREEN <<"Pesanan berhasil dibatalkan.\n";
                } else {
                    cout << RED <<"Nomor tidak valid.\n";
                }
                break;
            }
            case 5: {
                menuSortirDestinasi(wisata, TotalDestinasi);
                break;
            }            
            case 6:
                return;
            default:
                cout << RED << "Opsi tidak valid.\n" << RESET;
        }
    }
}

void RegisterAkun(Akun akun[], int &Jumlahakun) {
    if (Jumlahakun < MAX_AKUN) {
        cout << BLUE << "\n==========" <<  CYAN << " Halo! Silahkan Daftar " << BLUE << "==========\n" << RESET;
        cout << MAGENTA << "Syarat Username : Maksimal 15 karakter\n" << RESET;
        cout << MAGENTA << "Syarat Password : Minimal 5 karakter\n" << RESET;

        string username, password;
        // Validasi username
        while (true) {
            cout << "\nMasukkan Username: ";
            getline(cin, username);
            if (username.empty()) {
                cout << RED << "Username tidak boleh kosong.\n" << RESET;
            } else if (username.length() > 15) {
                cout << RED << "Username maksimal 15 karakter.\n" << RESET;
            } else {
                bool duplikat = false;
                for (int i = 0; i < Jumlahakun; i++) {
                    if (akun[i].nama == username) {
                        duplikat = true;
                        break;
                    }
                }
                if (duplikat) {
                    cout << RED << "Username sudah digunakan. Silakan pilih username lain.\n" << RESET;
                } else {
                    break;
                }
            }
        }
        // Validasi password
        while (true) {
            cout << "Masukkan Password: ";
            getline(cin, password);
            if (password.length() < 5) {
                cout << RED << "Password minimal 5 karakter.\n" << RESET;
            } else {
                break;
            }
        }
        akun[Jumlahakun].nama = username;
        akun[Jumlahakun].password = password;
        akun[Jumlahakun].isAdmin = false;
        Jumlahakun++;
        cout << GREEN << "Register berhasil! Silakan login kembali." << RESET << endl;
    } else {
        cout << RED << "Kapasitas akun penuh." << RESET << endl;
    }
}

void mainMenu(Destinasi wisata[], int &TotalDestinasi, Booking bookings[], int &TotalPesanan, Akun akun[], int &Jumlahakun) {
    bool isRunning = true;
    while (isRunning) {
        logoWisaPan();
        cout << BLUE << "============================================\n" << RESET;
        cout << "         Selamat Datang di" << CYAN << " WisaPan!\n" << RESET;
        cout << "       Wisata Alam di Ujung Kalimantan\n";
        cout << BLUE << "============================================\n" << RESET;
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Exit\n";
        cout << BLUE << "============================================\n" << RESET;
       int opsi = validasiaAngka(YELLOW + string("Pilih opsi: ") + RESET);

        switch(opsi) {
            case 1: {
                string user, pass;
                bool success = Login(0, 3, akun, Jumlahakun, user, pass);
                if (!success) {
                    cout << RED << "Anda gagal login 3 kali. Program berhenti.\n" << RESET;
                    goodbye();
                    return;
                }
                bool isAdmin = false;
                for (int i = 0; i < Jumlahakun; i++) {
                    if (user == akun[i].nama && pass == akun[i].password) {
                        isAdmin = akun[i].isAdmin; // cek status admin
                        break;
                    }
                }
                
                if (isAdmin)
                    MenuAdmin(wisata, TotalDestinasi, bookings, TotalPesanan);
                else
                    MenuPengguna(wisata, TotalDestinasi, bookings, TotalPesanan, user);
                break;
            }
            case 2:
                RegisterAkun(akun, Jumlahakun);
                break;
            case 3:
                goodbye();
                isRunning = false;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    }
}

int main() {
    Destinasi wisata[MAX_WISATA] = {
        {"Pantai Lamaru", "Balikpapan Timur", "2025-06-15", "15000", 50},
        {"Magrove Margomulyo", "Margomulyo", "2025-06-20", "10000", 30},
        {"Pantai Kemala", "Balikpapan Kota", "2025-06-28", "20000", 25},
        {"Kebun Raya BPP", "Kilometer 15", "2025-07-04", "5000", 40},
        {"Pantai Melwai", "Balikpapan Kota", "2025-07-10", "10000", 20},
        {"Bukit Alpha", "Gunung Bahagia", "2025-07-22", "10000", 100},
    };
    int TotalDestinasi = 6;

    Booking bookings[MAX_BOOKING] = {
        {"Pantai Lamaru", "Balikpapan Timur", "2025-06-15", "15000", 2, "wawan"},
        {"Pantai Kemala", "Balikpapan Kota", "2025-06-28", "20000", 3, "paras"},
        {"Bukit Alpha", "Gunung Bahagia", "2025-07-22", "10000", 1, "yusup"}
    };
    int TotalPesanan = 3;

    Akun akun[MAX_AKUN] = {
        {"wawan", "091", true},
        {"paras", "092", true},
        {"yusup", "093", true},
        {"rafii", "095", true}
    };
    int Jumlahakun = 4;

    mainMenu(wisata, TotalDestinasi, bookings, TotalPesanan, akun, Jumlahakun);
    return 0;
}