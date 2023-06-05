#include<bits/stdc++.h>
using namespace std;

template <class S, S (*op)(S, S), S (*e)()> struct segtree2d {
	public:
		segtree2d() : segtree2d(0, 0) {}
		explicit segtree2d(int h, int w) : segtree2d(vector<vector<S>>(h, vector<S>(w, e()))) {}
		explicit segtree2d(const vector<vector<S>>& u) : _h(int(u.size())), _w(int(u[0].size())) {
			hlog = ceil_pow(_h);
			hsize = 1 << hlog;
			wlog = ceil_pow(_w);
			wsize = 1 << wlog;
			v = vector<vector<S>>(2 * hsize, vector<S>(2 * wsize, e()));
			for (int i = 0; i < _h; i++) {
				for (int j = 0; j < _w; j++) {
						v[hsize + i][wsize + j] = u[i][j];
				}
			}
			for (int i = hsize * 2 - 1; i >= 1; i--) {
				if (i > hsize - 1) {
					for (int j = wsize - 1; j >= 1; j--) {
						update1(i, j);
					}
				}
				else {
					for (int j = wsize * 2 - 1; j >= 1; j--) {
						update2(i, j);
					}
				}
			}
		}
		void set(int p, int q, S x) {
			assert(0 <= p && p < _h && 0 <= q && q < _w);
			p += hsize;
			q += wsize;
			v[p][q] = x;
			for (int j = 1; j <= wlog; j++) {
				update1(p, q >> j);
			}
			for (int i = 1; i <= hlog; i++) {
				for (int j = 0; j <= wlog; j++) {
					update2(p >> i, q >> j);
				}
			}
		}
 
		S get(int p, int q) const {
			assert(0 <= p && p < _h && 0 <= q && q < _w);
			return v[p + hsize][q + wsize];
		}
 
		S prod(int u, int d, int l, int r) const {
			assert(0 <= l && l <= r && r <= _w && 0 <= u && u <= d && d <= _h);
			S smu = e(), smd = e();
			u += hsize;
			d += hsize;
 
			while (u < d) {
				if (u & 1) smu = op(smu, prod2(l, r, u++));
				if (d & 1) smd = op(prod2(l, r, --d), smd);
				u >>= 1;
				d >>= 1;
			}
			return op(smu, smd);
		}
 
		S all_prod() const { return v[1][1]; }
 
	private:
		int _h, hsize, hlog;
		int _w, wsize, wlog;
		std::vector<vector<S>> v;
 
		void update1(int i, int k) { v[i][k] = op(v[i][2 * k], v[i][2 * k + 1]); }
 
		void update2(int k, int j) { v[k][j] = op(v[2 * k][j], v[2 * k + 1][j]); }
 
		S prod2(int l, int r, int i) const {
			S sml = e(), smr = e();
			l += wsize;
			r += wsize;
 
			while (l < r) {
				if (l & 1) sml = op(sml, v[i][l++]);
				if (r & 1) smr = op(v[i][--r], smr);
				l >>= 1;
				r >>= 1;
			}
			return op(sml, smr);
		}
 
		int ceil_pow(int n) {
			int x = 0;
			while ((1U << x) < (unsigned int)(n)) x++;
			return x;
		}
};