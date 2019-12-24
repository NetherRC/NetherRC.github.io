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
int inv[300001],fac[300001],ifc[300001];
int A[1200001],B[1200001];
int q[300001];
int lim=1,lg=0;
inline int C(r int x,r int y) {
	return 1ll*fac[x]*ifc[y]%mod*ifc[x-y]%mod;
}
int Qpow(r int x,r int y) {
	r int ret=1;
	while(y) {
		if(y&1)
			ret=1ll*ret*x%mod;
		x=1ll*x*x%mod,y>>=1;
	}
	return ret;
}
inline int Add(r int a,r int b) {
	return a+b>=mod?a+b-mod:a+b;
}
inline int Sub(r int a,r int b) {
	return a-b<0?a-b+mod:a-b;
}
int G[2][25];
int p[1200001];
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
int ans[1200001];
int main() {
	G[0][23]=Qpow(3,119);
	G[1][23]=Qpow(G[0][23],mod-2);
	for(r int i=22;i;--i) {
		G[0][i]=1ll*G[0][i+1]*G[0][i+1]%mod;
		G[1][i]=1ll*G[1][i+1]*G[1][i+1]%mod; 
	}
	r int n=F<int>(),k=F<int>(),x,y;
	for(r int i=1;i<=n;++i)
		x=F<int>(),++q[x];
	inv[1]=fac[0]=fac[1]=ifc[0]=ifc[1]=1;
	for(r int i=2;i<=n;++i) {
		inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
		fac[i]=1ll*i*fac[i-1]%mod;
		ifc[i]=1ll*inv[i]*ifc[i-1]%mod;
	}
	for(r int i=1;i<=k;++i) {
		r int t=F<int>();
		x=y=0;
		for(r int j=1;j<t;++j)
			if(q[j]==1)
				++x;
			else
				if(q[j]>1)
					++y;
		lim=1,lg=0;
		while(lim<x+2*y+1)
			lim<<=1,++lg;
		Calc();
		for(r int j=0;j<=x;++j)
			A[j]=1ll*C(x,j)*Qpow(2,j)%mod;
		for(r int j=0;j<=2*y;++j)
			B[j]=C(2*y,j);
		for(r int j=x+1;j<lim;++j)
			A[j]=0;
		for(r int j=2*y+1;j<lim;++j)
			B[j]=0;
		NTT(A,0),NTT(B,0);
		for(r int j=0;j<lim;++j)
			A[j]=1ll*A[j]*B[j]%mod;
		NTT(A,1);
		r int Inv=Qpow(lim,mod-2);
		for(r int j=0;j<=x+2*y;++j)
			ans[j+t+1]=Add(ans[j+t+1],1ll*A[j]*Inv%mod);
	}
	r int Q=F<int>();
	while(Q--) {
		x=F<int>();
		printf("%d\n",ans[x/2]);
	}
	return 0;
}
