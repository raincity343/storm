#include <bits/stdc++.h>

using namespace std;

#define all(x) begin(x), end(x)
#define len(x) int((x).size())

using ll = long long;

template <class T>
inline bool chmin(T &a, const T &b) {
  if (b < a) {
    a = b;
    return true;
  } else {
    return false;
  }
}

template <class T>
inline bool chmax(T &a, const T &b) {
  if (a < b) {
    a = b;
    return true;
  } else {
    return false;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.exceptions(ios::failbit);
}
