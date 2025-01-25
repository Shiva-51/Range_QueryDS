class STable {
public:
    int n,LOG;
    vector<vector<int>>dp;
    vector<int>a,LogT;
    STable(vector<int>&x) {
        a=x;
        n=ssize(a);
        LOG=log2(n)+1;
        LogT.resize(n+1);
        dp.resize(LOG+1,vector<int>(n+1));
        build();
    }
    int merge(int l,int r) {
        return min(l,r);
    }
    void build() {
        for(int i=2;i<=n;i++) {
            LogT[i]=1+LogT[i/2];
        }
        for(int i=0;i<n;i++) dp[0][i]=a[i];
        for(int i=1;i<LOG;i++) {
            for(int j=0;j+(1ll<<(i-1))<=n;j++) {
                dp[i][j]=merge(dp[i-1][j],dp[i-1][j+(1ll<<(i-1))]);
            }
        }
    }
    int make_query(int l,int r) {
        int N=r-l+1;
        int lp=LogT[N];
        return merge(dp[lp][l],dp[lp][r-(1<<lp)+1]);
    }
    int make_query2(int l,int r) { //Non-idem
        int N=r-l+1;
        int ans=INT_MAX;
        for(int i=20;i>=0;i--) {
            if((1<<i)&N) {
                ans=merge(ans,dp[i][l]);
                l+=(1<<i);
            }
        }
    }
};
