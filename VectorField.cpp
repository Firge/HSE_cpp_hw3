#include "Headers.h"
#include "Fixed.cpp"
using namespace std;


template<int N, int M, class T>
class VectorField {
public:
    array<T, deltas.size()> v[N][M];

    template<typename T1>
    T &add(int x, int y, int dx, int dy, T1 dv) {
        return get(x, y, dx, dy) += dv;
    }

    T &get(int x, int y, int dx, int dy) {
//         size_t i = ranges::find(deltas, pair(dx, dy)) - deltas.begin();
//         assert(i < deltas.size());
//         return v[x][y][i];
        return v[x][y][((dy & 1) << 1) | (((dx & 1) & ((dx & 2) >> 1)) | ((dy & 1) & ((dy & 2) >> 1)))];

    }
};
