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
int p[3000001];
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
int d[3000001],ret[3000001];
int lend,lent;
int main() {
	G[0][23]=Qpow(3,119);
	G[1][23]=Qpow(G[0][23],mod-2);
	for(r int i=22;i;--i) {
		G[0][i]=1ll*G[0][i+1]*G[0][i+1]%mod;
		G[1][i]=1ll*G[1][i+1]*G[1][i+1]%mod; 
	}
	r int n=F<int>()>>1,k=F<int>(),x;
	for(r int i=1;i<=k;++i)
		x=F<int>(),d[x]=1,lend=std::max(lend,x);
	ret[0]=1;
	lent=0;
	r int q=n;
	while(q) {
		if(q&1) {
			lim=1,lg=0;
			while(lim<lend+lent+1)
				lim<<=1,++lg;
			Calc();
			NTT(d,0),NTT(ret,0);
			for(r int i=0;i<lim;++i)
				ret[i]=1ll*ret[i]*d[i]%mod;
			NTT(ret,1),NTT(d,1);
			r int inv=Qpow(lim,mod-2);
			for(r int i=0;i<lim;++i) {
				ret[i]=1ll*ret[i]*inv%mod;
				if(ret[i])
					lent=i;
			}
			for(r int i=0;i<lim;++i) {
				d[i]=1ll*d[i]*inv%mod;
				if(d[i])
					lend=i;
			}
		}
		lim=1,lg=0;
		while(lim<(lend<<1)+1)
				lim<<=1,++lg;
		Calc();
		NTT(d,0);
		for(r int i=0;i<lim;++i)
			d[i]=1ll*d[i]*d[i]%mod;
		NTT(d,1);
		r int inv=Qpow(lim,mod-2);
		for(r int i=0;i<lim;++i) {
			d[i]=1ll*d[i]*inv%mod;
			if(d[i])
				lend=i;
		}
		q>>=1;
	}
	r int ans=0;
	for(r int i=0;i<=lent+1;++i)
		ans=Add(ans,1ll*ret[i]*ret[i]%mod);
	printf("%d\n",ans); 
	return 0;
}
