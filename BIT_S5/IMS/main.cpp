#include <simlib.h>
#include <string.h>
#include "vlakyZ.hpp"
#include "generator.hpp"

#define StartInterval 0
#define EndInterval 1440
#define Days 7
#define Multiplier 1

#define NameOfFile "model.out"

int days = Days;
double multiplier = Multiplier;

bool loadArguments(int argc, char const* argv[])
{
    for(int i = 1; i < argc - 1; i++)
    {
        if(argv[i] == std::string("-m"))
        {
            multiplier = atof(argv[++i]);
        }
        else if(argv[i] == std::string("-d"))
        {
            days = atoi(argv[++i]);
        }
        else
        {
            return false;
        }
    }
    return true;
}

void generatorNakladnichVlaku()
{
    GeneratorNakl *gBohumin = new GeneratorNakl(BohuminNaklInterval/multiplier, "Bohumin");
    GeneratorNakl *gDetmarovice = new GeneratorNakl(DetmaroviceNaklInterval/multiplier, "Detmarovice");
    GeneratorNakl *gKarvina = new GeneratorNakl(KarvinaNaklInterval/multiplier, "Karvina");
    GeneratorNakl *gLouky = new GeneratorNakl(LoukyNaklInterval/multiplier, "Louky");    
    GeneratorNakl *gTesin = new GeneratorNakl(TesinNaklInterval/multiplier, "Tesin");
    GeneratorNakl *gTrinec = new GeneratorNakl(TrinecNaklInterval/multiplier, "Trinec");
    GeneratorNakl *gMosty = new GeneratorNakl(MostyNaklInterval/multiplier, "Mosty"); 

    gBohumin->Activate();
    gDetmarovice->Activate();
    gKarvina->Activate();
    gLouky->Activate();
    gTesin->Activate();
    gTrinec->Activate();
    gMosty->Activate();
}

void generatorOsobnichVlaku()
{
    GeneratorOsob *gBohuminOsob = new GeneratorOsob(BohuminOsobInterval, "Bohumin");
    GeneratorOsob *gMostyOsob = new GeneratorOsob(MostyOsobInterval, "Mosty");

    gBohuminOsob->Activate();
    gMostyOsob->Activate();
}

void generatorRychliku()
{
    GeneratorRychl *gRychl = new GeneratorRychl(RychlInterval);
    
    gRychl->Activate();
}

void vypisPoctuVygenerovanychVlakuVDanychStanicich()
{
    Print("-----------------------------------\n");
    Print("Pocet vygenerovanych vlaku(N-nakladni,O-osobni,R-rychliky)\n");
    Print("Bohumin: %d|N-%d|O-%d|R-%d|\n", genNaklBohumin + genOsobBohumin + genRychlBohumin, genNaklBohumin, genOsobBohumin, genRychlBohumin);
    Print("Detmarovice: %d|N-%d|O-%d|R-%d|\n", genNaklDetmarovice + genOsobDetmarovice + genRychlDetmarovice, genNaklDetmarovice, genOsobDetmarovice, genRychlDetmarovice);
    Print("Karvina: %d|N-%d|O-%d|R-%d|\n", genNaklKarvina + genOsobKarvina + genRychlKarvina, genNaklKarvina, genOsobKarvina, genRychlKarvina);
    Print("Louky: %d|N-%d|O-%d|R-%d|\n", genNaklLouky + genOsobLouky + genRychlLouky, genNaklLouky, genOsobLouky, genRychlLouky);
    Print("Tesin: %d|N-%d|O-%d|R-%d|\n", genNaklTesin + genOsobTesin + genRychlTesin, genNaklTesin, genOsobTesin, genRychlTesin);
    Print("Trinec: %d|N-%d|O-%d|R-%d|\n", genNaklTrinec + genOsobTrinec + genRychlTrinec, genNaklTrinec, genOsobTrinec, genRychlTrinec);
    Print("Mosty: %d|N-%d|O-%d|R-%d|\n", genNaklMosty + genOsobMosty + genRychlMosty, genNaklMosty, genOsobMosty, genRychlMosty);
    Print("\n");

}
void vypisPoctuVlakuVeStanici()
{
    Print("-----------------------------------\n");
    Print("Pocet pozustalych vlaku ve stanici\n");
    Print("Bohumin: %d\n", vlakyVBohumin);
    Print("Detmarovicich: %d\n", vlakyVDetmarovice);
    Print("Karvine: %d\n", vlakyVKarvine);
    Print("Louky: %d\n", vlakyVLouky);
    Print("Tesin: %d\n", vlakyVTesin);
    Print("Trinec: %d\n", vlakyVTrinec);
    Print("Mosty: %d\n", vlakyVMosty);
    Print("\n");
}

