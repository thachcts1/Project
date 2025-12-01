#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_MATERIAL 100

struct Material {
    char matId[10];
    char name[50];
    char unit[10];
    int qty;
    int status;
};

struct Transaction{
	char transID[20]; //ma giao dich
	char matId[10]; //ma vat tu
	char type[5]; // kieu xuat nhap ( in = nhap , out = xuat )
	char date[15]; // thoi gian giao dich
};

//cs1
int isUniqueId(struct Material materials[], int matCount, char *id) {
    for (int i = 0; i < matCount; i++) {
        if (strcmp(materials[i].matId, id) == 0) return 0;
    }
    return 1;
}

// bo khoang trnag
void inputString(char *prompt, char *buffer, int size) {
    while (1) {
        printf("%s", prompt);

        if (fgets(buffer, size, stdin) == NULL) {
            printf("Loi nhap, vui long nhap lai.\n");
            continue;
        }

        buffer[strcspn(buffer, "\n")] = '\0';  // xoa enter

        int valid = 0;
        for (int i = 0; buffer[i] != '\0'; i++) {
            if (buffer[i] != ' ' && buffer[i] != '\t') {
                valid = 1;
                break;
            }
        }

        if (!valid) {
            printf("Khong duoc de trong! Nhap lai.\n");
            continue;
        }

        break;
    }
}

int inputInt(char *prompt) {
    char buffer[50];
    int value;
    char check;
    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Loi nhap, vui long nhap lai.\n");
            continue;
        }
        if (sscanf(buffer, "%d %c", &value, &check) != 1 || value < 0) {
            printf("Chi duoc nhap so nguyen, nhap lai: ");
            continue;
        }
        return value;
    }
}

int isAlphaString(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!((str[i] >= 'A' && str[i] <= 'Z') ||
              (str[i] >= 'a' && str[i] <= 'z'))) {
            return 0;
        }
    }
    return 1;
}

// delete
void deleteMaterial(struct Material materials[], int *matCount, int index) {
    for (int i = index; i < (*matCount) - 1; i++) {
        materials[i] = materials[i + 1];
    }
    (*matCount)--;
    printf("Xoa vat tu thanh cong!\n");
}

// Thêm vat tu
void addMaterial(struct Material materials[], int *matCount) {
    if (*matCount >= MAX_MATERIAL) {
        printf("Danh sach day, khong the them!\n");
        return;
    }

    struct Material m;

    while (1) {
        inputString("Nhap ma vat tu: ", m.matId, sizeof(m.matId));
        if (!isUniqueId(materials, *matCount, m.matId)) {
            printf("Ma vat tu da ton tai, nhap lai!\n");
            continue;
        }
        break;
    }

    inputString("Nhap ten vat tu: ", m.name, sizeof(m.name));

    while (1) {
        inputString("Nhap don vi: ", m.unit, sizeof(m.unit));
        if (!isAlphaString(m.unit)) {
            printf("Don vi chi gom chu cai, nhap lai!\n");
            continue;
        }
        break;
    }

    m.qty = inputInt("Nhap so luong: ");
    m.status = 1;

    materials[*matCount] = m;
    (*matCount)++;

    printf("Them vat tu thanh cong!\n");
}

// Cap nhat vat tu
void updateMaterial(struct Material materials[], int matCount) {
    if (matCount == 0) {
        printf("Danh sach rong!\n");
        return;
    }

    char id[10];
    int found = -1;

    while (1) {
        inputString("Nhap ma vat tu can cap nhat: ", id, sizeof(id));
        found = -1;
        for (int i = 0; i < matCount; i++) {
            if (strcmp(materials[i].matId, id) == 0) {
                found = i;
                break;
            }
        }
        if (found == -1)
            printf("Khong tim thay, nhap lai!\n");
        else
            break;
    }

    inputString("Nhap ten moi: ", materials[found].name, sizeof(materials[found].name));

    while (1) {
        inputString("Nhap don vi moi: ", materials[found].unit, sizeof(materials[found].unit));
        if (!isAlphaString(materials[found].unit)) {
            printf("Don vi sai! Nhap lai.\n");
            continue;
        }
        break;
    }

    materials[found].qty = inputInt("Nhap so luong moi: ");
    printf("Cap nhat thanh cong!\n");
}

// Quan lý trang thái
void manageStatus(struct Material materials[], int *matCount) {
    if (*matCount == 0) {
        printf("Danh sach rong!\n");
        return;
    }

    char id[10];
    int found = -1;

    while (1) {
        inputString("Nhap ma vat tu: ", id, sizeof(id));
        found = -1;
        for (int i = 0; i < *matCount; i++) {
            if (strcmp(materials[i].matId, id) == 0) {
                found = i;
                break;
            }
        }
        if (found == -1)
            printf("Ma khong ton tai! Nhap lai.\n");
        else
            break;
    }

    printf("1. Khoa vat tu\n2. Xoa vat tu\n");

    int opt;
    while (1) {
        opt = inputInt("Nhap lua chon: ");
        if (opt == 1 || opt == 2) break;
        printf("Lua chon khong hop le!\n");
    }

    if (opt == 1) {
        materials[found].status = 0;
        printf("Da khoa vat tu!\n");
    } else {
        deleteMaterial(materials, matCount, found);
    }
}

