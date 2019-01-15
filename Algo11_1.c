#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

int matrix_chain_order(int *p);
void print_optimal_parens(int **S, int i, int j);

int m; //행렬의 크기

int main(void) {
	FILE* f; // 파일
	int startTime = 0, endTime = 0; //시간 측정을 위한 변수
	float gap; //시간 측정을 위한 변수
	int *p; //곱들의 값을 담은 변수
	int cost; //비용 출력을 위한 변수

	f = fopen("simple_mat2.txt", "rt"); //파일 열기

	if (f == NULL) {
		printf("파일이 열리지 않습니다.");
		exit(1);
	}

	if (feof(f) == 0) { //파일의 첫번째 값만 읽어온다
		fscanf(f, "%d", &m);
	}

	/*m+1만큼 크기 할당*/
	p = (int*)malloc(sizeof(int)*(m+1));

	/*파일 읽어와서 p배열 생성*/
	for (int i = 1; !feof(f); i++) {
		for (int j = 0; j < m + 1; j++) {
			fscanf(f, "%d", &p[j]);
		}
	}

	startTime = clock();

	cost = matrix_chain_order(p); //matrix_chain_order함수 실행
	printf("cost : %d\n", cost); //cost값 출력

	endTime = clock();
	gap = (float)(endTime - startTime) / (CLOCKS_PER_SEC);

	printf("측정 시간 : %f\n", gap);

	fclose(f); //파일 닫기

	system("pause"); // 테스트 보기 위해.
}

int matrix_chain_order(int *p) {
	int **M;
	int **S;
	int l, j, i, k; //반복문을 위한 변수
	int temp;

	/*가로,세로 각각 m만큼의 크기를 가진 2차원 배열 생성*/
	M = (int**)malloc(sizeof(int*)*m);
	S = (int**)malloc(sizeof(int*)*m);
	for (i = 0; i < m; i++) {
		M[i] = (int*)malloc(sizeof(int) * m);
		S[i] = (int*)malloc(sizeof(int) * m);
	}
	
	/*대각선을 0으로 초기화*/
	for (i = 0; i < m;i++) {
		M[i][i] = 0;
	}

	for (l = 2; l <= m;l++) { //m-1번 반복
		for (i =0; i < m - l + 1; i++) { //m-l번 반복
			j = i + l -1; 
			M[i][j] = 99999; //임의의 무한대 값으로 설정
			for (k=i; k <= j - 1; k++) {
				//각 인수를 구하는 곱셈 횟수 ,+ 두 인수를 곱하는데 필요한 곱셈의 횟수
				temp = M[i][k] + M[k + 1][j] + p[i] * p[k+1] * p[j+1];
				if (temp < M[i][j]) {
					M[i][j] = temp; //곱셈 횟수 저장
					S[i][j] = k; //최소값을 주는 k의 위치 저장
				}
			}
		}
	}

	print_optimal_parens(S,0,m-1); //print_optimal_parens호출
	printf("\n");

	return M[0][m-1]; //cost값 return

	/*메모리 free*/
	for (int i = 0; i < (m); i++) {
		free(M[i]);
		free(S[i]);
	}
	free(M);
	free(S);
}

/*optimal solution 출력*/
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