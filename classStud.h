#pragma once
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <iostream>
#include "Vector.h"

class Human{
    protected:
        std::string var, pav;
        Human () {};
        Human (std::string v, std::string p) : var(v), pav(p) {}
    public:
        void skaitymas_vard (std::string var_, std::string pav_);
        virtual inline std::string Vardas () const {return var;}
        virtual inline std::string Pavarde () const {return pav;}
};

class Studentas : public Human{
    private:
        double galutinis, mediana, galmed;
        Tomas::vector<int> nd;
    public:
        //Seteriai
        Studentas() {};
        //Studentas (const  Studentas& a);
        ~Studentas(){
            nd.clear();
        }
        void Vidurkis (double galutinis_, double mediana_, double galmed_);
        void skaitymas_Nd (int nd_);
        inline void popBack() {nd.pop_back();}
        inline void Rikiuoti() {std::sort(nd.begin(), nd.end());}
        //Geteriai
        inline std::string Vardas () const {return var;}
        inline std::string Pavarde () const {return pav;}
        inline int Nd (int i) const {return nd[i];}
        inline bool Empty () const {if (nd.empty()) return 1;}
        inline double Vidurkis () const {return galutinis;}
        inline double Mediana () const {return mediana;}
        inline double MedVid () const {return galmed;}
        //Operatoriai
        Studentas& operator = (const Studentas& a){
            if (&a == this) return *this;
            var = a.var;
            pav = a.pav;
            galutinis = a.galutinis;
            mediana = a.mediana;
            galmed = a.galmed;
            for (int i = 0; i < a.nd.size(); i++){
                nd[i] = a.nd[i];
            }
            return *this;
        }
        friend std::ostream& operator << (std::ostream& out, const Studentas& Tomas){
            out << Tomas.Vardas() << " " << Tomas.Pavarde() << " " << std::setprecision(3) << Tomas.Vidurkis() << " " << Tomas.MedVid();
            return out;
        }
        friend bool operator == (const Studentas& Tomas, const Studentas& Tomas1){
            if (Tomas.Vardas() == Tomas1.Vardas() && Tomas.Pavarde() == Tomas1.Pavarde()){
                return 1;
            }
            else{
                return 0;
            }
        }
        friend bool operator <= (const Studentas& Tomas, int n){
            if (Tomas.Vidurkis() <= n || Tomas.MedVid() <= n){
                return 1;
            }
            else{
                return 0;
            }
        }
        friend bool operator > (const Studentas& Tomas, int n){
            if (Tomas.Vidurkis() > n && Tomas.MedVid() > n){
                return 1;
            }
            else{
                return 0;
            }
        }
        friend bool operator != (const Studentas& Tomas, int n){
            if (Tomas.Vidurkis() != n && Tomas.MedVid() != n){
                return 1;
            }
            else{
                return 0;
            }
        }
};