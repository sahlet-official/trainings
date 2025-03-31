#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace solve1
{
    
    namespace LinkCutTree {
        struct Lazy {
            int a = 1, b = 0;
            bool empty(){ return (a == 1 && b == 0); }
        };
        
        struct Node {
            Lazy tag;
            Node* children[2] = {nullptr, nullptr};
            Node* parent = nullptr;
            bool reversed = false;
            int size, value, sum, minValue, maxValue, id;
            static int idcounter;

            Node(int val = 0) : id(++idcounter) {
                set(val);
            }
            
            void apply(Lazy other) {
                minValue = minValue * other.a + other.b;
                maxValue = maxValue * other.a + other.b;
                value = value * other.a + other.b;
                sum = sum * other.a + size * other.b;
                tag = {tag.a * other.a, tag.b * other.a + other.b};
            }

            void set(int val) {
                value = val;
                pull();
            }

            void push() {
                if (reversed) {
                    swap(children[0], children[1]);
                    if (children[0]) children[0]->reversed ^= true;
                    if (children[1]) children[1]->reversed ^= true;
                    reversed = false;
                }
                if (!tag.empty()) {
                    if (children[0]) children[0]->apply(tag);
                    if (children[1]) children[1]->apply(tag);
                    tag = Lazy();
                }
            }

            void pull() {
                sum = minValue = maxValue = value;
                size = 1;
                for (int i = 0; i < 2; i++) {
                    if (children[i]) {
                        minValue = min(minValue, children[i]->minValue);
                        maxValue = max(maxValue, children[i]->maxValue);
                        sum += children[i]->sum;
                        size += children[i]->size;
                    }
                }
            }

            bool isRoot() {
                return !parent || (parent->children[0] != this && parent->children[1] != this);
            }
        };
        int Node::idcounter = 0;

        void rotate(Node *x) {
            Node *p = x->parent, *g = p->parent;
            bool isLeftChild = (p->children[0] == x);
            bool pWasRoot = p->isRoot();

            p->children[!isLeftChild] = x->children[isLeftChild];
            if (x->children[isLeftChild]) {
                x->children[isLeftChild]->parent = p;
            }
        
            x->children[isLeftChild] = p;
            p->parent = x;
        
            x->parent = g;
            if (g && !pWasRoot) {
                g->children[g->children[1] == p] = x;
            }
        
            p->pull();
            x->pull();
        }

        void splay(Node *x) {
            while (!x->isRoot()) {
                Node *p = x->parent, *g = p->parent;
                if (!p->isRoot()) g->push();
                p->push();
                x->push();
                if (!p->isRoot()) {
                    bool zigZig = (g->children[0] == p) == (p->children[0] == x);
                    rotate(zigZig ? p : x);
                }
                rotate(x);
            }
            x->push();
            x->pull();
        }

        Node* access(Node *x) {
            Node *last = nullptr;
            for (Node *y = x; y; y = y->parent) {
                splay(y);
                y->children[1] = last;
                y->pull();
                last = y;
            }
            splay(x);
            return last;
        }

        void evert(Node *x) {
            access(x);
            x->reversed ^= true;
        }

        void link(Node *x, Node *y) {
            evert(x);
            x->parent = y;
        }

        void cut(Node *x, Node *y) {
            evert(x);
            access(y);
            if (y->children[0]) y->children[0]->parent = nullptr;
            y->children[0] = nullptr;
            y->pull();
        }

        Node* path(Node *x, Node *y) {
            evert(x);
            access(y);
            return y;
        }

        Node* LCA(Node *x, Node *y) {
            access(x);
            return access(y);
        }

        bool connected(Node *x, Node *y) {
            path(x, y);
            while (y->children[0])
                y = y->children[0];
            return x == y;
        }
    }    

    const int maxN = 2e5;
    LinkCutTree::Node LCT[maxN + 1];

    int N, Q;

    void solve()
    {
        scanf("%d%d", &N, &Q);

        for (int i = 1; i <= N; i++)
        {
            int val = 0;
            scanf("%d", &val);

            LCT[i].set(val);
        }

        for (int i = 2; i <= N; i++)
        {
            int a = 0, b = 0;
            scanf("%d%d", &a, &b);

            link(&LCT[a], &LCT[b]);
        }

        for (int i = 1; i <= Q; i++)
        {
            int t = 0, b = 0;
            scanf("%d", &t);
            
            if (t == 1)
            {
                int node = 0, val = 0;
                scanf("%d%d", &node, &val);

                LinkCutTree::access(&LCT[node]);
                LCT[node].set(val);
            }
            else if (t == 2)
            {
                int node1 = 0, node2 = 0;
                scanf("%d%d", &node1, &node2);

                auto path = LinkCutTree::path(&LCT[node1], &LCT[node2]);
                
                printf("%d\n", path->maxValue);
            }
        }
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    std::ios::sync_with_stdio(false);
    // ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    // std::cout.tie(0);

    long long testsNumber = 1;

    // cin >> testsNumber;
    // scanf("%lld", &testsNumber);

    for (long long i = 0; i < testsNumber; i++)
    {
        solve1::solve(); 
    }

    return 0;
}