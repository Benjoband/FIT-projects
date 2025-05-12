#include "vlakyZ.hpp"
#include <simlib.h>

Facility BohDet[BohDetNavestidla*2];  
Facility DetKar[DetKarNavestidla*2];
Facility KarLou[KarLouNavestidla*2];
Facility LouTes[LouTesNavestidla*2];
Facility TesTri[TesTriNavestidla*2];
Facility TriMos[TriMosNavestidla*2];

Stat dobaJizdyNaTratiBohuminDetmarovice("Doba jizdy na trati Bohumin Detmarovice");
Stat dobaJizdyNaTratiDetmaroviceKarvina("Doba jizdy na trati Detmarovice Karvina");
Stat dobaJizdyNaTratiKarvinaLouky("Doba jizdy na trati Karvina Louky");
Stat dobaJizdyNaTratiLoukyTesin("Doba jizdy na trati Louky Tesin");
Stat dobaJizdyNaTratiTesinTrinec("Doba jizdy na trati Tesin Trinec");
Stat dobaJizdyNaTratiTrinecMosty("Doba jizdy na trati Trinec Mosty");

Histogram dobaExistenceNaklVlaku("Doba existence nakladniho vlaku",0, 25, 12);
Histogram dobaExistenceOsobVlaku("Doba existence osobniho vlaku",60, 5, 10);
Histogram dobaExistenceRychlVlaku("Doba existence rychliku",25, 5, 10);

int genOsobBohumin = 0;
int genOsobDetmarovice = 0;
int genOsobKarvina = 0;
int genOsobLouky = 0;
int genOsobTesin = 0;
int genOsobTrinec = 0;
int genOsobMosty = 0;

int genNaklBohumin = 0;
int genNaklDetmarovice = 0;
int genNaklKarvina = 0;
int genNaklLouky = 0;
int genNaklTesin = 0;
int genNaklTrinec = 0;
int genNaklMosty = 0;

int genRychlBohumin = 0;
int genRychlDetmarovice = 0;
int genRychlKarvina = 0;
int genRychlLouky = 0;
int genRychlTesin = 0;
int genRychlTrinec = 0;
int genRychlMosty = 0;

int vlakyVBohumin = 0;
int vlakyVDetmarovice = 0;
int vlakyVKarvine = 0;
int vlakyVLouky = 0;
int vlakyVTesin = 0;
int vlakyVTrinec = 0;
int vlakyVMosty = 0;

int konecVBohumin = 0;
int konecVDetmarovice = 0;
int konecVKarvine = 0;
int konecVLouky = 0;
int konecVTesin = 0;
int konecVTrinec = 0;
int konecVMosty = 0;

int kapacitaBohumin = BohuminKoleje;
int kapacitaDetmarovice = DetmaroviceKoleje;
int kapacitaKarvina = KarvinaKoleje;
int kapacitaLouky = LoukyKoleje;
int kapacitaTesin = TesinKoleje;
int kapacitaTrinec = TrinecKoleje;
int kapacitaMosty = MostyKoleje;

int zaplnenostBohumin = 0;
int zaplnenostDetmarovice = 0;
int zaplnenostKarvina = 0;
int zaplnenostLouky = 0;
int zaplnenostTesin = 0;
int zaplnenostTrinec = 0;
int zaplnenostMosty = 0;

int pocetNakladnichVlaku = 0;
int pocetOsobnichVlaku = 0;
int pocetRychliku = 0;

Queue frontaBohumin("Cekani pred Bohuminem");
Queue frontaDetmarovice("Cekani pred Detmarovicemi");
Queue frontaKarvina("Cekani pred Karvinou");
Queue frontaLouky("Cekani pred Loukami");
Queue frontaTesin("Cekani pred Tesinem");
Queue frontaTrinec("Cekani pred Trincem");
Queue frontaMosty("Cekani pred Mosty");

void naklBohumin::Behavior()
{
    double zacatekJizdy = Time;
    
    if(zacatekExistence == -1)
    {
        pocetNakladnichVlaku++;
    }

    vlakyVBohumin++;
    double random = Random();
    if(random <= 0.5)
    {
        for(int i = 0; i < BohDetNavestidla - 1; i++)
        {
            Seize(BohDet[i]);
            Wait(BohDetCas);
            Release(BohDet[i]);
        }

        Seize(BohDet[BohDetNavestidla - 1]);

        if(vlakyVDetmarovice > kapacitaDetmarovice)
        {
            zaplnenostDetmarovice++;
            frontaDetmarovice.Insert(this);
            Passivate();
        }

        Wait(BohDetCas);
        Release(BohDet[BohDetNavestidla - 1]);

        dobaJizdyNaTratiBohuminDetmarovice(Time - zacatekJizdy);
        vlakyVBohumin--;
        if(frontaBohumin.Empty() == false)
        {
            frontaBohumin.GetFirst()->Activate();
        }
        if(zacatekExistence != -1)
        {
            zacatekJizdy = zacatekExistence;
        }
        (new naklDetmarovice(zacatekJizdy))->Activate();
    }
    else
    {
        if(zacatekExistence == -1)
        {
            zacatekExistence = Time;
        }
        dobaExistenceNaklVlaku(Time - zacatekExistence);
        konecVBohumin++;
        vlakyVBohumin--;
        if(frontaBohumin.Empty() == false)
        {
            frontaBohumin.GetFirst()->Activate();
        }
        return;
    }
}

