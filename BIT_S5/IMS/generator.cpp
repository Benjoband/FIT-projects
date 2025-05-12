#include "generator.hpp"
#include "vlakyZ.hpp"

using namespace std;

GeneratorNakl::GeneratorNakl(double interval, std::string stanice)
{
    this->interval = interval;
    this->stanice = stanice;
}

void GeneratorNakl::Behavior() {
        if("Bohumin" == this->stanice)
        {
            if(vlakyVBohumin <= kapacitaBohumin)
            {
                genNaklBohumin++;
                (new naklBohumin())->Activate();
                Activate(Time + Exponential(this->interval));
            }
            else
            {
                zaplnenostBohumin++;
            }
        }
        else if("Detmarovice" == this->stanice)
        {
            if(vlakyVDetmarovice <= kapacitaDetmarovice)
            {
                genNaklDetmarovice++;
                (new naklDetmarovice())->Activate();
                Activate(Time + Exponential(this->interval));
            }
            else
            {
                zaplnenostDetmarovice++;
            }
        }
        else if("Karvina" == this->stanice)
        {
            if(vlakyVKarvine <= kapacitaKarvina)
            {
                genNaklKarvina++;
                (new naklKarvina())->Activate();
                Activate(Time + Exponential(this->interval));
            }
            else
            {
                zaplnenostKarvina++;
            }
        }
        else if("Louky" == this->stanice)
        {
            if(vlakyVLouky <= kapacitaLouky)
            {
                genNaklLouky++;
                (new naklLouky())->Activate();
                Activate(Time + Exponential(this->interval));
            }
            else
            {
                zaplnenostLouky++;
            }
        }
        else if("Tesin" == this->stanice)
        {
            if(vlakyVTesin <= kapacitaTesin)
            {
                genNaklTesin++;
                (new naklTesin())->Activate();
                Activate(Time + Exponential(this->interval));
            }
            else
            {
                zaplnenostTesin++;
            }
        }
        else if("Trinec" == this->stanice)
        {
            if(vlakyVTrinec <= kapacitaTrinec)
            {
                genNaklTrinec++;
                (new naklTrinec())->Activate();
                Activate(Time + Exponential(this->interval));
            }
            else
            {
                zaplnenostTrinec++;
            }
        }
        else if("Mosty" == this->stanice)
        {
            if(vlakyVMosty <= kapacitaMosty)
            {
                genNaklMosty++;
                (new naklMosty())->Activate();
                Activate(Time + Exponential(this->interval));
            }
            else
            {
                zaplnenostMosty++;
            }
        }
        else
        {
            printf("Chyba v generatoru\n");
        }
}

GeneratorOsob::GeneratorOsob(double interval, std::string stanice)
{
    this->interval = interval;
    this->stanice = stanice;
}

void GeneratorOsob::Behavior() {
        int aktCas = int(Time)%1440;
        if(aktCas < 240)
        {
            Activate(Time + 240 - aktCas);
            return;
        }
        else if (aktCas > 1320)
        {
            Activate(Time + 1440 - aktCas + 240);
            return;
        }

        if("Bohumin" == this->stanice) 
        {
            if(vlakyVBohumin <= kapacitaBohumin)
            {
                genOsobBohumin++;
                (new osobBohumin())->Activate();
                Activate(Time + this->interval);
            }
            else
            {
                zaplnenostBohumin++;
            }
        }
        else if("Mosty" == this->stanice) 
        {
            if(vlakyVMosty <= kapacitaMosty)
            {
                genOsobMosty++;
                (new osobMosty())->Activate();
                Activate(Time + this->interval);
            }
            else
            {
                zaplnenostMosty++;
            }
        }
        else
        {
            printf("Chyba v generatoru\n");
        }
}

GeneratorRychl::GeneratorRychl(double interval)
{
    this->interval = interval;
}

void GeneratorRychl::Behavior()
{
    int aktCas = int(Time)%1440;
    if(aktCas < 240)
    {
        Activate(Time + 240 - aktCas);
        return;
    }
    else if (aktCas > 1320)
    {
        Activate(Time + 1440 - aktCas + 240);
        return;
    }

    double random = Random();

    if(random < 0.5)
    {
        if(vlakyVBohumin <= kapacitaBohumin)
        {
            genRychlBohumin++;
            (new rychlikBohumin())->Activate();
            Activate(Time + this->interval);
        }
        else
        {
            zaplnenostBohumin++;
        }
    }
    else if(random < 0.61)
    {
        if(vlakyVTrinec <= kapacitaTrinec)
        {
            genRychlTrinec++;
            (new rychlikTrinec())->Activate();
            Activate(Time + this->interval);
        }
        else
        {
            zaplnenostTrinec++;
        }
    }
    else
    {
        if(vlakyVMosty <= kapacitaMosty)
        {
            genRychlMosty++;
            (new rychlikMosty())->Activate();
            Activate(Time + this->interval);
        }
        else
        {
            zaplnenostMosty++;
        }
    }   
}

