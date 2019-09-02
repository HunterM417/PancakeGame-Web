#ifndef MINTREE
#define MINTREE
// #include "list_order.h"
// #include "Pancake_diff.h"
// #include "high_score.h"
// #include "game.h"
#include <string>
#include <vector>
#include <iostream>
#include <climits>
#include <queue>
#include <algorithm>

#include<emscripten/emscripten.h>
#include<emscripten/bind.h>
#include<emscripten/val.h>

using namespace emscripten;

std::vector<int> vecFromArray(const val &arr) { // was double
  unsigned int length = arr["length"].as<unsigned int>();
  std::vector<int> vec(length);
  val memory = val::module_property("buffer");
  val memoryView = val::global("Float64Array").new_(memory, reinterpret_cast<std::uintptr_t>(vec.data()), length);
  memoryView.call<void>("set", arr);
  return vec;
}

 struct node{
        int reversals;
        int sortednessAdv;
        int depth;
        std::vector<int> pancakeStack;
        std::vector<node*> childrenNodes;
    };

class minTree{
private:
    node *root;
public:
    static std::vector<std::vector<int> > completedMoves;
    minTree() {};
    ~minTree() {};
    static int numReversals(std::vector<int> pancakeStack);
    void createChilds(node* parent, int difficulty);
    void createTree(node* parent, int difficulty);
    static bool containsVector(std::vector<std::vector<int> > container, std::vector<int> combination);
    void displayTree();
    node* getRoot();
    static std::pair<std::pair<int, int>, std::vector<int> > get_return_info(int depth, bool flag, int min_score, int min_depth, std::vector<int> min_combo, std::vector<int> in_combo);
    static std::pair<std::pair<int, int>, std::vector<int> > getBestCombo(int depth, std::vector<int> in_combo, std::vector<int> parent_combo,std::vector<int> original_combo, int difficulty);
    static bool testAI(std::vector<int> AIvector, int depth);
    int return_index_flip(const val& a, int difficulty);
    //int return_index_flip(int depth, const val& a,const val& b,const val& c, int difficulty);
};
#endif
