#include<iostream>
#include<string>
#include<algorithm>
#include<iomanip>
#include <cctype>
using namespace std; 
string chuyenThanhChuThuong(string s){
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}
class phuong_tien{
	private: 
	int ma_xe;
	string loai_xe; 
	int gio_vao; 
	int tg_do;
	double phi_do_xe; 
	bool dangChiemCho = false; 
	
	public: 
	phuong_tien(){
		ma_xe = 0; 
		loai_xe = ""; 
		gio_vao = 0; 
		tg_do = 0; 
		phi_do_xe = 0.0; 
		dangChiemCho = false; 
	}
	phuong_tien(int ma, string loai, int gio, int tg){
		ma_xe = ma; 
		loai_xe = loai; 
		gio_vao = gio; 
		tg_do = tg; 
		dangChiemCho = true; 
		tinhPhiDoXe(); 
	}
	//Getters 
	 int getMaXe()const{
	 	return ma_xe; 
	 }
	 string getLoaiXe()const{
	 	return loai_xe; 
	 }
	 int getGioVao()const{
	 	return gio_vao; 
	 }
	 int getTgDo()const{
	 	return tg_do; 
	 }
	 double getPhiDoXe()const{
	 	return phi_do_xe; 
	 }
	 bool getDangChiemCho()const{
	 	return dangChiemCho; 
	 }
	 //Setter 
	 void setMaXe(int ma){
	 	ma_xe = ma; 
	 }
	 void setLoaiXe(string loai){
	 	loai_xe = loai;
	 	tinhPhiDoXe();
	 }
	 void setGioVao(int gio){
	 	gio_vao = gio; 
	 	tinhPhiDoXe();
	 }
	 void setTgDo(int tg){
	 	tg_do = tg;
	 	tinhPhiDoXe(); 
	 }
	 void setPhiDoXe(double phi){
	 	phi_do_xe = phi; 
	 }
	 void setDangChiemCho(bool trangThai){
	 	dangChiemCho = trangThai; 
	 	tinhPhiDoXe();
	 }
	 //Tinh phi do xe theo quy tac nghiep vu
	 void tinhPhiDoXe(){
	 	if(!dangChiemCho){
	 		phi_do_xe = 0.0; 
	 		return;
		 }
		 double donGiaCoBan = 0.0; 
		 string loaiThuong = chuyenThanhChuThuong(loai_xe); 
		 if(loaiThuong == "car"){
		 	donGiaCoBan = 6.0;
		 } 
		 else if(loaiThuong == "motorcycle"){
		 	donGiaCoBan = 4.0; 
		 }
		 else if(loaiThuong == "bicycle"){
		 	donGiaCoBan = 2.0; 
		 }
		 double tongPhi = 0.0; 
		 for(int gioThu = 1; gioThu <= tg_do; gioThu++){
		 	int gioHienTai = (gio_vao + gioThu - 1) % 24; 
		 	double donGiaHienTai = donGiaCoBan; 
		 	
		 	if(gioThu <= 2){
		 		bool laGioCaoDiem = (gioHienTai >=6 && gioHienTai <=9) ||(gioHienTai >=15 && gioHienTai <=18);
		 		if(laGioCaoDiem){
		 			donGiaHienTai *= 1.30; 
				 }
				 else{
				 	donGiaHienTai *= 0.95; 
				 }
			 }
			 else{
			 	donGiaHienTai *= 0.90;
			 }
			 tongPhi += donGiaHienTai; 
		 }
		 phi_do_xe = tongPhi; 
	 }
	 
	 void hienThi()const{
	 	if(!dangChiemCho) return; 
	 	cout << " + Ma xe: " << ma_xe
	 		 << " | Loai: "  << loai_xe
	 		 << " | Gio vao: "  << gio_vao << "h"
	 		 << " | Thoi gian: "  << tg_do << "h"
	 		 << " | Phi do xe: $"  << fixed << setprecision(2) << phi_do_xe << endl;
	 }
};

class bai_xe{
	private: 
	int ma_bai; 
	char kich_thuoc; 
	phuong_tien pt1, pt2, pt3; 
	bool co1, co2, co3; 
	
	public: 
	bai_xe(){
		ma_bai = 0; 
		kich_thuoc = 'S'; 
		co1 = co2 = co3 = false; 
	}
	bai_xe(int ma, char kt){
		ma_bai = ma; 
		kich_thuoc = toupper(kt); 
		co1 = co2 = co3 = false;
	}
	int getMaBai(){
	 	return ma_bai; 
	 } 
	char getKichThuoc(){
		return kich_thuoc; 
	}
	