// khong phan biet hoa hay thg.
void toLowerStr(char *dest, const char *src) {
    int i = 0;
    while (src[i]) {
        if (src[i] >= 'A' && src[i] <= 'Z')
            dest[i] = src[i] + 32;
        else
            dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// Tra cuu vat tu
void findMaterial(struct Material materials[], int matCount) {
    if (matCount == 0) {
        printf("Danh sach rong!\n");
        return;
    }

    int choice;
    do {
        choice = inputInt("Tim theo (1=Ma, 2=Ten): ");
    } while (choice != 1 && choice != 2);

    char keyword[50];
    int resultIndexes[MAX_MATERIAL];
    int resultCount;
    char keywordLower[50], matLower[50];

    do {
        inputString("Nhap tu khoa: ", keyword, sizeof(keyword));
        toLowerStr(keywordLower, keyword);

        resultCount = 0;
        for (int i = 0; i < matCount; i++) {
            if (choice == 1) toLowerStr(matLower, materials[i].matId);
            else toLowerStr(matLower, materials[i].name);

            if (strncmp(matLower, keywordLower, strlen(keywordLower)) == 0) {
                resultIndexes[resultCount++] = i;
            }
        }

        if (resultCount == 0)
            printf("Khong tim thay! Nhap lai.\n");

    } while (resultCount == 0);

    printf("\nKET QUA TIM THAY:\n");
    printf("|%-10s|%-20s|%-10s|%-10s|%-10s|\n",
           "Ma", "Ten", "Don vi", "SL", "Trang thai");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < resultCount; i++) {
        int idx = resultIndexes[i];
        printf("|%-10s|%-20s|%-10s|%-10d|%-10s|\n",
               materials[idx].matId,
               materials[idx].name,
               materials[idx].unit,
               materials[idx].qty,
               (materials[idx].status ? "Hoat dong" : "Khoa"));
    }
}

// Hien thi danh sách vat tu
void listMaterials(struct Material materials[], int matCount) {
    if (matCount == 0) {
        printf("Danh sach rong!\n");
        return;
    }

    int pageSize = 4;
    int totalPages = (matCount + pageSize - 1) / pageSize;
    if (totalPages > 6) totalPages = 6;
    int currentPage = 0;

    while (1) {
        //system("cls"); // Windows only, có th? b? ho?c thay clear n?u dùng Linux
        printf("===== DANH SACH VAT TU (Trang %d/%d) =====\n",
               currentPage + 1, totalPages);

        printf("|%-10s|%-20s|%-10s|%-10s|%-10s|\n",
               "Ma", "Ten", "Don vi", "SL", "Trang thai");
        printf("-------------------------------------------------------------\n");

        int start = currentPage * pageSize;
        int end = start + pageSize;
        if (end > matCount) end = matCount;

        for (int i = start; i < end; i++) {
            printf("|%-10s|%-20s|%-10s|%-10d|%-10s|\n",
                   materials[i].matId,
                   materials[i].name,
                   materials[i].unit,
                   materials[i].qty,
                   (materials[i].status ? "Hoat dong" : "Khoa"));
        }

        printf("-------------------------------------------------------------\n");
        printf("1. Trang truoc   2. Trang sau   0. Thoat: ");

        char buffer[10];
        int nav = 0;
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &nav);

        if (nav == 0) break;
        if (nav == 1 && currentPage > 0) currentPage--;
        if (nav == 2 && currentPage < totalPages - 1) currentPage++;
    }
}

// So sánh tên
int cmpByName(const void *a, const void *b) {
    struct Material *m1 = (struct Material *)a;
    struct Material *m2 = (struct Material *)b;
    return strcmp(m1->name, m2->name);
}

// So sánh so luong
int cmpByQty(const void *a, const void *b) {
    struct Material *m1 = (struct Material *)a;
    struct Material *m2 = (struct Material *)b;
    return m1->qty - m2->qty;
}

// Sap xep vat tu
void sortMaterials(struct Material materials[], int matCount) {
    if (matCount == 0) {
        printf("Danh sach vat tu rong!\n");
        return;
    }

    int choice;
    do {
        printf("Chon kieu sap xep:\n");
        printf("1. Sap xep theo ten\n");
        printf("2. Sap xep theo so luong\n");
        choice = inputInt("Lua chon: ");
    } while (choice != 1 && choice != 2);

    if (choice == 1) qsort(materials, matCount, sizeof(struct Material), cmpByName);
    else qsort(materials, matCount, sizeof(struct Material), cmpByQty);

    printf("Da sap xep thanh cong! Hien thi danh sach:\n");
    listMaterials(materials, matCount);
}

