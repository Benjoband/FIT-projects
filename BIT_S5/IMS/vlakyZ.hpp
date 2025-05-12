#ifndef VLAKY_HPP
#define VLAKY_HPP

#include <simlib.h>

//počet návěstidel na dané trati
#define BohDetNavestidla 5
#define DetKarNavestidla 6
#define KarLouNavestidla 5
#define LouTesNavestidla 3
#define TesTriNavestidla 6
#define TriMosNavestidla 20

//počet koleji v jednotlivých stanicích
#define BohuminKoleje 50
#define DetmaroviceKoleje 9
#define KarvinaKoleje 5
#define LoukyKoleje 7
#define TesinKoleje 12
#define TrinecKoleje 11
#define MostyKoleje 4

//čas za který vlak ujede jedno návěstidlo
#define BohDetCas 1.4561
#define DetKarCas 0.9613
#define KarLouCas 2.4324
#define LouTesCas 1.5878
#define TesTriCas 1.0072
#define TriMosCas 0.7680

#define rychlostOsobKNakl 1.3
#define rychlostRychlKNakl 0.85


extern Facility BohDet[BohDetNavestidla*2];
extern Facility DetKar[DetKarNavestidla*2];
extern Facility KarLou[KarLouNavestidla*2];
extern Facility LouTes[LouTesNavestidla*2];
extern Facility TesTri[TesTriNavestidla*2];
extern Facility TriMos[TriMosNavestidla*2];

extern Stat dobaJizdyNaTratiBohuminDetmarovice;
extern Stat dobaJizdyNaTratiDetmaroviceKarvina;
extern Stat dobaJizdyNaTratiKarvinaLouky;
extern Stat dobaJizdyNaTratiLoukyTesin;
extern Stat dobaJizdyNaTratiTesinTrinec;
extern Stat dobaJizdyNaTratiTrinecMosty;

extern Histogram dobaExistenceNaklVlaku;
extern Histogram dobaExistenceOsobVlaku;
extern Histogram dobaExistenceRychlVlaku;

extern int genOsobBohumin ;
extern int genOsobDetmarovice ;
extern int genOsobKarvina ;
extern int genOsobLouky ;
extern int genOsobTesin ;
extern int genOsobTrinec ;
extern int genOsobMosty ;

extern int genNaklBohumin ;
extern int genNaklDetmarovice ;
extern int genNaklKarvina ;
extern int genNaklLouky ;
extern int genNaklTesin ;
extern int genNaklTrinec ;
extern int genNaklMosty ;

extern int genRychlBohumin ;
extern int genRychlDetmarovice ;
extern int genRychlKarvina ;
extern int genRychlLouky ;
extern int genRychlTesin ;
extern int genRychlTrinec ;
extern int genRychlMosty ;

extern int vlakyVBohumin;
extern int vlakyVDetmarovice;
extern int vlakyVKarvine;
extern int vlakyVLouky;
extern int vlakyVTesin;
extern int vlakyVTrinec;
extern int vlakyVMosty;

extern int konecVBohumin;
extern int konecVDetmarovice;
extern int konecVKarvine;
extern int konecVLouky;
extern int konecVTesin;
extern int konecVTrinec;
extern int konecVMosty;

extern int kapacitaBohumin;
extern int kapacitaDetmarovice;
extern int kapacitaKarvina;
extern int kapacitaLouky;
extern int kapacitaTesin;
extern int kapacitaTrinec;
extern int kapacitaMosty;

extern int zaplnenostBohumin;
extern int zaplnenostDetmarovice;
extern int zaplnenostKarvina;
extern int zaplnenostLouky;
extern int zaplnenostTesin;
extern int zaplnenostTrinec;
extern int zaplnenostMosty;

extern int pocetNakladnichVlaku;
extern int pocetOsobnichVlaku;
extern int pocetRychliku;

extern Queue frontaBohumin;
extern Queue frontaDetmarovice;
extern Queue frontaKarvina;
extern Queue frontaLouky;
extern Queue frontaTesin;
extern Queue frontaTrinec;
extern Queue frontaMosty;


