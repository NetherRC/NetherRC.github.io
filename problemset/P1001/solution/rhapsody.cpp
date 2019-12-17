#include<cstdio>
#include<algorithm>
#define r register
#define inf (1ll<<60)
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
	x=ch^'0',ch=getchar();
	while(isd(ch))
		x=(x<<1)+(x<<3)+(ch^'0'),ch=getchar();
	bo&&(x=-x);
	return x;
}
class Graph {
	public:
		struct Edge {
			int to;
			long long dis;
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
		void Add(r int f,r int t,r long long d) {
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
}T;
long long len[200001];
int son[200001],siz[200001],dep[200001],p[200001];
int dfn[200001],top[200001],R[200001],udf[200001];
int tot;
void predfs(r int x) {
	siz[x]=1; 
	for(r Graph::Node j=T.Head[x];j!=T.Nul;j=j->nxt)
		if(j->to!=p[x]) {
			p[j->to]=x;
			len[j->to]=len[x]+j->dis;
			dep[j->to]=dep[x]+1;
			predfs(j->to);
			siz[x]+=siz[j->to];
			if(siz[j->to]>siz[son[x]])
				son[x]=j->to;
		} 
}
void sucdfs(r int x,r int tp) {
	dfn[x]=++tot;
	top[x]=tp;
	udf[tot]=x;
	if(son[x])
		sucdfs(son[x],tp);
	for(r Graph::Node j=T.Head[x];j!=T.Nul;j=j->nxt)
		if(j->to!=p[x]&&j->to!=son[x])
			sucdfs(j->to,j->to);
	R[x]=tot;
}
int LCA(r int u,r int v) {
	while(top[u]!=top[v]) {
		if(dep[top[u]]>dep[top[v]])
			std::swap(u,v);
		v=p[top[v]];
	}
	return dep[u]>dep[v]?v:u;
}
struct Path {
	int s,t;
	long long len;
}q[200001];
bool cmp(const Path &x,const Path &y) {
	return x.len<y.len;
}
struct tree {
	int val,tag;
	int lt,rt;
}t[800001];
inline void Pushup(r int x)  {
	t[x].val=std::max(t[x<<1].val,t[x<<1|1].val);
}
inline void Pushdown(r int x) {
	if(t[x].tag) {
		t[x<<1].val+=t[x].tag;
		t[x<<1|1].val+=t[x].tag;
		t[x<<1].tag+=t[x].tag;
		t[x<<1|1].tag+=t[x].tag;
		t[x].tag=0;
	}
}
#define mid (t[x].lt+t[x].rt>>1)
inline void Build(r int lt,r int rt,r int x) {
	t[x].lt=lt,t[x].rt=rt;
	if(lt==rt) {
		t[x].val=0;
		return;
	}
	Build(lt,mid,x<<1),Build(mid+1,rt,x<<1|1);
	Pushup(x);
}
inline void Update(r int lt,r int rt,r int key,r int x) {
	if(t[x].rt<lt||t[x].lt>rt)
		return;
	if(t[x].lt>=lt&&t[x].rt<=rt) {
		t[x].val+=key;
		t[x].tag+=key;
		return;
	}
	Pushdown(x);
	Update(lt,rt,key,x<<1);
	Update(lt,rt,key,x<<1|1);
	Pushup(x);
}
inline int Query(r int lt,r int rt,r int x) {
	if(t[x].rt<lt||t[x].lt>rt)
		return 0;
	if(t[x].lt>=lt&&t[x].rt<=rt)
		return t[x].val;
	Pushdown(x);
	return std::max(Query(lt,rt,x<<1),Query(lt,rt,x<<1|1));
}
inline void Solve(r int u,r int v,r int d) {
	while(top[u]!=top[v]) {
		if(dep[top[u]]>dep[top[v]])
			std::swap(u,v);
		Update(dfn[top[v]],dfn[v],d,1); 
		v=p[top[v]];
	}
	if(dep[u]>dep[v])
		std::swap(u,v); 
	Update(dfn[u],dfn[v],d,1);
}
int main() {
	freopen("rhapsody.in","r",stdin);
	freopen("rhapsody.out","w",stdout);
	r int n=F<int>(),u,v;
	r long long w;
	T.Resize(n);
	for(r int i=1;i<n;++i) {
		u=F<int>(),v=F<int>(),w=F<long long>();
		T.Add(u,v,w),T.Add(v,u,w);
	}
	predfs(1);
	sucdfs(1,1);
	Build(1,n,1);
	r int m=F<int>(),k=F<int>();
	for(r int i=1;i<=m;++i) {
		q[i].s=F<int>(),q[i].t=F<int>();
		q[i].len=len[q[i].s]+len[q[i].t]-2*len[LCA(q[i].s,q[i].t)];
	}
	std::sort(q+1,q+m+1,cmp);
	r int lt=1,rt=1;
	r long long ans=inf;
	for(;rt<=m;++rt) {
		Solve(q[rt].s,q[rt].t,1);
		while(t[1].val>=k&&lt<=rt) {
			ans=std::min(ans,q[rt].len-q[lt].len);
			Solve(q[lt].s,q[lt].t,-1),++lt;
		}
	}
	if(ans==inf)
		puts("-1");
	else
		printf("%lld\n",ans);
	return 0;
}