void naklDetmarovice::Behavior()
{
    double zacatekJizdy = Time;
    
    if(zacatekExistence == -1)
    {
        pocetNakladnichVlaku++;
    }

    vlakyVDetmarovice++;
    double random = Random();
    if(random <= 0.5)
    {
        for(int i = 0; i < DetKarNavestidla - 1; i++)
        {
            Seize(DetKar[i]);
            Wait(DetKarCas);
            Release(DetKar[i]);
        }

        Seize(DetKar[DetKarNavestidla - 1]);

        if(vlakyVKarvine > kapacitaKarvina)
        {
            zaplnenostKarvina++;
            frontaKarvina.Insert(this);
            Passivate();
        }

        Wait(DetKarCas);
        Release(DetKar[DetKarNavestidla - 1]);

        dobaJizdyNaTratiDetmaroviceKarvina(Time - zacatekJizdy);
        vlakyVDetmarovice--;
        if(frontaDetmarovice.Empty() == false)
        {
            frontaDetmarovice.GetFirst()->Activate();
        }
        if(zacatekExistence != -1)
        {
            zacatekJizdy = zacatekExistence;
        }
        (new naklKarvina(zacatekJizdy))->Activate();
    }
    else if(random <= 0.95)
    {
        for(int i = BohDetNavestidla; i < BohDetNavestidla * 2 - 1; i++)
        {
            Seize(BohDet[i]);
            Wait(BohDetCas);
            Release(BohDet[i]);
        }

        Seize(BohDet[BohDetNavestidla * 2 - 1]);

        if(vlakyVBohumin > kapacitaBohumin)
        {
            zaplnenostBohumin++;
            frontaBohumin.Insert(this);
            Passivate();
        }

        Wait(BohDetCas);
        Release(BohDet[BohDetNavestidla * 2 - 1]);

        dobaJizdyNaTratiBohuminDetmarovice(Time - zacatekJizdy);
        vlakyVDetmarovice--;
        if(frontaDetmarovice.Empty() == false)
        {
            frontaDetmarovice.GetFirst()->Activate();
        }
        if(zacatekExistence != -1)
        {
            zacatekJizdy = zacatekExistence;
        }
        (new naklBohumin(zacatekJizdy))->Activate();
    }
    else
    {
        if(zacatekExistence == -1)
        {
            zacatekExistence = Time;
        }
        dobaExistenceNaklVlaku(Time - zacatekExistence);
        konecVDetmarovice++;
        vlakyVDetmarovice--;
        if(frontaDetmarovice.Empty() == false)
        {
            frontaDetmarovice.GetFirst()->Activate();
        }
        return;
    }
}

void naklKarvina::Behavior()
{
    double zacatekJizdy = Time;

    if(zacatekExistence == -1)
    {
        pocetNakladnichVlaku++;
    }
    
    vlakyVKarvine++;
    double random = Random();
    if(random <= 0.5)
    {
        for(int i = 0; i < KarLouNavestidla - 1; i++)
        {
            Seize(KarLou[i]);
            Wait(KarLouCas);
            Release(KarLou[i]);
        }

        Seize(KarLou[KarLouNavestidla - 1]);

        if(vlakyVLouky > kapacitaLouky)
        {
            zaplnenostLouky++;
            frontaLouky.Insert(this);
            Passivate();
        }

        Wait(KarLouCas);
        Release(KarLou[KarLouNavestidla - 1]);

        dobaJizdyNaTratiKarvinaLouky(Time - zacatekJizdy);
        vlakyVKarvine--;
        if(frontaKarvina.Empty() == false)
        {
            frontaKarvina.GetFirst()->Activate();
        }
        if(zacatekExistence != -1)
        {
            zacatekJizdy = zacatekExistence;
        }
        (new naklLouky(zacatekJizdy))->Activate();
    }
    else if(random <= 0.91)
    {
        for(int i = DetKarNavestidla; i < DetKarNavestidla * 2 - 1; i++)
        {
            Seize(DetKar[i]);
            Wait(DetKarCas);
            Release(DetKar[i]);
        }

        Seize(DetKar[DetKarNavestidla * 2 - 1]);

        if(vlakyVDetmarovice > kapacitaDetmarovice)
        {
            zaplnenostDetmarovice++;
            frontaDetmarovice.Insert(this);	
            Passivate();
        }

        Wait(DetKarCas);
        Release(DetKar[DetKarNavestidla * 2 - 1]);

        dobaJizdyNaTratiDetmaroviceKarvina(Time - zacatekJizdy);
        vlakyVKarvine--;
        if(frontaKarvina.Empty() == false)
        {
            frontaKarvina.GetFirst()->Activate();
        }
        if(zacatekExistence != -1)
        {
            zacatekJizdy = zacatekExistence;
        }
        (new naklDetmarovice(zacatekJizdy))->Activate();
    }
    else
    {
        if(zacatekExistence == -1)
        {
            zacatekExistence = Time;
        }
        dobaExistenceNaklVlaku(Time - zacatekExistence);
        konecVKarvine++;
        vlakyVKarvine--;
        if(frontaKarvina.Empty() == false)
        {
            frontaKarvina.GetFirst()->Activate();
        }
        return;
    }
}

void naklLouky::Behavior() 
{
    double zacatekJizdy = Time;

    if(zacatekExistence == -1)
    {
        pocetNakladnichVlaku++;
    }
    
    vlakyVLouky++;
    double random = Random();
    if(random <= 0.46)
    {
        for(int i = 0; i < LouTesNavestidla - 1; i++)
        {
            Seize(LouTes[i]);
            Wait(LouTesCas);
            Release(LouTes[i]);
        }

        Seize(LouTes[LouTesNavestidla - 1]);

        if(vlakyVTesin > kapacitaTesin)
        {
            zaplnenostTesin++;
            frontaTesin.Insert(this);
            Passivate();
        }

        Wait(LouTesCas);
        Release(LouTes[LouTesNavestidla - 1]);

        dobaJizdyNaTratiLoukyTesin(Time - zacatekJizdy);
        vlakyVLouky--;
        if(frontaLouky.Empty() == false)
        {
            frontaLouky.GetFirst()->Activate();
        }
        if(zacatekExistence != -1)
        {
            zacatekJizdy = zacatekExistence;
        }
        (new naklTesin(zacatekJizdy))->Activate();
    }
    else if(random <= 0.88)
    {
        for(int i = KarLouNavestidla; i < KarLouNavestidla * 2 - 1; i++)
        {
            Seize(KarLou[i]);
            Wait(KarLouCas);
            Release(KarLou[i]);
        }

        Seize(KarLou[KarLouNavestidla * 2 - 1]);

        if(vlakyVKarvine > kapacitaKarvina)
        {
            zaplnenostKarvina++;
            frontaKarvina.Insert(this);
            Passivate();
        }

        Wait(KarLouCas);
        Release(KarLou[KarLouNavestidla * 2 - 1]);

        dobaJizdyNaTratiKarvinaLouky(Time - zacatekJizdy);
        vlakyVLouky--;
        if(frontaLouky.Empty() == false)
        {
            frontaLouky.GetFirst()->Activate();
        }
        if(zacatekExistence != -1)
        {
            zacatekJizdy = zacatekExistence;
        }
        (new naklKarvina(zacatekJizdy))->Activate();
    }
    else
    {
        if(zacatekExistence == -1)
        {
            zacatekExistence = Time;
        }
        dobaExistenceNaklVlaku(Time - zacatekExistence);
        konecVLouky++;
        vlakyVLouky--;
        if(frontaLouky.Empty() == false)
        {
            frontaLouky.GetFirst()->Activate();
        }
        return;
    }
}


