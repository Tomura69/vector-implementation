#include "classStud.h"

void Human::skaitymas_vard (std::string var_, std::string pav_){
    var = var_;
    pav = pav_;
}
/*Studentas::Studentas (const Studentas& a) {
    std::cout << "konstruktorius su obiektu" << std::endl;
    var = a.var;
    pav = a.pav;
    galutinis = a.galutinis;
    mediana = a.mediana;
    galmed = a.galmed;
    for (int i = 0; i < a.nd.size(); i++){
        nd[i] = a.nd[i];
    }
}*/
void Studentas::Vidurkis (double galutinis_, double mediana_, double galmed_){
    galutinis = galutinis_;
    mediana = mediana_;
    galmed = galmed_;
}
void Studentas::skaitymas_Nd (int nd_){
    nd.push_back(nd_);
}