//
// Created by Zalman on 19. 11. 2020.
//

#include <vector>
#include <string>
#include <memory>
#include "PsiFunction.h"

#ifndef SEMESTRALPROJECT_CUBICGRAPH_H
#define SEMESTRALPROJECT_CUBICGRAPH_H

class CubicGraph {

private:

    /* zoznam hran kazdeho vrchola v grafe*/
    std::vector< std::vector <int> > adjLists;
    int numberOfVertices{};

    /* strategia, pomocou ktorej pocita Psi */
    std::shared_ptr<PsiFunction> strategy;

    /* Zisti, ci je kubicky graf korektne zadefinovany */
    bool isCorrectlyDefined();

    /* zisti ci hrana, ktoru chceme
     * potlacit vobec existuje */
    bool edgeExist(std::pair<int, int> e);

    /* Opravi kubickost vrcholov "postihnutych"
     * potlacenim jedneho z vrcholov hrany e
     */
    void fixVertex(int suppressedVertex);



public:
    /* vrati string ako zaznam typu:
     * potlacena hrana: (v1, v2)    hodnota psi: x */
    std::string psiForAllEdges_toString(const char string[13]);

    /* GraphList je spriatelena trieda,
     * aby vedela lahko pracovat s listom
     * CubigGraph-ov
     *
     * GraphLoader je spriatelena trieda,
     * aby vedela lahko nacitat graf zo suboru*/
    friend class GraphList;
    friend class GraphLoader;

    /* Konstruktor, ktory vytvori prazdny graf*/
    CubicGraph()= default;;

    /* Konstruktor - dostane pocet Vrcholov
     * a zoznam hran kazdeho vrchola v grafe
     *
     * Usporiada hrany v zozname
     * Predpoklada, ze graf je uz korektne zadany!
     * * Default pre Psi strategiu je FactorPsi */
    explicit CubicGraph(const std::vector<std::vector<int>>& adjLists);

    /* Taky isty konstruktor ako vyssie
     * ma zadane, aku specificku Psi strategiu ma pouzivat */
    CubicGraph(const std::vector<std::vector<int>>& adjLists, std::shared_ptr<PsiFunction> strategy);

    /* Potlacenie hrany e
     * vytvori novy graf G
     * po polaceni hrany e
     * Ak taka hrana neexistuje
     * hodi edgeNotExist exception
     *
     * Momentalne nepotlaca hranu
     * podla definicie.
     * Namiesto vyhladenia vrcholov
     * im len odstrani hrany.
     *
     * Pre pocty hrnaovych farbeni by
     * to nemalo nic zmenit.
     * Myslim si, ze je to takto prehladnejsie*/
    CubicGraph suppressEdge(std::pair <int, int> e);

    /* funkcia, ktora najde hodnotu Psi
     * pre sucasny graf */
    int findPsiValue();

    /* vrati textovy subor Filename ako zaznam typu:
     * potlacena hrana: (v1, v2)    hodnota psi: x */
    void psiForAllEdges_toTxt(const std::string& Filename);

    /* vypise graf v sucasnom stave do suboru s nazvom Filename  */
    void toTxt( const std::string& Filename);

    /* vypise graf ako string,
     * podobne ako vyzera vypis grafu
     * v txt. subore */
    std::string toString();


    ~CubicGraph();
};


#endif //SEMESTRALPROJECT_CUBICGRAPH_H
