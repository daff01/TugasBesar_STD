#include <iostream>
#include "perpustakaan.h"

using namespace std;

int main() {
    ListBuku L;
    createListBuku(L);

    int pilihan;

    do {
        cout << "\n=== MENU PERPUSTAKAAN DIGITAL ===\n";
        cout << "1. Tambah Buku dan stok\n";
        cout << "2. Tambah Stok Buku\n";
        cout << "3. Hapus Buku\n";
        cout << "4. Hapus Stok Buku\n";
        cout << "5. Cari Buku\n";
        cout << "6. Tampilkan Semua Buku\n";
        cout << "7. Lihat Stok Terbanyak\n";
        cout << "8. Lihat Stok Tersedikit\n";
        cout << "0. Keluar\n";
        cout << "-----------------------------\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            int id, tahun, jumlahStok;
            char judul[100], pengarang[100], kategori[50];

            cout << "ID Buku      : ";
            cin >> id;
            cin.ignore();

            if (searchBuku(L, id) != NULL) {
                cout << "-----------------------------\n";
                cout << "ERROR: ID Buku sudah terdaftar.\n";
                continue;
            }

            cout << "Judul        : ";
            cin.getline(judul, 100);

            cout << "Pengarang    : ";
            cin.getline(pengarang, 100);

            cout << "Tahun Terbit : ";
            cin >> tahun;
            cin.ignore();

            cout << "Kategori     : ";
            cin.getline(kategori, 50);

            cout << "Jumlah Stok  : ";
            cin >> jumlahStok;

            adrBuku b = createElemenBuku(id, judul, pengarang, tahun, kategori);
            addBuku(L, b);

            for (int i = 1; i <= jumlahStok; i++) {
                adrStok s = createElemenStok(i);
                addStok(b, s);
            }
            cout << "-----------------------------\n";
            cout << "SUCCESS: Buku dan stok berhasil ditambahkan.\n";
        }
        else if (pilihan == 2) {
            int idBuku, jumlahStok;
            cout << "ID Buku      : ";
            cin >> idBuku;

            adrBuku b = searchBuku(L, idBuku);
            if (b == NULL) {
                cout << "-----------------------------\n";
                cout << "ERROR: Buku tidak ditemukan.\n";
                continue;
            }
            cout << "Jumlah Stok Tambahan : ";
            cin >> jumlahStok;

            int startId = 1;
            adrStok q = b->firstStok;
            while (q != NULL) {
                startId++;
                q = q->next;
            }

            for (int i = 0; i < jumlahStok; i++) {
                adrStok s = createElemenStok(startId++);
                addStok(b, s);
            }
            cout << "-----------------------------\n";
            cout << "SUCCESS: Stok berhasil ditambahkan.\n";
        }
        else if (pilihan == 3) {
            int idBuku;
            cout << "ID Buku: ";
            cin >> idBuku;

            deleteBuku(L, idBuku);
            cout << "-----------------------------\n";
            cout << "SUCCESS: Buku berhasil dihapus.\n";
        }
        else if (pilihan == 4) {
            int idBuku, jumlahHapus;

            cout << "ID Buku : ";
            cin >> idBuku;

            adrBuku b = searchBuku(L, idBuku);
            if (b == NULL) {
                cout << "-----------------------------\n";
                cout << "ERROR: Buku tidak ditemukan.\n";
                continue;
            }

            cout << "Jumlah stok yang akan dihapus : ";
            cin >> jumlahHapus;

            int stokSekarang = countStok(b);
            if (jumlahHapus > stokSekarang) {
                cout << "-----------------------------\n";
                cout << "PERINGATAN: Stok tidak mencukupi menghapus semua stok.\n";
            } else if (jumlahHapus <= stokSekarang){
                deleteStokJumlah(b, jumlahHapus);
                cout << "-----------------------------\n";
                cout << "SUCCESS: Stok berhasil dikurangi.\n";
            }
        }
        else if (pilihan == 5) {
            int sub;
            cout << "\n=== CARI BUKU ===\n";
            cout << "1. Berdasarkan ID\n";
            cout << "2. Berdasarkan Judul\n";
            cout << "3. Berdasarkan Pengarang\n";
            cout << "4. Berdasarkan Tahun Terbit\n";
            cout << "5. Berdasarkan Kategori\n";
            cout << "Pilih: ";
            cin >> sub;
            cin.ignore();

            if (sub == 1) {
                int id;
                cout << "ID Buku: ";
                cin >> id;
                adrBuku b = searchBuku(L, id);
                cout << "-----------------------------\n";
                if (b == NULL) {
                    cout << "ID Buku tidak ditemukan.\n";
                } else {
                    cout << "ID Buku     : " << b->info.idBuku << endl;
                    cout << "Judul       : " << b->info.judul << endl;
                    cout << "Pengarang   : " << b->info.pengarang << endl;
                    cout << "Tahun Terbit: " << b->info.tahunTerbit << endl;
                    cout << "Kategori    : " << b->info.kategori << endl;
                    cout << "Jumlah Stok : " << countStok(b) << endl;
                    cout << "-----------------------------\n";
                        }
            } else if (sub == 2) {
                char key[100];
                cout << "Judul (kata kunci): ";
                cin.getline(key, 100);
                searchBukuByJudul(L, key);
            } else if (sub == 3) {
                char key[100];
                cout << "Pengarang: ";
                cin.getline(key, 100);
                searchBukuByPengarang(L, key);
            } else if (sub == 4) {
                int tahun;
                cout << "Tahun Terbit: ";
                cin >> tahun;
                    searchBukuByTahun(L, tahun);
            } else if (sub == 5) {
                char key[50];
                cout << "Kategori/Genre: ";
                cin.getline(key, 50);
                searchBukuByKategori(L, key);
            }

        }
        else if (pilihan == 6) {
            adrBuku p = L.first;
            cout << "-----------------------------\n";

            while (p != NULL) {
                cout << "ID Buku     : " << p->info.idBuku << endl;
                cout << "Judul       : " << p->info.judul << endl;
                cout << "Pengarang   : " << p->info.pengarang << endl;
                cout << "Tahun Terbit: " << p->info.tahunTerbit << endl;
                cout << "Kategori    : " << p->info.kategori << endl;
                cout << "Jumlah Stok : " << countStok(p) << endl;
                cout << "-----------------------------\n";
                p = p->next;
            }
        }
        else if (pilihan == 7) {
            displayStokTerbanyak(L);
        }
        else if (pilihan == 8) {
            displayStokTersedikit(L);
        }


    } while (pilihan != 0);

    return 0;
}