void naklTesin::Behavior() 
{
    double zacatekJizdy = Time;

    if(zacatekExistence == -1)
    {
        pocetNakladnichVlaku++;
    }
    
    vlakyVTesin++;  
    double random = Random();
    if(random <= 0.5)
    {
        for(int i = 0; i < TesTriNavestidla - 1; i++)
        {
            Seize(TesTri[i]);
            Wait(TesTriCas);
            Release(TesTri[i]);
        }

        Seize(TesTri[TesTriNavestidla - 1]);

        if(vlakyVTrinec > kapacitaTrinec)
        {
            zaplnenostTrinec++;
            frontaTrinec.Insert(this);
            Passivate();
        }

        Wait(TesTriCas);
        Release(TesTri[TesTriNavestidla - 1]);

        dobaJizdyNaTratiTesinTrinec(Time - zacatekJizdy);
        vlakyVTesin--;
        if(frontaTesin.Empty() == false)
        {
            frontaTesin.GetFirst()->Activate();
        }
        if(zacatekExistence != -1)
        {
            zacatekJizdy = zacatekExistence;
        }
        (new naklTrinec(zacatekJizdy))->Activate();
    }
    else if(random <= 0.88)
    {
        for(int i = LouTesNavestidla; i < LouTesNavestidla * 2 - 1; i++)
        {
            Seize(LouTes[i]);
            Wait(LouTesCas);
            Release(LouTes[i]);
        }

        Seize(LouTes[LouTesNavestidla * 2 - 1]);

        if(vlakyVLouky > kapacitaLouky)
        {
            zaplnenostLouky++;
            frontaLouky.Insert(this);
            Passivate();
        }

        Wait(LouTesCas);
        Release(LouTes[LouTesNavestidla * 2 - 1]);

        dobaJizdyNaTratiLoukyTesin(Time - zacatekJizdy);
        vlakyVTesin--;
        if(frontaTesin.Empty() == false)
        {
            frontaTesin.GetFirst()->Activate();
        }
        if(zacatekExistence != -1)
        {
            zacatekJizdy = zacatekExistence;
        }
        (new naklLouky(zacatekJizdy))->Activate();
    }
    else 
    {
        if(zacatekExistence == -1)
        {
            zacatekExistence = Time;
        }
        dobaExistenceNaklVlaku(Time - zacatekExistence);
        konecVTesin++;
        vlakyVTesin--;
        if(frontaTesin.Empty() == false)
        {
            frontaTesin.GetFirst()->Activate();
        }
        return;
    }
}

void naklTrinec::Behavior() 
{
    double zacatekJizdy = Time;

    if(zacatekExistence == -1)
    {
        pocetNakladnichVlaku++;
    }
    
    vlakyVTrinec++;
    double random = Random();
    if(random <= 0.36)
    {
        for(int i = 0; i < TriMosNavestidla - 1; i++)
        {
            Seize(TriMos[i]);
            Wait(TriMosCas);
            Release(TriMos[i]);
        }

        Seize(TriMos[TriMosNavestidla - 1]);

        if(vlakyVMosty > kapacitaMosty)
        {
            zaplnenostMosty++;
            frontaMosty.Insert(this);
            Passivate();
        }

        Wait(TriMosCas);
        Release(TriMos[TriMosNavestidla - 1]);

        dobaJizdyNaTratiTrinecMosty(Time - zacatekJizdy);
        vlakyVTrinec--;
        if(frontaTrinec.Empty() == false)
        {
            frontaTrinec.GetFirst()->Activate();
        }
        if(zacatekExistence != -1)
        {
            zacatekJizdy = zacatekExistence;
        }
        (new naklMosty(zacatekJizdy))->Activate();
    }
    else if(random <= 0.75)
    {
        for(int i = TesTriNavestidla; i < TesTriNavestidla * 2 - 1; i++)
        {
            Seize(TesTri[i]);
            Wait(TesTriCas);
            Release(TesTri[i]);
        }

        Seize(TesTri[TesTriNavestidla * 2 - 1]);

        if(vlakyVTesin > kapacitaTesin)
        {
            zaplnenostTesin++;
            frontaTesin.Insert(this);
            Passivate();
        }

        Wait(TesTriCas);
        Release(TesTri[TesTriNavestidla * 2 - 1]);

        dobaJizdyNaTratiTesinTrinec(Time - zacatekJizdy);
        vlakyVTrinec--;
        if(frontaTrinec.Empty() == false)
        {
            frontaTrinec.GetFirst()->Activate();
        }
        if(zacatekExistence != -1)
        {
            zacatekJizdy = zacatekExistence;
        }
        (new naklTesin(zacatekJizdy))->Activate();
    }
    else
    {
        if(zacatekExistence == -1)
        {
            zacatekExistence = Time;
        }
        dobaExistenceNaklVlaku(Time - zacatekExistence);
        konecVTrinec++;
        vlakyVTrinec--;
        if(frontaTrinec.Empty() == false)
        {
            frontaTrinec.GetFirst()->Activate();
        }
        return;
    }   
}

