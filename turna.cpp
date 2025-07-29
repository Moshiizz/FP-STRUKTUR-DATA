// ===[ HEADERS & TYPEDEFS ]===
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <limits>
#include <queue>
using namespace std;

typedef vector<string> vs;

// ===[ GLOBAL CONSTANTS ]===
const vs ROLE_LIST = {"Duelist", "Initiator", "Controller", "Sentinel", "Flex"};
const map<string, vs> AGENTS_BY_ROLE = {
    {"Duelist", {"Jett", "Reyna", "Neon", "Raze", "Phoenix"}},
    {"Initiator", {"Sova", "Skye", "Breach", "Fade"}},
    {"Controller", {"Brimstone", "Omen", "Viper", "Astra", "Harbor"}},
    {"Sentinel", {"Cypher", "Killjoy", "Sage", "Chamber"}},
    {"Flex", {"Clove", "Iso", "Yoru", "Waylay", "Gekko", "KAY/O", "Tejo", "Deadlock", "Vyse"}}};

// ===[ STRUCTURES ]===

struct Pemain
{
    string nama, role, agent;
    Pemain *next = nullptr;
};

struct Tim
{
    int id;
    string namaTim;
    Pemain *daftarPemain = nullptr;
    int skor = 0;
};

struct Match
{
    int idTimA, idTimB;
};

// ===[ GLOBAL VARIABLES ]===

vector<Tim> daftar;
vector<Match> matchDraft;
queue<Match> q;
map<string, set<string>> grafPertemuan;

