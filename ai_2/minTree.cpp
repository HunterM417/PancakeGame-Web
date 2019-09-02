#include "minTree.h"

using namespace emscripten;
//////////////E X P O R T E D   F U N C T I O N S/////////////////////
//  int minTree::return_gbc_second(int depth, const val& a,const val& b,const val& c, int difficulty){
//        auto in_combo = vecFromArray(a);
//        auto parent_combo = vecFromArray(b);
//        auto original_combo = vecFromArray(c);
//        return getBestCombo(depth,in_combo,parent_combo,original_combo,difficulty).first.second;
//    };

   int minTree::return_index_flip(const val& a, int difficulty){
       auto combo = vecFromArray(a);
       std::vector<int> next_move_combo = getBestCombo(0,combo,combo,combo,difficulty).second;
       for(int p = 0 ; p<next_move_combo.size() ; p++){
           if(next_move_combo[p]!=combo[p]) return p;
       }
        return -1;
		// compare next_move_combo and combo to see which index is flipped
		// return the index for the flip
    };

    EMSCRIPTEN_BINDINGS(my_module) {
        class_<minTree>("minTree")
            .constructor()
            .function("returnIndexFlip", &minTree::return_index_flip)
            // .function("GBCSecond", &minTree::return_gbc_second)
            ;
    }



//////////////////////////////////////////////////////////////////////




// Calculates number of reversals in a given stack
int minTree::numReversals(std::vector<int> pancakeStack){
        bool prev = true;
        int count = 0;
        for(int i = 0; i < int(pancakeStack.size() - 1); i++){
            bool curr = (pancakeStack.at(i) < pancakeStack.at(i+1))? true : false;
            if(!prev != !curr){
                count++;
                prev = curr;
            }
        }
        return count;
}


// Checks if combination has been used before
bool minTree::containsVector(std::vector<std::vector<int> > container, std::vector<int> combination){
    bool contain = false;
    for(std::vector<int> x : container){
        if(combination == x){
            contain = true;
        }
    }
    return contain;
}

std::vector<std::vector<int> > minTree::completedMoves = std::vector<std::vector<int> >();

// Helper function to update values used in AI
void update_min_values(int& min_score, int& min_depth, std::vector<int>& min_combo, int new_score, int new_depth, std::vector<int> new_combo) {
    min_score = new_score;
    min_combo = new_combo;
    min_depth = new_depth;
}

// Helper function to update values used in AI
std::pair<std::pair<int, int>, std::vector<int> > make_result_thruple(int min_score, int min_depth, std::vector<int> min_combo) {
    std::pair<int, int> results(min_score, min_depth);
    return std::pair<std::pair<int, int>, std::vector<int> > (results,min_combo);
}

// Helper function to update values used in AI
std::pair<std::pair<int, int>, std::vector<int> > minTree::get_return_info(int depth, bool flag, int min_score, int min_depth, std::vector<int> min_combo, std::vector<int> in_combo) {
    if(depth == 0){
        if(flag) depth++;
        completedMoves.push_back(min_combo);
        return make_result_thruple(min_score, min_depth, min_combo);
    } else {
        return make_result_thruple(min_score, min_depth, in_combo);
    }
}

// AI function that recursively creates a tree in order to find the best move based on difficulty/depth
std::pair<std::pair<int, int>, std::vector<int> >minTree::getBestCombo(int depth, std::vector<int> in_combo, std::vector<int> parent_combo,std::vector<int> original_combo, int difficulty){
    if(depth >= difficulty){
        int score = numReversals(in_combo) - numReversals(parent_combo);
        std::pair<int, int> results(score, depth);
        return std::pair<std::pair<int, int>, std::vector<int> > (results,in_combo);
    }
    bool flag = false;
    std::vector<int> minCombo = in_combo;
    int minScore, minDepth = INT_MAX;
    for(int i = 1; i < int(in_combo.size()); i++){ // Create combinations and get the min combo from children
        std::vector<int> tempStack = in_combo;
        reverse(tempStack.begin(), tempStack.begin()+i+1);
        if(tempStack == original_combo || containsVector(completedMoves,tempStack)) continue;
        if(is_sorted(tempStack.begin(),tempStack.end())){
            update_min_values(minScore, minDepth, minCombo, (numReversals(tempStack) - numReversals(in_combo)), depth, tempStack);
            flag = true;
            break;
        }
        std::pair<std::pair<int, int>, std::vector<int> > values = getBestCombo(depth + 1, tempStack, in_combo, original_combo, difficulty);
        if(values.first.second < minDepth){
            if(values.second != original_combo && !containsVector(completedMoves,values.second)) update_min_values(minScore, minDepth, minCombo, values.first.first, values.first.second, values.second);  
        } else if(values.first.first < minScore){
            if(values.second != original_combo && !containsVector(completedMoves,values.second)) update_min_values(minScore, minDepth, minCombo, values.first.first, values.first.second, values.second); 
        }
    }
    return get_return_info(depth, flag, minScore, minDepth, minCombo, in_combo);
}

// Function to test AI in test.cpp
bool minTree::testAI(std::vector<int>AIvector, int depth){
    bool pass = false;
   std::pair<std::pair<int, int>, std::vector<int> >results = getBestCombo(depth,AIvector,AIvector,AIvector,depth);
   if(is_sorted(results.second.begin(), results.second.end())){
       pass = true;
   }
   return pass;
}