void naklMosty::Behavior() 
{
    double zacatekJizdy = Time;

    if(zacatekExistence == -1)
    {
        pocetNakladnichVlaku++;
    }
    
    vlakyVMosty++;
    double random = Random();
    if(random <= 0.5)
    {
        for(int i = TriMosNavestidla; i < TriMosNavestidla * 2 - 1; i++)
        {
            Seize(TriMos[i]);
            Wait(TriMosCas);
            Release(TriMos[i]);
        }

        Seize(TriMos[TriMosNavestidla * 2 - 1]);

        if(vlakyVTrinec > kapacitaTrinec)
        {
            zaplnenostTrinec++;
            frontaTrinec.Insert(this);
            Passivate();
        }

        Wait(TriMosCas);
        Release(TriMos[TriMosNavestidla * 2 - 1]);

        dobaJizdyNaTratiTrinecMosty(Time - zacatekJizdy);
        vlakyVMosty--;
        if(frontaMosty.Empty() == false)
        {
            frontaMosty.GetFirst()->Activate();
        }
        if(zacatekExistence != -1)
        {
            zacatekJizdy = zacatekExistence;
        }
        (new naklTrinec(zacatekJizdy))->Activate();
    }
    else
    {
        if(zacatekExistence == -1)
        {
            zacatekExistence = Time;
        }
        dobaExistenceNaklVlaku(Time - zacatekExistence);
        konecVMosty++;
        vlakyVMosty--;
        if(frontaMosty.Empty() == false)
        {
            frontaMosty.GetFirst()->Activate();
        }
        return;
    }
}

void osobBohumin::Behavior()
{
    double zacatekJizdy = Time;

    if(zacatekExistence == -1)
    {
        pocetOsobnichVlaku++;
    }
    
    vlakyVBohumin++;

    if(!doBohumin)
    {
        for(int i = 0; i < BohDetNavestidla - 1; i++)
        {
            Seize(BohDet[i]);
            Wait(BohDetCas * rychlostOsobKNakl);
            Release(BohDet[i]);
        }

        Seize(BohDet[BohDetNavestidla - 1]);

        if(vlakyVDetmarovice > kapacitaDetmarovice)
        {
            zaplnenostDetmarovice++;
            frontaDetmarovice.Insert(this);
            Passivate();
        }

        Wait(BohDetCas * rychlostOsobKNakl);
        Release(BohDet[BohDetNavestidla - 1]);

        dobaJizdyNaTratiBohuminDetmarovice(Time - zacatekJizdy);
        vlakyVBohumin--;
        if(frontaBohumin.Empty() == false)
        {
            frontaBohumin.GetFirst()->Activate();
        }
        if(zacatekExistence != -1)
        {
            zacatekJizdy = zacatekExistence;
        }
        (new osobDetmarovice(zacatekJizdy,doBohumin))->Activate();
    }
    else
    {
        if(zacatekExistence == -1)
        {
            zacatekExistence = Time;
        }
        dobaExistenceOsobVlaku(Time - zacatekExistence);
        konecVBohumin++;
        vlakyVBohumin--;
        if(frontaBohumin.Empty() == false)
        {
            frontaBohumin.GetFirst()->Activate();
        }
        return;
    }
}

void osobDetmarovice::Behavior()
{
    double zacatekJizdy = Time;
    
    if(zacatekExistence == -1)
    {
        pocetOsobnichVlaku++;
    }
    
    vlakyVDetmarovice++;

    if(!doBohumin)
    {
        for(int i = 0; i < DetKarNavestidla - 1; i++)
        {
            Seize(DetKar[i]);
            Wait(DetKarCas * rychlostOsobKNakl);
            Release(DetKar[i]);
        }

        Seize(DetKar[DetKarNavestidla - 1]);

        if(vlakyVKarvine > kapacitaKarvina)
        {
            zaplnenostKarvina++;
            frontaKarvina.Insert(this);
            Passivate();
        }

        Wait(DetKarCas * rychlostOsobKNakl);
        Release(DetKar[DetKarNavestidla - 1]);

        dobaJizdyNaTratiDetmaroviceKarvina(Time - zacatekJizdy);
        vlakyVDetmarovice--;
        if(frontaDetmarovice.Empty() == false)
        {
            frontaDetmarovice.GetFirst()->Activate();
        }
        if(zacatekExistence != -1)
        {
            zacatekJizdy = zacatekExistence;
        }
        (new osobKarvina(zacatekJizdy,doBohumin))->Activate();
    }
    else
    {
        for(int i = BohDetNavestidla; i < BohDetNavestidla * 2 - 1; i++)
        {
            Seize(BohDet[i]);
            Wait(BohDetCas * rychlostOsobKNakl);
            Release(BohDet[i]);
        }

        Seize(BohDet[BohDetNavestidla * 2 - 1]);

        if(vlakyVBohumin > kapacitaBohumin)
        {
            zaplnenostBohumin++;
            frontaBohumin.Insert(this);
            Passivate();
        }

        Wait(BohDetCas * rychlostOsobKNakl);
        Release(BohDet[BohDetNavestidla * 2 - 1]);

        dobaJizdyNaTratiBohuminDetmarovice(Time - zacatekJizdy);
        vlakyVDetmarovice--;
        if(frontaDetmarovice.Empty() == false)
        {
            frontaDetmarovice.GetFirst()->Activate();
        }
        if(zacatekExistence != -1)
        {
            zacatekJizdy = zacatekExistence;
        }
        (new osobBohumin(zacatekJizdy,doBohumin))->Activate();
    }
}

