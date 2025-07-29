# 🎮 Final Project Struktur Data – Manajemen Tim & Pemain Game

**Kelompok:**  
- Akhmad Rizky Fadhillah (24.11.6038)
- Muhammad Hanif Wibowo (24.11.6023)
- Ditto Dwi Saputra (24.11.6026)
- Choirul Fadillah (24.11.6031)
- I Kadek Putra Nata (24.11.5989)



---

## 📌 Deskripsi

Program ini merupakan implementasi struktur data untuk memanajemen tim dan pemain dalam sebuah game, dilengkapi dengan fitur antrian pertandingan dan pencatatan riwayat pertandingan. Program ditulis menggunakan bahasa C++ dan memanfaatkan berbagai struktur data seperti `vector`, `map`, dan `queue`.

---

## 🧱 Struktur Data

### `struct Pemain`
Menyimpan data pemain dalam bentuk linked list: nama, role, agent.

```cpp
struct Pemain {
    string nama, role, agent;
    Pemain *next = nullptr;
};
```

### `struct Tim`
Menyimpan nama tim, daftar pemain (linked list), ID, dan skor.

```cpp
struct Tim {
    int id;
    string namaTim;
    Pemain *daftarPemain = nullptr;
    int skor = 0;
};
```

### `struct Match`
Struktur sederhana untuk menyimpan ID dua tim yang akan bertanding.

```cpp
struct Match {
    int idTimA, idTimB;
};
```

### Struktur Lain:
- `vector<Tim> daftar;` → daftar semua tim yang dibuat
- `vector<Match> matchDraft;` → draft pertandingan
- `queue<Match> q;` → antrian pertandingan
- `map<string, set<string>> grafPertemuan;` → riwayat pertemuan antar tim

---

## ⚙️ Fungsi Utama

### 📌 Manajemen Tim
- `tambahTim()` – Menambahkan tim baru ke daftar
- `editTim()` – Mengubah nama tim
- `hapusTim()` – Menghapus tim dan mengatur ulang ID

### 📌 Manajemen Pemain
- `TambahPemain(Tim&)` – Menambahkan pemain ke tim tertentu
- `EditPemain(Tim&)` – Mengubah data pemain
- `HapusPemain(Tim&)` – Menghapus pemain dari tim (linked list)

### 📌 Antrian dan Pertandingan
- `tambahMatchDraft()` – Menyusun pasangan pertandingan
- `editMatchDraft()` – Mengedit pasangan tim dalam draft
- `hapusMatchDraft()` – Menghapus match dari draft
- `kirimDraftKeAntrian()` – Mengirim seluruh draft ke queue pertandingan
- `jalankanDanRegisterMatch()` – Menjalankan match dan mencatat skor

### 📌 Output dan Pencarian
- `tampilkanTimDanPemain()` – Menampilkan semua tim dan pemainnya
- `cariTimDanTampilkan()` – Mencari tim berdasarkan keyword
- `tampilkanAntrianMatch()` – Menampilkan antrian pertandingan
- `cetakGraf()` – Menampilkan riwayat pertemuan antar tim

### 📌 Auto Generator (Fitur Testing)
- `isiOtomatis8Tim()` – Generate 8 tim + pemain otomatis
- `isiOtomatis4Match()` – Membuat 4 match otomatis dari 8 tim
  
---

## 🛠️ Bahasa & Tools

- **Bahasa:** C++
- **IDE:** Visual Studio Code / Code::Blocks / Dev-C++
- **Compiler:** MinGW / g++
- **Struktur Data:** `map`, `vector`, `queue`

---

