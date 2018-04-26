#include <tuple>

/*
 *	Creates type of std::tuple<N types of T> (std::tuple<N...> )
 */
template<typename T,  std::size_t N>
struct tuple_n
{
  using rest_tuple = typename tuple_n<T, N-1>::type;
  using type = decltype(std::tuple_cat(std::declval<std::tuple<T>>(), std::declval<rest_tuple>()));
};


template<typename T>
struct tuple_n<T, 0>
{
  using type = std::tuple<>;
};

/*
 *	Add type M to std::tuple<T> and retun type (type of std::tuple<T, M> )
 */
template<typename T, typename M>
struct tuple_add_type
{
  using type = decltype(std::tuple_cat(std::declval<T>(), std::declval<std::tuple<M>>()));
};


/*
 *	Compares only N first elements of tuples t1 and t2
 */
template<typename... Args1, typename... Args2, std::size_t... Is>
bool partial_tuple_cmp_(const std::tuple<Args1...>& t1, const std::tuple<Args2...>& t2, std::index_sequence<Is...> ) {
 
  return std::tie(std::get<Is>(t1)...) == std::tie(std::get<Is>(t2)...);
};

template<size_t N, typename... Args1, typename... Args2> 
bool partial_tuple_cmp(const std::tuple<Args1...>& t1, const std::tuple<Args2...>& t2) {
  return partial_tuple_cmp_(t1, t2, std::make_index_sequence<N>());
};


/*
 *  Print std::tuple
 */
template<typename T, std::size_t N>
struct tuple_p {
    static void print(std::ostream& os, const T& t) 
    {
        tuple_p<T, N-1>::print(os, t);
        os << " " << std::get<N-1>(t);
    }
};

template<typename T>
struct tuple_p<T, 1> {
    static void print(std::ostream& os, const T& t) 
    {
        os << std::get<0>(t);
    }
};

/*
 * Print empty std::tuple
 */
template<typename T>
struct tuple_p<T, 0> {
    static void print(std::ostream& os, const T& t) {}
};