void osobKarvina::Behavior()
{
    double zacatekJizdy = Time;

    if(zacatekExistence == -1)
    {
        pocetOsobnichVlaku++;
    }
    
    vlakyVKarvine++;

    if(!doBohumin)
    {
        for(int i = 0; i < KarLouNavestidla - 1; i++)
        {
            Seize(KarLou[i]);
            Wait(KarLouCas * rychlostOsobKNakl);
            Release(KarLou[i]);
        }

        Seize(KarLou[KarLouNavestidla - 1]);

        if(vlakyVLouky > kapacitaLouky)
        {
            zaplnenostLouky++;
            frontaLouky.Insert(this);
            Passivate();
        }

        Wait(KarLouCas * rychlostOsobKNakl);
        Release(KarLou[KarLouNavestidla - 1]);

        dobaJizdyNaTratiKarvinaLouky(Time - zacatekJizdy);
        vlakyVKarvine--;
        if(frontaKarvina.Empty() == false)
        {
            frontaKarvina.GetFirst()->Activate();
        }
        if(zacatekExistence != -1)
        {
            zacatekJizdy = zacatekExistence;
        }
        (new osobLouky(zacatekJizdy,doBohumin))->Activate();
    }
    else
    {
        for(int i = DetKarNavestidla; i < DetKarNavestidla * 2 - 1; i++)
        {
            Seize(DetKar[i]);
            Wait(DetKarCas * rychlostOsobKNakl);
            Release(DetKar[i]);
        }

        Seize(DetKar[DetKarNavestidla * 2 - 1]);

        if(vlakyVDetmarovice > kapacitaDetmarovice)
        {
            zaplnenostDetmarovice++;
            frontaDetmarovice.Insert(this);
            Passivate();
        }

        Wait(DetKarCas * rychlostOsobKNakl);
        Release(DetKar[DetKarNavestidla * 2 - 1]);

        dobaJizdyNaTratiDetmaroviceKarvina(Time - zacatekJizdy);
        vlakyVKarvine--;
        if(frontaKarvina.Empty() == false)
        {
            frontaKarvina.GetFirst()->Activate();
        }
        if(zacatekExistence != -1)
        {
            zacatekJizdy = zacatekExistence;
        }
        (new osobDetmarovice(zacatekJizdy,doBohumin))->Activate();
    }
}

void osobLouky::Behavior() 
{
    double zacatekJizdy = Time;

    if(zacatekExistence == -1)
    {
        pocetOsobnichVlaku++;
    }
    
    vlakyVLouky++;

    if(!doBohumin)
    {
        for(int i = 0; i < LouTesNavestidla - 1; i++)
        {
            Seize(LouTes[i]);
            Wait(LouTesCas * rychlostOsobKNakl);
            Release(LouTes[i]);
        }

        Seize(LouTes[LouTesNavestidla - 1]);

        if(vlakyVTesin > kapacitaTesin)
        {
            zaplnenostTesin++;
            frontaTesin.Insert(this);
            Passivate();
        }

        Wait(LouTesCas * rychlostOsobKNakl);
        Release(LouTes[LouTesNavestidla - 1]);

        dobaJizdyNaTratiLoukyTesin(Time - zacatekJizdy);
        vlakyVLouky--;
        if(frontaLouky.Empty() == false)
        {
            frontaLouky.GetFirst()->Activate();
        }
        if(zacatekExistence != -1)
        {
            zacatekJizdy = zacatekExistence;
        }
        (new osobTesin(zacatekJizdy,doBohumin))->Activate();
    }
    else
    {
        for(int i = KarLouNavestidla; i < KarLouNavestidla * 2 - 1; i++)
        {
            Seize(KarLou[i]);
            Wait(KarLouCas * rychlostOsobKNakl);
            Release(KarLou[i]);
        }

        Seize(KarLou[KarLouNavestidla * 2 - 1]);

        if(vlakyVKarvine > kapacitaKarvina)
        {
            zaplnenostKarvina++;  
            frontaKarvina.Insert(this);
            Passivate();
        }

        Wait(KarLouCas * rychlostOsobKNakl);
        Release(KarLou[KarLouNavestidla * 2 - 1]);

        dobaJizdyNaTratiKarvinaLouky(Time - zacatekJizdy);
        vlakyVLouky--;
        if(frontaLouky.Empty() == false)
        {
            frontaLouky.GetFirst()->Activate();
        }
        if(zacatekExistence != -1)
        {
            zacatekJizdy = zacatekExistence;
        }
        (new osobKarvina(zacatekJizdy,doBohumin))->Activate();
    }
}

void osobTesin::Behavior() 
{
    double zacatekJizdy = Time;

    if(zacatekExistence == -1)
    {
        pocetOsobnichVlaku++;
    }
    
    vlakyVTesin++;  

    if(!doBohumin)
    {
        for(int i = 0; i < TesTriNavestidla - 1; i++)
        {
            Seize(TesTri[i]);
            Wait(TesTriCas * rychlostOsobKNakl);
            Release(TesTri[i]);
        }

        Seize(TesTri[TesTriNavestidla - 1]);

        if(vlakyVTrinec > kapacitaTrinec)
        {
            zaplnenostTrinec++;
            frontaTrinec.Insert(this);
            Passivate();
        }

        Wait(TesTriCas * rychlostOsobKNakl);
        Release(TesTri[TesTriNavestidla - 1]);

        dobaJizdyNaTratiTesinTrinec(Time - zacatekJizdy);
        vlakyVTesin--;
        if(frontaTesin.Empty() == false)
        {
            frontaTesin.GetFirst()->Activate();
        }
        if(zacatekExistence != -1)
        {
            zacatekJizdy = zacatekExistence;
        }
        (new osobTrinec(zacatekJizdy,doBohumin))->Activate();
    }
    else
    {
        for(int i = LouTesNavestidla; i < LouTesNavestidla * 2 - 1; i++)
        {
            Seize(LouTes[i]);
            Wait(LouTesCas * rychlostOsobKNakl);
            Release(LouTes[i]);
        }

        Seize(LouTes[LouTesNavestidla * 2 - 1]);

        if(vlakyVLouky > kapacitaLouky)
        {
            zaplnenostLouky++;
            frontaLouky.Insert(this);
            Passivate();
        }

        Wait(LouTesCas * rychlostOsobKNakl);
        Release(LouTes[LouTesNavestidla * 2 - 1]);

        dobaJizdyNaTratiLoukyTesin(Time - zacatekJizdy);
        vlakyVTesin--;
        if(frontaTesin.Empty() == false)
        {
            frontaTesin.GetFirst()->Activate();
        }
        if(zacatekExistence != -1)
        {
            zacatekJizdy = zacatekExistence;
        }
        (new osobLouky(zacatekJizdy,doBohumin))->Activate();
    }
}

