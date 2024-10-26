#include <iostream>
#include<string>
#include<vector>
#include<iterator>
#include<type_traits>
#include<iterator>
#include<algorithm>
#include<utility>
#include<fstream>

using namespace std;

int f(int);
bool g(int);
int h(int);

template <class T>
using ELEM = std::vector<T>;

template <class T>
using VEC = std::vector<ELEM<T>>;

template <class T>
using action_t = T(*) (int);

template <class T>
using pred_t = bool (*) (T);

template <class T>
using map_t = T(*) (T, T);

template <class T>
void printElem(ELEM<T>& v);

template <class T>
void initVec(VEC<T>& v, ELEM<T>&& cons);

template <class T>
void printVec(VEC<T>& v);

template <class T>
VEC<T> generate(int N, action_t<T> f);

template<class T>
VEC<T> zip(VEC<T>& v, VEC<T>& w);

template<class T>
VEC<T> filter(VEC<T>& v, pred_t<T> f);

template<class T>
VEC<T> map(VEC<T>& v, action_t<T> f);

template<class T>
ELEM<T> reduce(VEC<T>& v, map_t<T> f, ELEM<T> ident);



template<class T>
T k(T i,T j) {
    return i + j;
}


int main()
{
    VEC<int> v;
    initVec(v, ELEM<int>{1, 2, 3, 4});

    VEC<int> w;
    initVec(w, ELEM<int>{-1, 3, -3, 4});

    printVec(v);
    std::cout << std::string(10, '*') << std::endl;

    printVec(w);
    std::cout << std::string(10, '*') << std::endl;

    VEC<int> z = zip(v, w);
    printVec(z);
    std::cout << std::string(10, '*') << std::endl;

    VEC<int> x = zip(z, z);
    printVec(x);
    std::cout << std::string(10, '*') << std::endl;

    VEC<int> a = generate(10,f);// f is a function that squares 
    printVec(a);

    VEC<int> y = filter(w,g);// g is a bool function that returns true if arg > 0  
    printVec(y);

    VEC<int> u = map(w,h);// h is like g but returns 1 or 0
    printVec(u);

    ELEM<int> e = reduce(u, k, ELEM<int>{0});
    printElem(e);

    std::cout << std::endl << std::string(10, '$') << std::endl;

    VEC<std::string> ws;
    initVec(ws, ELEM<std::string>{"hello", "there", "franco", "carlacci"});
    printVec(ws);

    ELEM<std::string> es = reduce(ws, k, ELEM<std::string>{" "});
    printElem(es);

    VEC<char> wc;
    initVec(wc, ELEM<char>{'a', 'b', 'c', 'd'});
    std::cout << std::endl << std::string(10, '$') << std::endl;
    printVec(wc);

    ELEM<char> ec = reduce(wc, k, ELEM<char>{' '});
    std::cout << std::endl << std::string(10, '$') << std::endl;
    printElem(ec);

    cout << "\n\n";

    return 0;
}

int f(int a) {
    return a * a;
}

bool g(int a) {
    if (a > 0) {
        return true;
    }
    else {
        return false;
    }
}


int h(int a) {
    if (a > 0) {
        return 1;
    }
    else {
        return 0;
    }
}



template <class T>
void printElem(ELEM<T>& v) {
    if (v.size() > 1) cout << "(";

    for (auto e:v) {
        cout << e << " ";
    }

    if (v.size() > 1) cout << ")";
}

template <class T>
void initVec(VEC<T>& v, ELEM<T>&& cons) {
    for (auto i:cons) {
        v.push_back(ELEM<T>({i}));
    }
}

template <class T>
VEC<T> generate(int N, action_t<T> f) {
    VEC<T> temp;

    for (int i = 0; i < N;++i) {
        temp.push_back(ELEM<T>({f(i)}) );
    }
    return temp;
}

template <class T>
void printVec(VEC<T>& v) {
    cout << "[ ";

    for (auto i = 0; i<v.size();++i) {
        printElem(v[i]);
        cout << ( (i==v.size()-1) ? " " : ",");
    }

    cout << "]\n";

}

template<class T>
VEC<T> zip(VEC<T>& v, VEC<T>& w) {
    VEC<T> temp;

  

    for (int i = 0; i < v.size();++i) {
        ELEM<T> tMp;
        for (int j = 0; j < v[i].size();++j) {
           
            tMp.push_back(   v[i][j] );
        }

        for (int j = 0; j < v[i].size(); ++j) {
            tMp.push_back(w[i][j]);
        }

        temp.push_back(tMp);
    }
    return temp;
}


template<class T>
VEC<T> filter(VEC<T>& v, pred_t<T> f) {
    VEC<T> tmp;
    for (auto a : v) {
        bool flag = true;
        for (auto b : a) {
            flag = flag && f(b);
        }

        if (flag) {
            tmp.push_back(a);
        }
    }

    return tmp;
}

template<class T>
VEC<T> map(VEC<T>& v, action_t<T> f) {
    
    VEC<T> tmp;

    for (auto a : v) {
        ELEM<T> tMp;
        for (auto b : a) {
            tMp.push_back(f(b));
        }

        tmp.push_back(tMp);
    }

    return tmp;

}

template<class T>
ELEM<T> reduce(VEC<T>& v, map_t<T> f, ELEM<T> ident) {
    
    ELEM<T> tmp;

    T tmp1 = ident[0];

    for (auto a:v) {
        for (auto b:a) {
            tmp1 = f(tmp1,b);
       }
    }
    tmp.push_back(tmp1);
    return tmp;
}
