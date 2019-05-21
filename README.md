# vector-implementation
My vector
# 1
1-oji užduotis
```
iterator erase(const_iterator first, const_iterator last) {
                iterator f = &arr[first - arr];
                if (first == last) return f;
                for ( ; first != last; ++first)
                    (*first).~T();
                memmove(f, last, (vec_sz - (last - arr)) * sizeof(T));
                vec_sz -= last - first;
                return f;
            }
```
```
inline void reallocate(){
                T *tarr = new T[rsrv_sz];
                memcpy(tarr, arr, vec_sz * sizeof(T));
                delete [] arr;
                arr = tarr;
            }
```
```
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
```
```
vector(typename vector<T>::iterator first, typename vector<T>::iterator last) {
                size_type i, count = last - first;
                rsrv_sz = count << 2;
                arr = new T[rsrv_sz];
                for (i = 0; i < count; ++i, ++first)
                    arr[i] = *first;
                vec_sz = count;
            }
```
```
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
```
## 2
2-oji užduotis
```
Failo dydis: 10000
std::vecotor uztruko: 0.0003604 sekundziu
Tomas::vecotor uztruko: 6.27e-05 sekundziu
```
```
Failo dydis: 100000
std::vecotor uztruko: 0.0044502 sekundziu
Tomas::vecotor uztruko: 0.0014391 sekundziu
```
```
Failo dydis: 1000000
std::vecotor uztruko: 0.029106 sekundziu
Tomas::vecotor uztruko: 0.0130252 sekundziu
```
```
Failo dydis: 10000000
std::vecotor uztruko: 0.342436 sekundziu
Tomas::vecotor uztruko: 0.138391 sekundziu
```
```
Failo dydis: 100000000
std::vecotor uztruko: 3.36068 sekundziu
Tomas::vecotor uztruko: 1.72374 sekundziu
```
### 3
3-oji užduotis
```
Failo dydis: 100000000
std::vecotor uztruko: 3.46564 sekundziu
Tomas::vecotor uztruko: 2.09293 sekundziu
std::vector perskirstymu skaicius: 28
Tomas::vector perskirstymu skaicius: 13
```
