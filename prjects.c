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


int isUniqueId(struct Material materials[], int matCount, char *id) {
    for (int i = 0; i < matCount; i++) {
        if (strcmp(materials[i].matId, id) == 0) {
            return 0; 
    
    }
    return 1;
}


void inputString(char *prompt, char *buffer, int size) {
    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, size, stdin) == NULL) {
            printf("Loi nhap, vui long nhap lai.\n");
            continue;
        }
        buffer[strcspn(buffer, "\n")] = '\0';
        if (strlen(buffer) == 0) {
            printf("Khong duoc rong, vui long nhap lai.\n");
            continue;
        }
        break;
    }
}

int inputInt(char *prompt) {
    char buffer[50];
    int value;
    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Loi nhap, vui long nhap lai.\n");
            continue;
        }
        if (sscanf(buffer, "%d", &value) != 1) {
            printf("Chi duoc nhap so, vui long nhap lai.\n");
            continue;
        }
        if (value < 0) {
            printf("Gia tri phai >= 0, vui long nhap lai.\n");
            continue;
        }
        return value;
    }
}


int isAlphaString(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z'))) {
            return 0; 
        }
    }
    return 1;
}

// Them vat tu moi
void addMaterial(struct Material materials[], int *matCount) {
    if (*matCount >= MAX_MATERIAL) {
        printf("Danh sach da day, khong the them!\n");
        return;
    }

    struct Material m;

    // Validate matId
    while (1) {
        inputString("Nhap ma vat tu: ", m.matId, sizeof(m.matId));
        if (!isUniqueId(materials, *matCount, m.matId)) {
            printf("Ma vat tu da ton tai, vui long nhap lai!\n");
            continue;
        }
        break;
    }

    // Validate name
    inputString("Nhap ten vat tu: ", m.name, sizeof(m.name));

    // Validate unit chi cho phep chu cai
    while (1) {
        inputString("Nhap don vi vat tu: ", m.unit, sizeof(m.unit));
        if (!isAlphaString(m.unit)) {
            printf("Don vi chi duoc Kg, Cai, Hop,....!\n");
            continue;
        }
        break;
    }

    // Validate qty
    m.qty = inputInt("Nhap so luong ton kho: ");

    // Status mac dinh
    m.status = 1;

    materials[*matCount] = m;
    (*matCount)++;

    printf(" Them vat tu thanh cong!\n");
}

// Cap nhat vat tu
void updateMaterial(struct Material materials[], int matCount) {
    char id[10];
    inputString("Nhap ma vat tu can cap nhat: ", id, sizeof(id));

    int found = -1;
    for (int i = 0; i < matCount; i++) {
        if (strcmp(materials[i].matId, id) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Khong tim thay vat tu voi ma %s!\n", id);
        return;
    }

    // Ten moi
    inputString("Nhap ten moi: ", materials[found].name, sizeof(materials[found].name));

    // Don vi moi chi cho phep chu cai
    while (1) {
        inputString("Nhap don vi moi: ", materials[found].unit, sizeof(materials[found].unit));
        if (!isAlphaString(materials[found].unit)) {
            printf("Don vi chi duoc Kg, Cai, Hop,....\n");
            continue;
        }
        break;
    }

    // So luong moi
    materials[found].qty = inputInt("Nhap so luong moi: ");
    materials[found].status = (materials[found].qty > 0) ? 1 : 0;

    printf(" Cap nhat thanh cong!\n");
}

// Hien thi danh sach
void listMaterials(struct Material materials[], int matCount) {
    if (matCount == 0) {
        printf("Danh sach rong!\n");
        return;
    }

    printf("\n|%-10s|%-20s|%-10s|%-10s|%-10s|\n",
           "Ma VT", "Ten", "Don Vi", "So Luong", "Trang Thai");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < matCount; i++) {
        printf("|%-10s|%-20s|%-10s|%-10d|%-10s|\n",
               materials[i].matId,
               materials[i].name,
               materials[i].unit,
               materials[i].qty,
               (materials[i].status == 1) ? "Con hang" : "Het hang");
    }
}


void showMenu() {
    printf("\n|=========== MENU ===========|\n");
    printf("|1. Them vat tu moi\n");
    printf("|2. Cap nhat vat tu\n");
    printf("|3. Quan ly trang thai (Khoa/Xoa)\n");
    printf("|4. Tra cuu vat tu\n");
    printf("|5. Danh sach vat tu\n");
    printf("|6. Sap xep danh sach\n");
    printf("|7. Giao dich (Nhap/Xuat)\n");
    printf("|8. Lich su giao dich\n");
    printf("|0. THOAT\n");
    printf("|============================|\n");
}

int main() {
    int choice;
    struct Material materials[MAX_MATERIAL];
    int matCount = 0;

    while (1) {
        showMenu();
        choice = inputInt("Chon chuc nang: ");

        switch(choice) {
            case 1:
                addMaterial(materials, &matCount);
                break;
            case 2:
                updateMaterial(materials, matCount);
                break;
            case 5:
                listMaterials(materials, matCount);
                break;
            case 0:
                printf("Thoat chuong trinh\n");
                return 0;
            default:
                printf("Lua chon khong hop le!\n");
        }
    }

    return 0;
}
