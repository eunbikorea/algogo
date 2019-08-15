#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M, K, ans = 987654321;
int map[51][51];//1부터 시작
int cmap[51][51];
bool chk[7] = { 0 };
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };
//하우상좌

struct Rotate {
	int r, c, s;
};
vector <Rotate> v;
vector <int> index;


void Solve() {
	do {
		vector <int> select;
		for (int i = 0; i < index.size(); i++) {
			select.push_back(index[i]);
		}
		//cout << select[0] << select[1] << endl;
		//회전
		for (int i = 1; i <= N; i++)for (int j = 1; j <= M; j++) {
			cmap[i][j] = map[i][j];
		}
		for (int i = 0; i < select.size(); i++) {
			int s = v[select[i]].s;
			for (int z = 1; z <= s; z++) {
				int x = v[select[i]].r - z;
				int y = v[select[i]].c - z;
				int endX = x;
				int endY = y + 1;
				int nx = x;
				int ny = y;
				int tmp = map[x][y];
				for (int i = 0; i < 4; i++) {
					for (int cnt = 0; cnt < z * 2; cnt++) {
						nx += dx[i];
						ny += dy[i];

						map[x][y] = map[nx][ny];
						x = nx;
						y = ny;
					}
				}
				map[endX][endY] = tmp;
			}
		}

		//점수계산
		int result = 987654321;
		for (int i = 1; i <= N; i++) {
			int total = 0;
			for (int j = 1; j <= M; j++) {
				total += map[i][j];
			}
			if (result > total) result = total;
		}
		if (ans > result) ans = result;

		//맵복구
		for (int i = 1; i <= N; i++)for (int j = 1; j <= M; j++) {
			map[i][j] = cmap[i][j];
		}
	} while (next_permutation(index.begin(), index.end()));
}

int main() {
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++)for (int j = 1; j <= M; j++) {
		cin >> map[i][j];
	}
	for (int k = 0; k < K; k++) {
		int r, c, s;
		cin >> r >> c >> s;
		v.push_back({ r,c,s });
		index.push_back(k);
	}
	Solve();

	cout << ans;
	return 0;
}