void osobTrinec::Behavior()
{
    double zacatekJizdy = Time;

    if(zacatekExistence == -1)
    {
        pocetOsobnichVlaku++;
    }
    
    vlakyVTrinec++;

    if(!doBohumin)
    {
        for(int i = 0; i < TriMosNavestidla - 1; i++)
        {
            Seize(TriMos[i]);
            Wait(TriMosCas * rychlostOsobKNakl);
            Release(TriMos[i]);
        }

        Seize(TriMos[TriMosNavestidla - 1]);

        if(vlakyVMosty > kapacitaMosty)
        {
            zaplnenostMosty++;
            frontaMosty.Insert(this);
            Passivate();
        }

        Wait(TriMosCas * rychlostOsobKNakl);
        Release(TriMos[TriMosNavestidla - 1]);

        dobaJizdyNaTratiTrinecMosty(Time - zacatekJizdy);
        vlakyVTrinec--;
        if(frontaTrinec.Empty() == false)
        {
            frontaTrinec.GetFirst()->Activate();
        }
        if(zacatekExistence != -1)
        {
            zacatekJizdy = zacatekExistence;
        }
        (new osobMosty(zacatekJizdy,doBohumin))->Activate();
    }
    else
    {
        for(int i = TesTriNavestidla; i < TesTriNavestidla * 2 - 1; i++)
        {
            Seize(TesTri[i]);
            Wait(TesTriCas * rychlostOsobKNakl);
            Release(TesTri[i]);
        }

        Seize(TesTri[TesTriNavestidla * 2 - 1]);

        if(vlakyVTesin > kapacitaTesin)
        {
            zaplnenostTesin++;
            frontaTesin.Insert(this);
            Passivate();
        }

        Wait(TesTriCas * rychlostOsobKNakl);
        Release(TesTri[TesTriNavestidla * 2 - 1]);

        dobaJizdyNaTratiTesinTrinec(Time - zacatekJizdy);
        vlakyVTrinec--;
        if(frontaTrinec.Empty() == false)
        {
            frontaTrinec.GetFirst()->Activate();
        }
        if(zacatekExistence != -1)
        {
            zacatekJizdy = zacatekExistence;
        }
        (new osobTesin(zacatekJizdy,doBohumin))->Activate();
    }
}

void osobMosty::Behavior()
{
    double zacatekJizdy = Time;

    if(zacatekExistence == -1)
    {
        pocetOsobnichVlaku++;
    }
    
    vlakyVMosty++;

    if(doBohumin)
    {
        for(int i = TriMosNavestidla; i < TriMosNavestidla * 2 - 1; i++)
        {
            Seize(TriMos[i]);
            Wait(TriMosCas * rychlostOsobKNakl);
            Release(TriMos[i]);
        }

        Seize(TriMos[TriMosNavestidla * 2 - 1]);

        if(vlakyVTrinec > kapacitaTrinec)
        {
            zaplnenostTrinec++;
            frontaTrinec.Insert(this);
            Passivate();
        }

        Wait(TriMosCas * rychlostOsobKNakl);
        Release(TriMos[TriMosNavestidla * 2 - 1]);

        dobaJizdyNaTratiTrinecMosty(Time - zacatekJizdy);
        vlakyVMosty--;
        if(frontaMosty.Empty() == false)
        {
            frontaMosty.GetFirst()->Activate();
        }
        if(zacatekExistence != -1)
        {
            zacatekJizdy = zacatekExistence;
        }
        (new osobTrinec(zacatekJizdy,doBohumin))->Activate();
    }
    else
    {
        if(zacatekExistence == -1)
        {
            zacatekExistence = Time;
        }
        dobaExistenceOsobVlaku(Time - zacatekExistence);
        konecVMosty++;
        vlakyVMosty--;
        if(frontaMosty.Empty() == false)
        {
            frontaMosty.GetFirst()->Activate();
        }
        return;
    }
}

void rychlikBohumin::Behavior()
{
    double zacatekJizdy = Time;

    if(zacatekExistence == -1)
    {
        pocetRychliku++;
    }
    
    vlakyVBohumin++;

    if(!doBohumin)
    {
        for(int i = 0; i < BohDetNavestidla - 1; i++)
        {
            Seize(BohDet[i]);
            Wait(BohDetCas * rychlostRychlKNakl);
            Release(BohDet[i]);
        }

        Seize(BohDet[BohDetNavestidla - 1]);

        if(vlakyVDetmarovice > kapacitaDetmarovice)
        {
            zaplnenostDetmarovice++;
            frontaDetmarovice.Insert(this);
            Passivate();
        }

        Wait(BohDetCas * rychlostRychlKNakl);
        Release(BohDet[BohDetNavestidla - 1]);

        dobaJizdyNaTratiBohuminDetmarovice(Time - zacatekJizdy);
        vlakyVBohumin--;
        if(frontaBohumin.Empty() == false)
        {
            frontaBohumin.GetFirst()->Activate();
        }
        if(zacatekExistence != -1)
        {
            zacatekJizdy = zacatekExistence;
        }
        (new rychlikDetmarovice(zacatekJizdy,doBohumin))->Activate();
    }
    else
    {
        if(zacatekExistence == -1)
        {
            zacatekExistence = Time;
        }
        dobaExistenceRychlVlaku(Time - zacatekExistence);
        konecVBohumin++;
        vlakyVBohumin--;
        if(frontaBohumin.Empty() == false)
        {
            frontaBohumin.GetFirst()->Activate();
        }
        return;
    }
}

