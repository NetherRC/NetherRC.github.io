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
const int mod=1004535809;
int G[2][25];
int Qpow(r int x,r int y) {
	r int ret=1;
	while(y) {
		if(y&1)
			ret=1ll*x*ret%mod;
		x=1ll*x*x%mod,y>>=1;
	}
	return ret;
}
inline int Add(r int x,r int y) {
	return x+y>=mod?x+y-mod:x+y;
}
inline int Sub(r int x,r int y) {
	return x-y<0?x-y+mod:x-y; 
}
int w[500001];
int inv[12000001],fac[12000001],ifc[12000001]; 
inline int C(r int x,r int y) {
	return 1ll*fac[x]*ifc[x-y]%mod*ifc[y]%mod;
}
int f[1200001],g[1200001];
int p[1200001];
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
int main() {
	G[0][21]=Qpow(3,479);
	G[1][21]=Qpow(G[0][21],mod-2);
	for(r int i=20;i;--i) {
		G[0][i]=1ll*G[0][i+1]*G[0][i+1]%mod;
		G[1][i]=1ll*G[1][i+1]*G[1][i+1]%mod;
	}
	r int n=F<int>(),m=F<int>(),s=F<int>();
	r int mx=std::max(m,n);
	for(r int i=0;i<=m;++i)
		w[i]=F<int>();
	inv[1]=fac[1]=fac[0]=ifc[1]=ifc[0]=1;
	for(r int i=2;i<=mx;++i) {
		inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
		fac[i]=1ll*i*fac[i-1]%mod;
		ifc[i]=1ll*inv[i]*ifc[i-1]%mod; 
	}
	mx=std::min(n/s,m);
	for(r int i=0;i<=mx;++i)
		f[i]=1ll*fac[i]*C(m,i)%mod*fac[n]%mod*Qpow(m-i,n-i*s)%mod*Qpow(1ll*Qpow(fac[s],i)*fac[n-i*s]%mod,mod-2)%mod;
	for(r int i=0;i<=mx;++i)
		g[i]=((mx-i)&1?Sub(0,ifc[mx-i]):ifc[mx-i]);
	lim=1,lg=0;
	while(lim<2*mx+1)
		lim<<=1,++lg;
	Calc();
	NTT(f,0),NTT(g,0);
	for(r int i=0;i<lim;++i)
		f[i]=1ll*f[i]*g[i]%mod;
	NTT(f,1);
	r int Inv=Qpow(lim,mod-2),ans=0;
	for(r int i=0;i<=mx;++i)
		ans=(ans+1ll*w[i]*f[mx+i]%mod*ifc[i]%mod*Inv%mod)%mod;
	printf("%d\n",ans);
	return 0;
}
