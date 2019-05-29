#pragma once
#include <cstddef>
#include <cstring>
#include <utility>
#include <iterator>
#include <stdexcept>
#include <iostream>

#define LNI_VECTOR_MAX_SZ 1000000000

namespace Tomas {
    template <typename T>
    class vector {
        public:
            // types:
            typedef T value_type;
            typedef T& reference;
            typedef const T& const_reference;
            typedef T* iterator;
            typedef const T* const_iterator;
            typedef std::reverse_iterator<iterator> reverse_iterator;
            typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
            typedef unsigned int size_type;

            // konstruktoriai
            vector() noexcept {arr = new T[rsrv_sz];}
            explicit vector(size_type n) {
            	if (LNI_VECTOR_MAX_SZ <= n){
            		throw std::range_error("size is too big");
            	}
            	else{
	            	size_type i;
	                rsrv_sz = n << 2;
	                arr = new T[rsrv_sz];
            	}
                
            }
            vector(size_type n, const T &val) {
                if (LNI_VECTOR_MAX_SZ <= n){
            		throw std::range_error("size is too big");
            	}
            	else{
                    size_type i;
                    rsrv_sz = n << 2;
                    arr = new T[rsrv_sz];
                    for (i = 0; i < n; ++i)
                        arr[i] = val;
                    vec_sz = n;
                }
            }
            vector(typename vector<T>::iterator first, typename vector<T>::iterator last) {
                size_type i, count = last - first;
                rsrv_sz = count << 2;
                arr = new T[rsrv_sz];
                //nepriskiria reiksmiu kazkodel
                for (i = 0; i < count; ++i, ++first){
                    arr[i] = *first;
                }
                vec_sz = count;
            }
            vector(std::initializer_list<T> lst) {
                rsrv_sz = lst.size() << 2;
                arr = new T[rsrv_sz];
                for (auto &item: lst)
                    arr[vec_sz++] = item;
            }
            vector(const vector<T> &other) {
                size_type i;
                rsrv_sz = other.rsrv_sz;
                arr = new T[rsrv_sz];
                for (i = 0; i < other.vec_sz; ++i)
                    arr[i] = other.arr[i];
                vec_sz = other.vec_sz;
            }
            vector(vector<T> &&other) noexcept {
                size_type i;
                vec_sz = other.vec_sz;
                rsrv_sz = other.rsrv_sz;
                arr = new T[rsrv_sz];
                arr = other.arr;
            }
            ~vector() {
                delete [] arr;
                //std::cout << "D-tor" << std::endl;
                }
            vector<T> & operator = (const vector<T> &other) {
                size_type i;
                if (rsrv_sz < other.vec_sz) {
                    rsrv_sz = other.vec_sz << 2;
                    reallocate();
                }
                for (i = 0; i < other.vec_sz; ++i)
                    arr[i] = other.arr[i];
                vec_sz = other.vec_sz;
            }
            vector<T> & operator = (const vector<T> &&other) {
                size_type i;
                if (rsrv_sz < other.vec_sz) {
                    rsrv_sz = other.vec_sz << 2;
                    reallocate();
                }
                arr = other.arr;
                vec_sz = other.vec_sz;
            }
            vector<T> & operator = (std::initializer_list<T> lst) {
                if (rsrv_sz < lst.size()) {
                    rsrv_sz = lst.size() << 2;
                    reallocate();
                }
                vec_sz = 0;
                for (auto &item: lst)
                    arr[vec_sz++] = item;
            }
            void assign(size_type count, const T &value) {
                size_type i;
                if (count > rsrv_sz) {
                    rsrv_sz = count << 2;
                    reallocate();
                }
                for (i = 0; i < count; ++i)
                    arr[i] = value;
                vec_sz = count;
            }
            void assign(typename vector<T>::iterator first, typename vector<T>::iterator last) {
                size_type i, count = last - first;
                if (count > rsrv_sz) {
                    rsrv_sz = count << 2;
                    reallocate();
                }
                for (i = 0; i < count; ++i, ++first)
                    arr[i] = *first;
                vec_sz = count;
            }
            void assign(std::initializer_list<T> lst) {
                size_type i, count = lst.size();
                if (count > rsrv_sz) {
                    rsrv_sz = count << 2;
                    reallocate();
                }
                i = 0;
                for (auto &item: lst)
                    arr[i++] = item;
            }

            // iteratoriai:
            iterator begin() noexcept {return arr;}
            const_iterator cbegin() const noexcept {return arr;}
            iterator end() noexcept {return arr + vec_sz;}
            const_iterator cend() const noexcept {return arr + vec_sz;}
            reverse_iterator rbegin() noexcept {return reverse_iterator(arr + vec_sz);}
            const_reverse_iterator crbegin() const noexcept {return reverse_iterator(arr + vec_sz);}
            reverse_iterator rend() noexcept {return reverse_iterator(arr);}
            const_reverse_iterator crend() const noexcept {return reverse_iterator(arr);}

