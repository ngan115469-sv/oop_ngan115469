#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

class phuong_tien {
private:
    int ma_xe;
    string loai_xe;
    int gio_vao, tg_do;
public:
    phuong_tien() { ma_xe = 0; loai_xe = ""; gio_vao = 0; tg_do = 0; }
    phuong_tien(int ma, string loai, int gio, int tg) {
        ma_xe = ma; loai_xe = loai; gio_vao = gio; tg_do = tg;
    }
    int lay_ma_xe() const { return ma_xe; }
    string lay_loai_xe() const { return loai_xe; }

    double tinh_phi() const {
        double gia = 2.0;
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
        cout << "  ID: " << ma_xe << " | " << loai_xe << " | " << gio_vao << "h | "
             << tg_do << "h | Phi: $" << fixed << setprecision(2) << tinh_phi() << endl;
    }
};

class bai_xe {
private:
    int ma_bai;
    char kich_thuoc;
    static const int MAX_XE = 3;
    phuong_tien ds_xe[MAX_XE];
    int so_xe;
public:
    bai_xe() { ma_bai = 0; kich_thuoc = 'S'; so_xe = 0; }
    bai_xe(int ma, char kt) { ma_bai = ma; kich_thuoc = kt; so_xe = 0; }
    int lay_ma() const { return ma_bai; }

    int suc_chua() const {
        if (kich_thuoc == 'S') return 1;
        if (kich_thuoc == 'M') return 2;
        return 3;
    }
    bool la_day() const { return so_xe >= suc_chua(); }

    bool them(const phuong_tien& v) {
        if (la_day()) return false;
        ds_xe[so_xe++] = v;
        return true;
    }
    int tim_chi_so(int ma) const {
        for (int i = 0; i < so_xe; i++)
            if (ds_xe[i].lay_ma_xe() == ma) return i;
        return -1;
    }
    bool xoa(int ma) {
        int vt = tim_chi_so(ma);
        if (vt == -1) return false;
        for (int i = vt; i < so_xe - 1; i++) ds_xe[i] = ds_xe[i + 1];   // don mang
        so_xe--;
        return true;
    }
    void hien_thi() const {
        cout << "Bai " << ma_bai << " [" << kich_thuoc << "] " << so_xe << "/" << suc_chua() << " xe" << endl;
        for (int i = 0; i < so_xe; i++) ds_xe[i].hien_thi();
    }
    // dem so xe cung loai va tong phi cua chung
    void thong_ke(string loai, int& dem, double& tong) const {
        dem = 0; tong = 0;
        for (int i = 0; i < so_xe; i++)
            if (ds_xe[i].lay_loai_xe() == loai) { dem++; tong += ds_xe[i].tinh_phi(); }
    }
};

class SystemInterface {
private:
    static const int MAX_BAI = 10;
    bai_xe ds_bai[MAX_BAI];
    int so_bai;

    int nhap_so(string nhac, int min, int max) {
        int x;
        while (true) {
            cout << nhac;
            cin >> x;
            if (cin.fail()) {
                cout << "Loi: phai nhap so nguyen!" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
            } else if (x < min || x > max) cout << "Gia tri phai tu " << min << " den " << max << "!" << endl;
            else return x;
        }
    }
    // nhap loai xe, khong phan biet hoa thuong, tra ve Car/Motorcycle/Bicycle
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
        for (int i = 0; i < so_bai; i++)
            if (ds_bai[i].lay_ma() == ma) return i;
        return -1;
    }
    bool ton_tai_ma_bai(int ma) const { return tim_bai(ma) != -1; }
    bool ton_tai_ma_xe(int ma) const {
        for (int i = 0; i < so_bai; i++)
            if (ds_bai[i].tim_chi_so(ma) != -1) return true;
        return false;
    }
    int sinh_ma_ngau_nhien() { return rand() % 9000 + 1000; }

