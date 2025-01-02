#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

struct Obat {
    string nama;
    double harga;
    int stok;
};

class Apotek {
private:
    vector<Obat> daftarObat;

public:
    void tambahObat(const string &nama, double harga, int stok) {
        daftarObat.push_back({nama, harga, stok});
    }

    void tampilkanDaftarObat() {
        cout << "\nDaftar Obat:\n";
        cout << std::left << std::setw(5) << "No"
             << std::setw(20) << "Nama Obat"
             << std::setw(10) << "Harga"
             << "Stok" << endl;
        cout << std::string(40, '-') << endl;

        for (size_t i = 0; i < daftarObat.size(); ++i) {
            cout << std::left << std::setw(5) << i + 1
                 << std::setw(20) << daftarObat[i].nama
                 << std::setw(10) << daftarObat[i].harga
                 << daftarObat[i].stok << endl;
        }
    }

    bool pesanObat(int indeks, int jumlah, double &totalPembayaran) {
        if (indeks < 1 || indeks > daftarObat.size()) {
            cout << "Obat tidak ditemukan.\n";
            return false;
        }

        Obat &obat = daftarObat[indeks - 1];

        if (jumlah > obat.stok) {
            cout << "Stok tidak mencukupi.\n";
            return false;
        }

        obat.stok -= jumlah;
        totalPembayaran = jumlah * obat.harga;
        cout << "Pesanan berhasil. Total harga: Rp " << totalPembayaran << "\n";
        return true;
    }

    bool bayar(double totalPembayaran) {
        double bayar;
        do {
            cout << "\nMasukkan jumlah uang yang dibayar: Rp ";
            cin >> bayar;

            if (bayar < totalPembayaran) {
                cout << "Uang tidak cukup. Total yang harus dibayar adalah Rp " << totalPembayaran << ".\n";
                cout << "Silakan coba lagi.\n";
            }
        } while (bayar < totalPembayaran);

        double kembalian = bayar - totalPembayaran;
        cout << "Pembayaran berhasil! Kembalian: Rp " << kembalian << ".\n";
        return true;
    }
};

int main() {
    Apotek apotek;
    apotek.tambahObat("Paracetamol", 5000, 50);
    apotek.tambahObat("Amoxicillin", 10000, 30);
    apotek.tambahObat("Vitamin C", 15000, 20);
    apotek.tambahObat("Diabetasol", 3500, 25);

    int pilihan;
    double totalPembayaran = 0;
    do {
        cout << "\n=== Sistem Pemesanan Obat ===\n";
        cout << "1. Tampilkan daftar obat\n";
        cout << "2. Pesan obat\n";
        cout << "3. Keluar\n";
        cout << "Pilih menu: \n"; 
        cout << "> "; 
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            apotek.tampilkanDaftarObat();
            break;
        case 2: {
            int indeks, jumlah;
            cout << "\nMasukkan nomor obat yang ingin dipesan: ";
            cin >> indeks;
            cout << "Masukkan jumlah: ";
            cin >> jumlah;
            if (apotek.pesanObat(indeks, jumlah, totalPembayaran)) {
                apotek.bayar(totalPembayaran);
            }
            break;
        }
        case 3:
            cout << "Terima kasih telah menggunakan sistem kami.\n";
            break;
        default:
            cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 3);

    return 0;
}
