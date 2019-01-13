#include <bits/stdc++.h>

using namespace std;

// Compile time operations with fractions
namespace FractionComputer {
    template <int a, int b> struct Frac {
        static const int Num = a;
        static const int Den = b;
    };
    template <int X, int Y> struct GCD {
        static const int x = X;
        static const int y = Y;
        static const int result = GCD <y, x % y>::result;
    };
    template <int X> struct GCD <X, 0> {
        static const int result = X;
    };
    template <typename F> struct Simpl {
        static const int d = GCD <F::Num, F::Den>::result;
        typedef Frac <F::Num / d, F::Den / d> result;
    };
    template <typename F1, typename F2> struct Add {
        static const int a = F1::Num;
        static const int b = F1::Den;
        static const int c = F2::Num;
        static const int d = F2::Den;
        typedef typename Simpl <Frac <a * d + b * c, b * d> >::result result;
    };
}

// Compile time computing of e = 2.71...
namespace EComputer {
    using namespace FractionComputer;

    template <int N> struct Factorial {
        static const int value = N * Factorial <N - 1>::value;
    };
    template <> struct Factorial <0> {
        static const int value = 1;
    };

    template <int N> struct Euler {
        typedef typename Add <typename Euler <N - 1>::result, Frac <1, Factorial <N>::value> >::result result;
    };

    template <> struct Euler <0> {
        typedef Frac <1, 1> result;
    };

    void demo() {
        cout << Euler <0>::result::Num << ' ' << Euler <0>::result::Den << endl;
        cout << Euler <1>::result::Num << ' ' << Euler <1>::result::Den << endl;
        cout << Euler <2>::result::Num << ' ' << Euler <2>::result::Den << endl;
        cout << Euler <3>::result::Num << ' ' << Euler <3>::result::Den << endl;
        cout << Euler <4>::result::Num << ' ' << Euler <4>::result::Den << endl;
        cout << Euler <5>::result::Num << ' ' << Euler <5>::result::Den << endl;
        cout << Euler <6>::result::Num << ' ' << Euler <6>::result::Den << endl;
        cout << Euler <7>::result::Num << ' ' << Euler <7>::result::Den << endl;
    }
}

// Compile time linked lists
namespace ListComputer {
    // Define Integers - cheating, Peano would have sufficed
    template <int N> struct Int {
        static const int val = N;
    };

    // Define Linked Lists
    struct Nil;
    template <typename H, typename T = Nil> struct List {
        typedef H head;
        typedef T tail;
    };

    // Define length
    template <typename Lst> struct Length {
        static const int val = 1 + Length <typename Lst::tail>::val;
    };
    template <> struct Length <Nil> {
        static const int val = 0;
    };

    // Define NTh element
    template <typename Lst, int N> struct GetNth {
        typedef typename Lst::tail tl;
        typedef typename GetNth <tl, N - 1>::result result;
    };
    template <typename Lst> struct GetNth <Lst, 0> {
        typedef typename Lst::head result;
    };

    // Define catenation
    template <typename L1, typename L2 = Nil> struct Concat {
        typedef typename L1::head new_head;
        typedef typename Concat <typename L1::tail, L2>::result new_tail;
        typedef List <new_head, new_tail> result;
    };
    template <typename L2> struct Concat <Nil, L2> {
        typedef L2 result;
    };

    // Define print
    template <typename L> struct Print {
        static void print() {
            cout << L::head::val << ' ';
            Print <typename L::tail>::print();
        }
    };
    template <> struct Print <Nil> {
        static void print() {
            cout << "#" << endl;
        }
    };

    // Define fmap
    template <typename L, template <typename> typename F> struct Map {
        typedef typename F <typename L::head>::result new_head;
        typedef typename Map <typename L::tail, F>::result new_tail;
        typedef List <new_head, new_tail> result;
    };
    template <template <typename> typename F> struct Map <Nil, F> {
        typedef Nil result;
    };

    // Define (+10)
    template <typename T> struct Add10;
    template <int X> struct Add10 <Int <X> > {
        typedef Int <X + 10> result;
    };

    // Define type equality
    template <typename X, typename Y> struct Eq {
        static const int value = false;
    };
    template <typename X> struct Eq <X, X> {
        static const int value = true;
    };

    // Define List containment
    template <typename L, typename Elem> struct Contains {
        static const bool value = Eq <typename L::head, Elem>::value ||
                                  Contains <typename L::tail, Elem>::value;
    };
    template <typename Elem> struct Contains <Nil, Elem> {
        static const bool value = false;
    };

    // Define GetPos
    template <typename L, typename Elem> struct GetPos;
    template <bool, typename, typename> struct if_value {
        static const int value = 0;
    };
    template <typename T, typename Elem> struct if_value <false, T, Elem> {
        static const int value = 1 + GetPos <T, Elem> :: value;
    };
    template <typename L, typename Elem> struct GetPos {
        typedef typename L::head H;
        typedef typename L::tail T;
        static const bool found = Eq <H, Elem>::value;
        static const int value = if_value <found, T, Elem>::value;
    };
    template <typename Elem> struct GetPos <Nil, Elem> {
        static_assert(sizeof(Elem) < 0, "Failed to find element in list!");
    };

    // Q: Does this compile?
    // Q': In what circumstances is the C++ compiler "lazy"? (i.e. partial instantiation)
    // template <int N> struct A {
    //     static const bool val1 = true;
    //     static const bool val2 = true ? true : (A <N - 1> :: val2);
    // };
}

int main() {
    // Demo for liked lists
    using namespace ListComputer;

    typedef List <Int <3>, List <Int <2>, List<Int<1>>> > l2;
    typedef List <Int <6>, List <Int <5>, List<Int<4>>> > l1;
    typedef Concat <l1, l2>::result l3;

    typedef Map <l3, Add10>::result ans;

    Print <l3>::print();
    Print <ans>::print();

    cout << GetNth <l3, 0>::result::val << endl;
    cout << GetNth <l3, 1>::result::val << endl;
    cout << GetNth <l3, 2>::result::val << endl;
    cout << GetNth <l3, 3>::result::val << endl;
    cout << GetNth <l3, 4>::result::val << endl;
    cout << GetNth <l3, 5>::result::val << endl;

    cout << Contains <l3, Int <4> >::value << endl;
    cout << Contains <l3, Int <10> >::value << endl;
    
    // Q: Which of these do compile? 
    cout << GetPos <ans, Int <16> > :: value << endl;
    cout << GetPos <ans, Int <11> > :: value << endl;
    cout << GetPos <ans, Int <14> > :: value << endl;
    cout << GetPos <ans, Int <13> > :: value << endl;
    cout << GetPos <ans, Int <12> > :: value << endl;
    cout << GetPos <ans, Int <11> > :: value << endl;
    cout << GetPos <ans, Int <10> > :: value << endl;
    return 0;
}
