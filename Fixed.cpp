using namespace std;
#include <type_traits>


template<int N, int M>
class Fixed {
    static_assert(N == 8 || N == 16 || N == 32 || N == 64 || N == 128);
    using StorageType = typename std::conditional<N == 8, int8_t,
        typename std::conditional<N == 16, uint16_t,
        typename std::conditional<N == 32, uint32_t,
        typename std::conditional<N == 64, uint64_t, void>::type>::type>::type>::type;

public:
    StorageType v;

    constexpr Fixed(int v): v(v << M) {}
    constexpr Fixed(float f): v(f * (1 << M)) {}
    constexpr Fixed(double f): v(f * (1 << M)) {}
    constexpr Fixed(): v(0) {}

    static constexpr Fixed from_raw(__int128_t x) {
        Fixed ret;
        ret.v = x;
        return ret;
    }
    template<int N1, int M1>
    constexpr Fixed(const Fixed<N1, M1>& other) {
        if (M1 > M) {
            v = other.v >> (M1 - M);
        } else if (M1 < M) {
            v = other.v << (M - M1);
        } else {
            v = other.v;
        }
    }

    bool operator==(const Fixed&) const = default;

    template<int N1, int M1>
    bool operator==(const Fixed<N1, M1>& qq) const {
        Fixed<N, M> tmp(qq);
        return tmp == *this;
    }

    template<typename T>
    requires std::is_arithmetic_v<T>
    bool operator==(const T& qq) const {
        Fixed<N, M> tmp(qq);
        return tmp == *this;
    }

    operator float() const {
        return static_cast<float>(v << M);
    }

    operator double() const {
        return static_cast<double>(v << M);
    }


    std::strong_ordering operator<=>(const Fixed& other) const {
        return v <=> other.v;
    };

    template<typename T>
    requires std::is_arithmetic_v<T>
    std::strong_ordering operator<=>(const T& other) const {
        Fixed<N, M> tmp(other);
        return *this <=> tmp;
    }

    template<int N1, int M1>
    std::strong_ordering operator<=>(const Fixed<N1, M1>& other) const {
        Fixed tmp(other);
        return *this <=> tmp;
    }
};




constexpr std::array<pair<int, int>, 4> deltas{{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}};

template<int N, int M>
static constexpr Fixed<N, M> inf = Fixed<N, M>::from_raw(std::numeric_limits<int32_t>::max());

template<int N, int M>
static constexpr Fixed<N, M> eps = Fixed<N, M>::from_raw(deltas.size());

template<int N, int M>
Fixed<N, M> operator+(Fixed<N, M> a, Fixed<N, M> b) {
    return Fixed<N, M>::from_raw(a.v + b.v);
}

template<int N, int M, typename T>
Fixed<N, M> operator+(Fixed<N, M> a, T b) {
    return a + Fixed<N, M>(b);
}

template<int N, int M>
Fixed<N, M> operator-(Fixed<N, M> a, Fixed<N, M> b) {
    return Fixed<N, M>::from_raw(a.v - b.v);
}

template<int N, int M, typename T>
Fixed<N, M> operator-(Fixed<N, M> a, T b) {
    return a - Fixed<N, M>(b);
}

template<int N, int M>
Fixed<N, M> operator*(Fixed<N, M> a, Fixed<N, M> b) {
    return Fixed<N, M>::from_raw(((__int128) a.v * b.v) >> M);
}

template<int N, int M, typename T>
Fixed<N, M> operator*(Fixed<N, M> a, T b) {
    return a * Fixed<N, M>(b);
}

template<int N, int M>
Fixed<N, M> operator/(Fixed<N, M> a, Fixed<N, M> b) {
    return Fixed<N, M>::from_raw(((__int128) a.v << M) / b.v);
}

template<int N, int M, typename T>
Fixed<N, M> operator/(Fixed<N, M> a, T b) {
    return a / Fixed<N, M>(b);;
}

template<int N, int M>
Fixed<N, M> &operator+=(Fixed<N, M> &a, Fixed<N, M> b) {
    return a = a + b;
}

template<int N, int M, typename T>
Fixed<N, M> &operator+=(Fixed<N, M> &a, T b) {
    return a = a + b;
}

template<int N, int M>
Fixed<N, M> &operator-=(Fixed<N, M> &a, Fixed<N, M> b) {
    return a = a - b;
}

template<int N, int M, typename T>
Fixed<N, M> &operator-=(Fixed<N, M> &a, T b) {
    return a = a - b;
}

template<int N, int M>
Fixed<N, M> &operator*=(Fixed<N, M> &a, Fixed<N, M> b) {
    return a = a * b;
}

template<int N, int M, typename T>
Fixed<N, M> &operator*=(Fixed<N, M> &a, T b) {
    return a = a * b;
}

template<int N, int M>
Fixed<N, M> &operator/=(Fixed<N, M> &a, Fixed<N, M> b) {
    return a = a / b;
}

template<int N, int M, typename T>
Fixed<N, M> &operator/=(Fixed<N, M> &a, T b) {
    return a = a / Fixed<N, M>(b);
}

template<int N, int M>
Fixed<N, M> operator-(Fixed<N, M> x) {
    return Fixed<N, M>::from_raw(-x.v);
}

template<int N, int M>
Fixed<N, M> abs(Fixed<N, M> x) {
    if (x.v < 0) {
        x.v = -x.v;
    }
    return x;
}

template<int N, int M>
ostream &operator<<(ostream &out, Fixed<N, M> x) {
    return out << x.v / (double) (1 << M);
}

template<typename T1, typename T>
T1 min(const T1 a, const T& b) {
    return b > a ? a : T1(b);
}



template<typename T, int N, int M>
requires std::is_arithmetic_v<T>
T operator+(T a, Fixed<N, M> b) {
    return a + (T)(b.v << M);
}

template<typename T, int N, int M>
requires std::is_arithmetic_v<T>
T operator-(T a, Fixed<N, M> b) {
    return a - (T)(b.v << M);
}

template<typename T, int N, int M>
requires std::is_arithmetic_v<T>
T operator*(T a, Fixed<N, M> b) {
    return a * (T)(b.v << M);
}

template<typename T, int N, int M>
requires std::is_arithmetic_v<T>
T operator/(T a, Fixed<N, M> b) {
    return a / (T)(b.v << M);
}

template<int N, int M, typename T>
requires std::is_arithmetic_v<T>
T &operator+=(T &a, Fixed<N, M> b) {
    return a = a + b;
}

template<int N, int M, typename T>
requires std::is_arithmetic_v<T>
T &operator-=(T &a, Fixed<N, M> b) {
    return a = a - b;
}

template<int N, int M, typename T>
requires std::is_arithmetic_v<T>
T &operator*=(T &a, Fixed<N, M> b) {
    return a = a * b;
}

template<int N, int M, typename T>
requires std::is_arithmetic_v<T>
T &operator/=(T &a, Fixed<N, M> b) {
    return a = a / b;
}


mt19937 rnd(1337);

template<int N, int M>
Fixed<N, M> random01(Fixed<N, M> val) {
    return Fixed<N, M>::from_raw((rnd() & (((int64_t)1 << M) - 1)));
}

float random01(float val) {
    return rand() / (float) RAND_MAX;
}

double random01(double val) {
    return rand() / (double) RAND_MAX;
}
