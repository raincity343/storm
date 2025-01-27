template <int mod>
struct modint {
  using mint = modint;

  static constexpr int getMod() {
    return mod;
  }

  int v;

  modint(ll v_ = 0) : v(v_ % mod) {
    v += (v < 0) * mod;
  }

  mint &operator+=(mint x) {
    v += x.v, v -= (v >= mod) * mod;
    return *this;
  }

  mint &operator-=(mint x) {
    v -= x.v, v += (v < 0) * mod;
    return *this;
  }

  mint &operator*=(mint x) {
    v = ll(v) * x.v % mod;
    return *this;
  }

  friend mint operator+(mint x, mint y) {
    return x += y;
  }

  friend mint operator-(mint x, mint y) {
    return x -= y;
  }

  friend mint operator*(mint x, mint y) {
    return x *= y;
  }

  mint pow(ll n) const {
    assert(n >= 0);
    mint ans = 1, mul = *this;
    for (; n > 0; n >>= 1) {
      if ((n & 1) == 1) {
        ans *= mul;
      }
      mul *= mul;
    }
    return ans;
  }

  mint inv() const {
    return pow(mod - 2);
  }
};
