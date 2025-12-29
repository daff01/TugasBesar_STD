#include "perpustakaan.h"

void createListBuku(ListBuku &L) {
    L.first = nullptr;
    L.last  = nullptr;
}

bool isEmptyBuku(ListBuku L) {
    return (L.first == nullptr);
}

bool isEmptyStok(adrBuku p) {
    return (p->firstStok == nullptr);
}

adrBuku createElemenBuku(int idBuku, const char judul[], const char pengarang[], int tahunTerbit, const char kategori[]) {
    adrBuku p = new elemenBuku;

    p->info.idBuku = idBuku;
    strcpy(p->info.judul, judul);
    strcpy(p->info.pengarang, pengarang);
    p->info.tahunTerbit = tahunTerbit;
    strcpy(p->info.kategori, kategori);

    p->next = nullptr;
    p->prev = nullptr;
    p->firstStok = nullptr;

    return p;
}

adrStok createElemenStok(int idEksemplar) {
    adrStok q = new elemenStok;
    q->idEksemplar = idEksemplar;
    q->next = nullptr;
    return q;
}

void addBuku(ListBuku &L, adrBuku p) {
    if (isEmptyBuku(L)) {
        L.first = p;
        L.last  = p;
    } else {
        p->prev = L.last;
        L.last->next = p;
        L.last = p;
    }
}

void addStok(adrBuku &p, adrStok q) {
    if (isEmptyStok(p)) {
        p->firstStok = q;
    } else {
        q->next = p->firstStok;
        p->firstStok = q;
    }
}

adrBuku searchBuku(ListBuku L, int idBuku) {
    adrBuku p = L.first;
    while (p != nullptr) {
        if (p->info.idBuku == idBuku) {
            return p;
        }
        p = p->next;
    }
    return nullptr;
}

void deleteStok(adrBuku &p, int idEksemplar) {
    if (isEmptyStok(p)) return;

    adrStok q = p->firstStok;
    adrStok prev = nullptr;

    while (q != nullptr && q->idEksemplar != idEksemplar) {
        prev = q;
        q = q->next;
    }

    if (q == nullptr) return;

    if (prev == nullptr) {
        p->firstStok = q->next;
    } else {
        prev->next = q->next;
    }

    delete q;
}

void deleteBuku(ListBuku &L, int idBuku) {
    adrBuku p = searchBuku(L, idBuku);
    if (p == nullptr) return;

    adrStok q;
    while (p->firstStok != nullptr) {
        q = p->firstStok;
        p->firstStok = q->next;
        delete q;
    }

    if (p == L.first && p == L.last) {
        L.first = nullptr;
        L.last  = nullptr;
    } else if (p == L.first) {
        L.first = p->next;
        L.first->prev = nullptr;
    } else if (p == L.last) {
        L.last = p->prev;
        L.last->next = nullptr;
    } else {
        p->prev->next = p->next;
        p->next->prev = p->prev;
    }

    delete p;
}

void deleteStokJumlah(adrBuku &p, int jumlah) {
    if (p == NULL || p->firstStok == NULL) {
        return;
    }

    adrStok q;
    int count = 0;

    while (p->firstStok != NULL && count < jumlah) {
        q = p->firstStok;
        p->firstStok = q->next;
        delete q;
        count++;
    }
}

void displayStok(adrBuku p) {
    if (p == nullptr) {
        cout << "Buku tidak ditemukan." << endl;
        return;
    }
    if (p->firstStok == nullptr) {
        cout << "      Stok kosong." << endl;
        return;
    }
    adrStok q = p->firstStok;
    while (q != nullptr) {
        cout << "      ID Eksemplar: " << q->idEksemplar << endl;
        q = q->next;
    }
}


void displayListBuku(ListBuku L) {
    adrBuku p = L.first;
    while (p != nullptr) {
        cout << "ID Buku     : " << p->info.idBuku << endl;
        cout << "Judul       : " << p->info.judul << endl;
        cout << "Pengarang   : " << p->info.pengarang << endl;
        cout << "Tahun Terbit: " << p->info.tahunTerbit << endl;
        cout << "Kategori    : " << p->info.kategori << endl;
        cout << "Stok:" << endl;

        displayStok(p);

        cout << "-----------------------------" << endl;
        p = p->next;
    }
}

int countStok(adrBuku p) {
    int total = 0;
    adrStok q = p->firstStok;
    while (q != nullptr) {
        total++;
        q = q->next;
    }
    return total;
}

