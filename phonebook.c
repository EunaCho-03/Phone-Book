#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>



void addUser(char (*name)[10], int *age, char (*phone)[11], char *sex, int index) {
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
			printf("name: %10s,\t age: %10d, \t , sex: %c  pNumber: %11s\n", name[i], age[i], sex[i], phone[i]);
	}
	printf("=============================================================\n");
}

void genderList(char (*sex), char(*name)[10], int count) {
	char gender = 0;

	printf("Which gender would you like to see: ");
	scanf_s("%c", &gender);

	for (int i = 0; i < count; i++) {
		if (gender == sex[i]) {
			printf("%s: %s\n", gender=='m'?"male":"female", name[i]);
		}
	}
}

void mfNumber(char(*sex), int count, int maleCnt, int femaleCnt)  { 
	for (int i = 0; i <= count; i++){
		if (sex[i] == 'm') {
			maleCnt++;
		}
		else if (sex[i] == 'f') {
			femaleCnt++;
		}
	}
	printf("male: %2d\nfemale: %2d\n", maleCnt, femaleCnt);
}

int deleteUser(char(*name)[10], int count, int *age, char(*phone)[11], char(*sex), int num, int *isDeleted) {
	int ret = 0;
	char find[10];
	printf("Type a name you are trying to delete: ");
	scanf_s("%s", &find, sizeof(find));

	for (int i = 0; i <= count; i++) {
		if (strcmp(find, name[i]) == 0) {
			printf("We will delete %s\n", name[i]);
			isDeleted[i] = 1;
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

#define MAX 100

int main() {

	int cmd = 0;
	char name[MAX][10];
	int nameSize;
	int age[MAX];
	char phone[MAX][11];
	char sex[MAX];
	int count = -1;
	int maleCnt = 0;
	int femaleCnt = 0;
	char find[10];
	int num = 0;
	char edit[10];
	char gender[10];
	int isDeleted[MAX] = { 0 };

while (1) {
		printf("1: 추가, 2: 마지막 사람 삭제, 3: 리스트 보여주기, 4: 성별 리스트 5: 성별 숫자 6: 특정이름 삭제하기 7:특정이름 수정하기 8:끝내기\n");
		scanf_s("%d%*c", &cmd);

		switch (cmd)
		{
		case 1:
			count++;
			addUser(name, age, phone, sex, count);
showList(name, age, phone, sex, count, isDeleted);
			break;

		case 2:
			if (count > 0) {
				isDeleted[count] = 1;
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
			count++;
			mfNumber(sex, count, maleCnt, femaleCnt);
			break;
		case 6:
			int tem = deleteUser(name, count, age, phone, sex, num, isDeleted);
			showList(name, age, phone, sex, count, isDeleted);
			break;
		case 7:
			count++;
			editUser(name, find, count, edit);
			break;
		case 8:
			exit(1);
			break;

		default:
			printf("Wrong number. Plz input 1~7");
			break;
		}
	}
}
