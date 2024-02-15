#include<bits/stdc++.h>

using namespace std;

typedef long long int ll;

/* 繰り返し二乗法を使ったべき乗 mod m */
ll pow(ll a,ll b,ll m)
{
    ll ans = 1,n = a % m;
    while(b)
    {
        if(b & 0b1)ans = (n * ans) % m;
        n=(n*n) % m;
        b >>= 1;
    }
    return ans;
}

ll _combination(const ll n,const ll r,const ll m)
{
    /* nCrのbottom(分母)とtop(分子) */
    map<ll,ll> top,bottom;

    int sqrt_n = (int)ceil((ll)sqrt(n));

    /* エラトステネスの篩のprimeの3つのステータス */
    const int notPrime = 0; /* 素数でない */
    const int primeUnknown = 1; /* 初出の素数 */
    const int primeKnown = 2; /* 既出の素数 */

    /* エラトステネスの篩と素数を線形でつなぐもの */
    vector<char> prime(sqrt_n+1,primeUnknown);
    vector<int> nextPrime(sqrt_n+1,-1);

    /* aを素因数分解し、mp[素因数] = 指数 になるように加算 */
    auto factorization = [&](ll a,map<ll ,ll> &mp) -> void
    {
        int prevPrimeIdx = 0;

        int sqrt_a = (int)ceil((ll)sqrt(a));
        for(int p = 2;p < (int)sqrt(a)+1;p++)
        {
            /* pが素数でないとき */
            if(prime[p] == notPrime)continue;

            /* pが初出の素数のとき */
            if(prime[p] == primeUnknown)
            {
                /* 一つ前に出てきた素数と線形で接続 */
                nextPrime[prevPrimeIdx] = p;
                prime[p] = primeKnown;
                for(int j = p + p;j < sqrt_n; j += p)
                {
                    prime[j] = notPrime;
                }
            }

            /* 素数で割ってみる */
            while(a % p == 0)
            {
                a /= p;
                mp[p]++;
            }

            /* 素因数分解が完了したとき */
            if(a == 1) return;

            if(nextPrime[p] == -1) prevPrimeIdx = p;
            else p = nextPrime[p]-1;
            
        }

        /* sqrt(a)より大きい素因数を持っている場合 */
        if(a!=1)mp[a]++;
    };

    /* 素因数分解する */
    for(ll i = n; i > n - r ; i--) factorization(i,top);
    for(ll i = r; i > 0; i--) factorization(i,bottom);
    
    ll ans = 1;

    /* modを取りながら答えを計算する */
    for(auto itr = top.begin();itr != top.end();itr++)
    {
        ll factor = (ll)itr->first;
        ll top_exponent = (ll)itr->second;
        ll bottom_exponent = (ll)bottom[factor];

        ans = (ans * (ll)pow(factor, top_exponent-bottom_exponent ,m)) % m;
    }
    return ans;
}

template<typename T>
ll combination(const T n,const T r,const ll m)
{
    return _combination((ll)n,(ll)min(r,n-r),m);
}

int main(int argc, char **argv)
{
    ll n = atoll(argv[1]);
    ll r = atoll(argv[2]);
    ll m = atoll(argv[3]);
    cout << combination(n,r,m) << "\n";
    exit(EXIT_SUCCESS);
}