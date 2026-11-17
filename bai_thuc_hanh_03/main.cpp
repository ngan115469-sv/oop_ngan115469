#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cctype>

using namespace std;

//-------------------------------------------------
class phuong_tien {
private:
    int ma_xe;
    string loai_xe;
    int gio_vao;
    int tg_do;

public:
    phuong_tien() {
        ma_xe = 0;
        loai_xe = "";
        gio_vao = 0;
        tg_do = 0;
    }

    phuong_tien(int ma, string loai, int gio, int tg) {
        ma_xe = ma;
        loai_xe = loai;
        gio_vao = gio;
        tg_do = tg;
    }

    int lay_ma_xe() const { return ma_xe; }
    string lay_loai_xe() const { return loai_xe; }
    int lay_gio_vao() const { return gio_vao; }
    int lay_tg_do() const { return tg_do; }

    // Tính phí d? xe
    double tinh_phi() const {
        double gia = 2.0; // M?c d?nh Bicycle
        if (loai_xe == "Car") gia = 6.0;
        else if (loai_xe == "Motorcycle") gia = 4.0;

        bool cao_diem = (gio_vao >= 6 && gio_vao <= 9) || (gio_vao >= 15 && gio_vao <= 18);
        double tong = 0;
        for (int h = 0; h < tg_do; h++) {
            if (h >= 2) tong += gia * 0.90;
            else if (cao_diem) tong += gia * 1.30;
            else tong += gia * 0.95;
        }
        return tong;
    }

    void hien_thi() const {
        cout << "   ID: " << ma_xe << " | " << loai_xe << " | " << gio_vao << "h | "
             << tg_do << "h | Phi: $" << fixed << setprecision(2) << tinh_phi() << endl;
    }
};

//-------------------------------------------------
class bai_xe {
private:
    int ma_bai;
    char kich_thuoc;
    int suc_chua;
    int so_xe;
    phuong_tien** ds_xe;

    // Hàm n?i b? c?p phát b? nh? ban d?u
    void cap_phat(int cap) {
        suc_chua = cap;
        ds_xe = new phuong_tien*[suc_chua];
        for (int i = 0; i < suc_chua; i++) {
            ds_xe[i] = nullptr;
        }
    }

    // Hàm n?i b? gi?i phóng b? nh?
    void giai_phong() {
        if (ds_xe != nullptr) {
            for (int i = 0; i < so_xe; i++) {
                delete ds_xe[i];
                ds_xe[i] = nullptr;
            }
            delete[] ds_xe;
            ds_xe = nullptr;
        }
    }

public:
    // Constructor m?c d?nh và có tham s?
    bai_xe(int ma = 0, char kt = 'S') {
        ma_bai = ma;
        kich_thuoc = kt;
        so_xe = 0;
        int cap_ban_dau = (kt == 'S') ? 1 : (kt == 'M' ? 2 : 3);
        cap_phat(cap_ban_dau);
    }

    // 1. Destructor (~bai_xe): thu h?i bãi xe
    ~bai_xe() {
        giai_phong();
    }

    // 2. Copy Constructor (Sao chép sâu)
    bai_xe(const bai_xe& other) {
        ma_bai = other.ma_bai;
        kich_thuoc = other.kich_thuoc;
        so_xe = other.so_xe;
        suc_chua = other.suc_chua;

        ds_xe = new phuong_tien*[suc_chua];
        for (int i = 0; i < suc_chua; i++) {
            if (other.ds_xe[i] != nullptr) {
                ds_xe[i] = new phuong_tien(*(other.ds_xe[i]));
            } else {
                ds_xe[i] = nullptr;
            }
        }
    }

    // 3. Toán t? gán - Sao chép sâu
    bai_xe& operator=(const bai_xe& other) {
        if (this == &other) return *this;
        giai_phong();

        ma_bai = other.ma_bai;
        kich_thuoc = other.kich_thuoc;
        so_xe = other.so_xe;
        suc_chua = other.suc_chua;
        ds_xe = new phuong_tien*[suc_chua];
        for (int i = 0; i < suc_chua; i++) {
            if (other.ds_xe[i] != nullptr) {
                ds_xe[i] = new phuong_tien(*(other.ds_xe[i]));
            } else {
                ds_xe[i] = nullptr;
            }
        }
        return *this;
    }

