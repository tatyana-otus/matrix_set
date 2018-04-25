#include <iterator>
#include <algorithm>
#include <list>
#include "debug_log.h"
#include "tuple_assist.h"

template<typename T, T default_value, size_t dim = 2>
struct Matrix 
{
    static_assert(dim >= 2, "Invalid matrix dimension");

    using data_type = std::list<typename tuple_of_n<size_t, T,  dim>::type>;   

    template<size_t i, class data_type>
    struct idexer{

        T  cur_def = default_value;

        using idex_type = typename tuple_of_n<size_t, size_t, i>::type;

        idexer(idex_type val_, data_type& ext_data_):index(val_),ext_data(ext_data_) {}


        idexer<i+1, data_type> operator[](size_t idx_val) 
        {
            D_PF_LOG();
            static_assert (i < dim , "Invalid matrix index");
           
            return { std::tuple_cat(index, std::make_tuple(idx_val)), ext_data };
        }
       

         //T& operator=(const T value)
        T operator=(const T value)
        {   
            D_PF_LOG();

            static_assert (i == (dim -1), "Invalid matrix index");

            auto it = is_idx_exist();

            if ( it == ext_data.end() ) {
                if(value != cur_def){ 
                    ext_data.push_back(std::tuple_cat(index, std::make_tuple(value)));                    
                }    
            }
            else{
                if(value != cur_def){
                    std::get<dim>((*it)) = value;                   
                } 
                else {
                    ext_data.erase(it);    
                }
            }
            return value;
        }


        operator const T& () const
        {   
            D_PF_LOG();

            static_assert (i == (dim -1), "Invalid matrix index");

            auto it = is_idx_exist();

            if ( it == ext_data.end())
                return cur_def;
            else {
                return std::get<i+1>(*it);        
            }
        }

    private:

        idex_type   index;
        data_type&  ext_data; 

        auto is_idx_exist() const
        {
            auto it = std::find_if(ext_data.begin(), ext_data.end(), [this](auto d){
                                   return partial_tuple_cmp<dim>(this->index, d);});
            return it;
        }
    }; 
    

    idexer<0, data_type> operator[](size_t idx_val) 
    {
        D_PF_LOG();
        return { std::make_tuple(idx_val), data };
    }


    idexer<0, const data_type> operator[](size_t idx_val) const
    {
        D_PF_LOG();
        return { std::make_tuple(idx_val), data };
    }


    size_t size() const
    {       
        return data.size();;
    }


    void sort()
    {
        data.sort();
    }


    auto begin() const { return data.cbegin(); }
    auto end()   const { return data.cend();   }

    auto begin()  { return data.begin(); }
    auto end()    { return data.end();   }


    void print_non_empty (std::ostream& os = std::cout)
    {
        for(const auto & t: data)
        {
            tuple_p<decltype(t), dim + 1>::print(os, t);
            os << "\n";
        }
    }


    void print_square(size_t row_up, size_t col_left, size_t size, std::ostream& os = std::cout)
    {
        static_assert (dim == 2, "print_square() works only for 2D matrix ");

        for(auto i = row_up; i <= size; ++i){
            for(auto j = col_left; j <= size; ++j){
                os << (*this)[i][j] << " ";
            } 
            os << "\n";   
        }
    }

private:
    T  cur_def = default_value;
    data_type data;   
};
