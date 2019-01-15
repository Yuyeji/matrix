#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

int matrix_chain_order(int *p);
void print_optimal_parens(int **S, int i, int j);

int m; //����� ũ��

int main(void) {
	FILE* f; // ����
	int startTime = 0, endTime = 0; //�ð� ������ ���� ����
	float gap; //�ð� ������ ���� ����
	int *p; //������ ���� ���� ����
	int cost; //��� ����� ���� ����

	f = fopen("simple_mat2.txt", "rt"); //���� ����

	if (f == NULL) {
		printf("������ ������ �ʽ��ϴ�.");
		exit(1);
	}

	if (feof(f) == 0) { //������ ù��° ���� �о�´�
		fscanf(f, "%d", &m);
	}

	/*m+1��ŭ ũ�� �Ҵ�*/
	p = (int*)malloc(sizeof(int)*(m+1));

	/*���� �о�ͼ� p�迭 ����*/
	for (int i = 1; !feof(f); i++) {
		for (int j = 0; j < m + 1; j++) {
			fscanf(f, "%d", &p[j]);
		}
	}

	startTime = clock();

	cost = matrix_chain_order(p); //matrix_chain_order�Լ� ����
	printf("cost : %d\n", cost); //cost�� ���

	endTime = clock();
	gap = (float)(endTime - startTime) / (CLOCKS_PER_SEC);

	printf("���� �ð� : %f\n", gap);

	fclose(f); //���� �ݱ�

	system("pause"); // �׽�Ʈ ���� ����.
}

int matrix_chain_order(int *p) {
	int **M;
	int **S;
	int l, j, i, k; //�ݺ����� ���� ����
	int temp;

	/*����,���� ���� m��ŭ�� ũ�⸦ ���� 2���� �迭 ����*/
	M = (int**)malloc(sizeof(int*)*m);
	S = (int**)malloc(sizeof(int*)*m);
	for (i = 0; i < m; i++) {
		M[i] = (int*)malloc(sizeof(int) * m);
		S[i] = (int*)malloc(sizeof(int) * m);
	}
	
	/*�밢���� 0���� �ʱ�ȭ*/
	for (i = 0; i < m;i++) {
		M[i][i] = 0;
	}

	for (l = 2; l <= m;l++) { //m-1�� �ݺ�
		for (i =0; i < m - l + 1; i++) { //m-l�� �ݺ�
			j = i + l -1; 
			M[i][j] = 99999; //������ ���Ѵ� ������ ����
			for (k=i; k <= j - 1; k++) {
				//�� �μ��� ���ϴ� ���� Ƚ�� ,+ �� �μ��� ���ϴµ� �ʿ��� ������ Ƚ��
				temp = M[i][k] + M[k + 1][j] + p[i] * p[k+1] * p[j+1];
				if (temp < M[i][j]) {
					M[i][j] = temp; //���� Ƚ�� ����
					S[i][j] = k; //�ּҰ��� �ִ� k�� ��ġ ����
				}
			}
		}
	}

	print_optimal_parens(S,0,m-1); //print_optimal_parensȣ��
	printf("\n");

	return M[0][m-1]; //cost�� return

	/*�޸� free*/
	for (int i = 0; i < (m); i++) {
		free(M[i]);
		free(S[i]);
	}
	free(M);
	free(S);
}

/*optimal solution ���*/
void print_optimal_parens(int **S,int i, int j) {
	if (i == j) {
		printf("%d", i+1);
	}
	else {
		printf("(");
		print_optimal_parens(S, i, S[i][j]);
		print_optimal_parens(S, S[i][j] + 1, j);
		printf(")");
	}
}