void vypisPoctuUkonenychVlakuVeStanici()
{
    Print("-----------------------------------\n");
    Print("Celkovy pocet ukoncenych vlaku %d\n", konecVBohumin + konecVDetmarovice + konecVKarvine + konecVLouky + konecVTesin + konecVTrinec + konecVMosty);
    Print("V Bohumine: %d\n", konecVBohumin);
    Print("V Detmarovicich: %d\n", konecVDetmarovice);
    Print("V Karvine: %d\n", konecVKarvine);
    Print("V Loukach: %d\n", konecVLouky);
    Print("V Tesine: %d\n", konecVTesin);
    Print("V Trinci: %d\n", konecVTrinec);
    Print("V Mostech: %d\n", konecVMosty);
    Print("\n");
}

void vypisPoctuVlaku()
{
    Print("Celkovy pocet vlaku %d(na den %d)\n", pocetNakladnichVlaku + pocetOsobnichVlaku + pocetRychliku, (pocetNakladnichVlaku + pocetOsobnichVlaku + pocetRychliku )/ days);
    Print("Pocet nakladnich vlaku %d(na den %d)\n", pocetNakladnichVlaku, pocetNakladnichVlaku / days);
    Print("Pocet osobnich vlaku %d(na den %d)\n", pocetOsobnichVlaku, pocetOsobnichVlaku / days);
    Print("Pocet rychliku %d(na den %d)\n", pocetRychliku, pocetRychliku / days);
    Print("\n");
}

void vypisPoctuZaplneniStanic()
{
    Print("-----------------------------------\n");
    Print("Celkovy pocet zaplneni stanic %d\n", zaplnenostBohumin + zaplnenostDetmarovice + zaplnenostKarvina + zaplnenostLouky + zaplnenostTesin + zaplnenostTrinec + zaplnenostMosty);
    Print("Pocet zaplneni v Bohumine %d\n", zaplnenostBohumin);
    Print("Pocet zaplneni v Detmarovicich %d\n", zaplnenostDetmarovice);
    Print("Pocet zaplneni v Karvine %d\n", zaplnenostKarvina);
    Print("Pocet zaplneni v Loukach %d\n", zaplnenostLouky);
    Print("Pocet zaplneni v Tesine %d\n", zaplnenostTesin);
    Print("Pocet zaplneni v Trinci %d\n", zaplnenostTrinec);
    Print("Pocet zaplneni v Mostech %d\n", zaplnenostMosty);
    Print("\n");
}

void vypisStatistik()
{
    Print("-----------------------------------\n");
    Print("Statistiky\n");
    dobaJizdyNaTratiBohuminDetmarovice.Output();
    dobaJizdyNaTratiDetmaroviceKarvina.Output();
    dobaJizdyNaTratiKarvinaLouky.Output();
    dobaJizdyNaTratiLoukyTesin.Output();
    dobaJizdyNaTratiTesinTrinec.Output();
    dobaJizdyNaTratiTrinecMosty.Output();
    Print("\n");

}

void vypisHistogramu()
{
    Print("-----------------------------------\n");
    Print("Histogramy\n");
    dobaExistenceNaklVlaku.Output();
    dobaExistenceOsobVlaku.Output();
    dobaExistenceRychlVlaku.Output();
    Print("\n");
}

int main(int argc, char const* argv[])
{
    if(!loadArguments(argc, argv))
    {
        printf("Chybne argumenty\n");
        return 1;
    }

    SetOutput(NameOfFile);
    Print("Vlaky za %d dní\n", days);
    Print("Nasobitel generovani nakladnich vlaku %.2f\n\n", multiplier);
    Init(StartInterval,EndInterval * days);

    generatorRychliku();
    generatorOsobnichVlaku();
    generatorNakladnichVlaku();

    Run();

    vypisPoctuVlaku();

    vypisPoctuVygenerovanychVlakuVDanychStanicich();

    vypisPoctuVlakuVeStanici();

    vypisPoctuUkonenychVlakuVeStanici();

    vypisPoctuZaplneniStanic();

    vypisStatistik();

    vypisHistogramu();

    SIMLIB_statistics.Output();
}

