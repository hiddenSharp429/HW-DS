/*
閸ョ偞鏋冮弰顖涘瘹濮濓綀顕伴崣宥堫嚢閸у洨娴夐崥宀€娈戠€涙顑佹惔蹇撳灙閿涘苯顩ч垾娓乥ba閳ユ繂鎷伴垾娓乥dba閳ユ繂�5�7庨弰顖氭礀閺傚浄绱�?
娴ｅ棌鈧笀ood閳ユ繀绗夐弰顖氭礀閺傚洢鈧倽鐦崘娆庣娑擃亞鐣诲▔鏇炲灲鐎规氨绮扮€规氨娈戠€涙顑侀崥鎴﹀櫤閺勵垰鎯佹稉鍝勬礀閺傚洢鈧拷
(閹绘劗銇氶敍姘殺娑撯偓閸楀﹤鐡х粭锕€鍙嗛弽锟�)
*/

#include <stdio.h>
#include <string.h>
#define max 20
struct Stack {
	int base;
	int top;
};

bool IsPalindrome(char stack[], Stack S, char a[], int length) {
	int j;
	if (length % 2 == 0) j = length / 2;
	else j = (length / 2) + 1;
	for (int i = (S.top - 1); i > 0; i--) {
		if (stack[i] == a[j]) {
			j = j + 1;
		}
		else return false;
	}
	return true;
}

int StringLength(char a[]) {
	int length = 0;
	for (int i = 0; i < max; i++) {
		if (a[i] != '\0') {
			length++;
		}
		else break;
	}
	return length;
}

void InitStack(Stack& S) {
	S.base = 0;
	S.top = 0;
}

void PushStringInStack(char a[], Stack &S, int length, char stack[]) {
	if (length % 2 == 0) {
		for (int i = 0; i < length / 2; i++)
		{
			stack[i] = a[i];
			S.top = i + 1;
		}
	}
	else {
		for (int i = 0; i < (length - 1) / 2; i++) {
			stack[i] = a[i];
			S.top = i + 1;
		}
	}

}

int main() {
	Stack A;
	char stack[max];
	InitStack(A);
	char c[max];
	scanf("%s", c);
	int length = StringLength(c);
	PushStringInStack(c, A, length, stack);
	if (IsPalindrome(stack, A, c, length)) printf("璇ュ瓧绗﹀簭鍒椾负鍥炴枃瀛楃涓�?");
	else printf("涓嶄负鍥炴枃瀛楃涓�?");
	return 0;
}
