# FP-STRUKTUR-DATA
Kelompok :
Akhmad Rizky Fadhillah (24.11.6038)


🧩 Struktur Data
class Pemain
Menyimpan informasi individual pemain seperti nama, role, dan agent yang digunakan.

cpp
Copy
Edit
class Pemain {
    string nama;
    string role;
    string agent;
};
class Tim
Menyimpan nama tim dan daftar pemain menggunakan vector<Pemain>.

cpp
Copy
Edit
class Tim {
    string nama;
    vector<Pemain> daftarPemain;
};
map<string, Tim> daftarTim
Menyimpan seluruh tim berdasarkan nama tim sebagai key. Memudahkan pencarian dan manipulasi data tim.

queue<string> antrianPertandingan
Menyimpan antrian tim yang siap bertanding, FIFO (First In First Out).

vector<string> riwayatPertandingan
Menyimpan hasil pertandingan sebelumnya dalam format string untuk ditampilkan sebagai log riwayat.

⚙️ Fungsi Utama
tambahTim()
Menambahkan data tim dan pemain ke dalam struktur data.

hapusTim()
Menghapus tim tertentu dari daftarTim.

editTim()
Mengubah nama tim atau data pemain di dalam tim.

masukkanAntrian()
Menambahkan tim ke dalam antrianPertandingan.

simulasiPertandingan()
Mengambil dua tim terdepan dari antrian dan menentukan pemenang secara acak, lalu menyimpan hasilnya ke riwayatPertandingan.

tampilkanSemuaTim(), tampilkanPemain(), tampilkanAntrian(), tampilkanRiwayat()
Menampilkan berbagai informasi yang telah tersimpan.