class naklBohumin : public Process {
  void Behavior() override;

    double zacatekExistence = -1;

    public: naklBohumin() : Process() {};
            naklBohumin(double time) : Process() {
                if(zacatekExistence == -1)
                {
                    this->zacatekExistence = time;
                }
                };
};

class naklDetmarovice : public Process {
  void Behavior() override;

    double zacatekExistence = -1;

    public: naklDetmarovice() : Process() {};
            naklDetmarovice(double time) : Process() {
                if(zacatekExistence == -1)
                {
                    this->zacatekExistence = time;
                }
                };
};

class naklKarvina : public Process {
  void Behavior() override;

    double zacatekExistence = -1;

    public: naklKarvina() : Process() {};
            naklKarvina(double time) : Process() {
                if(zacatekExistence == -1)
                {
                    this->zacatekExistence = time;
                }
                };
};


class naklLouky : public Process {
    void Behavior() override;

    double zacatekExistence = -1;

    public: naklLouky() : Process() {};
            naklLouky(double time) : Process() {
                if(zacatekExistence == -1)
                {
                    this->zacatekExistence = time;
                }
                };
};

class naklTesin : public Process {
  void Behavior() override;

    double zacatekExistence = -1;

    public: naklTesin() : Process() {};
            naklTesin(double time) : Process() {
                if(zacatekExistence == -1)
                {
                    this->zacatekExistence = time;
                }
                };
};

class naklTrinec : public Process {
  void Behavior() override;

    double zacatekExistence = -1;

    public: naklTrinec() : Process() {};
            naklTrinec(double time) : Process() {
                if(zacatekExistence == -1)
                {
                    this->zacatekExistence = time;
                }
                };
};

class naklMosty : public Process {
  void Behavior() override;

    double zacatekExistence = -1;

    public: naklMosty() : Process() {};
            naklMosty(double time) : Process() {
                if(zacatekExistence == -1)
                {
                    this->zacatekExistence = time;
                }
                };
};

class osobBohumin : public Process {
    void Behavior() override;

    double zacatekExistence = -1;
    bool doBohumin = false;

    public: osobBohumin() : Process() {
                this->doBohumin = false;
            };
            osobBohumin(double time, bool doBohumin) : Process() {
                if(zacatekExistence == -1)
                {
                    this->zacatekExistence = time;
                }
                this->doBohumin = doBohumin;
            };
};

class osobDetmarovice : public Process {
    void Behavior() override;

    double zacatekExistence = -1;
    bool doBohumin = false;

    public: osobDetmarovice() : Process() {
                this->doBohumin = false;
            };
            osobDetmarovice(double time, bool doBohumin) : Process() {
                if(zacatekExistence == -1)
                {
                    this->zacatekExistence = time;
                }

                this->doBohumin = doBohumin;
            };
};

class osobKarvina : public Process {
    void Behavior() override;

    double zacatekExistence = -1;
    bool doBohumin = false;

    public: osobKarvina() : Process() {
                this->doBohumin = false;
            };
            osobKarvina(double time, bool doBohumin) : Process() {
                if(zacatekExistence == -1)
                {
                    this->zacatekExistence = time;
                }

                this->doBohumin = doBohumin;
            };
};

class osobLouky : public Process {
    void Behavior() override;

    double zacatekExistence = -1;
    bool doBohumin = false;

    public: osobLouky() : Process() {
                this->doBohumin = false;
            };
            osobLouky(double time, bool doBohumin) : Process() {
                if(zacatekExistence == -1)
                {
                    this->zacatekExistence = time;
                }

                this->doBohumin = doBohumin;
            };
};

class osobTesin : public Process {
    void Behavior() override;

    double zacatekExistence = -1;
    bool doBohumin = false;

