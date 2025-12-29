#ifndef PERPUSTAKAAN_H_INCLUDED
#define PERPUSTAKAAN_H_INCLUDED

#include <iostream>
#include <cstring>
using namespace std;

typedef struct elemenBuku *adrBuku;
typedef struct elemenStok *adrStok;

struct Buku {
    int idBuku;
    char judul[100];
    char pengarang[100];
    int tahunTerbit;
    char kategori[50];
};

struct elemenBuku {
    Buku info;
    adrBuku next;
    adrBuku prev;
    adrStok firstStok;
};

struct elemenStok {
    int idEksemplar;
    adrStok next;
};

struct ListBuku {
    adrBuku first;
    adrBuku last;
};

void createListBuku(ListBuku &L);
bool isEmptyBuku(ListBuku L);
bool isEmptyStok(adrBuku p);

adrBuku createElemenBuku(int id, const char judul[],const char pengarang[], int tahun, const char kategori[]);
adrStok createElemenStok(int idEksemplar);

void addBuku(ListBuku &L, adrBuku p);
void addStok(adrBuku &p, adrStok q);

adrBuku searchBuku(ListBuku L, int idBuku);

void deleteBuku(ListBuku &L, int idBuku);
void deleteStok(adrBuku &p, int idEksemplar);
void deleteStokJumlah(adrBuku &p, int jumlah);

void displayListBuku(ListBuku L);
void displayStok(adrBuku p);

int countStok(adrBuku p);

void searchBukuByJudul(ListBuku L, const char keyword[]);
void searchBukuByPengarang(ListBuku L, const char keyword[]);
void searchBukuByTahun(ListBuku L, int tahun);
void searchBukuByKategori(ListBuku L, const char keyword[]);

void displayStokTerbanyak(ListBuku L);
void displayStokTersedikit(ListBuku L);

#endif // PERPUSTAKAAN_H_INCLUDED
