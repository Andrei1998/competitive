#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

double getProgrTerm(double A, double R, int n) {
    return A + (n - 1.0) * R;
}

double getProgrSum(double A, double R, int n) {
    return (A + getProgrTerm(A, R, n)) * n / 2.0;
}

struct Node {
    int st, dr;

    double sum;
    double lazyA;
    double lazyR;

    Node *left, *right;

    Node(int _st = 0, int _dr = 0, double _sum = 0, double _lazyA = 0, double _lazyR = 0, Node *_left = NULL, Node *_right = NULL):
        st(_st), dr(_dr), sum(_sum), lazyA(_lazyA), lazyR(_lazyR), left(_left), right(_right) {}

    ~Node() {
        if (left != NULL)
            delete left;
        if (right != NULL)
            delete right;
    }

    void computeSum() {
        sum = 0;
        if (left != NULL)
            sum += left -> sum;
        if (right != NULL)
            sum += right -> sum;
    }

    void makeLazy(double A, double R) {
        if (st < dr) {
            lazyA += A;
            lazyR += R;
        }
        sum += getProgrSum(A, R, dr - st + 1);
    }

    void propagate() {
        if (lazyA || lazyR) {
            if (left == NULL)
                left = new Node(st, (st + dr) >> 1);
            left -> makeLazy(lazyA, lazyR);

            if (right == NULL)
                right = new Node(((st + dr) >> 1) + 1, dr);
            right -> makeLazy(getProgrTerm(lazyA, lazyR, ((st + dr) >> 1) - st + 2), lazyR);

            lazyA = 0;
            lazyR = 0;
        }
    }
};

int N;

Node *compress(Node *node) {
    if (node -> st == 1 && node -> dr == N)
        return node;

    if (!node -> lazyA && !node -> lazyR && (node -> left == NULL || node -> right == NULL)) {
        Node *aux = node;
        if (node -> left == NULL)
            node = node -> right;
        else
            node = node -> left;
        aux -> left = aux -> right = NULL;
        delete aux;
    }

    return node;
}

Node *expand(Node *node, int st, int dr) {
    if (node == NULL)
        return node;

    if (node -> st != st || node -> dr != dr) {
        int mid = (st + dr) >> 1;

        if (node -> dr <= mid)
            node = new Node(st, dr, node -> sum, 0, 0, node, NULL);
        else
            node = new Node(st, dr, node -> sum, 0, 0, NULL, node);
    }

    return node;
}

double repo;

Node* reset(Node *node, int st, int dr) {
    if (node == NULL)
        return NULL;

    if (node -> st == st && node -> dr == dr) {
        repo += node -> sum;
        delete node;
        return NULL;
    }
    node -> propagate();

    int mid = (node -> st + node -> dr) >> 1;

    if (dr <= mid) {
        node -> left = expand(node -> left, node -> st, mid);
        node -> left = reset(node -> left, st, dr);
    }
    else if (st > mid) {
        node -> right = expand(node -> right, mid + 1, node -> dr);
        node -> right = reset(node -> right, st, dr);
    }
    else {
        node -> left = expand(node -> left, node -> st, mid);
        node -> right = expand(node -> right, mid + 1, node -> dr);
        node -> left = reset(node -> left, st, mid);
        node -> right = reset(node -> right, mid + 1, dr);
    }

    node -> computeSum();
    node = compress(node);
    return node;
}

void add(Node *node, int st, int dr, double A, double R) {
    if (node -> st == st && node -> dr == dr) {
        node -> makeLazy(A, R);
        return ;
    }
    node -> propagate();

    int mid = (node -> st + node -> dr) >> 1;
    if (dr <= mid) {
        if (node -> left == NULL)
            node -> left = new Node(st, (st + dr) >> 1);

        node -> left = expand(node -> left, node -> st, mid);
        add(node -> left, st, dr, A, R);
    }
    else if (st > mid) {
        if (node -> right == NULL)
            node -> right = new Node(((st + dr) >> 1) + 1, dr);

        node -> right = expand(node -> right, mid + 1, node -> dr);
        add(node -> right, st, dr, A, R);
    }
    else {
        if (node -> left == NULL)
            node -> left = new Node(st, (st + dr) >> 1);
        if (node -> right == NULL)
            node -> right = new Node(((st + dr) >> 1) + 1, dr);

        node -> left = expand(node -> left, node -> st, mid);
        node -> right = expand(node -> right, mid + 1, node -> dr);
        add(node -> left, st, mid, A, R);
        add(node -> right, mid + 1, dr, getProgrTerm(A, R, mid - st + 2), R);
    }

    node -> computeSum();
    node = compress(node);
}

int main()
{
    //ios_base :: sync_with_stdio(false);
    //cin.tie(0);

    int p;
    cin >> N >> p;

    Node *root = new Node(1, N);

    int M = 0;
    cin >> M;

    int lastT = 0;
    while (M --) {
        int t;
        cin >> t;

        if (t > lastT) {
            add(root, 1, N, 1.0 * p * (t - lastT), 0);
            lastT = t;
        }

        string action;
        cin >> action;

        if (action == "save") {
            int l, r;
            cin >> l >> r;

            root = reset(root, l, r);
            if (root == NULL)
                root = new Node(1, N);
            cout << fixed << setprecision(8) << repo << '\n';
        }
        else {
            int where, d;
            cin >> where >> d;

            double A = repo / (1.0 * d * d);
            double B = A;

            add(root, where - d + 1, where, A, B);
            if (d > 1)
                add(root, where + 1, where + d - 1, (d - 1.0) * A, -B);
            repo = 0;
        }
    }
    return 0;
}