	int getSucChuaToiDa()const{
		if(kich_thuoc == 'S') return 1; 
		if(kich_thuoc == 'M') return 2;
		if(kich_thuoc == 'L') return 3;
		return 0;
	}
	int getSoLuongHienTai()const{
		int count = 0; 
		if (co1) count++; 
		if (co2) count++;
		if (co3) count++;
		return count;
	}
	bool getDayBai()const{
		return getSoLuongHienTai() >= getSucChuaToiDa(); 
	}
	
	bool them(phuong_tien v){
		int maxCap = getSucChuaToiDa(); 
		if(maxCap >= 1 && !co1){
			pt1 = v; co1 = true; return true; 
		}
			if(maxCap >= 2 && !co2){
			pt2 = v; co2 = true; return true; 
		}
			if(maxCap >= 3 && !co3){
			pt3 = v; co3 = true; return true; 
		}
		return false; 
	}
	
	bool xoa(int ma_xe){
		if(co1 && pt1.getMaXe() == ma_xe){
			co1 = false; return true; 
		}
		if(co2 && pt2.getMaXe() == ma_xe){
			co2 = false; return true; 
		}
		if(co3 && pt3.getMaXe() == ma_xe){
			co3 = false; return true; 
		}
		return false; 
	}
	//Kiem tra xe co trong bai khong
	bool chua(int ma_xe) const{
		if(co1 && pt1.getMaXe() == ma_xe) return true;
		if(co2 && pt2.getMaXe() == ma_xe) return true;
		if(co3 && pt3.getMaXe() == ma_xe) return true;
		return false; 
	}
	
	void hien_thi() const{
		cout  << "Bai xe ID: " << ma_bai
			  << " | Kich thuoc: " << kich_thuoc
			  << " | So luong xe: " << getSoLuongHienTai() 
			  << "/" << getSucChuaToiDa() << endl;
			  if(co1) pt1.hienThi(); 
			  if(co2) pt2.hienThi();
			  if(co3) pt3.hienThi();
	}
	//Liet ke xe theo xep loai 
	int hienThiTheoLoai(string loai)const{
	int dem = 0; 
	if(co1 && chuyenThanhChuThuong(pt1.getLoaiXe()) == loai){
            pt1.hienThi();
            dem++;
        }
        if(co2 && chuyenThanhChuThuong(pt2.getLoaiXe()) == loai){
            pt2.hienThi();
            dem++;
        }
        if(co3 && chuyenThanhChuThuong(pt3.getLoaiXe()) == loai){
            pt3.hienThi();
            dem++;
        }
        return dem;
	}
	//Thong ke chi tiet xe cua moi bai 
	void thongKeBai()const{
	double tongPhi = 0;
	
        if(co1) tongPhi += pt1.getPhiDoXe();
        if(co2) tongPhi += pt2.getPhiDoXe();
        if(co3) tongPhi += pt3.getPhiDoXe();

        int soXe = getSoLuongHienTai();
        cout << "\nBai xe " << ma_bai
             << " - So xe: " << soXe
             << " - Tong phi: $" << fixed << setprecision(2)
             << tongPhi;

        if(soXe > 0){
            cout << " - Trung binh: $" << tongPhi / soXe;
        }
        cout << endl;
    }
    void thongKeLoai(string loai, int &soXe, double &tongPhi) const{
    if(co1 && chuyenThanhChuThuong(pt1.getLoaiXe()) == loai){
        soXe++;
        tongPhi += pt1.getPhiDoXe();
    }

    if(co2 && chuyenThanhChuThuong(pt2.getLoaiXe()) == loai){
        soXe++;
        tongPhi += pt2.getPhiDoXe();
    }

    if(co3 && chuyenThanhChuThuong(pt3.getLoaiXe()) == loai){
        soXe++;
        tongPhi += pt3.getPhiDoXe();
    }
}
};
class giao_dien{
	private: 
	bai_xe bai1, bai2, bai3; 
	bool coBai1 = false; 
	bool coBai2 = false;
	bool coBai3 = false;
	
