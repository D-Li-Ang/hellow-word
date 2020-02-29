#include<iostream>
#include<algorithm>
#include<stack>
using namespace std;
struct dir{
	int x, y;
};
int n = 64;
dir di[8];
int d[8][2] = { 1,2,   1,-2,   -1,2,   -1,-2,    2,1,    2,-1,     -2,1,    -2,-1 };
int visit[8][8];
struct node {
	int x;
	int y;
	int d = 0;         //������ǴӸý�������ڼ����ٽ�λ��;
	int out_way() {
		int k = 0;
		for (int i = 0; i < 8; i++)
		{
			int X = this->x + di[i].x;
			int Y = this->y + di[i].y;
			if (!(X < 0 || X >= 8 || Y < 0 || Y >= 8 || visit[X][Y]== 1))
				k++;
		}
		return k;
	}
};
stack<node> stac;             //��Ž��
node  no;                     //��¼��ǰ���
node map[8][8];
bool cmp(dir a,dir b) {
	//��ʼ���±�
	int m = -1, n = -1;
	//����±겻�����������λ���ѷ���   ��С��m;n;
	if (no.x + a.x < 0 || no.x + a.x >= 8 || no.y + a.y < 0 || no.y + a.y >= 8 || visit[no.x + a.x][no.y + a.y] == 1)
		m = 0;
	if (no.x + b.x < 0 || no.x + b.x >= 8 || no.y + b.y < 0 || no.y + b.y >= 8 || visit[no.x + b.x][no.y + b.y] == 1)
		n = 0;
	//����±�δ����С������m,n��ʼ��Ϊ���ڽӵ��·������
	if (m != 0)
		m = map[no.x + a.x][no.y + a.y].out_way();
	if (n != 0)
		n = map[no.x + b.x][no.y + b.y].out_way();
	//ruturn m<n ��С�������� ���������������ӽڵ���Է��ʵ�����ǰ�� �������ճ�·���ٴ�С������� 
	return m < n;
}
void def() {
	while (stac.size() != 64)
	{
		if (stac.size() == 0)
		{
			cout << "�޽��" << endl;
			break;
		}
		//Ӧ�÷��ʵڼ������ڽӵ�
		int i = map[stac.top().x][stac.top().y].d;                 
		//����˸��ڽӵ�ȫ��������  ���ý���ʼ������ջ 
		if (i >= 8)                                                
		{
			visit[stac.top().x][stac.top().y]= 0;
			map[stac.top().x][stac.top().y].d = 0;
			stac.pop();
			continue;
		}
		//�õ���ǰջ����� ������
		no = stac.top();      
		sort(di, di + 8,cmp);
		//�������������ڽӵ� continue��
		int X = stac.top().x + di[i].x;
		int Y = stac.top().y + di[i].y;
		if (X < 0 || X >= 8 || Y < 0 || Y >= 8 || visit[X][Y]== 1)
		{
			map[stac.top().x][stac.top().y].d++;
			continue;
		}
		//��ջǰջ��Ԫ�����ٽ��ݽ�һ
		//cout << map[X][Y].x << ' ' << map[X][Y].y << ' '<<stac.size()<<endl;
		map[stac.top().x][stac.top().y].d++;
		//��������  ��ջ
		visit[X][Y]= 1;
		stac.push(map[X][Y]);
	}
}
int main() {
	//�������ά���鸳ֵ������ṹ��һά���� 
	for (int i = 0; i < 8; i++)
	{
		di[i].x = d[i][0];
		di[i].y = d[i][1];
	}

	int x, y;
	cin >> x >> y;
	//���̳�ʼ��
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			map[i][j].x = i;
			map[i][j].y = j;
		}
	//��һ���ڵ�ѹջ
	visit[x-1][y-1]= 1;
	stac.push(map[x-1][y-1]);

	def();
	//������ջ˳�򽫸��½�����a��ֵ  ���a;
	int a[8][8];
	while (stac.empty() == 0)
	{
		a[stac.top().x][stac.top().y] = n;
		n--;
		stac.pop();
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
			cout << a[i][j] << '\t';
		cout << endl;
	}
	system("pause");
	return 0;
}