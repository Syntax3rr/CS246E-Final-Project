#ifndef AGE_HELPERS_REDUCE_H
#define AGE_HELPERS_REDUCE_H

// Generic reduce function based on the one in C++17.
template<typename Iter, typename T, typename BinaryOp> T reduce(Iter first, Iter last, T init, BinaryOp op) {
    for (; first != last; ++first) {
        init = op(*first, init);
    }
    return init;
}

#endif
