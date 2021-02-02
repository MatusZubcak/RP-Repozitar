//
// Created by Zalman on 19. 11. 2020.
//

#ifndef SEMESTRALPROJECT_GRAPHLIST_H
#define SEMESTRALPROJECT_GRAPHLIST_H

#include "CubicGraph.h"

class GraphList {

private:

    /* list kubickych grafov, ktore vytvori */
    std::vector<CubicGraph> cubicGraphsList;
    int numberOfVertices{};

    /* vytvori cubicGraphList, pre potreby konstruktora */
    void createCubicGraphList(const std::string& Filename, const std::shared_ptr<PsiFunction>& strategy);

public:

    /* Konstruktor, ktory vytvori prazdny list grafov*/
    GraphList() = default;;

    /*Spriateleny Loader, aby mohol nacitat graphList */
    friend class GraphLoader;

    /* vypise grafy, co obsahuje cubicGraphsList do suboru
     * v tvare podobnom ako bol povodny input txt */
    void toTxt(const std::string& Filename);

    /* vypise pre kazdy graf, co obsahuje cubicGraphsList
     * hodnoty Psi pre kazdy jeho vrchol.
     * Tvar: Graf (v tvare podobnom ako bol povodny input)
     *       Vsetky Psi hodnoty (v tvare ako pri CubicGraph)
     *       (nasleduje riadok oddelujuci grafy)*/
    void psiForAllEdges_toTxt(const std::string& Filename);

};


#endif //SEMESTRALPROJECT_GRAPHLIST_H