public:
    SystemInterface() { so_bai = 0; }

    void runMenu() {
        int chon;
        do {
            cout << "\n===== QUAN LY BAI DO XE =====\n"
                 << "1. Tao bai do\n2. Them xe\n3. Xoa bai do\n4. Lay xe ra\n"
                 << "5. Hien thi tat ca bai do\n6. Hien thi xe theo bai\n"
                 << "7. Liet ke xe theo loai\n8. Bao cao phi trung binh\n9. Thoat\n";
            chon = nhap_so("Chon: ", 1, 9);

            switch (chon) {
            case 1: {
                if (so_bai >= MAX_BAI) { cout << "Da du " << MAX_BAI << " bai!" << endl; break; }
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
                ds_bai[so_bai++] = bai_xe(ma, kt);
                cout << "Da tao bai " << ma << endl;
                break;
            }
            case 2: {
                int ma = nhap_so("Ma xe: ", 1, 999999);
                string loai = nhap_loai();
                int gio = nhap_so("Gio vao (0-23): ", 0, 23);
                int tg = nhap_so("Thoi luong (1-23): ", 1, 23);
                int vt = -1;                       // bai dau tien con cho
                for (int i = 0; i < so_bai && vt == -1; i++)
                    if (!ds_bai[i].la_day()) vt = i;
                if (vt == -1) { cout << "Canh bao: khong con bai nao con cho!" << endl; break; }
                if (ton_tai_ma_xe(ma)) {
                    do { ma = sinh_ma_ngau_nhien(); } while (ton_tai_ma_xe(ma));
                    cout << "Canh bao: ma xe bi trung! Ma moi: " << ma << endl;
                }
                phuong_tien v(ma, loai, gio, tg);
                ds_bai[vt].them(v);
                cout << "Da them xe " << ma << " vao bai " << ds_bai[vt].lay_ma()
                     << " | Phi: $" << fixed << setprecision(2) << v.tinh_phi() << endl;
                break;
            }
            case 3: {
                int vt = tim_bai(nhap_so("Ma bai can xoa: ", 1, 999999));
                if (vt == -1) { cout << "Khong tim thay bai!" << endl; break; }
                for (int i = vt; i < so_bai - 1; i++) ds_bai[i] = ds_bai[i + 1];   // don mang
                so_bai--;
                cout << "Da xoa bai" << endl;
                break;
            }
            case 4: {
                int ma = nhap_so("Ma xe can lay ra: ", 1, 999999);
                bool ok = false;
                for (int i = 0; i < so_bai && !ok; i++) ok = ds_bai[i].xoa(ma);
                cout << (ok ? "Da lay xe ra" : "Khong tim thay xe") << endl;
                break;
            }
            case 5:
                if (so_bai == 0) cout << "Chua co bai do nao." << endl;
                for (int i = 0; i < so_bai; i++) ds_bai[i].hien_thi();
                break;
            case 6: {
                int vt = tim_bai(nhap_so("Ma bai: ", 1, 999999));
                if (vt == -1) cout << "Khong tim thay bai!" << endl;
                else ds_bai[vt].hien_thi();
                break;
            }
            case 7: {
                string loai = nhap_loai();
                bool co_xe = false;
                for (int i = 0; i < so_bai; i++) {
                    int dem; double phi;
                    ds_bai[i].thong_ke(loai, dem, phi);
                    if (dem > 0) { ds_bai[i].hien_thi(); co_xe = true; }
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
                        ds_bai[i].thong_ke(cac_loai[t], dem, phi);
                        tong_dem += dem; tong_phi += phi;
                    }
                    cout << cac_loai[t] << " (toan he thong): ";
                    if (tong_dem == 0) cout << "khong co xe" << endl;
                    else cout << "TB $" << tong_phi / tong_dem << endl;
                    for (int i = 0; i < so_bai; i++) {          // chi tiet theo bai
                        int dem; double phi;
                        ds_bai[i].thong_ke(cac_loai[t], dem, phi);
                        if (dem > 0) cout << "   Bai " << ds_bai[i].lay_ma() << ": TB $" << phi / dem << endl;
                    }
                }
                break;
            }
            case 9:
                cout << "Tam biet!" << endl;
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