// Case 7
void inOutTransaction(struct Material materials[], int matCount, struct Transaction trans[], int *transCount) {

    if (matCount == 0) {
        printf("Danh sach vat tu rong!\n");
        return;
    }

    char type[5];
    char matId[10];
    int found = -1;
    int qty;

    // Nhap loai giao dich (in/out)
    while (1) {
        inputString("Nhap loai giao dich (in = nhap, out = xuat): ", type, sizeof(type));
        char typeLower[5];
        toLowerStr(typeLower, type);

        if (strcmp(typeLower, "in") == 0 || strcmp(typeLower, "out") == 0) {
            strcpy(type, typeLower);
            break;
        }
        printf("Loai giao dich khong hop le! Chi duoc nhap 'in' hoac 'out'.\n");
    }

    // Nhap ma vat tu
    while (1) {
        inputString("Nhap ma vat tu: ", matId, sizeof(matId));

        found = -1;
        for (int i = 0; i < matCount; i++) {
            if (strcmp(materials[i].matId, matId) == 0) {
                found = i;
                break;
            }
        }

        if (found == -1) {
            printf("Ma vat tu khong ton tai trong danh sach! Nhap lai.\n");
        } else break;
    }

    // Nhap so luong
    qty = inputInt("Nhap so luong: ");

    if (strcmp(type, "in") == 0) {
        materials[found].qty += qty;
        sprintf(trans[*transCount].transID, "GD_%03d", *transCount + 1);
        strcpy(trans[*transCount].matId, matId);
        strcpy(trans[*transCount].type, "in");
        strcpy(trans[*transCount].date, "N/A");
        (*transCount)++;
        printf("Nhap vat tu %s thanh cong!\n", matId);
        return;
    }

    if (strcmp(type, "out") == 0) {
        if (qty > materials[found].qty) {
            printf("So luong xuat vat tu %s vuot qua so luong hien co!\n", matId);
            return;
        }

        materials[found].qty -= qty;
        sprintf(trans[*transCount].transID, "GD_%03d", *transCount + 1);
        strcpy(trans[*transCount].matId, matId);
        strcpy(trans[*transCount].type, "out");
        strcpy(trans[*transCount].date, "N/A");
        (*transCount)++;
        printf("Xuat vat tu %s thanh cong!\n", matId);
        return;
    }
}


//case 8
void historyTransaction(struct Transaction trans[], int transCount) {
    if (transCount == 0) {
        printf("Chua co giao dich nao!\n");
        return;
    }

    char matId[10];
    inputString("Nhap ma vat tu can xem lich su: ", matId, sizeof(matId));

    int found = 0;
    printf("\n=== LICH SU GIAO DICH CUA VAT TU %s ===\n", matId);
    printf("|%-10s|%-5s|%-10s|\n", "TransID", "Type", "Date");
    printf("-------------------------------------\n");

    for (int i = 0; i < transCount; i++) {
        if (strcmp(trans[i].matId, matId) == 0) {
            printf("|%-10s|%-5s|%-10s|\n",
                   trans[i].transID,
                   trans[i].type,
                   trans[i].date);
            found = 1;
        }
    }

    if (!found) {
        printf("Vat tu %s chua co giao dich nhap/xuat.\n", matId);
    }
}


// Menu chính
void showMenu() {
    printf("+-----------------------------+\n");
    printf("|         MENU CHINH          |\n");
    printf("+-----------------------------+\n");
    printf("| 1. Them vat tu moi          |\n");
    printf("| 2. Cap nhat vat tu          |\n");
    printf("| 3. Quan ly trang thai       |\n");
    printf("| 4. Tra cuu vat tu           |\n");
    printf("| 5. Danh sach vat tu         |\n");
    printf("| 6. Sap xep danh sach        |\n");
    printf("| 7. Giao dich (Nhap/Xuat)    |\n");
    printf("| 8. Lich su giao dich        |\n");
    printf("| 0. Thoat                    |\n");
    printf("===============================\n");
}

// Hàm main
int main() {
    struct Material materials[MAX_MATERIAL];
    int matCount = 0;

    struct Transaction transactions[100];
    int transCount = 0;

    int choice;

    while (1) {
        showMenu();
        choice = inputInt("Chon chuc nang: ");

        switch(choice) {
            case 1: addMaterial(materials, &matCount); break;
            case 2: updateMaterial(materials, matCount); break;
            case 3: manageStatus(materials, &matCount); break;
            case 4: findMaterial(materials, matCount); break;
            case 5: listMaterials(materials, matCount); break;
            case 6: sortMaterials(materials, matCount); break;
            case 7: inOutTransaction(materials, matCount, transactions, &transCount); break;
            case 8: historyTransaction(transactions, transCount); break;
            case 0: printf("Thoat!\n"); return 0;
            default: printf("Lua chon khong hop le!\n");
        }
    }
}
