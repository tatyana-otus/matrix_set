#include <iostream>
#include <iterator>
#include <tuple>
#include <map>
#include "debug_log.h"

template<typename T, T default_value, size_t dim = 2>
struct Matrix 
{   
    using index_type = std::array<size_t, dim>;
    using data_type  = std::map<index_type, T>;

    struct IdxStorage 
    {       

        IdxStorage(data_type& ext_data_, size_t index) : ext_data(ext_data_), cur_idx(0)
        {
            key[cur_idx++] = index;
        }


        void add_idx(size_t idx) 
        {
            D_PF_LOG();

            if(cur_idx >= dim)
                throw std::invalid_argument("Invalid matrix index");
            key[cur_idx++] = idx;
        }


        IdxStorage & operator[](size_t idx)
        {
            D_PF_LOG();

            add_idx(idx);
            return (*this);
        }


        //T& operator=(const T value)
        T operator=(const T value)
        {   
            D_PF_LOG();

            if(cur_idx != dim)
                throw std::invalid_argument("Invalid matrix index");

            if(value == cur_def){
                ext_data.erase(key);
                return cur_def; /// !!!
            }

            ext_data[key] = value;
            return ext_data[key];
        }


        operator const T& ()
        {   
            D_PF_LOG();
            if(cur_idx != dim)
                throw std::invalid_argument("Invalid matrix index");

            auto it = ext_data.find( key );
            if ( it == ext_data.end())
                return cur_def;
            else
                return it->second;           
        }

        private:
            data_type&  ext_data;            
            index_type  key;
            size_t      cur_idx;

            T  cur_def = default_value;
    };


    data_type data;

    IdxStorage operator[](size_t idx) 
    {
        return IdxStorage(data, idx);
    }


    size_t size() const
    {       
        return data.size();;
    }


    struct const_iterator : std::iterator<std::forward_iterator_tag, const T>
    {

        const_iterator(typename data_type::const_iterator it_) : it(it_){}
            
        const_iterator & operator++()
        {
            ++it;
            return *this;
        }


        auto  operator*()
        {
            return std::make_tuple(it->first, it->second);
        }
            
            
        bool operator==(const_iterator  & other)  
        {
            return (it == other.it);
        }
            
            
        bool operator!=(const_iterator  & other)  
        {
            return !(*this == other);
        } 

        private:
            typename data_type::const_iterator it;   
   
    };

    const_iterator begin() const { return const_iterator(data.cbegin()); }
    const_iterator end()   const { return const_iterator(data.cend());   }
};