void rychlikDetmarovice::Behavior()
{
    double zacatekJizdy = Time;

    if(zacatekExistence == -1)
    {
        pocetRychliku++;
    }
    
    vlakyVDetmarovice++;

    if(!doBohumin)
    {
        for(int i = 0; i < DetKarNavestidla - 1; i++)
        {
            Seize(DetKar[i]);
            Wait(DetKarCas * rychlostRychlKNakl);
            Release(DetKar[i]);
        }

        Seize(DetKar[DetKarNavestidla - 1]);

        if(vlakyVKarvine > kapacitaKarvina)
        {
            zaplnenostKarvina++;
            frontaKarvina.Insert(this);
            Passivate();
        }

        Wait(DetKarCas * rychlostRychlKNakl);
        Release(DetKar[DetKarNavestidla - 1]);  

        dobaJizdyNaTratiDetmaroviceKarvina(Time - zacatekJizdy);
        vlakyVDetmarovice--;
        if(frontaDetmarovice.Empty() == false)
        {
            frontaDetmarovice.GetFirst()->Activate();
        }
        if(zacatekExistence != -1)
        {
            zacatekJizdy = zacatekExistence;
        }
        (new rychlikKarvina(zacatekJizdy,doBohumin))->Activate();
    }
    else
    {
        for(int i = BohDetNavestidla; i < BohDetNavestidla * 2 - 1; i++)
        {
            Seize(BohDet[i]);
            Wait(BohDetCas * rychlostRychlKNakl);
            Release(BohDet[i]);
        }

        Seize(BohDet[BohDetNavestidla * 2 - 1]);

        if(vlakyVBohumin > kapacitaBohumin)
        {   
            zaplnenostBohumin++;
            frontaBohumin.Insert(this);
            Passivate();
        }

        Wait(BohDetCas * rychlostRychlKNakl);
        Release(BohDet[BohDetNavestidla * 2 - 1]);

        dobaJizdyNaTratiBohuminDetmarovice(Time - zacatekJizdy);
        vlakyVDetmarovice--;
        if(frontaDetmarovice.Empty() == false)
        {
            frontaDetmarovice.GetFirst()->Activate();
        }
        if(zacatekExistence != -1)
        {
            zacatekJizdy = zacatekExistence;
        }
        (new rychlikBohumin(zacatekJizdy,doBohumin))->Activate();
    }
}

void rychlikKarvina::Behavior()
{
    double zacatekJizdy = Time;

    if(zacatekExistence == -1)
    {
        pocetRychliku++;
    }
    
    vlakyVKarvine++;

    if(!doBohumin)
    {
        for(int i = 0; i < KarLouNavestidla - 1; i++)
        {
            Seize(KarLou[i]);
            Wait(KarLouCas * rychlostRychlKNakl);
            Release(KarLou[i]);
        }

        Seize(KarLou[KarLouNavestidla - 1]);

        if(vlakyVLouky > kapacitaLouky)
        {
            zaplnenostLouky++;
            frontaLouky.Insert(this);
            Passivate();
        }

        Wait(KarLouCas * rychlostRychlKNakl);
        Release(KarLou[KarLouNavestidla - 1]);

        dobaJizdyNaTratiKarvinaLouky(Time - zacatekJizdy);
        vlakyVKarvine--;
        if(frontaKarvina.Empty() == false)
        {
            frontaKarvina.GetFirst()->Activate();
        }
        if(zacatekExistence != -1)
        {
            zacatekJizdy = zacatekExistence;
        }
        (new rychlikLouky(zacatekJizdy,doBohumin))->Activate();
    }
    else
    {
        for(int i = DetKarNavestidla; i < DetKarNavestidla * 2 - 1; i++)
        {
            Seize(DetKar[i]);
            Wait(DetKarCas * rychlostRychlKNakl);
            Release(DetKar[i]);
        }

        Seize(DetKar[DetKarNavestidla * 2 - 1]);

        if(vlakyVDetmarovice > kapacitaDetmarovice)
        {
            zaplnenostDetmarovice++;
            frontaDetmarovice.Insert(this);
            Passivate();
        }

        Wait(DetKarCas * rychlostRychlKNakl);
        Release(DetKar[DetKarNavestidla * 2 - 1]);

        dobaJizdyNaTratiDetmaroviceKarvina(Time - zacatekJizdy);
        vlakyVKarvine--;
        if(frontaKarvina.Empty() == false)
        {
            frontaKarvina.GetFirst()->Activate();
        }
        if(zacatekExistence != -1)
        {
            zacatekJizdy = zacatekExistence;
        }
        (new rychlikDetmarovice(zacatekJizdy,doBohumin))->Activate();   
    }
}

void rychlikLouky::Behavior()
{
    double zacatekJizdy = Time;

    if(zacatekExistence == -1)
    {
        pocetRychliku++;
    }
    
    vlakyVLouky++;

   if(!doBohumin)
    {
        for(int i = 0; i < LouTesNavestidla - 1; i++)
        {
            Seize(LouTes[i]);
            Wait(LouTesCas * rychlostRychlKNakl);
            Release(LouTes[i]);
        }

        Seize(LouTes[LouTesNavestidla - 1]);

        if(vlakyVTesin > kapacitaTesin)
        {
            zaplnenostTesin++;
            frontaTesin.Insert(this);
            Passivate();
        }

        Wait(LouTesCas * rychlostRychlKNakl);
        Release(LouTes[LouTesNavestidla - 1]);

        dobaJizdyNaTratiLoukyTesin(Time - zacatekJizdy);
        vlakyVLouky--;
        if(frontaLouky.Empty() == false)
        {
            frontaLouky.GetFirst()->Activate();
        }
        if(zacatekExistence != -1)
        {
            zacatekJizdy = zacatekExistence;
        }
        (new rychlikTesin(zacatekJizdy,doBohumin))->Activate();
    }
    else
    {
        for(int i = KarLouNavestidla; i < KarLouNavestidla * 2 - 1; i++)
        {
            Seize(KarLou[i]);
            Wait(KarLouCas * rychlostRychlKNakl);
            Release(KarLou[i]);
        }

        Seize(KarLou[KarLouNavestidla * 2 - 1]);

        if(vlakyVKarvine > kapacitaKarvina)
        {
            zaplnenostKarvina++;
            frontaKarvina.Insert(this);
            Passivate();
        }

        Wait(KarLouCas * rychlostRychlKNakl);
        Release(KarLou[KarLouNavestidla * 2 - 1]);

        dobaJizdyNaTratiKarvinaLouky(Time - zacatekJizdy);
        vlakyVLouky--;
        if(frontaLouky.Empty() == false)
        {
            frontaLouky.GetFirst()->Activate();
        }
        if(zacatekExistence != -1)
        {
            zacatekJizdy = zacatekExistence;
        }
        (new rychlikKarvina(zacatekJizdy,doBohumin))->Activate();
    }
}