    int lay_ma() const { return ma_bai; }
    char lay_kich_thuoc() const { return kich_thuoc; }
    int lay_so_xe() const { return so_xe; }
    int lay_suc_chua() const { return suc_chua; }
    bool la_day() const { return so_xe >= suc_chua; }

    // T? d?ng m? r?ng s?c ch?a khi bãi d?y
    void mo_rong(int suc_chua_moi) {
        phuong_tien** ds_moi = new phuong_tien*[suc_chua_moi];
        for (int i = 0; i < suc_chua_moi; i++) {
            ds_moi[i] = nullptr;
        }
        for (int i = 0; i < so_xe; i++) {
            ds_moi[i] = ds_xe[i];
        }
        delete[] ds_xe;
        ds_xe = ds_moi;
        suc_chua = suc_chua_moi;
    }

    // Thêm xe vào bãi (t? d?ng nhân dôi s?c ch?a n?u d?y)
    bool them(const phuong_tien& v) {
        if (so_xe >= suc_chua) {
            mo_rong(suc_chua * 2);
        }
        ds_xe[so_xe] = new phuong_tien(v);
        so_xe++;
        return true;
    }

    // Tìm v? trí c?a xe theo mã xe
    int tim_chi_so(int ma) const {
        for (int i = 0; i < so_xe; i++) {
            if (ds_xe[i] != nullptr && ds_xe[i]->lay_ma_xe() == ma) {
                return i;
            }
        }
        return -1;
    }

    // Xóa xe an toàn theo mã
    bool xoa(int ma) {
        int vt = tim_chi_so(ma);
        if (vt == -1) return false;
        delete ds_xe[vt]; // Thu h?i b? nh? d?i tu?ng xe

        // D?n m?ng con tr? sang trái
        for (int i = vt; i < so_xe - 1; i++) {
            ds_xe[i] = ds_xe[i + 1];
        }
        ds_xe[so_xe - 1] = nullptr;
        so_xe--;
        return true;
    }

    void hien_thi() const {
        cout << "Bai " << ma_bai << " [" << kich_thuoc << "] " << so_xe << "/" << suc_chua << " xe" << endl;
        for (int i = 0; i < so_xe; i++) {
            ds_xe[i]->hien_thi();
        }
    }

    
    void thong_ke(string loai, int& dem, double& tong) const {
        dem = 0;
        tong = 0;
        for (int i = 0; i < so_xe; i++) {
            if (ds_xe[i]->lay_loai_xe() == loai) {
                dem++;
                tong += ds_xe[i]->tinh_phi();
            }
        }
    }
};
//-------------------------------------------------
class SystemInterface {
private:
    int suc_chua_he_thong;
    int so_bai;
    bai_xe** ds_bai; // M?ng con tr? d?ng ch?a các bãi d?

    void cap_phat_sys(int cap) {
        suc_chua_he_thong = cap;
        ds_bai = new bai_xe*[suc_chua_he_thong];
        for (int i = 0; i < suc_chua_he_thong; i++) {
            ds_bai[i] = nullptr;
        }
    }

    void giai_phong_sys() {
        if (ds_bai != nullptr) {
            for (int i = 0; i < so_bai; i++) {
                delete ds_bai[i];
                ds_bai[i] = nullptr;
            }
            delete[] ds_bai;
            ds_bai = nullptr;
        }
    }

    int nhap_so(string nhac, int min, int max) {
        int x;
        while (true) {
            cout << nhac;
            cin >> x;
            if (cin.fail()) {
                cout << "Loi: phai nhap so nguyen!" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
            } else if (x < min || x > max) {
                cout << "Gia tri phai tu " << min << " den " << max << "!" << endl;
            } else {
                return x;
            }
        }
    }

