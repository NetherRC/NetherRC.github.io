#include<cstdio>
#include<cstring>
#include<algorithm>
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
	x=ch^'0',ch=getchar();
	while(isd(ch))
		x=(x<<1)+(x<<3)+(ch^'0'),ch=getchar();
	bo&&(x=-x);
	return x;
}
const int mod=998244353;
const int qpow(r int a,r int b) {
	r int ret=1;
	while(b) {
		if(b&1)
			ret=1ll*ret*a%mod;
		a=1ll*a*a%mod,b>>=1;
	}
	return ret;
}
int p[5000001];
int G[2][24];
using std::swap;
int Add(r int a,r int b) {
	return a+b>=mod?a+b-mod:a+b;
}
int Sub(r int a,r int b) {
	return a-b<0?a-b+mod:a-b;
}
int lim=1;
void NTT(int *x,r bool inv) {
	for(r int i=0;i<lim;++i)
		if(i<p[i])
			swap(x[i],x[p[i]]);
	for(r int mid=1,o=1;mid<lim;mid<<=1,++o) {
		r int Wn=G[inv][o];
		for(r int t=mid<<1,i=0;i<lim;i+=t) {
			r int w=1;
			for(r int j=0;j<mid;++j,w=1ll*w*Wn%mod) {
				r int t1=x[i+j],t2=1ll*w*x[i+j+mid]%mod;
				x[i+j]=Add(t1,t2);
				x[i+j+mid]=Sub(t1,t2);
			}
		} 
	}
}
int a[500001],b[500001];
int g[500001],f[500001];
void Solve(r int lt,r int rt,r int lg) {
	if(lt==rt)
		return;
	r int mid=(lt+rt)>>1;
	Solve(lt,mid,lg-1);
	lim=1<<lg;
	for(r int i=0;i<lim;++i)
		p[i]=(p[i>>1]>>1)|((i&1)<<(lg-1));
	memset(a+(lim>>1),0,sizeof(int)*(lim>>1));
	memcpy(a,f+lt,sizeof(int)*(lim>>1));
	memcpy(b,g,sizeof(int)*lim);
	NTT(a,0),NTT(b,0);
	for(r int i=0;i<lim;++i)
		a[i]=1ll*a[i]*b[i]%mod;
	NTT(a,1);
	r int t=qpow(lim,mod-2);
	for(r int i=0;i<lim;++i)
		a[i]=1ll*a[i]*t%mod;
	for(r int i=(lim>>1);i<lim;++i)
		f[lt+i]=Add(f[lt+i],a[i]);
	Solve(mid+1,rt,lg-1);
}
int main() {
	r int n=F<int>();
	G[0][23]=15311432;
	G[1][23]=qpow(G[0][23],mod-2);
	for(r int i=22;i>=0;--i)
		G[0][i]=1ll*G[0][i+1]*G[0][i+1]%mod,G[1][i]=1ll*G[1][i+1]*G[1][i+1]%mod;
	for(r int i=1;i<n;++i)
		g[i]=F<int>();
	f[0]=1;
	r int ed=1,o=0;
	while(ed<n)
		ed<<=1,++o;
	Solve(0,ed-1,o);
	for(r int i=0;i<=n-1;++i)
		printf("%d ",f[i]);
	puts("");
	return 0;
}