void rychlikTesin::Behavior()
{
    double zacatekJizdy = Time;

    if(zacatekExistence == -1)
    {
        pocetRychliku++;
    }
    
    vlakyVTesin++;  

    if(!doBohumin)
    {
        for(int i = 0; i < TesTriNavestidla - 1; i++)
        {
            Seize(TesTri[i]);
            Wait(TesTriCas * rychlostRychlKNakl);
            Release(TesTri[i]);
        }

        Seize(TesTri[TesTriNavestidla - 1]);

        if(vlakyVTrinec > kapacitaTrinec)
        {
            zaplnenostTrinec++;
            frontaTrinec.Insert(this);
            Passivate();
        }

        Wait(TesTriCas * rychlostRychlKNakl);
        Release(TesTri[TesTriNavestidla - 1]);

        dobaJizdyNaTratiTesinTrinec(Time - zacatekJizdy);
        vlakyVTesin--;
        if(frontaTesin.Empty() == false)
        {
            frontaTesin.GetFirst()->Activate();
        }
        if(zacatekExistence != -1)
        {
            zacatekJizdy = zacatekExistence;
        }
        (new rychlikTrinec(zacatekJizdy,doBohumin))->Activate();
    }
    else
    {
        for(int i = LouTesNavestidla; i < LouTesNavestidla * 2 - 1; i++)
        {
            Seize(LouTes[i]);
            Wait(LouTesCas * rychlostRychlKNakl);
            Release(LouTes[i]);
        }

        Seize(LouTes[LouTesNavestidla * 2 - 1]);

        if(vlakyVLouky > kapacitaLouky)
        {
            zaplnenostLouky++;
            frontaLouky.Insert(this);
            Passivate();
        }

        Wait(LouTesCas * rychlostRychlKNakl);
        Release(LouTes[LouTesNavestidla * 2 - 1]);

        dobaJizdyNaTratiLoukyTesin(Time - zacatekJizdy);
        vlakyVTesin--;
        if(frontaTesin.Empty() == false)
        {
            frontaTesin.GetFirst()->Activate();
        }
        if(zacatekExistence != -1)
        {
            zacatekJizdy = zacatekExistence;
        }
        (new rychlikLouky(zacatekJizdy,doBohumin))->Activate();
    }
}

void rychlikTrinec::Behavior()
{
    double zacatekJizdy = Time;

    if(zacatekExistence == -1)
    {
        pocetRychliku++;
    }
    
    vlakyVTrinec++;

    if(!doBohumin)
    {
        for(int i = 0; i < TriMosNavestidla - 1; i++)
        {
            Seize(TriMos[i]);
            Wait(TriMosCas * rychlostRychlKNakl);
            Release(TriMos[i]);
        }

        Seize(TriMos[TriMosNavestidla - 1]);

        if(vlakyVMosty > kapacitaMosty)
        {
            zaplnenostMosty++;
            frontaMosty.Insert(this);
            Passivate();
        }

        Wait(TriMosCas * rychlostRychlKNakl);
        Release(TriMos[TriMosNavestidla - 1]);

        dobaJizdyNaTratiTrinecMosty(Time - zacatekJizdy);
        vlakyVTrinec--;
        if(frontaTrinec.Empty() == false)
        {
            frontaTrinec.GetFirst()->Activate();
        }
        if(zacatekExistence != -1)
        {
            zacatekJizdy = zacatekExistence;
        }
        (new rychlikMosty(zacatekJizdy,doBohumin))->Activate();
    }
    else
    {
        for(int i = TesTriNavestidla; i < TesTriNavestidla * 2 - 1; i++)
        {
            Seize(TesTri[i]);
            Wait(TesTriCas * rychlostRychlKNakl);
            Release(TesTri[i]);
        }

        Seize(TesTri[TesTriNavestidla * 2 - 1]);

        if(vlakyVTesin > kapacitaTesin)
        {
            zaplnenostTesin++;
            frontaTesin.Insert(this);
            Passivate();
        }

        Wait(TesTriCas * rychlostRychlKNakl);
        Release(TesTri[TesTriNavestidla * 2 - 1]);

        dobaJizdyNaTratiTesinTrinec(Time - zacatekJizdy);
        vlakyVTrinec--;
        if(frontaTrinec.Empty() == false)
        {
            frontaTrinec.GetFirst()->Activate();
        }
        if(zacatekExistence != -1)
        {
            zacatekJizdy = zacatekExistence;
        }
        (new rychlikTesin(zacatekJizdy,doBohumin))->Activate();
    }
}

void rychlikMosty::Behavior()
{
    double zacatekJizdy = Time;

    if(zacatekExistence == -1)
    {
        pocetRychliku++;
    }
    
    vlakyVMosty++;

    if(doBohumin)
    {
        for(int i = TriMosNavestidla; i < TriMosNavestidla * 2 - 1; i++)
        {
            Seize(TriMos[i]);
            Wait(TriMosCas * rychlostRychlKNakl);
            Release(TriMos[i]);
        }

        Seize(TriMos[TriMosNavestidla * 2 - 1]);

        if(vlakyVTrinec > kapacitaTrinec)
        {
            zaplnenostTrinec++;
            frontaTrinec.Insert(this);
            Passivate();
        }

        Wait(TriMosCas * rychlostRychlKNakl);
        Release(TriMos[TriMosNavestidla * 2 - 1]);

        dobaJizdyNaTratiTrinecMosty(Time - zacatekJizdy);
        vlakyVMosty--;
        if(frontaMosty.Empty() == false)
        {
            frontaMosty.GetFirst()->Activate();
        }
        if(zacatekExistence != -1)
        {
            zacatekJizdy = zacatekExistence;
        }
        (new rychlikTrinec(zacatekJizdy,doBohumin))->Activate();
    }
    else
    {
        if(zacatekExistence == -1)
        {
            zacatekExistence = Time;
        }
        dobaExistenceRychlVlaku(Time - zacatekExistence);
        vlakyVMosty--;
        konecVMosty++;
        if(frontaMosty.Empty() == false)
        {
            frontaMosty.GetFirst()->Activate();
        }
        return;
    }
}