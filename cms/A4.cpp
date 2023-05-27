#include <bits/extc++.h>
using namespace std;
int main() {
    int n, i, sum = 0;
    cin >> n;
    vector<int> graph(10005, 0);
    for (int s = 0, p; s < n; s++) {
        cin >> p;
        if (s)
            if (graph[p] != 0)
                return 1;
            else if (graph[p + 1] == 0 && graph[p - 1] == 0)
                return 1;
        graph[p] = (s & 1) ? 1 : -1;
        // cout << "test\n";
        for (i = p + 1; i <= 10000; i++) {
            // cout << "t\t" << i << endl;
            if (graph[p] == graph[i]) {
                for (i--; i > p; i--) graph[i] = graph[p];
                break;
            }
            if (graph[i] == 0) break;
        }
        // cout << "test\n";
        for (i = p - 1; i > 0; i--) {
            // cout << "t\t" << i << endl;
            if (graph[p] == graph[i]) {
                for (i++; i < p; i++) graph[i] = graph[p];
                break;
            }
            if (graph[i] == 0) break;
        }
        //        for (int d = 0; d < 10005; d++)
        //           if (graph[d])   cout << d << ". " << graph[d] << endl;
    }
    for (int v : graph) sum += v;
    // cout << sum << endl;
    if (sum > 0)
        cout << "BrineTW\n";
    else if (sum < 0)
        cout << "Repkironca\n";
    else
        cout << "Aaw\n";
}
