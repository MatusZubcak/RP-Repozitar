//
// Created by Zalman on 5. 12. 2020.
//

#ifndef SEMESTRALPROJECT_RECCURSIVEFACTORPSI_H
#define SEMESTRALPROJECT_RECCURSIVEFACTORPSI_H


#include "PsiFunction.h"

class ReccursiveFactorPsi : public PsiFunction {

private:
    /* pomocna na pocitanie psi hodnoty v rekurzii */
    int psiValue;

    /* normalizuje AdjLists do tvaru bez osamotenych vrcholov
     * a usorti Lists */
    void normalise (std::vector<std::vector<int>> &adjLists);

    /* rekurzivne zgeneruje vsetky mozne 1-faktory a vypocita pre kazdy z nich pocet ofarbeni */
    void reccursivellyCountPsi(std::vector<std::pair<int,bool>> linearGraphRepresentation, int vertex);

    /*zisti ci je kruznica parnej dlzky.
     * Ak je, vykona aj reziu potrebnu na "vymazanie" danych hran z grafovej reprezentacie
     * aby sme tu istu kruznicu nepocitali 2-krat*/
    bool cycleIsEven( std::vector< std::pair <int, bool> > &linearGraphRepresentation, int vertex);


public:

    /* Konstruktor */
    ReccursiveFactorPsi();

    /* Samotna PsiFunkcia
     *Zisti hodnotu Psi pomocou metody 1 a 2 faktorov*/
    int getPsiValue(std::vector< std::vector < int >> adjLists) override;

};


#endif //SEMESTRALPROJECT_RECCURSIVEFACTORPSI_H
