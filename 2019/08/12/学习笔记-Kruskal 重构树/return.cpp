#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
#define r register
#define inf 2147483647
inline bool isd(r char ch) {
	return ch<='9'&&ch>='0';
}
template<class temp>
inline temp F() {
	r temp x=0;
	r bool bo=0;
	r char ch=getchar();
	while(ch!='-'&&!isd(ch))
		ch=getchar();
	(ch=='-')&&(bo=1,ch=getchar());
	while(isd(ch))
		x=(x<<1)+(x<<3)+(ch^'0'),ch=getchar();
	bo&&(x=-x);
	return x;
}
class Graph {
	public:
		struct Edge {
			int to,dis;
			Edge* nxt;
		};
		typedef Edge* Node;
		Node Nul,*Head;
		int Size;
		void Resize(r int siz) {
			Head=new Node[siz+1];
			for(r int i=0;i<=siz;++i)
				Head[i]=Nul;
			Size=siz;
		}
		void Add(r int f,r int t,r int d) {
			Node x=new Edge();
			x->to=t;
			x->dis=d;
			x->nxt=Head[f],Head[f]=x;
		}
		void Clear() {
			Node x,y;
			for(r int i=0;i<=Size;++i) {
				x=Head[i];
				while(x!=Nul) {
					y=x->nxt;
					delete x;
					x=y;
				}
			}
			delete []Head;
		}
}P,T;
int cnt;
struct Edge {
	int f,t,dis;
}E[800001];
inline bool operator<(r Edge a,r Edge b) {
	return a.dis>b.dis;
}
void Add(r int f,r int t,r int dis) {
	E[++cnt]=(Edge){f,t,dis};
}
struct Node {
	long long dis;
	int nm;
	Node(r long long d,r int i) {
		dis=d,nm=i;
	}
};
inline bool operator<(r Node a,r Node b) {
	if(a.dis!=b.dis)
		return a.dis>b.dis;
	return a.nm>b.nm;
}
long long dis[800001];
int bin[21],p[800001],val[800001],f[800001][20];
int dep[800001];
int n,m;
int tot;
int Find(r int x) {
	return x==p[x]?x:p[x]=Find(p[x]);
}
void Dijkstra() {
	memset(dis,63,sizeof dis);
	std::priority_queue<Node>q;
	dis[1]=0;
	q.push(Node(0,1));
	while(!q.empty())
	{
		r Node t=q.top();
		q.pop();
		if(dis[t.nm]!=t.dis)
			continue;
		for(r Graph::Node j=P.Head[t.nm];j!=P.Nul;j=j->nxt)
			if(j->dis+dis[t.nm]<dis[j->to]) {
				dis[j->to]=j->dis+dis[t.nm];
        		q.push(Node(dis[j->to],j->to));
            }
	}
}
void Kruskal() {
	std::sort(E+1,E+m+1);
	tot=n;
	for(r int i=1;i<=m;++i) {
		r int x=Find(E[i].f),y=Find(E[i].t);
		if(x!=y) {
			p[x]=p[y]=f[x][0]=f[y][0]=++tot;
			T.Add(tot,x,0),T.Add(tot,y,0);
			val[tot]=E[i].dis;
			if(tot==(n<<1)-1)
				break;
		}
	}
}
void dfs(r int x) {
	for(r int i=1;i<=19;++i)
		if(dep[x]>=bin[i])
			f[x][i]=f[f[x][i-1]][i-1];
		else
			break;
	for(r Graph::Node j=T.Head[x];j!=T.Nul;j=j->nxt)
		dep[j->to]=dep[x]+1,dfs(j->to),dis[x]=std::min(dis[x],dis[j->to]);
}
int Calc(r int x,r int v)
{
	for(r int i=19;i>=0;--i)
		if(dep[x]>=bin[i]&&val[f[x][i]]>v)
			x=f[x][i];
	return x;
}
void Main() {
	cnt=0;
	memset(dep,0,sizeof dep);
	memset(f,0,sizeof f);
	n=F<int>(),m=F<int>();
	P.Resize(n),T.Resize(n<<1);
	r int x,y,l,a;
	for(r int i=1,ed=(n<<1);i<=ed;++i)
		p[i]=i;
	for(r int i=1;i<=n;++i)
		val[i]=inf;
	for(r int i=1;i<=m;++i) {
		x=F<int>(),y=F<int>(),l=F<int>(),a=F<int>();
		Add(x,y,a),P.Add(x,y,l),P.Add(y,x,l);
	}
	Dijkstra();
	Kruskal();
	r int o;
	dep[o=Find(1)]=0;
	dfs(o);
	r int Q=F<int>(),k=F<int>(),s=F<int>(),v,p;
	r long long ans=0;
	while(Q--)
	{
		v=F<int>(),p=F<int>();
		v=(v+k*ans-1)%n+1;
		p=(p+k*ans)%(s+1);
		r int t=Calc(v,p);
		printf("%lld\n",ans=dis[t]);
	}
	P.Clear(),T.Clear();
}
int main() {
	freopen("return.in","r",stdin);
	freopen("return.out","w",stdout);
	bin[0]=1;
	for(r int i=1;i<20;++i)
		bin[i]=bin[i-1]<<1;
	r int T=F<int>();
	while(T--)
		Main();
	return 0;
}

