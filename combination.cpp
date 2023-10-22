#include<bits/stdc++.h>

using namespace std;

typedef long long int ll;

template<typename T>
ll _combination(const T n,const T r)
{
    map<ll,ll> top,bottom;

    int sqrt_n = (int)sqrt(n-1) + 2;

    vector<char> isPrime(sqrt_n,1);
    vector<int> nextPrime(sqrt_n,-1);

    auto factorization = [&](ll a,map<ll ,ll> &mp) -> void
    {
        int prevPrimeIdx = 0;

        for(int p = 2;p < (int)sqrt(a) + 2;p++)
        {
            
            if(!isPrime[p])continue;

            if(isPrime[p] == 1)
            {
                nextPrime[prevPrimeIdx] = p;
                isPrime[p] = 2;
                for(int j = p + p;j < sqrt_n; j += p)
                {
                    isPrime[j] = 0;
                }
            }

            while(a % p == 0)
            {
                a /= p;
                mp[p]++;
            }

            if(a == 1) return;

            if(nextPrime[p] == -1) prevPrimeIdx = p;
            else p = nextPrime[p]-1;
            
        }
        if(a!=1)mp[a]++;
    };

    for(ll i = n; i > n - r ; i--) factorization(i,top);
    
    for(ll i = r; i > 0; i--) factorization(i,bottom);
    
    ll ans = 1;

    for(auto itr = top.begin();itr != top.end();itr++)
    {
        ans *= (ll)pow((ll)itr->first,(ll)itr->second - (ll)bottom[itr ->first]);
    }
    return ans;
}

template<typename T>
ll combination(const T n,const T r)
{
    return _combination(n,min(r,n-r));
}

template<typename T>
ll combi_pas(const T n,const T r)
{
    vector<vector<ll>> v(n+1,vector<ll>(n+1,0));
    for(int i = 0; i < n + 1; i++)
    {
        v[i][0] = 1;
        v[i][i] = 1;
    }
    for(int k = 1;k <v.size();k++)
    {
        for(int j = 1;j<k;j++)
        {
            v[k][j]=(v[k-1][j-1]+v[k-1][j]);
        }
    }

    return v[n][r];
}

//solve
void solve()
{
    ll n , r;
    cin >> n >> r;


    clock_t start = clock();
    cout << (ll)combination(n,r) << endl;
    clock_t end = clock();

    double time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
    printf("time %lf[ms]\n", time);

    start = clock();
    cout << (ll)combi_pas(n,r) << endl;
    end = clock();
    time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
    printf("time %lf[ms]\n", time);


}
 
int main(void){
    cin.tie(0); 
    ios::sync_with_stdio(false);
    solve();
    return 0;
}