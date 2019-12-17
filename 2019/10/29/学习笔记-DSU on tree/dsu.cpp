#include<cstdio>
#define r register
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
			Size=siz;
		}
		void Add(r int f,r int t) {
			Node x=new Edge();
			x->to=t;
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
int v[100001];
int son[100001],size[100001],p[100001];
void predfs(r int x) {
	size[x]=1;
	for(r Graph::Node j=T.Head[x];j!=T.Nul;j=j->nxt)
		if(j->to!=p[x])
			p[j->to]=x,predfs(j->to),size[x]+=size[j->to],(size[j->to]>size[son[x]])&&(son[x]=j->to);
}
int cnt[100001],Son,ans=0;
long long dp[100001];
long long sum=0;
void update(r int x,r int d) {
	cnt[v[x]]+=d;
	if(~d) {
		if(cnt[v[x]]>ans)
			ans=cnt[v[x]],sum=v[x];
		else
			if(cnt[v[x]]==ans)
				sum+=v[x];
	}
	for(r Graph::Node j=T.Head[x];j!=T.Nul;j=j->nxt)
		if(j->to!=p[x]&&j->to!=Son)
			update(j->to,d);
} 
void sucdfs(r int x,r bool h) {
	for(r Graph::Node j=T.Head[x];j!=T.Nul;j=j->nxt)
		if(j->to!=p[x]&&j->to!=son[x])
			sucdfs(j->to,0);
	if(son[x])
		sucdfs(son[x],1),Son=son[x];
	update(x,1),Son=0,dp[x]=sum;
	if(!h)
		update(x,-1),ans=sum=0;
}
int main() {
	r int n=F<int>(),x,y;
	T.Resize(n);
	for(r int i=1;i<=n;++i)
		v[i]=F<int>();
	for(r int i=1;i<n;++i) {
		r int x=F<int>(),y=F<int>();
		T.Add(x,y),T.Add(y,x);
	}
	predfs(1);
	sucdfs(1,1);
	for(r int i=1;i<=n;++i)
		printf("%lld ",dp[i]);
	return 0;
}
