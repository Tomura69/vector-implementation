#include "Headers.h"
#include "classStud.h"

int main (int argc, char *argv[]){
    int m = 0;
    bool sauga = 0;
    TipasC Studentai, Minksti;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> range(1, 10);

    cout << "Darbas su vector:" << endl;
    int dydis = 10;
    for (int i = 0; i < 5; i++){
        auto startas = std::chrono::system_clock::now();
        try {
            Generavimas (dydis);
            Skaitymas (dydis, m, Studentai);
            } catch (const char* msg){
                cout << msg << endl;
                sauga = 1;
                break;
                
            }
        auto pabaiga = std::chrono::system_clock::now();
        auto uztruko = std::chrono::duration_cast<
        std::chrono::duration<double> >(pabaiga - startas).count();
        cout << dydis << "-ies dydzio failo " /*generavimas ir */"skaitymas uztruko: " << uztruko << " sekundziu" << endl;
        dydis = dydis * 10;
    }
    if (sauga){
        cout << "Rusiavimas neivyko, del nuskaitymo arba irasymo klaidos" << endl;
    }
    else {
        {auto startas = std::chrono::system_clock::now();
        Minksti = Rusiavimas (Studentai);
        auto pabaiga = std::chrono::system_clock::now();
        auto uztruko = std::chrono::duration_cast<
        std::chrono::duration<double> >(pabaiga - startas).count();
        cout << "Duomenu isrusiavimas uztruko: " << uztruko << " sekundziu" << endl;}
        
        {auto startas = std::chrono::system_clock::now();
        Irasymas (Minksti, Studentai);
        auto pabaiga = std::chrono::system_clock::now();
        auto uztruko = std::chrono::duration_cast<
        std::chrono::duration<double> >(pabaiga - startas).count();
        cout << "Duomenu isvedimas uztruko: " << uztruko << " sekundziu" << endl;}
        cout << endl;
    }
    
    return 0;
}