    string nhap_loai() {
        string s;
        while (true) {
            cout << "Loai xe (Car/Motorcycle/Bicycle): ";
            cin >> s;
            for (int i = 0; i < (int)s.length(); i++) s[i] = tolower(s[i]);
            if (s == "car") return "Car";
            if (s == "motorcycle") return "Motorcycle";
            if (s == "bicycle") return "Bicycle";
            cout << "Loai xe khong hop le!" << endl;
        }
    }

    int tim_bai(int ma) const {
        for (int i = 0; i < so_bai; i++) {
            if (ds_bai[i] != nullptr && ds_bai[i]->lay_ma() == ma) return i;
        }
        return -1;
    }

    bool ton_tai_ma_bai(int ma) const { return tim_bai(ma) != -1; }

    bool ton_tai_ma_xe(int ma) const {
        for (int i = 0; i < so_bai; i++) {
            if (ds_bai[i] != nullptr && ds_bai[i]->tim_chi_so(ma) != -1) return true;
        }
        return false;
    }

    int sinh_ma_ngau_nhien() { return rand() % 9000 + 1000; }

    void mo_rong_sys(int cap_moi) {
        bai_xe** ds_moi = new bai_xe*[cap_moi];
        for (int i = 0; i < cap_moi; i++) {
            ds_moi[i] = nullptr;
        }
        for (int i = 0; i < so_bai; i++) {
            ds_moi[i] = ds_bai[i];
        }
        delete[] ds_bai;
        ds_bai = ds_moi;
        suc_chua_he_thong = cap_moi;
    }

public:
    SystemInterface() {
        so_bai = 0;
        cap_phat_sys(5);
    }

    ~SystemInterface() {
        giai_phong_sys();
    }

