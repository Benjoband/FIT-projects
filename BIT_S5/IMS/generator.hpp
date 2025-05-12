#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <simlib.h>
#include <string.h>

//po kolika minutách se má generovat nakladni vlak ve stanici
#define BohuminNaklInterval 160
#define DetmaroviceNaklInterval 1440
#define KarvinaNaklInterval 720
#define LoukyNaklInterval 480
#define TesinNaklInterval 360
#define TrinecNaklInterval 180
#define MostyNaklInterval 96

#define BohuminOsobInterval 57
#define MostyOsobInterval 57

#define RychlInterval 39

class GeneratorNakl : public Event {
    private:
            double interval;
            std::string stanice;

    public: 
            GeneratorNakl(double interval, std::string stanice);
            void Behavior() override; 

};

class GeneratorOsob : public Event {
    private:
            double interval;
            std::string stanice;

    public: 
            GeneratorOsob(double interval, std::string stanice);
            void Behavior() override; 

};  

class GeneratorRychl : public Event {
    private:
            double interval;

    public: 
            GeneratorRychl(double interval);
            void Behavior() override; 

};
#endif // GENERATOR_HPP
