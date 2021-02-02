//
// Created by Zalman on 24. 12. 2020.
//

#ifndef SEMESTRALPROJECT_GRAPHLOADER_H
#define SEMESTRALPROJECT_GRAPHLOADER_H

#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "CubicGraph.h"
#include "GraphList.h"
#include "GraphExceptions.h"

class GraphLoader{

public:

    GraphLoader()= default;;

    /* Nacita zo suboru s nazvom Filename kubicky graf reprezentovany vertikalnou maticou susednosti
    * Vzhladom na charakteristiku suboru, ktory poziva takyto zapis predpokladame, ze vrcholy su indexovane od 1
    * Grafu prideli strategiu na pocitanie Psi hodnoty strategy*/
    static CubicGraph loadVerticalGraph (const std::string& Filename, std::shared_ptr<PsiFunction> strategy);


    /* Nacita kubicky graf zo suboru s nazvnom Filename. Graf je reprezentovany ako matica susednosti pre jednotlive vrcholy
    * horizontalne. Vrcholy indexujeme od 0
    * Grafu prideli strategiu na pocitanie Psi hodnoty strategy*/
    static CubicGraph loadHorizontalGraph (const std::string& Filename, std::shared_ptr<PsiFunction> strategy);


    /* Nacita zo suboru s nazvom Filename List kubickych grafov reprezentovany vertikalnou maticou susednosti
    * Vzhladom na charakteristiku suboru, ktory poziva takyto zapis predpokladame, ze vrcholy su indexovane od 1
    * Grafom  prideli strategiu na pocitanie Psi hodnoty strategy*/
    static GraphList loadVerticalGraphList (const std::string& Filename, const std::shared_ptr<PsiFunction>& strategy);


    /* Nacita list kubickych grafov zo suboru s nazvnom Filename. Graf je reprezentovany ako matica susednosti
    * pre jednotlive vrcholy horizontalne. Vrcholy indexujeme od 0
    * Grafom prideli strategiu na pocitanie Psi hodnoty strategy*/
    static GraphList loadHorizontalGraphList (const std::string& Filename, const std::shared_ptr<PsiFunction>& strategy);

    /* Nacita zo suboru s nazvom Filename kubicky graf reprezentovany vertikalnou maticou susednosti
    * Vzhladom na charakteristiku suboru, ktory poziva takyto zapis predpokladame, ze vrcholy su indexovane od 1
    * Grafu prideli najrychlejsiu strategiu na pocitanie hodnoty Psi - strategiu ReccursiveFactorPsi */
    static CubicGraph loadVerticalGraph (const std::string& Filename);


    /* Nacita kubicky graf zo suboru s nazvnom Filename. Graf je reprezentovany ako matica susednosti pre jednotlive vrcholy
    * horizontalne. Vrcholy indexujeme od 0
    * Grafu prideli najrychlejsiu strategiu na pocitanie hodnoty Psi - strategiu ReccursiveFactorPsi */
    static CubicGraph loadHorizontalGraph (const std::string& Filename);


    /* Nacita zo suboru s nazvom Filename List kubickych grafov reprezentovany vertikalnou maticou susednosti
    * Vzhladom na charakteristiku suboru, ktory poziva takyto zapis predpokladame, ze vrcholy su indexovane od 1
    * Grafu prideli najrychlejsiu strategiu na pocitanie hodnoty Psi - strategiu ReccursiveFactorPsi */
    static GraphList loadVerticalGraphList (const std::string& Filename);


    /* Nacita list kubickych grafov zo suboru s nazvnom Filename. Graf je reprezentovany ako matica susednosti
    * pre jednotlive vrcholy horizontalne. Vrcholy indexujeme od 0
    * Grafu prideli najrychlejsiu strategiu na pocitanie hodnoty Psi - strategiu ReccursiveFactorPsi */
    static GraphList loadHorizontalGraphList (const std::string& Filename);


};

#endif //SEMESTRALPROJECT_GRAPHLOADER_H