    void runMenu() {
        int chon;
        do {
            cout << "\n===== QUAN LY BAI DO XE =====\n"
                 << "1. Tao bai do\n"
                 << "2. Them xe\n"
                 << "3. Xoa bai do\n"
                 << "4. Lay xe ra\n"
                 << "5. Hien thi tat ca bai do\n"
                 << "6. Hien thi xe theo bai\n"
                 << "7. Liet ke xe theo loai\n"
                 << "8. Bao cao phi trung binh\n"
                 << "9. Thoat\n";
            chon = nhap_so("Chon: ", 1, 9);

            switch (chon) {
            case 1: {
                if (so_bai >= suc_chua_he_thong) {
                    mo_rong_sys(suc_chua_he_thong * 2);
                }
                int ma = nhap_so("Ma bai: ", 1, 999999);
                char kt;
                do {
                    cout << "Kich thuoc (S/M/L): ";
                    cin >> kt;
                    kt = toupper(kt);
                } while (kt != 'S' && kt != 'M' && kt != 'L');

                if (ton_tai_ma_bai(ma)) {
                    do { ma = sinh_ma_ngau_nhien(); } while (ton_tai_ma_bai(ma));
                    cout << "Canh bao: ma bai bi trung! Ma moi: " << ma << endl;
                }
                ds_bai[so_bai++] = new bai_xe(ma, kt); // C?p phát d?ng bãi xe
                cout << "Da tao bai " << ma << endl;
                break;
            }
            case 2: {
                if (so_bai == 0) {
                    cout << "Canh bao: chua co bai do nao trong he thong!" << endl;
                    break;
                }
                int ma = nhap_so("Ma xe: ", 1, 999999);
                string loai = nhap_loai();
                int gio = nhap_so("Gio vao (0-23): ", 0, 23);
                int tg = nhap_so("Thoi luong (1-23): ", 1, 23);

                // Uu tiên tìm bãi chua d?y; n?u t?t c? d?u d?y thì ch?n bãi d?u tiên d? t? d?ng m? r?ng
                int vt = -1;
                for (int i = 0; i < so_bai; i++) {
                    if (!ds_bai[i]->la_day()) {
                        vt = i;
                        break;
                    }
                }
                if (vt == -1) vt = 0;

                if (ton_tai_ma_xe(ma)) {
                    do { ma = sinh_ma_ngau_nhien(); } while (ton_tai_ma_xe(ma));
                    cout << "Canh bao: ma xe bi trung! Ma moi: " << ma << endl;
                }

                phuong_tien v(ma, loai, gio, tg);
                ds_bai[vt]->them(v);
                cout << "Da them xe " << ma << " vao bai " << ds_bai[vt]->lay_ma()
                     << " | Phi: $" << fixed << setprecision(2) << v.tinh_phi() << endl;
                break;
            }
            case 3: {
                int vt = tim_bai(nhap_so("Ma bai can xoa: ", 1, 999999));
                if (vt == -1) {
                    cout << "Khong tim thay bai!" << endl;
                    break;
                }
                delete ds_bai[vt]; // Gi?i phóng b? nh? bãi xe tru?c khi d?n m?ng
                for (int i = vt; i < so_bai - 1; i++) {
                    ds_bai[i] = ds_bai[i + 1];
                }
                ds_bai[so_bai - 1] = nullptr;
                so_bai--;
                cout << "Da xoa bai" << endl;
                break;
            }
            case 4: {
                int ma = nhap_so("Ma xe can lay ra: ", 1, 999999);
                bool ok = false;
                for (int i = 0; i < so_bai && !ok; i++) {
                    ok = ds_bai[i]->xoa(ma);
                }
                cout << (ok ? "Da lay xe ra" : "Khong tim thay xe") << endl;
                break;
            }
            case 5: {
                if (so_bai == 0) {
                    cout << "Chua co bai do nao." << endl;
                } else {
                    for (int i = 0; i < so_bai; i++) {
                        if (ds_bai[i] != nullptr) {
                            ds_bai[i]->hien_thi();
                        }
                    }
                }
                break;
            }
            case 6: {
                int vt = tim_bai(nhap_so("Ma bai: ", 1, 999999));
                if (vt == -1) cout << "Khong tim thay bai!" << endl;
                else ds_bai[vt]->hien_thi();
                break;
            }
            case 7: {
                string loai = nhap_loai();
                bool co_xe = false;
                for (int i = 0; i < so_bai; i++) {
                    int dem;
                    double phi;
                    ds_bai[i]->thong_ke(loai, dem, phi);
                    if (dem > 0) {
                        ds_bai[i]->hien_thi();
                        co_xe = true;
                    }
                }
                if (!co_xe) cout << "Khong co xe loai " << loai << endl;
                break;
            }
            case 8: {
                string cac_loai[3] = {"Car", "Motorcycle", "Bicycle"};
                cout << fixed << setprecision(2);
                for (int t = 0; t < 3; t++) {
                    int tong_dem = 0;
                    double tong_phi = 0;
                    for (int i = 0; i < so_bai; i++) {
                        int dem;
                        double phi;
                        ds_bai[i]->thong_ke(cac_loai[t], dem, phi);
                        tong_dem += dem;
                        tong_phi += phi;
                    }
                    cout << cac_loai[t] << " (toan he thong): ";
                    if (tong_dem == 0) cout << "khong co xe" << endl;
                    else cout << "TB $" << tong_phi / tong_dem << endl;

                    for (int i = 0; i < so_bai; i++) {
                        int dem;
                        double phi;
                        ds_bai[i]->thong_ke(cac_loai[t], dem, phi);
                        if (dem > 0) {
                            cout << "   Bai " << ds_bai[i]->lay_ma() << ": TB $" << phi / dem << endl;
                        }
                    }
                }
                break;
            }
            case 9:
                cout << "Tam biet! Toan bo bo nho Heap da duoc giai phong sach se." << endl;
                break;
            }
        } while (chon != 9);
    }
};

//-------------------------------------------------
int main() {
    srand(time(0));
    SystemInterface sys;
    sys.runMenu();
    return 0;
}
