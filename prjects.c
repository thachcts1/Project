#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_MATERIAL 100
#define MAX_TRANSACTION 200

struct Material {
    char matId[10];
    char name[50];
    char unit[10];
    int qty;
    int status; 
};

struct Transaction {
    char transID[20];
    char matId[10];
    char type[5]; 
    char date[15];
};



// chuyen chuoi thanh chu thg
void toLowerStr(char *dest, const char *src) {
    int i = 0;
    while (src[i]) {
        if (src[i] >= 'A' && src[i] <= 'Z')
            dest[i] = src[i] + ('a' - 'A');
        else
            dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// add chuoi
void inputString(char *prompt, char *buffer, int size) {
    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, size, stdin) == NULL) {
            printf("Loi nhap, vui long nhap lai.\n");
        
            clearerr(stdin);
            continue;
        }
        buffer[strcspn(buffer, "\n")] = '\0'; // remove newline

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

//validate
int inputInt(char *prompt) {
    char buffer[128];
    int value;
    char extra;
    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Loi nhap, vui long nhap lai.\n");
            clearerr(stdin);
            continue;
        }
        
        if (sscanf(buffer, "%d %c", &value, &extra) == 1 && value >= 0) {
            return value;
        }
        printf("Chi duoc nhap so nguyen >= 0! Nhap lai.\n");
    }
}


int isAlphaString(const char *str) {
    if (str[0] == '\0') return 0;
    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')))
            return 0;
    }
    return 1;
}




int isUniqueId(struct Material materials[], int matCount, const char *id) {
    for (int i = 0; i < matCount; i++) {
        if (strcmp(materials[i].matId, id) == 0) return 0;
    }
    return 1;
}

//clear
void deleteMaterial(struct Material materials[], int *matCount, int index) {
    if (index < 0 || index >= *matCount) return;
    for (int i = index; i < (*matCount) - 1; i++) {
        materials[i] = materials[i + 1];
    }
    (*matCount)--;
    printf("Xoa vat tu thanh cong!\n");
}

// case 1
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
        inputString("Nhap don vi (kg, hop, cai,...): ", m.unit, sizeof(m.unit));
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

//Case 2
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


  // Case 3
   

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
        char confirm[4];
        while (1) {
            inputString("Ban co chac muon khoa vat tu? (y/n): ", confirm, sizeof(confirm));
            if (confirm[0] == 'y' || confirm[0] == 'Y') {
                materials[found].status = 0;
                printf("Da khoa vat tu!\n");
                break;
            } else if (confirm[0] == 'n' || confirm[0] == 'N') {
                printf("Huy thao tac khoa!\n");
                break;
            } else {
                printf("Vui long nhap y hoac n.\n");
            }
        }
    } else {
        // confirm xóa
        char confirm[4];
        while (1) {
            inputString("Ban co chac muon xoa vat tu? (y/n): ", confirm, sizeof(confirm));
            if (confirm[0] == 'y' || confirm[0] == 'Y') {
                deleteMaterial(materials, matCount, found);
                break;
            } else if (confirm[0] == 'n' || confirm[0] == 'N') {
                printf("Huy thao tac xoa!\n");
                break;
            } else {
                printf("Vui long nhap y hoac n.\n");
            }
        }
    }
}


//Kh piet hoa hay thg

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
    char keywordLower[50];
    char matLower[50];
    int resultIndexes[MAX_MATERIAL];
    int resultCount;

    do {
        inputString("Nhap tu khoa: ", keyword, sizeof(keyword));
        toLowerStr(keywordLower, keyword);

        resultCount = 0;

        for (int i = 0; i < matCount; i++) {
            if (choice == 1) toLowerStr(matLower, materials[i].matId);
            else toLowerStr(matLower, materials[i].name);

            if (strstr(matLower, keywordLower) != NULL) {
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

//show phan trang

void listMaterials(struct Material materials[], int matCount) {
    if (matCount == 0) {
        printf("Danh sach rong!\n");
        return;
    }

    int pageSize = 4;
    int totalPages = (matCount + pageSize - 1) / pageSize;
    if (totalPages > 6) totalPages = 6;
    int currentPage = 0;
    char buffer[16];

    while (1) {
        printf("\n===== DANH SACH VAT TU (Trang %d/%d) =====\n",
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

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) break;
        int nav = -1;
        sscanf(buffer, "%d", &nav);

        if (nav == 0) break;
        if (nav == 1 && currentPage > 0) currentPage--;
        if (nav == 2 && currentPage < totalPages - 1) currentPage++;
    }
}



int cmpByName(const void *a, const void *b) {
    const struct Material *m1 = a;
    const struct Material *m2 = b;
    return strcmp(m1->name, m2->name);
}

int cmpByQty(const void *a, const void *b) {
    const struct Material *m1 = a;
    const struct Material *m2 = b;
    return m1->qty - m2->qty;
}

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

//case 7

void inOutTransaction(struct Material materials[], int matCount,
                      struct Transaction trans[], int *transCount) {

    if (matCount == 0) {
        printf("Danh sach vat tu rong!\n");
        return;
    }

    char type[8];
    char typeLower[8];
    char matId[10];
    int found = -1;
    int qty;

    // Nhap loai giao dich (in/out)
    while (1) {
        inputString("Nhap loai giao dich (in = nhap, out = xuat): ", type, sizeof(type));
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
    if (qty <= 0) {
        printf("So luong phai > 0.\n");
        return;
    }

    if (strcmp(type, "in") == 0) {
        materials[found].qty += qty;
        sprintf(trans[*transCount].transID, "GD_%03d", *transCount + 1);
        strcpy(trans[*transCount].matId, matId);
        strcpy(trans[*transCount].type, "in");
        strcpy(trans[*transCount].date, "N/T/N");
        (*transCount)++;
        printf("Nhap vat tu %s thanh cong!\n", matId);
        return;
    }

    if (strcmp(type, "out") == 0) {
        if (qty > materials[found].qty) {
            printf("So luong xuat vuot qua so luong hien co!\n");
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


void showMenu() {
    printf("+--------------------------------+\n");
    printf("|         MENU CHINH             |\n");
    printf("+--------------------------------+\n");
    printf("| 1. Them vat tu moi             |\n");
    printf("| 2. Cap nhat vat tu             |\n");
    printf("| 3. Quan ly trang thai(Khoa|Xoa)|\n");
    printf("| 4. Tra cuu vat tu              |\n");
    printf("| 5. Danh sach vat tu            |\n");
    printf("| 6. Sap xep danh sach           |\n");
    printf("| 7. Giao dich (Nhap/Xuat)       |\n");
    printf("| 8. Lich su giao dich           |\n");
    printf("| 0. Thoat                       |\n");
    printf("==================================\n");
}



int main() {
    struct Material materials[MAX_MATERIAL];
    int matCount = 0;

    struct Transaction transactions[MAX_TRANSACTION];
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

    return 0;
}
