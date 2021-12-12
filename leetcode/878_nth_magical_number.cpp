#include <iostream>
#include <vector>

#define INF 1000000007

using namespace std;

typedef long long int ll;
typedef vector<int> vi;
typedef pair<int, int> ii;

class Solution {
public:
    int gcd(int a, int b) {
        if (a == b) return a;
        if (a > b) swap(a, b);
        return gcd(a, b-a);
    }
    int lcm(int a, int b) {
        return a * b / gcd(a, b);
    }
    int nthMagicalNumber(int n, int a, int b) {
        if (a > b) swap(a, b);
        // speedup with lcm
        ll temp = lcm(a, b);
        int ma = temp / a, mb = temp / b;
        temp = n / (ma + mb - 1);
        n -= temp * (ma + mb - 1);
        temp = (ll) a * (ll) ma * temp;
        ll n1, n2, curr;
        n1 = n2 = curr = temp;
        n1 += a; n2 += b;
        while (n-- > 0) {
            if (n1 > n2) {
                curr = n2;
                n2 += b;
            } else {
                curr = n1;
                n1 += a;
            }
        }
        return (int) (curr % INF);
    }

    int nthMagicalNumber2(int n, int a, int b) {
        // find lcm and s p e e d
        ll curr, n1, n2;
        int i = 1, j = 1, mi = INF, mj = INF, temp;
        if (a == b) {
            return (int) (((ll) a * (ll) n )% INF);
        } else if (a > b) {
            swap(a, b);
        }
        while (n-- > 0) {
            n1 = (ll) a * i;
            n2 = (ll) b * j;
            if (n1 < n2) {
                curr = n1;
                i++;
            } else if (n2 < n1) {
                curr = n2;
                j++;
            } else if (mi == INF) {
                mi = i;
                mj = j;
                // speedup based on lcm
                temp = n / (mi + mj - 1);
                i += mi * temp;
                j += mj * temp;
                n -= (mi + mj - 1) * temp;
                if (n != 0) { n++; i++; }
                curr = (ll) a * i;
            }
            // cout << i << " " << j << " " << n << " " << curr << endl;
        }
        return (int) (curr % (INF));
    }
};

int main() {
    Solution t;
    cout << t.nthMagicalNumber(8, 8, 8) << endl;
    cout << "done" << endl;
    return 0;
}