struct Node {
    int maxPref,sum;
    Node() {
        maxPref=0,sum=0;
    }
};
 
struct Tree {
    int n;
    vector<int>a;
    vector<Node>seg;
    Tree(vector<int>&x) {
        a=x;
        n=ssize(a);
        int sz=1;
        while(sz<2*n) sz<<=1;
        seg.resize(sz,Node());
        build(1,0,n-1);
    }
    Node merge(Node &l,Node &r) {
        Node curr;
        curr.maxPref=max({l.sum+r.sum,l.maxPref,l.sum+r.maxPref});
        curr.sum=l.sum+r.sum;
        return curr;
    }
    void build(int index,int start,int end) {
        if(start==end) {
            seg[index].maxPref=a[start];
            seg[index].sum=a[start];
            return;
        }
        int mid=(start+end)/2;
        build(2*index,start,mid);
        build(2*index+1,mid+1,end);
        seg[index]=merge(seg[2*index],seg[2*index+1]); 
    }
    void update(int index,int start,int end,int pt,int val) {
        if(start==end) {
            seg[index].maxPref=val;
            seg[index].sum=val;
            return;
        }
        int mid=(start+end)/2;
        if(pt<=mid) {
            update(2*index,start,mid,pt,val);
        }
        else {
            update(2*index+1,mid+1,end,pt,val);
        }
        seg[index]=merge(seg[2*index],seg[2*index+1]);
    }
    Node query(int index,int start,int end,int qL,int qR) {
        if(start>=qL and end<=qR) {
            return seg[index];
        }
        if(start>qR or end<qL) {
            return Node();
        }
        int mid=(start+end)/2;
        auto ansL=query(2*index,start,mid,qL,qR);
        auto ansR=query(2*index+1,mid+1,end,qL,qR);
        return merge(ansL,ansR);
    }
    int make_query(int l,int r) {
        auto q=query(1,0,n-1,l,r);
        return max(q.maxPref,q.sum);
    }
    void make_update(int p,int val) {
        update(1,0,n-1,p,val);
    }
};
