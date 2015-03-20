//���·���㷨

# define INF 0x3fffffff		//infinity,ע�Ᵽ֤����INF��Ӳ����

int n;			//�����Ŀ
int map[n+1][n+1];		//����ͨ·����Ϊ INF, ÿһ�㵽����ľ����ʼ��Ϊ 0

void initMap();			//��ʼ���ڽӾ�������ͨ·�����ʼ��Ϊ INF
 
//��Դ���· Dijkstra

void Dijkstra(int start)			//start :Դ��
{
	int prev[n+1];   //prev[i] ��ʾ�� i �����ǰһ����
	int dist[n+1];		//����
	bool isVisit[n+1];		//����Ƿ��Ѿ�������·��
	for(int i = 1; i <= n; ++i)
	{
		dist[i] = map[start][i];
		isVisit[i] = false;
		if(dist[i] == INF)
			prev[i] = 0;			//��ʾ��ʱ��ǰһ����
		else
			prev[i] = start;
	}
	dist[start] = 0;
	isVisit[start] = true;

	for(int i = 2; i <= n; ++i)
	{
		int u = start;
		int tmp = INF;

		for(int j = 1; j <= n; ++j)
		{
			if(!isVisit[j] && dist[j] < tmp)
			{
				u = j;				//u ��ʾ��ǰ�ٽӵ��о�����С�ĵ�
				tmp = dist[j];
			}
		}
		isVisit[u] = true;
		//����dist��
		for(int j = 1; j <= n; ++j)
		{
			if(!isVisit[j] && map[u][j] < INF)
			{
				int tmp = map[u][j] + d[u];
				if(tmp < d[j])
				{
					d[j] = tmp;
					prev[j] = u;
				}
			}
		}
	}
	//��dist[]��������·������Ӧ�ĵ㣬��prev[]�������Ӧ��·��
}


//Floyd�㷨��������������֮������·��
//���·���㷨����¼ÿһ�����ǰһ���㣨һ��DP������ŷ������㷨��
void Floyd(void)
{
	int floydDist[n+1][n+1][n+1]; //floydDist[k][i][j]��ʾ����ǰ k ����ʱ i �� j �ľ���
	for(int i = 1; i <= n; ++i)
	{
		for(int j = 1; j <= n; ++j)
		{
			floydDist[0][i][j]= map[i][j];
		}
	}
	for(int k = 1; k <= n; ++k)
	{
		for(int i = 1; i <= n; ++i)
		{
			for(int j = 1; j <= n; ++j)
			{
				floydDist[k][i][j] = floydDist[k-1][i][j] < (floydDist[k-1][i][k]+floydDist[k-1][k][j]) 
								   ? floydDist[k-1][i][j] : (floydDist[k-1][i][k]+floydDist[k-1][k][j]);
			}
		}
	}
	/*�������̿���ѹ��״̬�ռ䣬�ö�ά����ʵ��
	Code:
	int floydDist[n+1][n+1];   //floydDist[i][j]��ʾ�� i ���� j ����̾���
	for(int i = 1; i <= n; ++i)
	{
		for(int j = 1; j <= n; ++j)
		{
			floydDist[i][j]= map[i][j];
		}
	}
	for(int k = 1; k <= n; ++k)
	{
		for(int i = 1; i <= n; ++i)
		{
			for(int j = 1; j <= n; ++j)
			{
				floydDist[i][j] = floydDist[i][j] < (floydDist[i][k] + floydDist[k][j]) 
								? floydDist[i][j] : (floydDist[i][k] + floydDist[k][j]);
			}
		}
	}
	*/
}


//SPFA �㷨�����ڸ�Ȩ����û�и�Ȩ��·(Shortest Path Faster Algorithm)
/*
SPFA�㷨�������Ż��㷨 SLF �� LLL�� SLF��Small Label First ���ԣ���Ҫ����Ľڵ���j������Ԫ��Ϊi����dist(j)<dist(i)����j�����
�ף���������β�� LLL��Large Label Last ���ԣ������Ԫ��Ϊi������������distֵ��ƽ��ֵΪx����dist(i)>x��i���뵽��β��������
һԪ�أ�ֱ���ҵ�ĳһiʹ��dist(i)<=x����i���Խ����ɳڲ����� SLF ��ʹ�ٶ���� 15 ~ 20%��SLF + LLL �����Լ 50%�� ��ʵ�ʵ�Ӧ��
��SPFA���㷨ʱ��Ч�ʲ��Ǻ��ȶ���Ϊ�˱��������ĳ��֣�ͨ��ʹ��Ч�ʸ����ȶ���Dijkstra�㷨��
*/
//���ڽӱ�洢ͼ�����Ч��
# include <queue>
void Spfa(int start)  //start:Դ��
{
	bool isVisit[n+1];
	queue <int> Q;
	int dist[n+1];
	int prev[n+1];		//prev[i] ��ʾ�� i �����ǰһ����,���ڻ����ҳ�����·��
	int queueTimes[n+1];
	//��¼ÿһ���������еĴ���������һ���������д������� n ������ڸ�Ȩ����SPFA �޷������������
	for(int i = 1; i <= n; ++i)
	{
		isVisit[i] = false;
		dist[i] = INF;
		queueTimes[i] = 0;
		prev[i] = 0;
	}
	dist[start] = 0;
	isVisit[start] = true;

	Q.push(start);
	++queueTimes[start];
	while(!Q.empty())
	{
		int tmp = Q.front();
		for(int i = 1; i <= n; ++i)
		{
			if(map[tmp][i] != INF && dist[tmp] + map[tmp][i] < dist[i])
			{
				dist[i] = dist[tmp] + map[tmp][i];
				prev[i] = tmp;
				if(!isVisit[i])
				{
					Q.push(i);
					isVisit[i] = true;
					++queueTimes[i];

					if(queueTimes[i] > n)
						return;		//���ָ�Ȩ��
				}
			}
		}
		Q.pop();
		isVisit[tmp] = false;
	}
}//SPFA �㷨Ҳ�������ڽӱ�洢ͼ


//SPFA ��ջд�� Code:
void Spfa(int start)  //start:Դ��
{
	bool isVisit[n+1];
	int stack[n+1], top = 0;
	int dist[n+1];
	int prev[n+1];		//prev[i] ��ʾ�� i �����ǰһ����,���ڻ����ҳ�����·��
	int stackTimes[n+1];
	//��¼ÿһ�������ջ�Ĵ���������һ�������ջ�������� n ������ڸ�Ȩ��
	for(int i = 1; i <= n; ++i)
	{
		isVisit[i] = false;
		dist[i] = INF;
		stackTimes[i] = 0;
		prev[i] = 0;
	}
	dist[start] = 0;

	isVisit[start] = true;
	stack[top++] = start;
	++stackTimes[start];
	while(top > 0)
	{
		int tmp = stack[--top];
		for(int i = 1; i <= n; ++i)
		{
			if(map[tmp][i] != INF && dist[tmp] + map[tmp][i] < dist[i])
			{
				dist[i] = dist[tmp] + map[tmp][i];
				prev[i] = tmp;
				if(!isVisit[i])
				{
					stack[top++] = i;
					isVisit[i] = true;
					++stackTimes[i];

					if(stackTimes[i] > n)
						return;		//���ָ�Ȩ��
				}
			}
		}
		isVisit[tmp] = false;
	}
}
