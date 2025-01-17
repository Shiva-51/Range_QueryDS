class Tree {
public:
    struct Node {
        int tot,pref,suff,maxi;
        Node() {
            tot=0;
            pref=suff=maxi=LLONG_MIN;
        }
    };
    int n;
    vector<int>a;
    vector<Node>seg;
    Tree(vector<int> &x) {
        a=x;
        n=ssize(a);
        seg.resize(4*n,Node());
        build(1,0,n-1);
    }
    Node merge(auto &l,auto &r) {
        Node curr;
        curr.tot=l.tot+r.tot;
        curr.maxi=max({l.pref,r.pref,l.suff,r.suff,l.tot+r.tot,l.suff+r.pref,l.maxi,r.maxi});
        curr.pref=max({l.pref,l.tot+r.pref});
        curr.suff=max({r.suff,l.suff+r.tot});
        return curr;
    }
    void build(int index,int start,int end) {
        if(start==end) {
            seg[index].tot=a[start];
            seg[index].pref=a[start];
            seg[index].suff=a[start];
            seg[index].maxi=a[start];
            return;
        }
        int mid=(start+end)/2;
        build(2*index,start,mid);
        build(2*index+1,mid+1,end);
        seg[index]=merge(seg[2*index],seg[2*index+1]);
    }
    void update(int index,int start,int end,int pt,int val) {
        if(start==end) {
            seg[index].tot=val;
            seg[index].pref=val;
            seg[index].suff=val;
            seg[index].maxi=val;
            return;
        }
        int mid=(start+end)/2;
        if(pt<=mid) {
            update(2*index,start,mid,pt,val);
        }
        else{
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
    void make_update(int pt,int val) {
        update(1,0,n-1,pt,val);
    }
    int make_query(int l,int r) {
        return query(1,0,n-1,l,r).maxi;
    }
};
