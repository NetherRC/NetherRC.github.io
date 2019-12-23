#include<cstdio>
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
	while(isd(ch))
		x=(x<<1)+(x<<3)+(ch^'0'),ch=getchar();
	bo&&(x=-x);
	return x;
}
const int mod=998244353;
int Qpow(r int x,r long long y) {
	r int ret=1;
	while(y) {
		if(y&1)
			ret=1ll*ret*x%mod;
		x=1ll*x*x%mod,y>>=1;
	}
	return ret;
}
int inv[100001],ifc[100001],fac[100001];
int C(r int x,r int y) {
	return 1ll*fac[x]*ifc[y]%mod*ifc[x-y]%mod;
}
int f[500001],g[500001],z[500001];
int Add(r int a,r int b) {
	return a+b>=mod?a+b-mod:a+b;
}
int Sub(r int a,r int b) {
	return a-b<0?a-b+mod:a-b;
}
int G[2][25];
int p[500001];
int lim=1,lg=0;
void Calc() {
	for(r int i=0;i<lim;++i)
		p[i]=(p[i>>1]>>1)|((i&1)<<(lg-1));
}
void NTT(int *x,r bool inv) {
	for(r int i=0;i<lim;++i)
		if(i<p[i])
			std::swap(x[i],x[p[i]]);
	for(r int mid=1,o=1;mid<lim;mid<<=1,++o) {
		r int Wn=G[inv][o];
		for(r int t=mid<<1,i=0;i<lim;i+=t)
			for(r int j=0,w=1;j<mid;++j,w=1ll*w*Wn%mod) {
				r int t1=x[i+j],t2=1ll*x[i+j+mid]*w%mod;
				x[i+j]=Add(t1,t2);
				x[i+j+mid]=Sub(t1,t2);
			}
	}
} 
void Inv(r int n,int *x,int *y) {
	if(n==1) {
		y[0]=Qpow(x[0],mod-2);
		return;
	}
	Inv((n+1)>>1,x,y);
	lim=1,lg=0;
	while(lim<2*n)
		lim<<=1,++lg; 
	Calc();
	for(r int i=0;i<n;++i)
		z[i]=x[i];
	for(r int i=n;i<lim;++i)
		z[i]=0;
	NTT(z,0),NTT(y,0);
	for(r int i=0;i<lim;++i)
		y[i]=1ll*Sub(2,1ll*z[i]*y[i]%mod)*y[i]%mod;
	NTT(y,1);
	r int iv=Qpow(lim,mod-2);
	for(r int i=0;i<lim;++i)
		y[i]=1ll*y[i]*iv%mod;
	for(r int i=n;i<lim;++i)
		y[i]=0;
}
int main() {
	G[0][23]=Qpow(3,119);
	G[1][23]=Qpow(G[0][23],mod-2);
	for(r int i=22;i;--i) {
		G[0][i]=1ll*G[0][i+1]*G[0][i+1]%mod;
		G[1][i]=1ll*G[1][i+1]*G[1][i+1]%mod; 
	}
	r int n=F<int>();
	inv[1]=fac[0]=fac[1]=ifc[0]=ifc[1]=1;
	for(r int i=2;i<=n;++i) {
		inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
		fac[i]=1ll*i*fac[i-1]%mod;
		ifc[i]=1ll*inv[i]*ifc[i-1]%mod;
	}
	g[0]=1;
	for(r int i=1;i<=n;++i)
		g[i]=1ll*Qpow(2,1ll*i*(i-1)/2)*ifc[i]%mod;
	Inv(n+1,g,f);
	for(r int i=1;i<=n;++i)
		f[i]=1ll*Sub(0,f[i])*fac[i]%mod;
	if(n>=1)
		puts("1");
	if(n>=2)
		puts("-1");
	for(r int i=3;i<=n;++i)
		printf("%lld\n",1ll*fac[i-1]*Qpow(2,1ll*i*(i-3)/2)%mod*Qpow(f[i],mod-2)%mod);
	return 0;
}
