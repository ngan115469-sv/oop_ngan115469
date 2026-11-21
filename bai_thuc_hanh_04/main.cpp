#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

class phuong_tien {
protected:
    int ma_xe;
    int gio_vao;
    int tg_do;

public:
    phuong_tien() : ma_xe(0), gio_vao(0), tg_do(0) {}
    phuong_tien(int ma, int gio, int tg) : ma_xe(ma), gio_vao(gio), tg_do(tg) {}

    virtual ~phuong_tien() {}

    int lay_ma_xe() const { return ma_xe; }
    int lay_gio_vao() const { return gio_vao; }
    int lay_tg_do() const { return tg_do; }

//Ham ao thuan tuy
    virtual double tinh_phi() const = 0;
    virtual void hien_thi() const = 0;
    virtual string lay_loai_xe() const = 0;
};

//Lop con xe hoi
class XeHoi : public phuong_tien {
private:
    int so_cho;

public:
    XeHoi() : phuong_tien(), so_cho(4) {}
    XeHoi(int ma, int gio, int tg, int cho = 4)
        : phuong_tien(ma, gio, tg), so_cho(cho) {}

    double tinh_phi() const override {
        const double GIA_CO_BAN = 6.00;
        double tong = 0;
        for (int h = 0; h < tg_do; h++) {
            int gio_hien_tai = gio_vao + h;
            bool cao_diem = (gio_hien_tai >= 7 && gio_hien_tai <= 9) ||
                            (gio_hien_tai >= 17 && gio_hien_tai <= 19);
            if (h >= 2) tong += GIA_CO_BAN * 0.90;
            else if (cao_diem) tong += GIA_CO_BAN * 1.30;
            else tong += GIA_CO_BAN * 0.95;
        }
        return tong;
    }

    void hien_thi() const override {
        cout << "  [Xe hoi] ID: " << ma_xe << " | " << gio_vao << "h | " << tg_do << "h"
             << " | So cho: " << so_cho
             << " | Phi: $" << fixed << setprecision(2) << tinh_phi() << endl;
    }

    string lay_loai_xe() const override { return "Car"; }
};

//Lop con xe may 
class XeMay : public phuong_tien {
private:
    int dung_tich_xi_lanh;

public:
    XeMay() : phuong_tien(), dung_tich_xi_lanh(100) {}
    XeMay(int ma, int gio, int tg, int cc = 100)
        : phuong_tien(ma, gio, tg), dung_tich_xi_lanh(cc) {}

    double tinh_phi() const override {
        const double GIA_CO_BAN = 4.00;
        double tong = 0;
        for (int h = 0; h < tg_do; h++) {
            int gio_hien_tai = gio_vao + h;
            bool cao_diem = (gio_hien_tai >= 7 && gio_hien_tai <= 9) ||
                            (gio_hien_tai >= 17 && gio_hien_tai <= 19);
            if (h >= 2) tong += GIA_CO_BAN * 0.90;
            else if (cao_diem) tong += GIA_CO_BAN * 1.30;
            else tong += GIA_CO_BAN * 0.95;
        }
        return tong;
    }

    void hien_thi() const override {
        cout << "  [Xe may] ID: " << ma_xe << " | " << gio_vao << "h | " << tg_do << "h"
             << " | Dung tich: " << dung_tich_xi_lanh << "cc"
             << " | Phi: $" << fixed << setprecision(2) << tinh_phi() << endl;
    }

    string lay_loai_xe() const override { return "Motorcycle"; }
};

//Lop con xe dap
class XeDap : public phuong_tien {
private:
    bool la_xe_dien;

public:
    XeDap() : phuong_tien(), la_xe_dien(false) {}
    XeDap(int ma, int gio, int tg, bool dien = false)
        : phuong_tien(ma, gio, tg), la_xe_dien(dien) {}

    double tinh_phi() const override {
        const double GIA_CO_BAN = 2.00;
        double tong = 0;
        for (int h = 0; h < tg_do; h++) {
            int gio_hien_tai = gio_vao + h;
            bool cao_diem = (gio_hien_tai >= 7 && gio_hien_tai <= 9) ||
                            (gio_hien_tai >= 17 && gio_hien_tai <= 19);
            if (h >= 2) tong += GIA_CO_BAN * 0.90;
            else if (cao_diem) tong += GIA_CO_BAN * 1.30;
            else tong += GIA_CO_BAN * 0.95;
        }
        return tong;
    }

    void hien_thi() const override {
        cout << "  [Xe dap] ID: " << ma_xe << " | " << gio_vao << "h | " << tg_do << "h"
             << " | Loai: " << (la_xe_dien ? "Xe dap dien" : "Xe dap thuong")
             << " | Phi: $" << fixed << setprecision(2) << tinh_phi() << endl;
    }

    string lay_loai_xe() const override { return "Bicycle"; }
};

