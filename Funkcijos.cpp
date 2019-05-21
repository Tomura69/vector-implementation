#include "Headers.h"

bool Patikra (std::string a){
    for (int i = 0; i < a.size(); i++){
                if (isalpha(a[i]) == 0){
                    throw "Blogai ivesti duomenys";
                    return 1;
                    break;
                }
            }
}


void Ilgiausias (int & didvar, int & didpav, std::string var, std::string pav){
    if (didvar < var.size()){
        didvar = var.size();
    }
    if (didpav < pav.size()){
        didpav = pav.size();
    }
}


void Generavimas (int dydis){
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> range(1, 10);
    std::string s = std::to_string(dydis);
    std::ofstream fr("test" + s + ".md");
    if (fr.is_open()){
        for (int i = 1; i <= dydis; i++){
            std::string s = std::to_string(i);
            fr << "Vardas" + s << " Pavarde" + s;
            for (int y = 0; y < 10; y++){
                fr << " " << range(mt);
            }
            if (i != dydis)
            fr << endl;
        }
    }
    else {
        cout << "Negalima sukurti failo" << endl;
    }
    fr.close();
}


void Skaitymas (int dydis, int & m, TipasC& Studentai){
    std::string s = std::to_string(dydis);
    std::ifstream fd("test" + s + ".md");
    if (!fd.good()){
        throw "Failai neegzistuoja";
    }
    int laik;
    std::string pvz;
    while (!fd.eof()){
        
        int sum = 0, kas = 0;
        std::string var, pav;
        Studentai.push_back(Studentas());
        getline(fd, pvz);
        std::istringstream in_line(pvz);
        try {
            in_line >> var;
            //Patikra (Duomenys[m].var);
            in_line >> pav;
            //Patikra (Duomenys[m].pav);
            Studentai[m].skaitymas_vard(var, pav);
        } catch (const char* msg){
            cout << msg << endl;
        }
        
        while (in_line >> laik){
            if (laik <= 0){
                cout << "Blogai ivesti duomenys pas studenta: " << Studentai[m].Vardas() << ", " << dydis << "-ame faile" << endl;
                sum = 0;
                break;
            }
            sum = sum + laik;
            Studentai[m].skaitymas_Nd(laik);
            kas++;
        }

        if (Studentai[m].Empty()){
            cout << "Blogai ivesti duomenys " << dydis << "-ame faile" << endl;
            break;
        }
        int egz = Studentai[m].Nd(kas-1);
        kas--;
        Studentai[m].popBack();
        sum = sum - egz;
        Skaiciavimai (Studentai, m, kas, sum, egz);
        m++;
    } 
    fd.close();
}

void Skaiciavimai (TipasC& Studentai, int m, int kas, int sum, int egz){
    
    Studentai[m].Rikiuoti();    
    bool lyginis = (kas%2 == 0);
    if (lyginis){
        double med = (Studentai[m].Nd(kas/2-1) + Studentai[m].Nd(kas/2)) / 2.0;
        double gal = 0.4*((double)sum / kas)+0.6*egz;
        double galmed = 0.4*med+0.6*egz;
        Studentai[m].Vidurkis(gal, med, galmed);
    }
    else {
        double med = Studentai[m].Nd(kas/2);
        double gal = 0.4*((double)sum / kas)+0.6*egz;
        double galmed = 0.4*med+0.6*egz;
        Studentai[m].Vidurkis(gal, med, galmed);
    }
}


bool Skola(const Studentas & i){
    return (i > 5 && i > 5);
}

TipasC Rusiavimas (TipasC& Studentai){
    TipasC::iterator it =
        std::stable_partition(Studentai.begin(), Studentai.end(), Skola);
        TipasC Minksti(it, Studentai.end());
        Studentai.erase(it, Studentai.end());
    return Minksti;
}

void Irasymas (TipasC& Minksti, TipasC& Studentai){
    std::ofstream fr1("Saunuoliai.md");
    std::ofstream fr2("Vargsiukai.md");
    for (int i = 0; i < Minksti.size(); i++){
        fr2 << Minksti[i] << endl;
    }
    for (int i = 0; i < Studentai.size(); i++){
        fr1 << Studentai[i] << endl;
    }
    fr1.close();
    fr2.close();
    //Minksti.clear();
    //Studentai.clear();
}