            // parametrai
            bool empty() const noexcept {return vec_sz == 0;}
            size_type size() const noexcept {return vec_sz;}
            size_type max_size() const noexcept {return LNI_VECTOR_MAX_SZ;}
            size_type capacity() const noexcept {return rsrv_sz;}
            void resize(size_type sz) {
                if (sz > vec_sz) {
                    if (sz > rsrv_sz) {
                        rsrv_sz = sz;
                        reallocate();
                    }
                } else {
                    size_type i;
                    for (i = vec_sz; i < sz; ++i)
                        arr[i].~T();
                }
                vec_sz = sz;
            }
            void resize(size_type sz, const T & c) {
                if (sz > vec_sz) {
                    if (sz > rsrv_sz) {
                        rsrv_sz = sz;
                        reallocate();
                    }
                    size_type i;
                    for (i = vec_sz; i < sz; ++i)
                        arr[i] = c;
                } else {
                    size_type i;
                    for (i = vec_sz; i < sz; ++i)
                        arr[i].~T();
                }
                vec_sz = sz;
            }
            void reserve(size_type _sz) {
                if (_sz > rsrv_sz) {
                    rsrv_sz = _sz;
                    reallocate();
                }
            }
            void shrink_to_fit() {
                rsrv_sz = vec_sz;
                reallocate();
            }

            // iteravimas
            reference operator [](size_type idx) {
            	if (idx < vec_sz)
                    return arr[idx];
                else
                    throw std::out_of_range("accessed position is out of range");
            }
            const_reference operator [](size_type idx) const {
            	if (idx < vec_sz)
                    return arr[idx];
                else
                    throw std::out_of_range("accessed position is out of range");
            }
            reference at(size_type pos) {
                if (pos < vec_sz)
                    return arr[pos];
                else
                    throw std::out_of_range("accessed position is out of range");
            }
            const_reference at(size_type pos) const {
                if (pos < vec_sz)
                    return arr[pos];
                else
                    throw std::out_of_range("accessed position is out of range");
            }
            reference front() {return arr[0];}
            const_reference front() const {return arr[0];}
            reference back() {return arr[vec_sz - 1];}
            const_reference back() const {return arr[vec_sz - 1];}

            T* data() noexcept {return arr;}
            const T* data() const noexcept {return arr;} 

            // funkcijos
            template <class ... Args> void emplace_back(Args && ... args) {
                if (vec_sz == rsrv_sz) {
                    rsrv_sz <<= 2;
                    reallocate();
                }
                arr[vec_sz] = std::move( T( std::forward<Args>(args) ... ) );
                ++vec_sz;
            }
            void push_back(const T &val) {
                if (vec_sz == rsrv_sz) {
                    rsrv_sz <<= 2;
                    reallocate();
                }
                arr[vec_sz] = val;
                ++vec_sz;
            }
            void push_back(T &&val) {
                if (vec_sz == rsrv_sz) {
                    rsrv_sz <<= 2;
                    reallocate();
                }
                arr[vec_sz] = std::move(val);
                ++vec_sz;
            }
            void pop_back() {
                --vec_sz;
                arr[vec_sz].~T();
            }
    