//Lop bai xe - da hinh
class bai_xe {
private:
    int ma_bai;
    char kich_thuoc;
    static const int MAX_XE = 10;  
    phuong_tien** ds_xe;           //mang con tro da hinh
    int so_xe;

public:
    bai_xe() : ma_bai(0), kich_thuoc('S'), so_xe(0) {
        ds_xe = new phuong_tien*[MAX_XE];
        for (int i = 0; i < MAX_XE; i++) ds_xe[i] = nullptr;
    }

    bai_xe(int ma, char kt) : ma_bai(ma), kich_thuoc(kt), so_xe(0) {
        ds_xe = new phuong_tien*[MAX_XE];
        for (int i = 0; i < MAX_XE; i++) ds_xe[i] = nullptr;
    }

    ~bai_xe() {
        for (int i = 0; i < so_xe; i++) {
            delete ds_xe[i]; 
        }
        delete[] ds_xe;
    }

    int lay_ma() const { return ma_bai; }

    int suc_chua() const {
        if (kich_thuoc == 'S') return 2;
        if (kich_thuoc == 'M') return 5;
        return 10;
    }
    bool la_day() const { return so_xe >= suc_chua(); }

    // Thêm con tr? xe vào bãi
    bool them(phuong_tien* v) {
        if (la_day()) return false;
        ds_xe[so_xe++] = v;
        return true;
    }

    int tim_chi_so(int ma) const {
        for (int i = 0; i < so_xe; i++)
            if (ds_xe[i] && ds_xe[i]->lay_ma_xe() == ma) return i;
        return -1;
    }

    bool xoa(int ma) {
        int vt = tim_chi_so(ma);
        if (vt == -1) return false;
        delete ds_xe[vt];  // G?i dúng destructor l?p con
        for (int i = vt; i < so_xe - 1; i++) ds_xe[i] = ds_xe[i + 1];
        ds_xe[--so_xe] = nullptr;
        return true;
    }

    void hien_thi() const {
        cout << "\nBai " << ma_bai << " [" << kich_thuoc << "] " << so_xe << "/" << suc_chua() << " xe" << endl;
        for (int i = 0; i < so_xe; i++) {
            ds_xe[i]->hien_thi();  
        }
    }

    void thong_ke(string loai, int& dem, double& tong) const {
        dem = 0; tong = 0;
        for (int i = 0; i < so_xe; i++) {
            if (ds_xe[i]->lay_loai_xe() == loai) {
                dem++;
                tong += ds_xe[i]->tinh_phi();  // ? Ða hình
            }
        }
    }
};

//Lop quan ly he thong
class SystemInterface {
private:
    static const int MAX_BAI = 10;
    bai_xe** ds_bai;  // M?ng con tr? bãi xe
    int so_bai;

    int nhap_so(string nhac, int min, int max) {
        int x;
        while (true) {
            cout << nhac;
            cin >> x;
            if (cin.fail()) {
                cout << "Loi: phai nhap so nguyen!\n";
                cin.clear();
                cin.ignore(1000, '\n');
            } else if (x < min || x > max) cout << "Gia tri phai tu " << min << " den " << max << "!\n";
            else return x;
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
            cout << "Loai xe khong hop le!\n";
        }
    }

    int tim_bai(int ma) const {
        for (int i = 0; i < so_bai; i++)
            if (ds_bai[i]->lay_ma() == ma) return i;
        return -1;
    }

    bool ton_tai_ma_bai(int ma) const { return tim_bai(ma) != -1; }

    bool ton_tai_ma_xe(int ma) const {
        for (int i = 0; i < so_bai; i++)
            if (ds_bai[i]->tim_chi_so(ma) != -1) return true;
        return false;
    }

    int sinh_ma_ngau_nhien() { return rand() % 9000 + 1000; }

public:
    SystemInterface() : so_bai(0) {
        ds_bai = new bai_xe*[MAX_BAI];
        for (int i = 0; i < MAX_BAI; i++) ds_bai[i] = nullptr;
    }

    ~SystemInterface() {
        for (int i = 0; i < so_bai; i++) delete ds_bai[i];
        delete[] ds_bai;
    }

