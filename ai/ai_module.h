#ifndef AI_MODULE_H
//#include <string>
#include <vector>
#include <iostream>
#include <climits>
#include <queue>
#include <algorithm>

//using namespace emscripten;

template<typename T>
using _vec = std::vector<T>;
template<typename T1, typename T2>
using _p = std::pair<T1,T2>;
typedef char _b;

struct node{
    int reversals;
    int sortednessAdv;
    int depth;
    _vec<int> pancakeStack;
    _vec<node*> childrenNodes;
};

class ai_module{
    private:
        node *root;
        static void update_min_values(int&, int&, _vec<int>&, int, int, _vec<int>*);
    public:
        static _vec< _vec<int> > completed_moves; //= std::vector<std::vector<int> >();
        ai_module(){
            //root = new node;
        };
        ~ai_module(){
            //delete root;
        };
        static int num_reversals(_vec<int>*);
        void create_child(node*, int);
        void create_tree(node*, int);
        static _b contains_vector(const _vec<_vec<int> >* container, _vec<int>* combination);
        void display_tree();
        node* get_root();
        static _b test_ai(_vec<int>*, int);
        static _p<_p<int, int>, _vec<int> > get_return_info(int, _b, int, int, _vec<int>*, _vec<int>*);
        static _p<_p<int, int>, _vec<int> > get_best_combo(int, _vec<int>*, _vec<int>*, _vec<int>*, int);
        //  int return_gbc_first(int depth, const val& a,const val& b,const val& c, int difficulty);
        //  int return_gbc_second(int depth, const val& a,const val& b,const val& c, int difficulty);
};

#define AI_MODULE_H
#endif // AI_MODULE_H