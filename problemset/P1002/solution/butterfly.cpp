#include<cstdio>
#include<cmath>
#include<cstring>
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
using std::sqrt;
template<int n,int m> 
struct matrix {
	int val[n+1][m+1];
	int *operator[](r int i) {
		return val[i];
	}
	const int *operator[](r int i)const {
		return val[i];
	} 
};
const int mod=998244353;
template<int n,int m,int p>
matrix<n,m>operator*(const matrix<n,p>&a,const matrix<p,m>&b) {
	static matrix<n,m> c;
	r int *C;
	r const int *B;
	r long long A;
	memset(&c,0,sizeof c);
	for(r int i=1;i<=n;++i) {
		r int j=1;
		for(C=c[i];j<=p;++j)
			if(A=a[i][j]) {
				r int k=1;
				for(B=b[j];k<=m;++k)
					C[k]=(C[k]+A*B[k])%mod;
			}
	}
	return c;
}
matrix<2,2>I,ans,t;
void qpow(r long long k) {
	while(k) {
		if(k&1)
			I=I*t;
		t=t*t,k>>=1;
	}
}
int main() {
	freopen("butterfly.in","r",stdin);
	freopen("butterfly.out","w",stdout);
	r long long d=F<long long>(),k=F<long long>();
	r long long x,y=1;
	while(1) {
		x=sqrt(d*y*y+1);
		if(x*x-d*y*y==1)
			break;
		++y;
	}
	I[1][1]=1,I[1][2]=0;
	I[2][1]=0,I[2][2]=1;
	t[1][1]=x,t[1][2]=1ll*y*d%mod;
	t[2][1]=y,t[2][2]=x;
	qpow(k-1);
	r long long nx=(I[1][1]*x%mod+I[1][2]*y%mod)%mod,ny=(I[2][1]*x%mod+I[2][2]*y%mod)%mod;
	printf("%lld\n",((nx+ny-k-1)%mod+mod)%mod);
	return 0;
}
