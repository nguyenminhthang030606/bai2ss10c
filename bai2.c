#include <stdio.h>
#include <string.h>

#define MAX_VE 50

struct VeSuKien {
    int maVe;
    char tenSuKien[50];
    char loaiVe[20];
    float giaGoc;
    int isEarlyBird;
    int daCheckIn;
};

int timVeTheoMa(struct VeSuKien dsVe[], int soLuong, int maVe);
int phatHanhVe(struct VeSuKien dsVe[], int *soLuong, struct VeSuKien veMoi);
void checkInVe(struct VeSuKien dsVe[], int soLuong, int maVe);
int huyVe(struct VeSuKien dsVe[], int *soLuong, int maVe);
void hienThiDanhSach(struct VeSuKien dsVe[], int soLuong);

int main() {
    struct VeSuKien dsVe[MAX_VE];
    int soLuong = 0;

    struct VeSuKien v1 = {1001, "Live Concert VIBE 2025", "VIP", 2000000, 1, 0};
    struct VeSuKien v2 = {1002, "Live Concert VIBE 2025", "GA", 1000000, 0, 0};
    struct VeSuKien v3 = {1003, "Live Concert VIBE 2025", "Zone A", 1500000, 1, 0};

    printf("1. KHOI TAO 3 VE BAN DAU\n");
    phatHanhVe(dsVe, &soLuong, v1);
    phatHanhVe(dsVe, &soLuong, v2);
    phatHanhVe(dsVe, &soLuong, v3);

    printf("\n2. HIEN THI DANH SACH\n");
    hienThiDanhSach(dsVe, soLuong);

    printf("\n3. PHAT HANH THEM 1 VE MOI\n");
    struct VeSuKien v4 = {1004, "Live Concert VIBE 2025", "VIP", 2000000, 0, 0};
    phatHanhVe(dsVe, &soLuong, v4);

    printf("\n4. QUET MA QR CHECK-IN THUONG\n");
    checkInVe(dsVe, soLuong, 1002);

    printf("\n5. QUET LAI MA QR VUA CHECK-IN (LOI DUPLICATE)\n");
    checkInVe(dsVe, soLuong, 1002);

    printf("\n6. THUC HIEN HUY VE (MA 1003)\n");
    huyVe(dsVe, &soLuong, 1003);

    printf("\n7. QUET MA QR KHONG TON TAI\n");
    checkInVe(dsVe, soLuong, 9999);

    printf("\n8. HIEN THI LAI DANH SACH CUOI CUNG\n");
    hienThiDanhSach(dsVe, soLuong);

    return 0;
}

int timVeTheoMa(struct VeSuKien dsVe[], int soLuong, int maVe) {
    for (int i = 0; i < soLuong; i++) {
        if (dsVe[i].maVe == maVe) {
            return i;
        }
    }
    return -1;
}

int phatHanhVe(struct VeSuKien dsVe[], int *soLuong, struct VeSuKien veMoi) {
    if (*soLuong >= MAX_VE) {
        printf("[LOI]: He thong da dat suc chua toi da (%d ve). Khong the phat hanh!\n", MAX_VE);
        return 0;
    }
    dsVe[*soLuong] = veMoi;
    (*soLuong)++;
    printf("[THANH CONG]: Phat hanh ve %d thanh cong.\n", veMoi.maVe);
    return 1;
}

void checkInVe(struct VeSuKien dsVe[], int soLuong, int maVe) {
    if (soLuong == 0) {
        printf("[LOI]: Danh sach ve dang rong. Khong the soat ve!\n");
        return;
    }
    int index = timVeTheoMa(dsVe, soLuong, maVe);
    if (index == -1) {
        printf("[LOI]: Ma ve %d khong ton tai tren he thong!\n", maVe);
        return;
    }
    if (dsVe[index].daCheckIn == 1) {
        printf("[CANH BAO GIAN LAN]: Ma ve %d da duoc su dung de qua cong truoc do!\n", maVe);
    } else {
        dsVe[index].daCheckIn = 1;
        printf("[THANH CONG]: Ve %d hop le. Chao mung den voi su kien!\n", maVe);
    }
}

int huyVe(struct VeSuKien dsVe[], int *soLuong, int maVe) {
    if (*soLuong == 0) {
        printf("[LOI]: Danh sach rong. Khong the thao tac huy ve!\n");
        return 0;
    }
    int index = timVeTheoMa(dsVe, *soLuong, maVe);
    if (index == -1) {
        printf("[LOI]: Khong the huy. Ma ve %d khong ton tai!\n", maVe);
        return 0;
    }
    for (int i = index; i < *soLuong - 1; i++) {
        dsVe[i] = dsVe[i + 1];
    }
    (*soLuong)--;
    printf("[THANH CONG]: Da huy ve %d va xoa khoi he thong.\n", maVe);
    return 1;
}

void hienThiDanhSach(struct VeSuKien dsVe[], int soLuong) {
    if (soLuong == 0) {
        printf("[THONG BAO]: He thong dang khong co ve nao.\n");
        return;
    }
    printf("%-10s %-10s %-15s %-10s %-15s\n", "MA VE", "KHU VUC", "GIA GOC (VND)", "EARLY BIRD", "GIA THUC TE (VND)");
    printf("------------------------------------------------------------------\n");
    for (int i = 0; i < soLuong; i++) {
        float giaThucTe = dsVe[i].giaGoc;
        char ebStatus[5] = "Khong";
        if (dsVe[i].isEarlyBird == 1) {
            giaThucTe = dsVe[i].giaGoc * 0.85f;
            strcpy(ebStatus, "Co");
        }
        printf("%-10d %-10s %-15.0f %-10s %-15.0f\n", 
               dsVe[i].maVe, dsVe[i].loaiVe, dsVe[i].giaGoc, ebStatus, giaThucTe);
    }
    printf("------------------------------------------------------------------\n");
}