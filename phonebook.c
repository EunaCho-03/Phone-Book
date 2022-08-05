#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

/*
This code enables the user to make a phonebook
It allows the user to input name, age. phone number, and gender
The options of this projects are add, delete(either last or specific name), show list,
number of female/male, edit name, delete phone number, swap two phone numbers, and compare ages
The user can save the list as a text file
*/


void addUser(char(*name)[10], int *age, char(*phone)[11], char *sex, int *count, int *numOfDeleted, int *isDeleted) {
    int index = *count;
    if (*count > 9) {
        if (*numOfDeleted > 0) {
            for (int i = 0; i < *count; i++) {
                if (isDeleted[i] == 1) {
                    index = i;
                    isDeleted[i] = 0;
                    (*count)--;
                    (*numOfDeleted)--;
                    break;
                }
            }
        }
        else {
            printf("There are already 10 users. Please delete one.\n");
            return;
        }
    }

    printf("Input your name: ");
    gets_s(name[index], sizeof(name[index]));

    printf("Input your age: ");
    scanf_s("%d%*c", &age[index], sizeof(age[index]));

    printf("Input your phone number(without -): ");
    gets_s(phone[index], sizeof(phone[index]));

    printf("Input your sex (m or f): ");
    scanf_s("%c", &sex[index], sizeof(sex[index]));

}

void showList(char(*name)[10], int *age, char(*phone)[11], char(*sex), int count, int *isDeleted) {

    printf("Show user list\n");
    printf("=============================================================\n");
    for (int i = 0; i <= count; i++) {
        if (isDeleted[i] != 1)
            printf("%d\t name: %10s,\t age: %10d, \t , sex: %c  pNumber: %11s\n", i + 1, name[i], age[i], sex[i], phone[i]);
    }
    printf("=============================================================\n");
}

void genderList(char(*sex), char(*name)[10], int count) {
    char gender = 0;

    printf("Which gender would you like to see: ");
    scanf_s("%c", &gender);

    for (int i = 0; i <= count; i++) {
        if (gender == sex[i]) {
            printf("%s: %s\n", gender == 'm' ? "male" : "female", name[i]);
        }
    }

}

void mfNumber(char(*sex), int count) {
    int maleCnt = 0, femaleCnt = 0;

    for (int i = 0; i <= count; i++) {
        if (sex[i] == 'm') {
            maleCnt++;
        }
        else if (sex[i] == 'f') {
            femaleCnt++;
        }
    }
    printf("male: %2d\nfemale: %2d\n", maleCnt, femaleCnt);

}

int deleteUser(char(*name)[10], int count, int *age, char(*phone)[11], char(*sex), int num, int *isDeleted, int *numOfDeleted) {
    int ret = 0;
    char find[10];
    printf("Type a name you are trying to delete: ");
    scanf_s("%s", &find, sizeof(find));

    for (int i = 0; i <= count; i++) {
        if (strcmp(find, name[i]) == 0) {
            printf("We will delete %s\n", name[i]);
            isDeleted[i] = 1;
            (*numOfDeleted)++;
            ret = 1;
            break;
        }
        else {
            if (i == count) {
                printf("We don't have the name\n");
                ret = 0;
                break;
            }
        }
    }

    return ret;
}


void editUser(char(*name)[10], int count) {
    char change[10];
    char edit[10];
    char temporary[10];
    printf("Type a name you are trying to edit: ");
    scanf_s("%s", &change, sizeof(change));

    printf("How do you want to change it: ");
    scanf_s("%s", &edit, sizeof(edit));

    for (int i = 0; i <= count; i++) {
        if (strcmp(change, name[i]) == 0) {
            printf("We will edit %s\n", name[i]);
            strcpy(name[i], edit);
        }
    }
}


