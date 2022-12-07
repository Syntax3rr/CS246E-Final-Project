#ifndef AGE_HELPERS_FUNCTIONALVECTORTRANSFORM_H
#define AGE_HELPERS_FUNCTIONALVECTORTRANSFORM_H
#include <vector>

using std::vector;
namespace age {
    template <typename T, typename U> vector<U> transform(vector<T> v, U(*f)(T)) {
        vector<U> result{};
        result.reserve(v.size());
        for (T t : v) result.push_back(f(t));
        return result;
    }
}
#endif