void searchBukuByJudul(ListBuku L, const char keyword[]) {
    adrBuku p = L.first;
    int total = 0;

    while (p != nullptr) {
        if (strstr(p->info.judul, keyword) != nullptr) {
            cout << "ID Buku     : " << p->info.idBuku << endl;
            cout << "Judul       : " << p->info.judul << endl;
            cout << "Pengarang   : " << p->info.pengarang << endl;
            cout << "Tahun Terbit: " << p->info.tahunTerbit << endl;
            cout << "Kategori    : " << p->info.kategori << endl;
            cout << "Jumlah Stok : " << countStok(p) << endl;
            cout << "-----------------------------" << endl;
            total++;
        }
        p = p->next;
    }
    cout << "Total buku ditemukan: " << total << endl;
}

void searchBukuByPengarang(ListBuku L, const char keyword[]) {
    adrBuku p = L.first;
    int total = 0;

    while (p != nullptr) {
        if (strstr(p->info.pengarang, keyword) != nullptr) {
            cout << "ID Buku     : " << p->info.idBuku << endl;
            cout << "Judul       : " << p->info.judul << endl;
            cout << "Pengarang   : " << p->info.pengarang << endl;
            cout << "Tahun Terbit: " << p->info.tahunTerbit << endl;
            cout << "Kategori    : " << p->info.kategori << endl;
            cout << "Jumlah Stok : " << countStok(p) << endl;
            cout << "-----------------------------" << endl;
            total++;
        }
        p = p->next;
    }
    cout << "Total buku ditemukan: " << total << endl;
}

void searchBukuByTahun(ListBuku L, int tahun) {
    adrBuku p = L.first;
    int total = 0;

    while (p != nullptr) {
        if (p->info.tahunTerbit == tahun) {
            cout << "ID Buku     : " << p->info.idBuku << endl;
            cout << "Judul       : " << p->info.judul << endl;
            cout << "Pengarang   : " << p->info.pengarang << endl;
            cout << "Kategori    : " << p->info.kategori << endl;
            cout << "Jumlah Stok : " << countStok(p) << endl;
            cout << "-----------------------------" << endl;
            total++;
        }
        p = p->next;
    }
    cout << "Total buku ditemukan: " << total << endl;
}

void searchBukuByKategori(ListBuku L, const char keyword[]) {
    adrBuku p = L.first;
    int total = 0;

    while (p != nullptr) {
        if (strstr(p->info.kategori, keyword) != nullptr) {
            cout << "ID Buku     : " << p->info.idBuku << endl;
            cout << "Judul       : " << p->info.judul << endl;
            cout << "Pengarang   : " << p->info.pengarang << endl;
            cout << "Tahun Terbit: " << p->info.tahunTerbit << endl;
            cout << "Kategori    : " << p->info.kategori << endl;
            cout << "Jumlah Stok : " << countStok(p) << endl;
            cout << "-----------------------------" << endl;
            total++;
        }
        p = p->next;
    }

    cout << "Total buku ditemukan: " << total << endl;
}

void displayStokTerbanyak(ListBuku L) {
    if (isEmptyBuku(L)) {
        cout << "Data buku kosong.\n";
        return;
    }

    adrBuku p = L.first;
    int maxStok = -1;

    while (p != nullptr) {
        int total = countStok(p);
        if (total > maxStok) {
            maxStok = total;
        }
        p = p->next;
    }

    cout << "\nBuku dengan stok TERBANYAK\n";
    cout << "-----------------------------\n";

    p = L.first;
    while (p != nullptr) {
        if (countStok(p) == maxStok) {
            cout << "Judul       : " << p->info.judul << endl;
            cout << "Jumlah Stok : " << maxStok << endl;
            cout << "-----------------------------\n";
        }
        p = p->next;
    }
}

void displayStokTersedikit(ListBuku L) {
    if (isEmptyBuku(L)) {
        cout << "Data buku kosong.\n";
        return;
    }
    adrBuku p = L.first;
    int minStok = countStok(p);

    while (p != nullptr) {
        int total = countStok(p);
        if (total < minStok) {
            minStok = total;
        }
        p = p->next;
    }

    cout << "\nBuku dengan stok TERSEDIKIT\n";
    cout << "-----------------------------\n";

    p = L.first;
    while (p != nullptr) {
        if (countStok(p) == minStok) {
            cout << "Judul       : " << p->info.judul << endl;
            cout << "Jumlah Stok : " << minStok << endl;
            cout << "-----------------------------\n";
        }
        p = p->next;
    }
}
