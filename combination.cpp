#include<bits/stdc++.h>

using namespace std;

typedef long long int ll;
typedef unsigned long long int ull;

typedef long double ld;

typedef pair<int,int> pi;
typedef vector<pi> vpi;

typedef pair<ll,ll> pll;
typedef vector<pll> vpll;

typedef pair<ll,int> plli;
typedef vector<plli> vplli;

typedef vector<int> vi;
typedef vector<vi> vvi;

typedef vector<ll> vll;
typedef vector<vll> vvll;

typedef vector<ull> vull;
typedef vector<vull> vvull;

typedef vector<string> vstr;

typedef vector<bool> vb;
typedef vector<vb> vvb;

typedef set<int> si;
typedef vector<si> vsi;

typedef vector<char> vc;
typedef vector<vc> vvc;

#define rep(i,n) for(ll i=0;i<n;i++)
#define rrep(i,start,end) for(ll i=start; i<=end; i++)
#define rep_itr(itr,v) for(auto itr=(v).begin(); itr!=(v).end(); itr++)

#define all(a) (a).begin(), (a).end()

#define INF_MAX_64 9023372036854775807LL
#define INF_MIN_64 -9023372036854775808LL
#define INF_MAX_32 2047483647
#define INF_MIN_32 -2047483648

//debug function
template<typename T>void debug1(const T &vec){cout << endl << "DEBUG" << endl;rep_itr(itr,vec){cout << *itr << " ";}cout << endl;}
template<typename T>void debug1(const T &vec,string s){cout << endl << "DEBUG : " << s << endl;rep_itr(itr,vec){cout << *itr << " ";}cout << endl;}
template<typename T>void debug2(const vector<T> &vec){cout << endl << "DEBUG" << endl;rep(i,vec.size()){cout << "[" << i << "] : ";rep_itr(itr,vec[i]){cout << *itr << " ";}cout << endl;}}
template<typename T>void debug2(const vector<T> &vec,string s){cout << endl << "DEBUG : " << s << endl;rep(i,vec.size()){cout << "[" << i << "] : ";rep_itr(itr,vec[i]){cout << *itr << " ";}cout << endl;}}

//overload function
template<typename T>T pow(T a,T b,T m){T ans = 1,num = a % m;while(b){if(b & 0b1)ans = (num * ans) % m;num=(num*num) % m;b >>= 1;}return ans;}

//my function
template<typename T>bool isRange(T a,T mi, T ma){return (min(mi,ma) <= a && a <= max(mi,ma))?true:false;}


template<typename T>T _combination(const T n,const T r)
{
    map<ll,ll> top,bottom;

    int sqrt_n = (int)sqrt(n) + 2;

    vector<char> isPrime(sqrt_n,1);
    vector<int> nextPrime(sqrt_n,-1);

    auto factorization = [&](T a,map<ll,ll> &mp) -> void
    {
        int prevPrimeIdx = 0;

        for(int ii = 2;ii < (int)sqrt(a) + 2;ii++)
        {
            
            if(!isPrime[ii])continue;

            if(isPrime[ii] == 1)
            {
                nextPrime[prevPrimeIdx] = ii;
                isPrime[ii] = 2;
                for(int j = ii + ii;j < sqrt_n; j += ii)
                {
                    isPrime[j] = 0;
                }
            }

            while(a % ii == 0)
            {
                a /= ii;
                mp[ii]++;
            }

            if(a == 1) return;

            if(nextPrime[ii] == -1) prevPrimeIdx = ii;
            else ii = nextPrime[ii]-1;
        }
        if(a!=1)mp[a]++;
    };

    for(int i = n; i > n - r ; i--)factorization(i,top);
    for(int i = r; i > 0; i--)factorization(i,bottom);

    for(auto itr = bottom.begin();itr != bottom.end(); itr++)top[itr->first] -= itr->second;

    ll ans = 1;

    for(auto itr = top.begin();itr != top.end();itr++)
    {
        ans *= (ll)pow((ll)itr->first,(ll)itr->second);
    }
    return ans;
}

template<typename T>T combination(const T n,const T r)
{
    return _combination(n,min(r,n-r));
}

template<typename T>T combi_pas(const T n,const T r)
{
    vvll v(n+1,vll(n+1,0));
    rep(i,n+1)
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
    clock_t start = clock();
    cout << (ll)combination((ll)100000,(ll)50000) << endl;
    clock_t end = clock();

    double time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
    printf("time %lf[ms]\n", time);



    start = clock();
    cout << (ll)combi_pas((ll)100000,(ll)50000) << endl;
    end = clock();
    time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
    printf("time %lf[ms]\n", time);


    // int n;
    // cin >> n;
    // vi a(n),b(n);
    // rep(i,n)cin >> a[i];
    
    // rrep(i,1,n-1)b[i] = a[i] - a[i-1];

    // int left = 0, right = 1;
    // ll ans = 0;

    // while(left < n)
    // {
    //     while(right < n && (b[right] > 0 || left >= right))right++;
    //     ans += combination((ll)right-left+1,(ll)2);

    //     left = right ;
    // }

    // cout << ans << endl;
}
 
int main(void){
    cin.tie(0); 
    ios::sync_with_stdio(false);
    solve();
    return 0;
}