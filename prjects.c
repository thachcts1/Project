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

// Kiem tra ID 
int isUniqueId(struct Material materials[], int matCount, char *id) {
    for (int i = 0; i < matCount; i++) {
        if (strcmp(materials[i].matId, id) == 0) {
            return 0; 
        }
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

// Kiem tra chuoi chi gom chu cai
int isAlphaString(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z'))) {
            return 0;
        }
    }
    return 1;
}


void deleteMaterial(struct Material materials[], int *matCount, int index) {
    for (int i = index; i < (*matCount) - 1; i++) {
        materials[i] = materials[i + 1];
    }
    (*matCount)--;
    printf("Xoa vat tu thanh cong!\n");
}

// Them vat tu
void addMaterial(struct Material materials[], int *matCount) {
    if (*matCount >= MAX_MATERIAL) {
        printf("Danh sach da day, khong the them!\n");
        return;
    }

    struct Material m;

    while (1) {
        inputString("Nhap ma vat tu: ", m.matId, sizeof(m.matId));
        if (!isUniqueId(materials, *matCount, m.matId)) {
            printf("Ma vat tu da ton tai, vui long nhap lai!\n");
            continue;
        }
        break;
    }

    inputString("Nhap ten vat tu: ", m.name, sizeof(m.name));

    while (1) {
        inputString("Nhap don vi vat tu: ", m.unit, sizeof(m.unit));
        if (!isAlphaString(m.unit)) {
            printf("Don vi chi duoc nhap chu, vi du: Kg, Cai, Hop...\n");
            continue;
        }
        break;
    }

    m.qty = inputInt("Nhap so luong ton kho: ");
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

        if (found == -1) {
            printf("Khong tim thay vat tu voi ma %s. Vui long nhap lai.\n", id);
        } else {
            break;
        }
    }

    inputString("Nhap ten moi: ", materials[found].name, sizeof(materials[found].name));

    while (1) {
        inputString("Nhap don vi moi: ", materials[found].unit, sizeof(materials[found].unit));
        if (!isAlphaString(materials[found].unit)) {
            printf("Don vi chi duoc nhap chu!\n");
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

        if (found == -1) {
            printf("Ma vat tu khong ton tai! Vui long nhap lai.\n");
        } else {
            break; 
        }
    }

    printf("\n+--- CHON CHUC NANG ---+\n");
    printf("1. Khoa vat tu\n");
    printf("2. Xoa vat tu\n");

    int opt;

    while (1) {
        opt = inputInt("Nhap lua chon: ");
        if (opt == 1 || opt == 2) {
            break;
        }
        printf("Lua chon khong hop le! Vui long nhap lai.\n");
    }

    switch (opt) {
        case 1:
            if (materials[found].status == 0) {
                printf("Vat tu da bi khoa truoc do va KHONG THE MO LAI!\n");
            } else {
                materials[found].status = 0;
                printf("Da KHOA vat tu vinh vien!\n");
            }
            break;

        case 2:
            deleteMaterial(materials, matCount, found);
            break;
    }
}



// Hien thi danh sach
void listMaterials(struct Material materials[], int matCount) {
    if (matCount == 0) {
        printf("Danh sach rong!\n");
        return;
    }

    printf("\n|%-10s|%-20s|%-10s|%-10s|%-10s|\n",
           "Ma VT", "Ten", "Don Vi", "So Luong", "Trang Thai");
    printf("----------------------------------------------------------------\n");

    for (int i = 0; i < matCount; i++) {
        printf("|%-10s|%-20s|%-10s|%-10d|%-10s|\n",
               materials[i].matId,
               materials[i].name,
               materials[i].unit,
               materials[i].qty,
               (materials[i].status == 1) ? "Hoat dong" : "Khoa");
    }
}

// Tim kiem
void findMaterial(struct Material materials[], int matCount) {
    if (matCount == 0) {
        printf("Danh sach rong!\n");
        return;
    }

    char keyword[50];
    inputString("Nhap ma hoac ten can tim: ", keyword, sizeof(keyword));

    int found = 0;
    printf("\n|%-10s|%-20s|%-10s|%-10s|%-10s|\n",
           "Ma Vat Tu(ID)", "Ten", "Don Vi", "So Luong", "Trang Thai");
    printf("----------------------------------------------------------------\n");

    for (int i = 0; i < matCount; i++) {
        if (strstr(materials[i].matId, keyword) ||
            strstr(materials[i].name, keyword)) {

            printf("|%-10s|%-20s|%-10s|%-10d|%-10s|\n",
                   materials[i].matId,
                   materials[i].name,
                   materials[i].unit,
                   materials[i].qty,
                   (materials[i].status == 1) ? "Hoat dong" : "Khoa");

            found = 1;
        }
    }

    if (!found) printf("Khong tim thay!\n");
}



void showMenu() {
    printf("\n+-----------------------------+\n");
    printf("|         MENU CHINH          |\n");
    printf("+-----------------------------+\n");
    printf("| 1. Them vat tu moi          |\n");
    printf("| 2. Cap nhat vat tu          |\n");
    printf("| 3. Quan ly trang thai       |\n");
    printf("| 4. Tim kiem vat tu          |\n");
    printf("| 5. Danh sach vat tu         |\n");
    printf("| 6. Sap xep danh sach        |\n");
    printf("| 7. Giao dich (Nhap/Xuat)    |\n");
    printf("| 8. Lich su giao dich        |\n");
    printf("| 0. Thoat                    |\n");
    printf("+=============================+\n");
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
            case 3:
                manageStatus(materials, &matCount);
                break;
            case 4:
                findMaterial(materials, matCount);
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
