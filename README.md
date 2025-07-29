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

### `class Pemain`
Menyimpan informasi individual pemain seperti nama, role, dan agent yang digunakan.

```cpp
class Pemain {
    string nama;
    string role;
    string agent;
};
```

### `class Tim`
Menyimpan nama tim dan daftar pemain menggunakan `vector<Pemain>`.

```cpp
class Tim {
    string nama;
    vector<Pemain> daftarPemain;
};
```

### `map<string, Tim> daftarTim`
Menyimpan seluruh tim berdasarkan nama tim sebagai *key*. Memudahkan pencarian dan manipulasi data tim.

### `queue<string> antrianPertandingan`
Menyimpan antrian tim yang siap bertanding, dengan konsep FIFO (First In First Out).

### `vector<string> riwayatPertandingan`
Menyimpan hasil pertandingan sebelumnya dalam format string untuk ditampilkan sebagai log riwayat.

---

## ⚙️ Fungsi Utama

- **`tambahTim()`**  
  Menambahkan data tim dan pemain ke dalam `daftarTim`.

- **`hapusTim()`**  
  Menghapus tim tertentu dari `daftarTim`.

- **`editTim()`**  
  Mengubah nama tim atau data pemain dalam tim.

- **`masukkanAntrian()`**  
  Menambahkan tim ke dalam `antrianPertandingan`.

- **`simulasiPertandingan()`**  
  Mengambil dua tim terdepan dari antrian dan menentukan pemenang secara acak, lalu menyimpan hasilnya ke `riwayatPertandingan`.

- **`tampilkanSemuaTim()`**  
  Menampilkan seluruh tim beserta daftar pemainnya.

- **`tampilkanPemain()`**  
  Menampilkan pemain dari tim tertentu.

- **`tampilkanAntrian()`**  
  Menampilkan daftar antrian tim yang akan bertanding.

- **`tampilkanRiwayat()`**  
  Menampilkan hasil-hasil pertandingan yang telah berlangsung.

---

## 🛠️ Bahasa & Tools

- **Bahasa:** C++
- **IDE:** Visual Studio Code / Code::Blocks / Dev-C++
- **Compiler:** MinGW / g++
- **Struktur Data:** `map`, `vector`, `queue`

---

