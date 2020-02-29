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
	int d = 0;         //用来标记从该结点该跳向第几个临近位置;
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
stack<node> stac;             //存放结点
node  no;                     //记录当前结点
node map[8][8];
bool cmp(dir a,dir b) {
	//初始化下标
	int m = -1, n = -1;
	//如果下标不符合条件或该位置已访问   最小化m;n;
	if (no.x + a.x < 0 || no.x + a.x >= 8 || no.y + a.y < 0 || no.y + a.y >= 8 || visit[no.x + a.x][no.y + a.y] == 1)
		m = 0;
	if (no.x + b.x < 0 || no.x + b.x >= 8 || no.y + b.y < 0 || no.y + b.y >= 8 || visit[no.x + b.x][no.y + b.y] == 1)
		n = 0;
	//如果下标未被最小化，将m,n初始化为子邻接点出路个数；
	if (m != 0)
		m = map[no.x + a.x][no.y + a.y].out_way();
	if (n != 0)
		n = map[no.x + b.x][no.y + b.y].out_way();
	//ruturn m<n 从小到大排序 （不符合条件的子节点或以访问的排在前面 其他按照出路多少从小大大排序） 
	return m < n;
}
void def() {
	while (stac.size() != 64)
	{
		if (stac.size() == 0)
		{
			cout << "无结果" << endl;
			break;
		}
		//应该访问第几个子邻接点
		int i = map[stac.top().x][stac.top().y].d;                 
		//如果八个邻接点全部访问完  将该结点初始化并出栈 
		if (i >= 8)                                                
		{
			visit[stac.top().x][stac.top().y]= 0;
			map[stac.top().x][stac.top().y].d = 0;
			stac.pop();
			continue;
		}
		//得到当前栈顶结点 排序用
		no = stac.top();      
		sort(di, di + 8,cmp);
		//不符合条件的邻接点 continue；
		int X = stac.top().x + di[i].x;
		int Y = stac.top().y + di[i].y;
		if (X < 0 || X >= 8 || Y < 0 || Y >= 8 || visit[X][Y]== 1)
		{
			map[stac.top().x][stac.top().y].d++;
			continue;
		}
		//入栈前栈顶元素子临界点递进一
		//cout << map[X][Y].x << ' ' << map[X][Y].y << ' '<<stac.size()<<endl;
		map[stac.top().x][stac.top().y].d++;
		//符合条件  入栈
		visit[X][Y]= 1;
		stac.push(map[X][Y]);
	}
}
int main() {
	//将方向二维数组赋值给方向结构体一维数组 
	for (int i = 0; i < 8; i++)
	{
		di[i].x = d[i][0];
		di[i].y = d[i][1];
	}

	int x, y;
	cin >> x >> y;
	//棋盘初始化
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			map[i][j].x = i;
			map[i][j].y = j;
		}
	//第一个节点压栈
	visit[x-1][y-1]= 1;
	stac.push(map[x-1][y-1]);

	def();
	//依靠出栈顺序将给新建数组a赋值  输出a;
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
