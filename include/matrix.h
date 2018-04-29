#include <iterator>
#include <algorithm>
#include <set>
#include <map>
#include "debug_log.h"
#include "tuple_assist.h"


template<typename T, T default_value, size_t DIM = 2>
struct Matrix 
{
    static_assert(DIM >= 2, "Invalid matrix dimension");

    using set_data_type  = std::set<typename tuple_add_type<typename tuple_n<size_t, DIM>::type, T>::type>;
    using map_index_type = std::map<typename tuple_n<size_t, DIM>::type, typename set_data_type::iterator>;


    template<size_t I, class U>
    struct Indexer{

        using index_type = typename tuple_n<size_t, I + 1>::type;

        Indexer(index_type val_, U& parent_):index(val_), parent(parent_) {}
        


        Indexer<I + 1, U> operator[](size_t idx_val) 
        {
            D_PF_LOG();
            static_assert (I < DIM, "Invalid matrix index");
           
            return { std::tuple_cat(index, std::make_tuple(idx_val)), parent };
        }

        const Indexer<I + 1, U> operator[](size_t idx_val) const
        {
            D_PF_LOG();
            static_assert (I < DIM, "Invalid matrix index");
           
            return { std::tuple_cat(index, std::make_tuple(idx_val)), parent };
        }

        
        T operator=(const T value)
        {   
            D_PF_LOG();

            static_assert (I == (DIM - 1), "Invalid matrix index");

            auto it = parent.data_index.find(index);
            if( it == parent.data_index.end()) { 
                if(value != default_value){ 
                    auto res = parent.data_set.insert(std::tuple_cat(index, std::make_tuple(value)));
                    parent.data_index[index] = res.first;
                } 
            }
            else{
                if(value != default_value){
                    parent.data_set.erase(it->second);
                    auto res = parent.data_set.insert(std::tuple_cat(index, std::make_tuple(value)));
                    parent.data_index[index] = res.first;
                } 
                else {
                    parent.data_set.erase(it->second);
                    parent.data_index.erase(it);
                }
                
            }
            return value;
        }


        operator const T () const
        {   
            D_PF_LOG();

            static_assert (I == (DIM - 1), "Invalid matrix index");

            auto it = parent.data_index.find(index);
            if( it == parent.data_index.end()) {
                return default_value; 
            }
            else{
                return std::get<DIM>(*(it->second));
            }
        }

    private:
        index_type  index; 
        U&          parent; 
    }; 


    Indexer<0, Matrix> operator[](size_t idx_val) 
    {
        D_PF_LOG();
        return { std::make_tuple(idx_val), *this };
    }


    const Indexer<0, const Matrix> operator[](size_t idx_val) const
    {
        D_PF_LOG();
        return { std::make_tuple(idx_val), *this };
    }


    size_t size() const
    {       
        return data_set.size();;
    }

    auto begin() const { return data_set.cbegin(); }
    auto end()   const { return data_set.cend();   }

    auto begin()  { return data_set.begin(); }
    auto end()    { return data_set.end();   }


    void print_non_empty (std::ostream& os = std::cout)
    {
        for(const auto & t: data_set)
        {
            tuple_p<decltype(t), DIM + 1>::print(os, t);
            os << "\n";
        }
    }


    void print_square(size_t row_up, size_t col_left, size_t size, std::ostream& os = std::cout)
    {
        static_assert (DIM == 2, "print_square() works only for 2D matrix ");

        for(auto i = row_up; i <= size; ++i){
            for(auto j = col_left; j <= size; ++j){
                os << (*this)[i][j] << " ";
            } 
            os << "\n";   
        }
    }

private:
    set_data_type   data_set;
    map_index_type  data_index;

};