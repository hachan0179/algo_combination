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
