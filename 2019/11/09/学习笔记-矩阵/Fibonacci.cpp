#include<cstdio>
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
	x=ch^'0',ch=getchar();
	while(isd(ch))
		x=(x<<1)+(x<<3)+(ch^'0'),ch=getchar();
	bo&&(x=-x);
	return x;
}
template<int n,int m> 
struct matrix {
	int val[n+1][m+1];
	int *operator[](int i) {
		return val[i];
	}
	const int *operator[](int i)const {
		return val[i];
	} 
};
const int mod=1e9+7;
template<int n,int m,int p>
matrix<n,m>operator*(const matrix<n,p>&a,const matrix<p,m>&b) {
	static matrix<n,m>c;
	int *C;
	const int *B;
	long long A;
	memset(&c,0,sizeof c);
	for(register int i=1;i<=n;++i) {
		int j=1;
		for(C=c[i];j<=p;++j)
			if(A=a[i][j]) {
				int k=1;
				for(B=b[j];k<=m;++k)
					C[k]=(C[k]+A*B[k])%mod;
			}
	}
	return c;
}
matrix<2,2>I;
template<int n>
matrix<n,n>qpow(matrix<n,n>&a,long long k) {
	static matrix<n,n>b,c;
	b=a,c=I;
	while(k) {
		if(k&1)
			c=c*b;
		b=b*b,k>>=1;
	}
	return c;
}
matrix<2,2>a,b;
int main() {
	r long long k=F<long long>();
	I[1][1]=1,I[1][2]=0;
	I[2][1]=0,I[2][2]=1;
	a[1][1]=0,a[1][2]=1;
	a[2][1]=1,a[2][2]=1;
	b=qpow(a,k-1);
	printf("%lld\n",(0ll+b[1][1]+b[1][2])%mod);
	return 0;
}
