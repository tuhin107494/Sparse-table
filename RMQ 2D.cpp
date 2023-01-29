#include <bits/stdc++.h>
using namespace std ;
#define ll long long int 

const int ln = 9 ;
int rmq[502][502][10][10];
int n , m , a[505][505],Log[506];  /// a is the given matrix
void log_fun()
{
       for(int i=1;i<=505;i++){
        int j = 0 ;
        while(1<<(j+1)<=i) j++;
        Log[i] = j ;
    }
}
void preprocess () {
// point 0 base
    for(int i=0;i<ln;i++){
        for(int j=0;j<ln;j++){
            for(int x=0;x<n;x++){
                if (x+(1<<i)-1>n) break;
                for(int y=0;y<n;y++){
                    if (y+(1<<j)-1>n) break;
                    if (i==0 and j==0) {
                        rmq[x][y][0][0] = a[x][y] ;
                    }
                    else if (i==0) {
                        int yh = y + (1<<(j-1)) ;
                        rmq[x][y][0][j] = max(rmq[x][y][0][j-1],rmq[x][yh][0][j-1]) ;
                    }
                    else if (j==0) {
                        int xh = x + (1<<(i-1)) ;
                        rmq[x][y][i][0] = max(rmq[x][y][i-1][0],rmq[xh][y][i-1][0]) ;
                    }
                    else {
                        int xh = x + (1<<(i-1)) , yh = y + (1<<(j-1)) ;
                        rmq[x][y][i][j] = max(rmq[x][y][i][j-1],rmq[x][yh][i][j-1]) ;
                    }
                }
            }
        }
    }
}

int query(int x1,int y1,int x2,int y2) {        /// gives maximum of matrix with upper left point (x1,y1) and lower right point (x2,y2)
    int lx = x2-x1+1 , ly = y2-y1+1 , kx = 0 , ky = 0;
    kx = Log[lx] , ky = Log[ly] ;
    x2 = x2+1-(1<<kx) , y2 = y2+1-(1<<ky) ;
    return max({rmq[x1][y1][kx][ky],rmq[x1][y2][kx][ky],rmq[x2][y1][kx][ky],rmq[x2][y2][kx][ky]}) ;
}

int main () {

    //IN ;
   #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("Error.txt", "w", stderr);
    #endif 
    ios::sync_with_stdio(false); cin.tie(0);cout.tie(0);
    ll t,cs=0;
    cin>>t;
    log_fun();
    while(t--){
    cin >> n >> m ;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cin>>a[i][j];
        }
    }
    preprocess();
    cout<<"Case "<<++cs<<":\n";
    while(m--)
    {
        ll x1,y1,x2,y2,s;
        cin>>x1>>y1>>s;
        x1--;
        y1--;
        x2=x1+s-1;
        y2=y1+s-1;
        cout<<query(x1,y1,x2,y2)<<endl;
    }

}

    return 0 ;
}