// ===[ UTILITIES ]===

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void tungguEnter()
{
    cout << "\nTekan ENTER untuk kembali...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ===[ FUNCTION DECLARATIONS ]===

// Start (Manage Tim)
void tambahTim()
{
    Tim t;
    t.id = daftar.size() + 1; // buat nambah ruang index
    cout << "Nama Tim: ";
    getline(cin, t.namaTim);
    daftar.push_back(t);
    cout << "Tim berhasil ditambahkan.\n";
}

void editTim()
{
    int id;
    cout << "ID Tim yang ingin diedit: ";
    cin >> id;
    cin.ignore();
    if (id > 0 && id <= (int)daftar.size())
    {
        cout << "Nama baru: ";
        getline(cin, daftar[id - 1].namaTim); // yang ini buat ngecek index vector sebelumnya makanya -1
        cout << "Nama tim berhasil diubah.\n";
    }
    else
        cout << "ID tidak ditemukan.\n";
}

void hapusTim()
{
    int id;
    cout << "ID Tim yang ingin dihapus: ";
    cin >> id;
    cin.ignore();
    if (id > 0 && id <= (int)daftar.size())
    {
        daftar.erase(daftar.begin() + (id - 1));
        for (int i = 0; i < (int)daftar.size(); i++)
            daftar[i].id = i + 1;
        cout << "Tim berhasil dihapus.\n";
    }
    else
        cout << "ID tidak ditemukan.\n";
}

void menuManageTim()
{
    int pilih;
    do
    {
        clearScreen();
        cout << "== Manage Tim ==\n";
        cout << "1. Tambah Tim\n2. Edit Nama Tim\n3. Hapus Tim\n0. Kembali\nPilihan: ";
        cin >> pilih;
        cin.ignore();
        switch (pilih)
        {
        case 1:
            tambahTim();
            break;
        case 2:
            editTim();
            break;
        case 3:
            hapusTim();
            break;
        }
    } while (pilih != 0);
}
// End (Manage Tim)

// Start (Manage Pemain)
string tampilkanRoleDanPilih()
{
    cout << "\n=== Pilih Role ===\n";
    for (int i = 0; i < ROLE_LIST.size(); i++)
        cout << "  " << (i + 1) << ". " << ROLE_LIST[i] << "\n";
    cout << "Pilih Role (1-" << ROLE_LIST.size() << "): ";
    int rc;
    cin >> rc;
    cin.ignore();
    return (rc >= 1 && rc <= ROLE_LIST.size() ? ROLE_LIST[rc - 1] : ROLE_LIST[0]);
}

string tampilkanAgentDanPilih(const string &role)
{
    clearScreen();
    auto &ags = AGENTS_BY_ROLE.at(role);
    cout << "\n=== Pilih Agent (Role: '" << role << "') ===\n";
    for (int i = 0; i < ags.size(); i++)
        cout << "  " << (i + 1) << ". " << ags[i] << "\n";
    cout << "Pilih Agent (1-" << ags.size() << "): ";
    int ac;
    cin >> ac;
    cin.ignore();
    return (ac >= 1 && ac <= (int)ags.size() ? ags[ac - 1] : ags[0]);
}

void TambahPemain(Tim &t)
{
    string na;
    cout << "Nama Pemain: ";
    getline(cin, na);

    string selRole = tampilkanRoleDanPilih();
    string selAg = tampilkanAgentDanPilih(selRole);

    // linked list insertion
    Pemain *p = new Pemain{na, selRole, selAg, nullptr};
    if (!t.daftarPemain)
        t.daftarPemain = p;
    else
    {
        Pemain *c = t.daftarPemain;
        while (c->next)
            c = c->next;
        c->next = p;
    }
    cout << "Pemain berhasil ditambahkan.\n";
}

void EditPemain(Tim &t)
{
    Pemain *p = t.daftarPemain;
    if (!p)
    {
        cout << "Tidak ada pemain di tim ini.\n";
        return;
    }
    int no = 1;
    vector<Pemain *> urut;
    cout << "\nDaftar Pemain:\n";
    while (p)
    {
        cout << "  " << no << ". " << p->nama << " (" << p->role << ", " << p->agent << ")\n";
        urut.push_back(p);
        p = p->next;
        no++;
    }

    int idx;
    cout << "Pilih nomor pemain yang ingin diedit: ";
    cin >> idx;
    cin.ignore();

    if (idx >= 1 && idx <= (int)urut.size())
    {
        Pemain *selected = urut[idx - 1];
        cout << "Nama baru: ";
        getline(cin, selected->nama);

        string selRole = tampilkanRoleDanPilih();
        selected->role = selRole;
        selected->agent = tampilkanAgentDanPilih(selRole);

        cout << "Pemain berhasil diedit.\n";
    }
    else
        cout << "Nomor tidak valid.\n";
}

void HapusPemain(Tim &t)
{
    Pemain *p = t.daftarPemain;
    if (!p)
    {
        cout << "Tidak ada pemain di tim ini.\n";
        return;
    }
    int no = 1;
    vector<Pemain *> urut;
    cout << "\nDaftar Pemain:\n";
    while (p)
    {
        cout << "  " << no << ". " << p->nama << " (" << p->role << ", " << p->agent << ")\n";
        urut.push_back(p);
        p = p->next;
        no++;
    }
    int idx;
    cout << "Pilih nomor pemain yang ingin dihapus: ";
    cin >> idx;
    cin.ignore();
    if (idx >= 1 && idx <= (int)urut.size())
    {
        Pemain *target = urut[idx - 1];
        if (target == t.daftarPemain)
        {
            t.daftarPemain = target->next;
        }
        else
        {
            Pemain *prev = t.daftarPemain;
            while (prev && prev->next != target)
                prev = prev->next;
            if (prev)
                prev->next = target->next;
        }
        delete target;
        cout << "Pemain berhasil dihapus.\n";
    }
    else
    {
        cout << "Nomor tidak valid.\n";
    }
}

void menuManagePemain()
{
    clearScreen();
    cout << "-- Manage Pemain --\n";
    int id;
    cout << "ID Tim: ";
    cin >> id;
    cin.ignore();
    if (id <= 0 || id > (int)daftar.size())
    {
        cout << "ID Tim tidak valid.\n";
        tungguEnter();
        return;
    }

    Tim &t = daftar[id - 1];
    int pilih;
    do
    {
        clearScreen();
        cout << "== Manage Pemain Tim: " << t.namaTim << " ==\n";
        cout << "1. Tambah Pemain\n2. Edit Pemain\n3. Hapus Pemain\n0. Kembali\nPilihan: ";
        cin >> pilih;
        cin.ignore();

        switch (pilih)
        {
        case 1:
            TambahPemain(t);
            break;
        case 2:
            EditPemain(t);
            break;
        case 3:
            HapusPemain(t);
            break;
        }

        if (pilih != 0)
            tungguEnter();

    } while (pilih != 0);
}
// End (Manage Pemain)

// Start (Tampilkan Tim & Pemain)
void tampilkanTimDanPemain(const vector<Tim> &daftar)
{
    cout << "\n=== Daftar Tim & Pemain ===\n";
    if (daftar.empty())
    {
        cout << "(Belum ada tim)\n";
    }
    for (const auto &t : daftar)
    {
        cout << t.id << ". " << t.namaTim << " (Skor: " << t.skor << ")\n";
        Pemain *p = t.daftarPemain;
        if (!p)
        {
            cout << "   (Belum ada pemain)\n";
            continue;
        }
        int no = 1;
        while (p)
        {
            cout << "   " << no++ << ". " << p->nama
                 << " | Role: " << p->role
                 << " | Agent: " << p->agent << "\n";
            p = p->next;
        }
    }
    cout << "===========================\n";
    tungguEnter();
}
// End (Tampilkan Tim & Pemain)

// Start (Cari Tim & Pemain)
void cariTimDanTampilkan()
{
    vector<Tim *> res;
    cout << "-- Cari Tim --\n";
    string k;
    cout << "Keyword: ";
    getline(cin, k);
    string lk = k;
    transform(lk.begin(), lk.end(), lk.begin(), ::tolower);
    for (auto &t : daftar)
    {
        string ln = t.namaTim;
        transform(ln.begin(), ln.end(), ln.begin(), ::tolower);
        if (ln.find(lk) != string::npos)
            res.push_back(&t);
    }
    cout << "\nHasil Pencarian:\n";
    for (auto *p : res)
    {
        cout << "* " << p->namaTim << "\n";
        Pemain *pm = p->daftarPemain;
        int no = 1;
        while (pm)
        {
            cout << "   " << no++ << ". " << pm->nama
                 << " | Role: " << pm->role
                 << " | Agent: " << pm->agent << "\n";
            pm = pm->next;
        }
    }
    if (res.empty())
        cout << "(Tidak ditemukan)\n";
    tungguEnter();
}
// End (Cari Tim & Pemain)

// Start (Match)
void tambahMatchDraft(const vector<Tim> &daftar)
{
    int a, b;
    cout << "ID Tim A: ";
    cin >> a;
    cout << "ID Tim B: ";
    cin >> b;
    cin.ignore();
    if (a == b || a <= 0 || b <= 0 || a > daftar.size() || b > daftar.size())
    {
        cout << "ID tidak valid.\n";
    }
    else
    {
        matchDraft.push_back({a, b});
        cout << "Match ditambahkan ke draft.\n";
    }
}

void editMatchDraft(const vector<Tim> &daftar)
{
    if (matchDraft.empty())
    {
        cout << "Belum ada match untuk diedit.\n";
        return;
    }
    int idx;
    cout << "Nomor match yang ingin diedit: ";
    cin >> idx;
    cin.ignore();
    if (idx >= 1 && idx <= matchDraft.size())
    {
        int a, b;
        cout << "ID Tim A baru: ";
        cin >> a;
        cout << "ID Tim B baru: ";
        cin >> b;
        cin.ignore();
        if (a == b || a <= 0 || b <= 0 || a > daftar.size() || b > daftar.size())
        {
            cout << "ID tidak valid.\n";
        }
        else
        {
            matchDraft[idx - 1] = {a, b};
            cout << "Match berhasil diubah.\n";
        }
    }
    else
    {
        cout << "Nomor tidak valid.\n";
    }
}

void hapusMatchDraft()
{
    if (matchDraft.empty())
    {
        cout << "Belum ada match untuk dihapus.\n";
        return;
    }
    int idx;
    cout << "Nomor match yang ingin dihapus: ";
    cin >> idx;
    cin.ignore();
    if (idx >= 1 && idx <= matchDraft.size())
    {
        matchDraft.erase(matchDraft.begin() + (idx - 1));
        cout << "Match berhasil dihapus.\n";
    }
    else
    {
        cout << "Nomor tidak valid.\n";
    }
}

void kirimDraftKeAntrian(queue<Match> &q, const vector<Tim> &daftar)
{
    if (matchDraft.empty())
    {
        cout << "Draft kosong. Tidak ada match dikirim.\n";
        return;
    }
    for (const auto &m : matchDraft)
        q.push(m);
    cout << matchDraft.size() << " match dikirim ke antrian.\n";
    matchDraft.clear();
}

void tampilkanAntrianMatch(const queue<Match> &q, const vector<Tim> &daftar)
{
    cout << "\n=== Antrian Match ===\n";
    if (q.empty())
    {
        cout << "(Kosong)\n";
    }
    else
    {
        queue<Match> temp = q;
        while (!temp.empty())
        {
            Match m = temp.front();
            temp.pop();
            string namaA = (m.idTimA >= 1 && m.idTimA <= daftar.size()) ? daftar[m.idTimA - 1].namaTim : "Unknown";
            string namaB = (m.idTimB >= 1 && m.idTimB <= daftar.size()) ? daftar[m.idTimB - 1].namaTim : "Unknown";
            cout << "  " << namaA << " vs " << namaB << "\n";
        }
    }
    cout << "=====================\n";
    tungguEnter();
}

void tampilkanMatchDraft(const vector<Match> &draft, const vector<Tim> &daftar)
{
    cout << "\n=== Draft Match Saat Ini ===\n";
    if (draft.empty())
    {
        cout << "(Belum ada match)\n";
    }
    else
    {
        for (int i = 0; i < (int)draft.size(); ++i)
        {
            const Match &m = draft[i];
            string namaA = (m.idTimA >= 1 && m.idTimA <= daftar.size()) ? daftar[m.idTimA - 1].namaTim : "Unknown";
            string namaB = (m.idTimB >= 1 && m.idTimB <= daftar.size()) ? daftar[m.idTimB - 1].namaTim : "Unknown";
            cout << i + 1 << ". " << namaA << " vs " << namaB << "\n";
        }
    }
}

void menuAntrianMatchBaru(queue<Match> &q, const vector<Tim> &daftar)
{
    int pilih;
    do
    {
        clearScreen();
        tampilkanMatchDraft(matchDraft, daftar);
        cout << "\n1. Tambah Match\n2. Edit Match\n3. Hapus Match\n4. Kirim ke Antrian\n0. Kembali\n";
        cout << "Pilihan: ";
        cin >> pilih;
        cin.ignore();

        switch (pilih)
        {
        case 1:
            tambahMatchDraft(daftar);
            break;
        case 2:
            editMatchDraft(daftar);
            break;
        case 3:
            hapusMatchDraft();
            break;
        case 4:
            kirimDraftKeAntrian(q, daftar);
            break;
        }

        if (pilih != 0)
            tungguEnter();

    } while (pilih != 0);
}

// End (Match)

// Start (JalankanMatch)
void addPertemuan(const string &A, const string &B)
{
    grafPertemuan[A].insert(B);
    grafPertemuan[B].insert(A);
}

void jalankanDanRegisterMatch(queue<Match> &q, vector<Tim> &daftar)
{
    cout << "-- Jalankan & Register Match --\n";

    if (q.empty())
    {
        cout << "Tidak ada match.\n";
        tungguEnter();
        return;
    }

    Match m = q.front();
    q.pop();

    if (m.idTimA <= daftar.size() && m.idTimB <= daftar.size())
    {
        string A = daftar[m.idTimA - 1].namaTim;
        string B = daftar[m.idTimB - 1].namaTim;

        //skor random max 12
        int sA = rand() % 13, sB = rand() % 13;
        while (sA == sB)
            sB = rand() % 13;

        cout << "Match: " << A << " vs " << B << "\n";
        cout << "Hasil: " << sA << " - " << sB << "\n";

        if (sA > sB)
        {
            daftar[m.idTimA - 1].skor += 3;
            cout << A << " +3 poin\n";
        }
        else
        {
            daftar[m.idTimB - 1].skor += 3;
            cout << B << " +3 poin\n";
        }

        addPertemuan(A, B);
    }
    else
    {
        cout << "ID tim tidak valid.\n";
    }

    tungguEnter();
}
// End (JalankanMatch)

// Start (CetakRiwayat)
void cetakGraf()
{
    cout << "\n=== Riwayat Pertemuan ===\n";
    for (auto &[tim, lawan] : grafPertemuan)
    {
        cout << "- " << tim << ": ";
        bool first = true;
        for (auto &o : lawan)
        {
            if (!first)
                cout << ", ";
            cout << o;
            first = false;
        }
        cout << "\n";
    }
    cout << "=========================\n";
    tungguEnter();
}
// End (CetakRiwayat)

// ===[ AUTOMATIC FILLERS ]===

void isiOtomatis8Tim(vector<Tim> &daftar)
{
    vs names = {"Alpha", "Bravo", "Charlie", "Delta", "Echo", "Foxtrot", "Golf", "Hotel"};
    srand((unsigned)time(nullptr));
    int base = daftar.size() + 1;
    for (int i = 0; i < 8; ++i)
    {
        Tim t;
        t.id = base + i;
        t.namaTim = names[i];
        for (int j = 0; j < 5; ++j)
        {
            string nm = "Pl" + to_string(j + 1) + "_" + names[i];
            string rl = ROLE_LIST[rand() % ROLE_LIST.size()];
            auto &ags = AGENTS_BY_ROLE.at(rl);
            string ag = ags[rand() % ags.size()];
            Pemain *p = new Pemain{nm, rl, ag, nullptr};
            if (!t.daftarPemain)
                t.daftarPemain = p;
            else
            {
                Pemain *c = t.daftarPemain;
                while (c->next)
                    c = c->next;
                c->next = p;
            }
        }
        daftar.push_back(t);
    }
}

void isiOtomatis4Match(vector<Tim> &daftar, vector<Match> &draft)
{
    draft.push_back({daftar[0].id, daftar[1].id});
    draft.push_back({daftar[2].id, daftar[3].id});
    draft.push_back({daftar[4].id, daftar[5].id});
    draft.push_back({daftar[6].id, daftar[7].id});
}

// ===[ MAIN FUNCTION ]===

int main()
{
    srand((unsigned)time(nullptr));
    int pil;
    do
    {
        clearScreen();
        cout << "\n======== MENU ========\n"
             << "\n-- Manajemen Tim & Pemain --\n"
             << "1. Manage Tim (Tambah/Edit/Hapus)\n"
             << "2. Manage Pemain (Tambah/Edit/Hapus)\n"
             << "3. Tampilkan Tim & Pemain\n"
             << "4. Cari Tim\n"

             << "\n-- Antrian & Pertandingan --\n"
             << "5. Manage Antrian Match (Tambah/Edit/Hapus)\n"
             << "6. Jalankan & Register Match\n"
             << "7. Lihat Antrian Match\n"

             << "\n-- Statistik & Peringkat --\n"
             << "8. Sort & Ranking\n"

             << "\n-- Riwayat --\n"
             << "9. Cetak Riwayat Pertemuan\n"

             << "\n0. Keluar\n"
             << "========================\n"
             << "Pilihan: ";
        cin >> pil;
        cin.ignore();
        switch (pil)
        {
        case 1:
            clearScreen();
            menuManageTim();
            break;
        case 2:
            clearScreen();
            menuManagePemain();
            break;
        case 3:
            clearScreen();
            tampilkanTimDanPemain(daftar);
            break;
        case 4:
            clearScreen();
            cariTimDanTampilkan();
            break;
        case 5:
            clearScreen();
            menuAntrianMatchBaru(q, daftar);
            break;

        case 6:
            clearScreen();
            jalankanDanRegisterMatch(q, daftar);
            break;
        case 7:
            clearScreen();
            tampilkanAntrianMatch(q, daftar);
            break;

        case 8:
            clearScreen();
            sort(daftar.begin(), daftar.end(), [](auto &a, auto &b)
                 { return a.skor > b.skor; });
            tampilkanTimDanPemain(daftar);
            break;
        case 9:
            clearScreen();
            cetakGraf();
            break;
        case 99:
            isiOtomatis8Tim(daftar);
            isiOtomatis4Match(daftar, matchDraft);
            break;
        }
    } while (pil != 0);
    return 0;
}
