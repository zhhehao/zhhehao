#include <cstdio>
#include <cstring>
#include <queue>
#include <stack>
using namespace std;
char buf[20];
int num[9], sign[10], n, ans[20], si[10], cnt;
const int ten[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
bool yes;

void init() {
    memset(num, 0, sizeof(num));
    for (n = 0; buf[n] != '='; n++) {
        num[n] = buf[n] - '0';
    }
}

inline int gnum(int s, int e) {
    int len = e - s;
    int sum = 0;
    for (int i = s; i <= e; i++) {
        sum += ten[len--]*num[i];
    }
    return sum;
}

void cal() {
    stack<int> s1; while (!s1.empty()) s1.pop();
    queue<int> q; while (!q.empty()) q.pop();
    int len = cnt + cnt + 1;
    for (int i = 0; i < len; i++) {
        if (ans[i] >= 0) q.push(ans[i]);
        else {
            if (s1.empty()) {
                s1.push(ans[i]);
                continue;
            }
            else {
                if (ans[i] == -3) {
                    while (s1.top() == -3) {
                        q.push(s1.top());
                        s1.pop();
                        if (s1.empty()) break;
                    }
                    s1.push(ans[i]);
                }
                else {
                    while (!s1.empty()) {
                        q.push(s1.top());
                        s1.pop();
                    }
                    s1.push(ans[i]);
                }
            }

        }
    }
    while (!s1.empty()) {
        q.push(s1.top());
        s1.pop();
    }
    stack<int> s2; while (!s2.empty()) s2.pop();
    int rem;
    for (;;) {
        if (q.empty()) {
            rem = s2.top(); s2.pop();
            break;
        }
        if (q.front() >= 0) {
            s2.push(q.front());
            q.pop();
        }
        else if (q.front() == -1) {
            int q1 = s2.top(); s2.pop();
            int q2 = s2.top(); s2.pop();
            s2.push(q1+q2);
            q.pop();
        }
        else if (q.front() == -2) {
            int q2 = s2.top(); s2.pop();
            int q1 = s2.top(); s2.pop();
            s2.push(q1-q2);
            q.pop();
        }
        else if (q.front() == -3) {
            int q1 = s2.top(); s2.pop();
            int q2 = s2.top(); s2.pop();
            s2.push(q1*q2);
            q.pop();
        }
    }
    if (rem == 2000) {
        if (!yes) yes = true;
        printf("  ");
        for (int i = 0; i < len; i++) {
            if (ans[i] >= 0) printf("%d", ans[i]);
            else if (ans[i] == -1) printf("%c", '+');
            else if (ans[i] == -2) printf("%c", '-');
            else if (ans[i] == -3) printf("%c", '*');
        }
        printf("=\n");
    }
}

void prepcal() { // 生成计算表达式
    memset(ans, 0, sizeof(ans));
    int s = 0, e = -1, cc = 0, acc = 0;
    do {
        s = e + 1;
        if (cc == cnt)
            e = n - 1;
        else
            e = sign[cc++];
        ans[acc] = gnum(s, e);
        acc += 2;
    } while (e != n-1);
    acc = 1;
    for (int i = 0; i < cnt; i++) {
        ans[acc] = si[i];
        acc += 2;
    }
//    int len = cnt + cnt + 1;
//    for (int i = 0; i < len; i++)
//        printf("%d ", ans[i]);
//    printf("\n");
    cal();
}

void fillsign(int d) { // 递归生成符号
    if (d == cnt) {
        prepcal();
        return;
    }
    for (int i = 1; i <= 3; i++) {
        si[d] = -1 * i;
        fillsign(d+1);
    }
}

void getsign(int s) {
    memset(sign, -1, sizeof(sign));
    cnt = 0;
    for (int i = 0; i < n-1; i++) {
        if (s&(1<<i))
            sign[cnt++] = i;
    }
//    for (int i = 0; i < cnt; i++)
//        printf("%d ", sign[i]);
//    printf("\n");
    for (int i = 0; i < cnt; i++) // 先导0的判断
        if (num[sign[i]+1] == 0)
            if (sign[i+1] != sign[i]+1 && sign[i]+1 != n-1)
                return;
    memset(si, 0, sizeof(si));
    fillsign(0);
}

void solve() {
    yes = false;
    for (int i = 1; i < (1<<(n-1)); i++) { // 二进制枚举所有的符号插入子集
        getsign(i);
    }
    if (!yes) {
        printf("  IMPOSSIBLE\n");
    }
}

int main() {
    int kase = 0;
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
    while (scanf("%s", buf) && buf[0] != '=') {
        init();
        printf("Problem %d\n", ++kase);
        if (n <= 3) {
            printf("  IMPOSSIBLE\n");
            continue;
        }
        solve();
    }
    return 0;
}
