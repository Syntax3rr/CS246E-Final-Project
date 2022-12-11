#ifndef AGE_HELPERS_FUNCTIONALTRANSFORM_H
#define AGE_HELPERS_FUNCTIONALTRANSFORM_H
#include <vector>

using std::vector;
namespace age {
    template <typename T, typename U, class Iter> vector<U> transform(Iter start, Iter end, U(*f)(T)) {
        vector<U> result{};
        for (; start != end; ++start)
            result.push_back(f(*start));
        return result;
    }
}
#endif