	public: 
	//Kiem tra ma bai xe da ton tai 
	bool kiemTraMaBai(int ma){
        if(coBai1 && bai1.getMaBai() == ma) return true;
        if(coBai2 && bai2.getMaBai() == ma) return true;
        if(coBai3 && bai3.getMaBai() == ma) return true;

        return false;
    }
    //Kiem tra ma xe da ton tai 
     bool kiemTraMaXe(int ma){
        if(coBai1 && bai1.chua(ma)) return true;
        if(coBai2 && bai2.chua(ma)) return true;
        if(coBai3 && bai3.chua(ma)) return true;

        return false;
    }
    // 1. Tao bai xe moi 
    void taoBaiXe(){
        int ma;
        char kt;

        cout << "\nNhap ma bai xe: ";
        cin >> ma;

        if(kiemTraMaBai(ma)){
            cout << "Ma bai xe da ton tai!\n";
            return;
        }

        cout << "Nhap kich thuoc (S/M/L): ";
        cin >> kt;

        kt = toupper(kt);

        if(kt != 'S' && kt != 'M' && kt != 'L'){
            cout << "Kich thuoc khong hop le!\n";
            return;
        }

        if(!coBai1){
            bai1 = bai_xe(ma, kt);
            coBai1 = true;
        }
        else if(!coBai2){
            bai2 = bai_xe(ma, kt);
            coBai2 = true;
        }
        else if(!coBai3){
            bai3 = bai_xe(ma, kt);
            coBai3 = true;
        }
        else{
            cout << "He thong da du 3 bai xe!\n";
            return;
        }

        cout << "Tao bai xe thanh cong!\n";
    }
    //Tu dong them xe vao bai con cho 
     bool themXeVaoBai(phuong_tien v){
        if(coBai1 && bai1.them(v)) return true;
        if(coBai2 && bai2.them(v)) return true;
        if(coBai3 && bai3.them(v)) return true;
        return false;
    }
    // 2. Them xe 
	void themXe(){
        int ma, gio, tg;
        string loai;

        cout << "\nNhap ma xe: ";
        cin >> ma;

        if(kiemTraMaXe(ma)){
            cout << "Ma xe da ton tai!\n";
            return;
        }

        cout << "Nhap loai xe (Car/Motorcycle/Bicycle): ";
        cin >> loai;

        loai = chuyenThanhChuThuong(loai);

        if(loai != "car" && loai != "motorcycle" && loai != "bicycle"){
            cout << "Loai xe khong hop le!\n";
            return;
        }

        cout << "Nhap gio vao bai (0-23): ";
        cin >> gio;

        if(gio < 0 || gio > 23){
            cout << "Gio vao khong hop le!\n";
            return;
        }

        cout << "Nhap thoi gian do (1-23): ";
        cin >> tg;

        if(tg < 1 || tg > 23){
            cout << "Thoi gian do khong hop le!\n";
            return;
        }

        phuong_tien v(ma, loai, gio, tg);

        if(themXeVaoBai(v)){
            cout << "Them xe thanh cong!\n";
        }
        else{
            cout << "Khong co bai xe phu hop hoac bai da day!\n";
        }
    }
 // 3. Xoa bai xe
 void xoaBaiXe(){
        int ma;

        cout << "\nNhap ma bai xe can xoa: ";
        cin >> ma;

        if(coBai1 && bai1.getMaBai() == ma){
        if(bai1.getSoLuongHienTai() > 0){
            cout << "Bai xe dang co xe, khong the xoa!\n";
            return;
        }
        bai1 = bai_xe();
        coBai1 = false;
        cout << "Da xoa bai xe!\n";
        return;
    }

    if(coBai2 && bai2.getMaBai() == ma){
        if(bai2.getSoLuongHienTai() > 0){
            cout << "Bai xe dang co xe, khong the xoa!\n";
            return;
        }
        bai2 = bai_xe();
        coBai2 = false;
        cout << "Da xoa bai xe!\n";
        return;
    }

    if(coBai3 && bai3.getMaBai() == ma){
        if(bai3.getSoLuongHienTai() > 0){
            cout << "Bai xe dang co xe, khong the xoa!\n";
            return;
        }
        bai3 = bai_xe();
        coBai3 = false;
        cout << "Da xoa bai xe!\n";
        return;
    }

    cout << "Khong tim thay bai xe!\n";
}
 // 4. Lay xe ra khoi bai 
 void layXe(){
        int ma;

        cout << "\nNhap ma xe can lay: ";
        cin >> ma;

        if(coBai1 && bai1.xoa(ma)){
            cout << "Lay xe thanh cong!\n";
            return;
        }

        if(coBai2 && bai2.xoa(ma)){
            cout << "Lay xe thanh cong!\n";
            return;
        }

        if(coBai3 && bai3.xoa(ma)){
            cout << "Lay xe thanh cong!\n";
            return;
        }

        cout << "Khong tim thay xe!\n";
    }
// 5. Hien thi tat ca bai xe
void hienThiTatCa(){
        if(!coBai1 && !coBai2 && !coBai3){
            cout << "He thong chua co bai xe!\n";
            return;
        }

        if(coBai1) bai1.hien_thi();
        if(coBai2) bai2.hien_thi();
        if(coBai3) bai3.hien_thi();
    }
// 6. Hien thi xe theo bai cu the
void hienThiTheoBai(){
        int ma;

        cout << "\nNhap ma bai xe: ";
        cin >> ma;

        if(coBai1 && bai1.getMaBai() == ma){
            bai1.hien_thi();
            return;
        }

        if(coBai2 && bai2.getMaBai() == ma){
            bai2.hien_thi();
            return;
        }

        if(coBai3 && bai3.getMaBai() == ma){
            bai3.hien_thi();
            return;
        }

        cout << "Khong tim thay bai xe!\n";
    }
 // 7. Liet ke xe theo loai
void lietKeTheoLoai(){
        string loai;
        int dem = 0;

        cout << "\nNhap loai xe (Car/Motorcycle/Bicycle): ";
        cin >> loai;

        loai = chuyenThanhChuThuong(loai);

        if(loai != "car" && loai != "motorcycle" && loai != "bicycle"){
            cout << "Loai xe khong hop le!\n";
            return;
        }

        cout << "\nDanh sach xe theo loai " << loai << ":\n";

        if(coBai1) dem += bai1.hienThiTheoLoai(loai);
        if(coBai2) dem += bai2.hienThiTheoLoai(loai);
        if(coBai3) dem += bai3.hienThiTheoLoai(loai);

        if(dem == 0){
            cout << "Khong co xe nao thuoc loai nay!\n";
        }
        else{
            cout << "Tong so xe: " << dem << endl;
        }
    }
 // 8. Bao cao thong ke phi do xe
  // Thong ke mot loai xe
    void thongKeMotLoai(string loai){
        int soXe = 0;
        double tongPhi = 0;

        if(coBai1) bai1.thongKeLoai(loai, soXe, tongPhi);
        if(coBai2) bai2.thongKeLoai(loai, soXe, tongPhi);
        if(coBai3) bai3.thongKeLoai(loai, soXe, tongPhi);

        cout << "\nLoai xe: " << loai
             << "\nSo luong: " << soXe
             << "\nTong phi: $" << fixed << setprecision(2) << tongPhi;

        if(soXe > 0){
            cout << "\nPhi trung binh: $" << tongPhi / soXe;
        }
        else{
            cout << "\nChua co xe!";
        }

        cout << endl;
    }