            template <class ... Args> iterator emplace(const_iterator it, Args && ... args){
                iterator iit = &arr[it - arr];
                if (vec_sz == rsrv_sz) {
                    rsrv_sz <<= 2;
                    reallocate();
                }
                memmove(iit + 1, iit, (vec_sz - (it - arr)) * sizeof(T));
                (*iit) = std::move( T( std::forward<Args>(args) ... ) );
                ++vec_sz;
                return iit;
            } 
            iterator insert(const_iterator it, const T &val) {
                iterator iit = &arr[it - arr];
                if (vec_sz == rsrv_sz) {
                    rsrv_sz <<= 2;
                    reallocate();
                }
                memmove(iit + 1, iit, (vec_sz - (it - arr)) * sizeof(T));
                (*iit) = val;
                ++vec_sz;
                return iit;
            }
            iterator insert(const_iterator it, T &&val) {
                iterator iit = &arr[it - arr];
                if (vec_sz == rsrv_sz) {
                    rsrv_sz <<= 2;
                    reallocate();
                }
                memmove(iit + 1, iit, (vec_sz - (it - arr)) * sizeof(T));
                (*iit) = std::move(val);
                ++vec_sz;
                return iit;
            }
            iterator insert(const_iterator it, size_type cnt, const T &val) {
                iterator f = &arr[it - arr];
                if (!cnt) return f;
                if (vec_sz + cnt > rsrv_sz) {
                    rsrv_sz = (vec_sz + cnt) << 2;
                    reallocate();
                }
                memmove(f + cnt, f, (vec_sz - (it - arr)) * sizeof(T));
                vec_sz += cnt;
                for (iterator it = f; cnt--; ++it)
                    (*it) = val;
                return f;
            }
            template <class InputIt> iterator insert(const_iterator it, InputIt first, InputIt last) {
                iterator f = &arr[it - arr];
                size_type cnt = last - first;
                if (!cnt) return f;
                if (vec_sz + cnt > rsrv_sz) {
                    rsrv_sz = (vec_sz + cnt) << 2;
                    reallocate();
                }
                memmove(f + cnt, f, (vec_sz - (it - arr)) * sizeof(T));
                for (iterator it = f; first != last; ++it, ++first)
                    (*it) = *first;
                vec_sz += cnt;
                return f;
            }
            iterator insert(const_iterator it, std::initializer_list<T> lst) {
                size_type cnt = lst.size();
                iterator f = &arr[it - arr];
                if (!cnt) return f;
                if (vec_sz + cnt > rsrv_sz) {
                    rsrv_sz = (vec_sz + cnt) << 2;
                    reallocate();
                }
                memmove(f + cnt, f, (vec_sz - (it - arr)) * sizeof(T));
                iterator iit = f;
                for (auto &item: lst) {
                    (*iit) = item;
                    ++iit;
                }
                vec_sz += cnt;
                return f;
            }
            iterator erase(const_iterator it) {
                iterator iit = &arr[it - arr];
                (*iit).~T();
                memmove(iit, iit + 1, (vec_sz - (it - arr) - 1) * sizeof(T));
                --vec_sz;
                return iit;
            }
            iterator erase(const_iterator first, const_iterator last) {
                iterator f = &arr[first - arr];
                if (first == last) return f;
                //Neiskviecia destruktoriaus
                for ( ; first != last; ++first){
                    //delete[] first;
                    (*first).~T();
                    //std::cout << *first << std::endl;
                }
                memmove(f, last, (vec_sz - (last - arr)) * sizeof(T));
                vec_sz -= last - first;
                return f;
            }
            void swap(vector<T> &rhs) {
                size_t tvec_sz = vec_sz,
                       trsrv_sz = rsrv_sz;
                T *tarr = arr;

                vec_sz = rhs.vec_sz;
                rsrv_sz = rhs.rsrv_sz;
                arr = rhs.arr;

                rhs.vec_sz = tvec_sz;
                rhs.rsrv_sz = trsrv_sz;
                rhs.arr = tarr;
            }
            void clear() noexcept {
                size_type i;
                for (i = 0; i < vec_sz; ++i)
                    arr[i].~T();
                vec_sz = 0;
                rsrv_sz = 4;
            }

            // daugiau operatoriu
            friend vector<T> operator + (const vector<T> &a, const vector<T> &b) {
                if (a.size() != b.size())
                    throw std::runtime_error("Vektorių dydžio neatitikimas!");
                auto size = a.size();
                vector<T> c(size);
                for (auto i = 0; i != a.size(); ++i) c.arr[i] = a.arr[i] + b.arr[i];
                return c;
            }
            bool operator == (const vector<T> &rhs) const {
                if (vec_sz != rhs.vec_sz) return false;
                size_type i;
                for (i = 0; i < vec_sz; ++i)
                    if (arr[i] != rhs.arr[i])
                        return false;
                return true;
            }
            bool operator != (const vector<T> &rhs) const {
                if (vec_sz != rhs.vec_sz) return true;
                size_type i;
                for (i = 0; i < vec_sz; ++i)
                    if (arr[i] != rhs.arr[i])
                        return true;
                return false;
            }
            bool operator < (const vector<T> &rhs) const {
                size_type i, j, ub = vec_sz < rhs.vec_sz ? vec_sz : rhs.vec_sz;
                for (i = 0; i < ub; ++i)
                    if (arr[i] != rhs.arr[i])
                        return arr[i] < rhs.arr[i];
                return vec_sz < rhs.vec_sz;
            }
            bool operator <= (const vector<T> &rhs) const {
                size_type i, j, ub = vec_sz < rhs.vec_sz ? vec_sz : rhs.vec_sz;
                for (i = 0; i < ub; ++i)
                    if (arr[i] != rhs.arr[i])
                        return arr[i] < rhs.arr[i];
                return vec_sz <= rhs.vec_sz;
            }
            bool operator > (const vector<T> &rhs) const {
                size_type i, j, ub = vec_sz < rhs.vec_sz ? vec_sz : rhs.vec_sz;
                for (i = 0; i < ub; ++i)
                    if (arr[i] != rhs.arr[i])
                        return arr[i] > rhs.arr[i];
                return vec_sz > rhs.vec_sz;
            }
            bool operator >= (const vector<T> &rhs) const {
                size_type i, j, ub = vec_sz < rhs.vec_sz ? vec_sz : rhs.vec_sz;
                for (i = 0; i < ub; ++i)
                    if (arr[i] != rhs.arr[i])
                        return arr[i] > rhs.arr[i];
                return vec_sz >= rhs.vec_sz;
            }
        private:
            size_type rsrv_sz = 4;
            size_type vec_sz = 0;
            T *arr;

            inline void reallocate(){
                size_type i;
                T *tarr = new T[rsrv_sz];
                memcpy(tarr, arr, vec_sz * sizeof(T));
                //delete [] arr;
                for (i = rsrv_sz; i = 0; --i){
                    delete[] arr;
                }
                arr = tarr;
            }
    };
}