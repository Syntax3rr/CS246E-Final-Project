#ifndef AGE_HELPERS_FUNCTIONALVECTORTRANSFORM_H
#define AGE_HELPERS_FUNCTIONALVECTORTRANSFORM_H
#include <vector>
#include <algorithm>

using std::vector;
namespace age {
    template <typename T, typename U> vector<U> transform(vector<T> v, U(*f)(T)) {
        vector<U> result;
        std::transform(v.begin(), v.end(), std::back_inserter(result), f);
        return result;
    }
}
#endif