    // 8. Bao cao thong ke
    void baoCao(){
        cout << "\n========== BAO CAO PHI DO XE ==========\n";

        thongKeMotLoai("car");
        thongKeMotLoai("motorcycle");
        thongKeMotLoai("bicycle");

        cout << "\n========== CHI TIET TUNG BAI ==========\n";

        if(coBai1) bai1.thongKeBai();
        if(coBai2) bai2.thongKeBai();
        if(coBai3) bai3.thongKeBai();
    }
void runMenu(){
int chon;
        do{
            cout << "\n========== QUAN LY BAI DO XE ==========\n";
            cout << "1. Tao bai do xe moi\n";
            cout << "2. Them xe vao bai do\n";
            cout << "3. Xoa mot bai do xe\n";
            cout << "4. Lay xe ra khoi bai\n";
            cout << "5. Hien thi danh sach tat ca bai xe\n";
            cout << "6. Hien thi danh sach xe theo bai\n";
            cout << "7. Liet ke xe theo loai phuong tien\n";
            cout << "8. Bao cao thong ke phi do xe\n";
            cout << "9. Thoat chuong trinh\n";

            cout << "Nhap lua chon: ";
            cin >> chon;

            switch(chon){
                case 1:
                    taoBaiXe();
                    break;

                case 2:
                    themXe();
                    break;

                case 3:
                    xoaBaiXe();
                    break;

                case 4:
                    layXe();
                    break;

                case 5:
                    hienThiTatCa();
                    break;

                case 6:
                    hienThiTheoBai();
                    break;

                case 7:
                    lietKeTheoLoai();
                    break;

                case 8:
                    baoCao();
                    break;

                case 9:
                    cout << "Thoat chuong trinh!\n";
                    break;

                default:
                    cout << "Lua chon khong hop le!\n";
            }

        }while(chon != 9);
    }
};
int main(){
    giao_dien gd;
    gd.runMenu();

    return 0;
}
