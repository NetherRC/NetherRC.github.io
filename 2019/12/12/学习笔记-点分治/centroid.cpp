#include<cstdio>
#include<queue>
#include<algorithm>
using std::priority_queue;
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
template<class temp>
class Heap {
	private:
		priority_queue<temp>A,B;
		void maintain() {
			while(!B.empty()&&A.top()==B.top())
				A.pop(),B.pop();
		}
	public:
		temp top() {
			return A.top();
		}
		void pop() {
			A.pop();
			maintain();
		}
		void erase(temp x) {
			B.push(x);
			maintain();
		}
		void push(temp x) {
			A.push(x);
		}
		temp second() {
			temp t=A.top(),ret;
			pop();
			ret=A.top();
			A.push(t);
			return ret; 
		} 
		unsigned size() {
			return A.size()-B.size();
		}
};
Heap<int>d[100001],ch[100001],ans;
class Graph {
	public:
		struct Edge {
			int to;
			Edge* nxt;
		};
		typedef Edge* Node;
		Node Nul,*Head;
		int Size;
		void Resize(int siz) {
			Head=new Node[siz+1];
			for(r int i=0;i<=siz;++i)
				Head[i]=Nul;
		} 
		void Add(int f,int t) {
			Node x=new Edge();
			x->to=t;
			x->nxt=Head[f],Head[f]=x;
		}
}P;
namespace Work1 {
	int siz[100001];
	int p[100001];
	int udf[100001];
	int dfn[100001];
	int dep[100001];
	int top[100001];
	int tot;
	int son[100001];
	void dfs(r int x) {
		siz[x]=1;
		for(r Graph::Node j=P.Head[x];j!=P.Nul;j=j->nxt)
			if(j->to!=p[x]) {
				p[j->to]=x;
				dep[j->to]=dep[x]+1;
				dfs(j->to);
				siz[x]+=siz[j->to];
				if(siz[son[x]]<siz[j->to])
					son[x]=j->to;
			} 
	}
	void dfs(r int x,r int tp) {
		udf[dfn[x]=++tot]=x;
		top[x]=tp;
		if(son[x])
			dfs(son[x],tp); 
		for(r Graph::Node j=P.Head[x];j!=P.Nul;j=j->nxt)
			if(j->to!=p[x]&&j->to!=son[x])
				dfs(j->to,j->to);
	}
	int LCA(r int x,r int y) {
		while(top[x]!=top[y]) {
			if(dep[top[x]]>dep[top[y]])
				std::swap(x,y);
			y=p[top[y]];
		}
		return dfn[x]<dfn[y]?x:y;
	}
	inline int dist(r int x,r int y) {
		return dep[x]+dep[y]-(dep[LCA(x,y)]<<1);
	} 
	void Init() {
		dfs(1);
		dfs(1,1);
	}
}
namespace Work2 {
	int rt,sum;
	int siz[100001];
	int mx[100001];
	int dep[100001];
	bool vis[100001];
	int p[100001];
	void GetRoot(r int x,r int fa) {
		mx[x]=0;
		siz[x]=1;
		for(r Graph::Node j=P.Head[x];j!=P.Nul;j=j->nxt)
			if(j->to!=fa&&!vis[j->to]) {
				GetRoot(j->to,x);
				siz[x]+=siz[j->to];
				mx[x]=std::max(mx[x],siz[j->to]);
			}
		mx[x]=std::max(mx[x],sum-siz[x]);
		if(mx[rt]>mx[x])
			rt=x;
	}
	void dfs(r int x,r int f,r int d,Heap<int>&y) {
		y.push(d);
		for(r Graph::Node j=P.Head[x];j!=P.Nul;j=j->nxt)
			if(j->to!=f&&!vis[j->to])
				dfs(j->to,x,d+1,y);
	}
	void Build(r int x) {
		vis[x]=1;
		for(r Graph::Node j=P.Head[x];j!=P.Nul;j=j->nxt)
			if(!vis[j->to]) {
				sum=siz[j->to];
				rt=0;
				GetRoot(j->to,0);
				GetRoot(rt,0);
				dfs(j->to,0,1,d[rt]);
				ch[x].push(d[rt].top());
				dep[rt]=dep[x]+1;
				p[rt]=x;
				Build(rt);
			}
		ch[x].push(0);
		if(ch[x].size()>=2)
			ans.push(ch[x].top()+ch[x].second());
		else
			if(ch[x].size())
				ans.push(ch[x].top());
	}
	void Init(r int n) {
		sum=n;
		rt=0;
		mx[0]=inf;
		GetRoot(1,0);
		GetRoot(rt,0);
		Build(rt);
	}
}
char c[11];
bool col[100001];
int dis[100001][21];
using Work2::dep;
using Work2::p;
int main() {
	r int n=F<int>();
	P.Resize(n);
	r int x,y;
	for(r int i=1;i<n;++i) {
		x=F<int>(),y=F<int>();
		P.Add(x,y),P.Add(y,x);
	} 
	Work1::Init();
	Work2::Init(n);
	for(r int i=1;i<=n;++i)
		for(r int j=i;j;j=p[j])
			dis[i][dep[i]-dep[j]]=Work1::dist(i,j);
	r int Q=F<int>();
	while(Q--) {
		scanf("%s",c+1);
		if(c[1]=='G') {
			if(ans.size())
				printf("%d\n",ans.top());
			else
				puts("-1");
		}
		else {
			r int opt=F<int>();
			if(!col[opt]) {
				if(ch[opt].size()>=2)
					ans.erase(ch[opt].top()+ch[opt].second());
				ch[opt].erase(0);
				if(ch[opt].size()>=2)
					ans.push(ch[opt].top()+ch[opt].second()); 
				for(r int i=opt;p[i];i=p[i]) {
					if(ch[p[i]].size()>=2)
						ans.erase(ch[p[i]].top()+ch[p[i]].second());
					ch[p[i]].erase(d[i].top());
					d[i].erase(dis[opt][dep[opt]-dep[p[i]]]);
					if(d[i].size())
						ch[p[i]].push(d[i].top());
					if(ch[p[i]].size()>=2)
						ans.push(ch[p[i]].top()+ch[p[i]].second());
				}
			}
			else {
				if(ch[opt].size()>=2)
					ans.erase(ch[opt].top()+ch[opt].second());
				ch[opt].push(0);
				if(ch[opt].size()>=2)
					ans.push(ch[opt].top()+ch[opt].second()); 
				for(r int i=opt;p[i];i=p[i]) {
					if(ch[p[i]].size()>=2)
						ans.erase(ch[p[i]].top()+ch[p[i]].second());
					if(d[i].size())
						ch[p[i]].erase(d[i].top());
					d[i].push(dis[opt][dep[opt]-dep[p[i]]]);
					ch[p[i]].push(d[i].top());
					if(ch[p[i]].size()>=2)
						ans.push(ch[p[i]].top()+ch[p[i]].second());
				}
			}
			col[opt]^=1;
		}
	}
	return 0;
}