void swapNumber(char(*phone)[11], int count) {
    char firstNum[11];
    char secondNum[11];

    printf("Type first number you wish to swap: ");
    scanf_s("%s", &firstNum, sizeof(firstNum));

    printf("Type second number you wish to swap: ");
    scanf_s("%s", &secondNum, sizeof(secondNum));

    for (int i = 0; i <= count; i++) {
        if (strcmp(firstNum, phone[i]) == 0) {
            strcpy(phone[i], secondNum);
        }
        else if (strcmp(secondNum, phone[i]) == 0) {
            strcpy(phone[i], firstNum);
        }
    }
}


void deleteNumber(int count, char(*phone)[11]) {
    char find[10];
    printf("Type a number you are trying to delete: ");
    scanf_s("%s", &find, sizeof(find));

    for (int i = 0; i <= count; i++) {
        if (strcmp(find, phone[i]) == 0) {
            printf("We will delete %s\n", phone[i]);
            strcpy(phone[i], "Deleted");
        }
    }
}

void compare(int *age, char(*name)[10], int count) {
    int minimum = 0;
    printf("Type a minimum number of age: ");
    scanf_s("%d%*c", &minimum, sizeof(minimum));
    printf("People older than %d: \n", minimum);

    for (int i = 0; i <= count; i++) {
        if (age[i] > minimum) {
            printf("%s\n", name[i]);
        }
    }
}

void saveList(char(*name)[10], int *age, char(*phone)[11], char(*sex), int count, int *isDeleted) {
    FILE *fp = fopen("Phone Book.txt", "w");
    for (int i = 0; i <= count; i++) {
        fprintf(fp, "%d\t name: %10s,\t age: %10d, \t , sex: %c  pNumber: %11s\n", i + 1, name[i], age[i], sex[i], phone[i]);
    }
    fclose(fp);
}



#define MAX 10

int main() {

    int cmd = 0;
    char name[MAX][10];
    int age[MAX];
    char phone[MAX][11];
    char sex[MAX];
    int count = -1;
    int maleCnt = 0;
    int femaleCnt = 0;
    int num = 0;
    char gender[10];
    int isDeleted[MAX] = { 0 };
    char find[10];
    int numOfDeleted = 0;


    while (1) {
        printf("1: 추가, 2: 마지막 사람 삭제, 3: 리스트 보여주기, 4: 성별 리스트 5: 성별 숫자 6: 특정이름 삭제하기 7:특정이름 수정하기 8:전화번호 두개 바꾸기 9:특정번호 삭제하기 10:나이 비교 11:끝내기 12:전화번호부 파일로 저장하기\n");
        scanf_s("%d%*c", &cmd);

        switch (cmd)
        {
        case 1:
            count++;
            addUser(name, age, phone, sex, &count, &numOfDeleted, isDeleted);
            showList(name, age, phone, sex, count, isDeleted);
            break;

        case 2:
            if (count > 0) {
                isDeleted[count] = 1;
                numOfDeleted++;
                showList(name, age, phone, sex, count, isDeleted);
            }
            else {
                count = -1;
                printf("There is no data\n");
            }

            break;
        case 3:
            showList(name, age, phone, sex, count, isDeleted);
            break;

        case 4:
            genderList(sex, name, count);
            break;

        case 5:
            mfNumber(sex, count, maleCnt, femaleCnt);
            break;
        case 6:
            deleteUser(name, count, age, phone, sex, num, isDeleted, &numOfDeleted);
            showList(name, age, phone, sex, count, isDeleted);
            break;
        case 7:
            editUser(name, count);
            showList(name, age, phone, sex, count, isDeleted);
            break;
        case 8:
            swapNumber(phone, count);
            showList(name, age, phone, sex, count, isDeleted);
            break;
        case 9:
            deleteNumber(count, phone);
            showList(name, age, phone, sex, count, isDeleted);
            break;
        case 10:
            compare(age, name, count);
            break;
        case 11:
            exit(1);
            break;
        case 12:
            saveList(name, age, phone, sex, count, isDeleted);
            break;

        default:
            printf("Wrong number. Plz input 1~7");
            break;
        }
    }
}