    void runMenu() {
        int chon;
        do {
            cout << "\n===== QUAN LY BAI DO XE - GIAI DOAN 4 =====\n"
                 << "1. Tao bai do\n2. Them xe\n3. Xoa bai do\n4. Lay xe ra\n"
                 << "5. Hien thi tat ca bai do\n6. Hien thi xe theo bai\n"
                 << "7. Liet ke xe theo loai\n8. Bao cao phi trung binh\n9. Thoat\n";
            chon = nhap_so("Chon: ", 1, 9);

            switch (chon) {
            case 1: {
                if (so_bai >= MAX_BAI) { cout << "Da du " << MAX_BAI << " bai!\n"; break; }
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
                ds_bai[so_bai++] = new bai_xe(ma, kt);
                cout << "Da tao bai " << ma << endl;
                break;
            }
            case 2: {
                int ma = nhap_so("Ma xe: ", 1, 999999);
                string loai = nhap_loai();
                int gio = nhap_so("Gio vao (0-23): ", 0, 23);
                int tg = nhap_so("Thoi luong (1-23): ", 1, 23);

                // Tìm bãi còn ch?
                int vt = -1;
                for (int i = 0; i < so_bai && vt == -1; i++)
                    if (!ds_bai[i]->la_day()) vt = i;
                if (vt == -1) { cout << "Canh bao: khong con bai nao con cho!\n"; break; }

                if (ton_tai_ma_xe(ma)) {
                    do { ma = sinh_ma_ngau_nhien(); } while (ton_tai_ma_xe(ma));
                    cout << "Canh bao: ma xe bi trung! Ma moi: " << ma << endl;
                }

                // ? T?o Ð?I TU?NG ÐA HÌNH
                phuong_tien* xe_moi = nullptr;
                if (loai == "Car") {
                    int cho = nhap_so("So cho ngoi: ", 1, 50);
                    xe_moi = new XeHoi(ma, gio, tg, cho);
                }
                else if (loai == "Motorcycle") {
                    int cc = nhap_so("Dung tich xi lanh (cc): ", 50, 2000);
                    xe_moi = new XeMay(ma, gio, tg, cc);
                }
                else if (loai == "Bicycle") {
                    int chon_loai;
                    cout << "Loai xe dap (0=Thuong, 1=Dien): ";
                    cin >> chon_loai;
                    xe_moi = new XeDap(ma, gio, tg, chon_loai == 1);
                }

                ds_bai[vt]->them(xe_moi);
                cout << "Da them xe " << ma << " vao bai " << ds_bai[vt]->lay_ma()
                     << " | Phi: $" << fixed << setprecision(2) << xe_moi->tinh_phi() << endl;
                break;
            }
            case 3: {
                int vt = tim_bai(nhap_so("Ma bai can xoa: ", 1, 999999));
                if (vt == -1) { cout << "Khong tim thay bai!\n"; break; }
                delete ds_bai[vt];
                for (int i = vt; i < so_bai - 1; i++) ds_bai[i] = ds_bai[i + 1];
                ds_bai[--so_bai] = nullptr;
                cout << "Da xoa bai\n";
                break;
            }
            case 4: {
                int ma = nhap_so("Ma xe can lay ra: ", 1, 999999);
                bool ok = false;
                for (int i = 0; i < so_bai && !ok; i++) ok = ds_bai[i]->xoa(ma);
                cout << (ok ? "Da lay xe ra\n" : "Khong tim thay xe\n");
                break;
            }
            case 5:
                if (so_bai == 0) { cout << "Chua co bai do nao.\n"; break; }
                for (int i = 0; i < so_bai; i++) ds_bai[i]->hien_thi();
                break;
            case 6: {
                int vt = tim_bai(nhap_so("Ma bai: ", 1, 999999));
                if (vt == -1) cout << "Khong tim thay bai!\n";
                else ds_bai[vt]->hien_thi();
                break;
            }
            case 7: {
                string loai = nhap_loai();
                bool co_xe = false;
                for (int i = 0; i < so_bai; i++) {
                    int dem; double phi;
                    ds_bai[i]->thong_ke(loai, dem, phi);
                    if (dem > 0) { ds_bai[i]->hien_thi(); co_xe = true; }
                }
                if (!co_xe) cout << "Khong co xe loai " << loai << endl;
                break;
            }
            case 8: {
                string cac_loai[3] = {"Car", "Motorcycle", "Bicycle"};
                cout << fixed << setprecision(2);
                for (int t = 0; t < 3; t++) {
                    int tong_dem = 0; double tong_phi = 0;
                    for (int i = 0; i < so_bai; i++) {
                        int dem; double phi;
                        ds_bai[i]->thong_ke(cac_loai[t], dem, phi);
                        tong_dem += dem; tong_phi += phi;
                    }
                    cout << "\n" << cac_loai[t] << " (toan he thong): ";
                    if (tong_dem == 0) cout << "khong co xe";
                    else cout << "TB $" << tong_phi / tong_dem;
                    cout << endl;
                    for (int i = 0; i < so_bai; i++) {
                        int dem; double phi;
                        ds_bai[i]->thong_ke(cac_loai[t], dem, phi);
                        if (dem > 0) cout << "   Bai " << ds_bai[i]->lay_ma() << ": TB $" << phi / dem << endl;
                    }
                }
                break;
            }
            case 9:
                cout << "Tam biet!\n";
                break;
            }
        } while (chon != 9);
    }
};

int main() {
    srand(time(0));
    SystemInterface sys;
    sys.runMenu();
    return 0;
}

