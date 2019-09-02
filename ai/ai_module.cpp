#include "ai_module.h"

// Initialize vector //
_vec<_vec<int> > ai_module::completed_moves = _vec<_vec<int> >();
//////////////////////

// Calculates number of reversals in a given stack
int ai_module::num_reversals(_vec<int>* pancakeStack){
    std::cout << "num reversals! with size " << pancakeStack->size() << std::endl;
        _b prev = 1;
        int count = 0;
        for(int i = 0; i < int(pancakeStack->size() - 1); i++){
            _b curr = (pancakeStack->at(i) < pancakeStack->at(i+1))? 1 : 0;
            if(!prev != !curr){
                count++;
                prev = curr;
            }
        }
    return count;
}


// Checks if combination has been used before
_b ai_module::contains_vector(const _vec<_vec<int> >* container, _vec<int>* combination){
    std::cout << "contains vector! UGH \n";
    for(auto&& y : *combination) std::cout << y << " ";
    std::cout << "\n";
    _b contain = 0;
    contain = (char) std::any_of(container->begin(), container->end(), [&*combination](const _vec<int>& x)
                                                                        { return x == *combination; });
    // int i = 0;
    // _vec<_vec<int> >::const_iterator row;
    // for (row = container.begin(); row != container.end(); row++) {
    //     std::cout << " vector : " << ++i;
    //     if(find(row->begin(), row->end(), combination) != row->end() )
    //         return (char)1;
    // }
    // return (char)0;
    // // for(auto& x : container){ // was _vec<int>
    // //     std::cout << "vector : " << ++i; 
    // //     for(auto& y : x) std::cout << y << " in contains_vector ";
    // //     if(combination == x){
    // //         contain = 1;
    // //     }
    // //     std::cout << std::endl;
    // // }
    return contain;
}


// Helper function to update values used in AI
void ai_module::update_min_values(int& min_score, int& min_depth, _vec<int>& min_combo, int new_score, int new_depth, _vec<int>* new_combo) {
    std::cout << "update min values! \n";
    min_score = new_score;
    min_combo = *new_combo;
    min_depth = new_depth;
}

// Helper function to update values used in AI
_p<_p<int, int>, _vec<int> > make_result_thruple(int min_score, int min_depth, _vec<int>* min_combo) {
    std::cout << "result thruple! \n";
    _p<int, int> results(min_score, min_depth);
    return _p<_p<int, int>, _vec<int> > (results,*min_combo);
}

// Helper function to update values used in AI
_p<_p<int, int>, _vec<int> > ai_module::get_return_info(int depth, _b flag, int min_score, int min_depth, _vec<int>* min_combo, _vec<int>* in_combo) {
    std::cout << "return info! \n";
    if(depth == 0){
        if(flag) depth++;
        completed_moves.push_back(*min_combo);
    }
    return make_result_thruple(min_score, min_depth, in_combo);
}

// AI function that recursively creates a tree in order to find the best move based on difficulty/depth
_p<_p<int, int>, _vec<int> >ai_module::get_best_combo(int depth, _vec<int>* in_combo, _vec<int>* parent_combo, _vec<int>* original_combo, int difficulty){
    std::cout << "get best combo! \n";
    if(depth >= difficulty){
        int score = num_reversals(&*in_combo) - num_reversals(&*parent_combo);
        _p<int, int> results(score, depth);
        return _p<_p<int, int>, _vec<int> > (results,*in_combo);
    }
    _b flag = 0;
    _vec<int> minCombo(*in_combo);
    int minScore, minDepth = INT_MAX;
    for(int i = 1; i < int(in_combo->size()); i++){ // Create combinations and get the min combo from children
        _vec<int> tempStack(*in_combo);
        reverse(tempStack.begin(), tempStack.begin()+i+1);
        if(tempStack == *original_combo || contains_vector(&completed_moves,&tempStack)) continue;
        if(is_sorted(tempStack.begin(),tempStack.end())){
            update_min_values(minScore, minDepth, minCombo, (num_reversals(&tempStack) - num_reversals(&*in_combo)), depth, &tempStack);
            flag = 1;
            break;
        }
        _p<_p<int, int>, _vec<int> > values = get_best_combo(depth + 1, &tempStack, in_combo, original_combo, difficulty);
        // if(values.first.second < minDepth)
        //     if(values.second != original_combo && !contains_vector(completed_moves,values.second)) 
        //         update_min_values(minScore, minDepth, minCombo, values.first.first, values.first.second, values.second);  
        // else if(values.first.first < minScore){
        //     if(values.second != original_combo && !contains_vector(completed_moves,values.second)) update_min_values(minScore, minDepth, minCombo, values.first.first, values.first.second, values.second); 
        // }
        _b check = (values.second != *original_combo && !contains_vector(&completed_moves,&values.second)) ? 1 : 0;
        if(values.first.second < minDepth && check)
                update_min_values(minScore, minDepth, minCombo, values.first.first, values.first.second, &values.second);  
        else if(values.first.first < minScore && check){
                update_min_values(minScore, minDepth, minCombo, values.first.first, values.first.second, &values.second); 
        }
    }
    return get_return_info(depth, flag, minScore, minDepth, &minCombo, in_combo);
}

// Function to test AI in test.cpp
_b ai_module::test_ai(_vec<int>* AIvector, int depth){
    for(auto&& v : *AIvector) std::cout << v << " ";
    std::cout << std::endl;
   _p<_p<int, int>, _vec<int> >results = get_best_combo(depth,AIvector,AIvector,AIvector,3);
   if(is_sorted(results.second.begin(), results.second.end())) return (_b)1;
   return (_b)0;
}
