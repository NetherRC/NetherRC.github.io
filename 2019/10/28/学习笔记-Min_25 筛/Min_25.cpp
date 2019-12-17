#include<cstdio>
#include<cmath>
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
const int mod=1e9+7,INV6=166666668;
long long n;
int sqn,cnt;
int p[100001];
bool isp[100001];
long long s[2][100001];
void Sieve() {
	for(r int i=2;i<=sqn;++i) {
		if(!isp[i]) {
			p[++cnt]=i;
			s[0][cnt]=(s[0][cnt-1]+i)%mod;
			s[1][cnt]=(s[1][cnt-1]+1ll*i*i%mod)%mod;
		}
		for(r int j=1;j<=cnt&&1ll*i*p[j]<=sqn;++j) {
			isp[p[j]*i]=1;
			if(i%p[j]==0)
				break;
		}
	}
}
long long G[2][200001];
int id[2][100001];
int tot;
long long val[200001];
inline int GetID(r long long w) {
	return w<=sqn?id[0][w]:id[1][n/w];
}
inline int Sub(r long long x,r long long y) {
	return x>=y?x-y:x-y+mod;
}
void GetG() {
	for(r long long i=1,j;i<=n;i=j+1) {
		j=n/(n/i);
		r long long w=n/i;
		val[++tot]=w;
		if(w<=sqn)
			id[0][w]=tot;
		else
			id[1][n/w]=tot;
		w%=mod;
		G[0][tot]=w*(w+1)/2%mod;
		G[1][tot]=w*(w+1)%mod*(2*w+1)%mod*INV6%mod;
		G[0][tot]=Sub(G[0][tot],1);
		G[1][tot]=Sub(G[1][tot],1);
	}
	for(r int j=1;j<=cnt;++j) {
		for(r int i=1;i<=tot&&1ll*p[j]*p[j]<=val[i];++i) {
			r int k=GetID(val[i]/p[j]);
			G[0][i]=Sub(G[0][i],1ll*p[j]*Sub(G[0][k],s[0][j-1])%mod);
			G[1][i]=Sub(G[1][i],1ll*p[j]*p[j]%mod*Sub(G[1][k],s[1][j-1])%mod);
		}
	}
}
int GetS(r long long x,r int y) {
	if(x<p[y]||x<=1)
		return 0;
	r int k=GetID(x);
	r long long res=Sub(Sub(G[1][k],G[0][k]),Sub(s[1][y-1],s[0][y-1]));
	for(r int i=y;i<=cnt&&p[i]*p[i]<=x;++i) {
		r long long t1=p[i],t2=1ll*p[i]*p[i];
		for(r int j=1;t2<=x;++j,t1=t2,t2*=p[i]) {
			r long long r1=t1%mod,r2=t2%mod;
			res=(res+GetS(x/t1,i+1)*r1%mod*Sub(r1,1)%mod+r2*Sub(r2,1)%mod)%mod;
		}
	}
	return res;
}
int main() {
	n=F<long long>();
	sqn=sqrt(n);
	Sieve();
	GetG();
	printf("%d\n",(GetS(n,1)+1)%mod);
	return 0;
}
