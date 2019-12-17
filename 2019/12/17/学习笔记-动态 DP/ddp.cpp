#include<cstdio>
#include<cstring>
#include<algorithm>
using std::max;
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
			int to;
			Edge* nxt;
		};
		typedef Edge* Node;
		Node Nul,*Head;
		int Size;
		void Resize(r int siz) {
			Head=new Node[siz+1];
			for(r int i=0;i<=siz;++i)
				Head[i]=Nul;
		}
		void Add(r int f,r int t) {
			Node x=new Edge();
			x->to=t;
			x->nxt=Head[f],Head[f]=x;
		}
}P;
int siz[100001];
int son[100001];
int top[100001];
int dep[100001];
int dfn[100001];
int udf[100001];
int btm[100001];
int p[100001];
int tot;
template<int n,int m> 
struct matrix {
	int val[n+1][m+1];
	int *operator[](int i) {
		return val[i];
	}
	const int *operator[](int i)const {
		return val[i];
	} 
	matrix() {
		memset(val,0xc0,sizeof val);
	}
};
int f[100001][2];
int v[100001];
matrix<2,2>Val[100001];
template<int n,int m,int p>
matrix<n,m>operator*(const matrix<n,p>&a,const matrix<p,m>&b) {
	static matrix<n,m>c;
	int *C;
	const int *B;
	int A;
	memset(&c,0,sizeof c);
	for(r int i=1;i<=n;++i) {
		int j=1;
		for(C=c[i];j<=p;++j) {
			A=a[i][j];
			int k=1;
			for(B=b[j];k<=m;++k)
				C[k]=std::max(C[k],A+B[k]);
		}
	}
	return c;
}
void dfs(r int x) {
	siz[x]=1;
	for(r Graph::Node j=P.Head[x];j!=P.Nul;j=j->nxt)
		if(j->to!=p[x]) {
			dep[j->to]=dep[x]+1;
			p[j->to]=x;
			dfs(j->to);
			siz[x]+=siz[j->to];
			if(siz[son[x]]<siz[j->to])
				son[x]=j->to;
		}
} 
void dfs(r int x,r int tp) {
	udf[dfn[x]=++tot]=x;
	top[x]=tp;
	f[x][0]=0,f[x][1]=v[x];
	Val[x][1][1]=Val[x][1][2]=0;
	Val[x][2][1]=v[x];
	btm[tp]=x;
	if(son[x]) {
		dfs(son[x],tp);
		f[x][0]+=max(f[son[x]][0],f[son[x]][1]);
		f[x][1]+=f[son[x]][0]; 
	}
	for(r Graph::Node j=P.Head[x];j!=P.Nul;j=j->nxt)
		if(j->to!=p[x]&&j->to!=son[x]) {
			dfs(j->to,j->to);
			f[x][0]+=max(f[j->to][0],f[j->to][1]);
			f[x][1]+=f[j->to][0]; 
			Val[x][1][1]+=max(f[j->to][0],f[j->to][1]);
			Val[x][1][2]=Val[x][1][1];
			Val[x][2][1]+=f[j->to][0];
		}
}
struct SegmentNode {
	int lt,rt;
	matrix<2,2>val;
}T[400001];
void Pushup(r int o) {
	T[o].val=T[o<<1].val*T[o<<1|1].val;
}
#define mid ((T[o].lt+T[o].rt)>>1)
void Build(r int lt,r int rt,r int o) {
	T[o].lt=lt,T[o].rt=rt;
	if(lt==rt) {
		T[o].val=Val[udf[lt]];
		return;
	}
	Build(lt,mid,o<<1);
	Build(mid+1,rt,o<<1|1);
	Pushup(o);
}
void Update(r int x,r int o) {
	if(T[o].lt==T[o].rt) {
		T[o].val=Val[udf[x]];
		return;
	}
	if(x<=mid)
		Update(x,o<<1);
	else
		Update(x,o<<1|1);
	Pushup(o);
}
matrix<2,2>Query(r int lt,r int rt,r int o) {
	if(lt==T[o].lt&&rt==T[o].rt)
		return T[o].val;
	if(rt<=mid)
		return Query(lt,rt,o<<1);
	if(lt>mid)
		return Query(lt,rt,o<<1|1);
	return Query(lt,mid,o<<1)*Query(mid+1,rt,o<<1|1);
}
int Solve(r int x,r int y) {
	Val[x][2][1]+=y-v[x];
	v[x]=y;
	matrix<2,2>a,b;
	while(x) {
		a=Query(dfn[top[x]],dfn[btm[top[x]]],1);
		Update(dfn[x],1);
		b=Query(dfn[top[x]],dfn[btm[top[x]]],1);
		x=p[top[x]];
		Val[x][1][1]+=max(b[1][1],b[2][1])-max(a[1][1],a[2][1]);
		Val[x][1][2]=Val[x][1][1];
		Val[x][2][1]+=b[1][1]-a[1][1];
	}
	matrix<2,2>ans=Query(dfn[1],dfn[btm[1]],1);
	return max(ans[1][1],ans[2][1]);
}
int main() {
	r int n=F<int>(),m=F<int>();
	P.Resize(n);
	for(r int i=1;i<=n;++i)
		v[i]=F<int>();
	r int x,y;
	for(r int i=1;i<n;++i) {
		x=F<int>(),y=F<int>(); 
		P.Add(x,y),P.Add(y,x);
	}
	dfs(1);
	dfs(1,1);
	Build(1,n,1);
	while(m--) {
		x=F<int>(),y=F<int>();
		printf("%d\n",Solve(x,y));
	}
	return 0;
}