    public: osobTesin() : Process() {
                this->doBohumin = false;
            };
            osobTesin(double time, bool doBohumin) : Process() {
                if(zacatekExistence == -1)
                {
                    this->zacatekExistence = time;
                }

                this->doBohumin = doBohumin;
            };
};

class osobTrinec : public Process {
    void Behavior() override;

    double zacatekExistence = -1;
    bool doBohumin = false;

    public: osobTrinec() : Process() {
                this->doBohumin = false;
            };
            osobTrinec(double time, bool doBohumin) : Process() {
                if(zacatekExistence == -1)
                {
                    this->zacatekExistence = time;
                }

                this->doBohumin = doBohumin;
            };
};

class osobMosty : public Process {
    void Behavior() override;

    double zacatekExistence = -1;
    bool doBohumin = false;

    public: osobMosty() : Process() {
                this->doBohumin = true;
            };
            osobMosty(double time, bool doBohumin) : Process() {
                if(zacatekExistence == -1)
                {
                    this->zacatekExistence = time;
                }

                this->doBohumin = doBohumin;
            };
};

class rychlikBohumin : public Process {
    void Behavior() override;

    double zacatekExistence = -1;
    bool doBohumin = false;

    public: rychlikBohumin() : Process() {
                this->doBohumin = false;
            };
            rychlikBohumin(double time, bool doBohumin) : Process() {
                this->doBohumin = doBohumin;
                if(zacatekExistence == -1)
                {
                    this->zacatekExistence = time;
                }
            };
};

class rychlikDetmarovice : public Process {
    void Behavior() override;

    double zacatekExistence = -1;
    bool doBohumin = false;

    public: rychlikDetmarovice() : Process() {
                this->doBohumin = false;
            };
            rychlikDetmarovice(double time, bool doBohumin) : Process() {
                this->doBohumin = doBohumin;
                if(zacatekExistence == -1)
                {
                    this->zacatekExistence = time;
                }
            };
};

class rychlikKarvina : public Process {
    void Behavior() override;

    double zacatekExistence = -1;
    bool doBohumin = false;

    public: rychlikKarvina() : Process() {
                this->doBohumin = false;
            };
            rychlikKarvina(double time, bool doBohumin) : Process() {
                this->doBohumin = doBohumin;
                if(zacatekExistence == -1)
                {
                    this->zacatekExistence = time;
                }
            };
};

class rychlikLouky : public Process {
    void Behavior() override;

    double zacatekExistence = -1;
    bool doBohumin = false;

    public: rychlikLouky() : Process() {
                this->doBohumin = false;
            };
            rychlikLouky(double time, bool doBohumin) : Process() {
                this->doBohumin = doBohumin;
                if(zacatekExistence == -1)
                {
                    this->zacatekExistence = time;
                }
            };
};

class rychlikTesin : public Process {
    void Behavior() override;

    double zacatekExistence = -1;
    bool doBohumin = false;

    public: rychlikTesin() : Process() {
                this->doBohumin = false;
            };
            rychlikTesin(double time, bool doBohumin) : Process() {
                this->doBohumin = doBohumin;
                if(zacatekExistence == -1)
                {
                    this->zacatekExistence = time;
                }
            };
};

class rychlikTrinec : public Process {
    void Behavior() override;

    double zacatekExistence = -1;
    bool doBohumin = false;

    public: rychlikTrinec() : Process() {
                this->doBohumin = true; //TODO: zmenit na false
            };
            rychlikTrinec(double time, bool doBohumin) : Process() {
                this->doBohumin = doBohumin;
                if(zacatekExistence == -1)
                {
                    this->zacatekExistence = time;
                }
            };
};

class rychlikMosty : public Process {
    void Behavior() override;

    double zacatekExistence = -1;
    bool doBohumin = false;

    public: rychlikMosty() : Process() {
                this->doBohumin = true;
            };
            rychlikMosty(double time, bool doBohumin) : Process() {
                this->doBohumin = doBohumin;
                if(zacatekExistence == -1)
                {
                    this->zacatekExistence = time;
                }
            };
};
#endif // VLAKY_HPP