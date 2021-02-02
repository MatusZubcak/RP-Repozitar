//
// Created by Zalman on 19. 11. 2020.
//

#include "CubicGraph.h"
#include "GraphExceptions.h"
#include "ReccursiveFactorPsi.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

    /* Konstruktor - dostane pocet Vrcholov
    * a zoznam hran kazdeho vrchola v grafe
    *
    * Usporiada hrany v zozname
    * Predpoklada, ze graf je uz korektne zadany!
    * Default pre Psi strategiu je FactorPsi */
    CubicGraph::CubicGraph(const std::vector<std::vector<int>>& adjLists){
        this->numberOfVertices = adjLists.size();
        this->adjLists = adjLists;
        strategy = std::shared_ptr<PsiFunction>(new ReccursiveFactorPsi());
    }

    /* Taky isty konstruktor ako vyssie
     * ma zadane, aku specificku Psi strategiu ma pouzivat */
    CubicGraph::CubicGraph(const std::vector<std::vector<int>>& adjLists, std::shared_ptr<PsiFunction> strategy){
        this->numberOfVertices = adjLists.size();
        this->adjLists = adjLists;
        this->strategy = std::move(strategy);
    }

    int CubicGraph::findPsiValue() {
        return strategy->getPsiValue(this->adjLists);
    }

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
    CubicGraph CubicGraph::suppressEdge(std::pair <int, int> e){
        if(edgeExist(e)){
            CubicGraph newGraph = CubicGraph(adjLists, strategy);

            for(int i = 0; i < newGraph.adjLists[e.first].size(); i++) {
                if (newGraph.adjLists[e.first][i] == e.second) {
                    newGraph.adjLists[e.first][i] = newGraph.adjLists[e.first].back();
                    newGraph.adjLists[e.first].pop_back();
                }
            }
            newGraph.fixVertex( e.first );
            newGraph.adjLists[e.first].clear();

            for(int i = 0; i < newGraph.adjLists[e.second].size(); i++){
                if(newGraph.adjLists[e.second][i] == e.first){
                    newGraph.adjLists[e.second][i] = newGraph.adjLists[e.second].back();
                    newGraph.adjLists[e.second].pop_back();
                }
            }
            newGraph.fixVertex( e.second );
            newGraph.adjLists[e.second].clear();

            return newGraph;

        } else{
            throw EdgeNotExistException();
        }
    }

    /* vrati textovy subor Filename ako zaznam typu:
    * potlacena hrana: (v1, v2)    hodnota psi: x */
    void CubicGraph::psiForAllEdges_toTxt(const std::string& Filename) {
        std::ofstream f;
        f.open(Filename);
        if (!f) {
            std::cerr << "Unable to open file " << Filename;
            exit(1);   // call system to stop
        }

        for(int i = 0; i < numberOfVertices; i++){
            for(int j = 0; j < adjLists[i].size(); j++){
                if(adjLists[i][j] > i){
                    CubicGraph newGraph = suppressEdge(std::pair<int,int>(i, adjLists[i][j]));
                    int psi = newGraph.findPsiValue();
                    f << "potlacena hrana: ( " << i << ", " << adjLists[i][j] << " )    hodnota psi: " << psi << std::endl;
                }
            }
        }
        f.close();
    }

    /* Opravi kubickost
    * vrcholov "postihnutych"
    * potlacenim jedneho
    * z vrcholov hrany e
    */
    void CubicGraph::fixVertex(int suppressedVertex){

        int fixVertex1 = adjLists[suppressedVertex].front();
        for(int i = 0; i < adjLists[fixVertex1].size(); i++){
            if(adjLists[fixVertex1][i] == suppressedVertex){
                adjLists[fixVertex1][i] = adjLists[fixVertex1].back();
                adjLists[fixVertex1].pop_back();
            }
        }

        int fixVertex2 = adjLists[suppressedVertex].back();
        for(int i = 0; i < adjLists[fixVertex2].size(); i++){
            if(adjLists[fixVertex2][i] == suppressedVertex){
                adjLists[fixVertex2][i] = adjLists[fixVertex2].back();
                adjLists[fixVertex2].pop_back();
            }
        }

        int edgeForV1;
        edgeForV1 = fixVertex2;
        adjLists[fixVertex1].push_back(edgeForV1);
        sort(adjLists[fixVertex1].begin(), adjLists[fixVertex1].end());

        int edgeForV2;
        edgeForV2 = fixVertex1;
        adjLists[fixVertex2].push_back(edgeForV2);
        sort(adjLists[fixVertex2].begin(), adjLists[fixVertex2].end());

    }

    /* Zisti, ci je kubicky graf korektne zadefinovany */
    bool CubicGraph::isCorrectlyDefined(){
        for( int j = 0; j < numberOfVertices; j++ ) {
            /* Zisti, ci každý vrchol ma 3 hrany */
            if ( adjLists[j].size() != 3 ){
                return false;
            }
            /* Zisti, ci je kazda hrana korektne definovana */
            for ( int k = 0; k < 3; k++ ) {
                bool edgeIsCorrect = false;
                for ( int l = 0; l < 3; l++ ) {
                    if ( adjLists[adjLists[j][k]][l] == j) {
                        edgeIsCorrect = true;
                    }
                }
                if ( !edgeIsCorrect ){
                    return false;
                }
            }
        }
        return true;
    }

    /* zisti ci hrana, ktoru chceme
     * potlacit vobec existuje */
    bool CubicGraph::edgeExist(std::pair<int, int> e) {
        bool correctEdge = false;
        for (int i = 0; i < adjLists[e.first].size(); i++) {
            if (adjLists[e.first][i] == e.second) correctEdge = true;
        }
        if (!correctEdge) return false;

        correctEdge = false;
        for (int i = 0; i < adjLists[e.second].size(); i++) {
            if (adjLists[e.second][i] == e.first) correctEdge = true;
        }

        return correctEdge;
    }

    /* vypise graf v sucasnom stave do suboru s nazvom Filename  */
    void CubicGraph::toTxt( const std::string& Filename){
        std::ofstream f;
        f.open( Filename );
        if (!f) {
            std::cerr << "Unable to open file " << Filename;
            exit(1);   // call system to stop
        }

        f << numberOfVertices << std::endl;
        for( int i = 0; i < numberOfVertices; i++ ){

            if(!adjLists[i].empty()){

                for( int j = 0; j < adjLists[i].size(); j++ ){
                    f << adjLists[i][j];
                    if( j < adjLists[i].size() - 1 ){
                        f << " ";
                    } else{
                        f << std::endl;
                    }
                }

            } else{
                f << "_ _ _" << std::endl;
            }
        }
        f.close();
    }

    /* vypise graf ako string,
     * podobne ako vyzera vypis grafu
     * v txt. subore */
    std::string CubicGraph::toString(){
        std::string graphString = std::to_string(numberOfVertices) + "\n";
        for( int i = 0; i < numberOfVertices; i++ ){
            if(!adjLists[i].empty()) {
                for (int j = 0; j < adjLists[i].size(); j++) {

                    graphString.append(std::to_string(adjLists[i][j]));
                    if (j < adjLists[i].size() - 1) {
                        graphString.append(" ");
                    } else {
                        graphString.append("\n");
                    }

                }
            }
            else{
                graphString.append("_ _ _\n");
            }
        }
        return graphString;
    }

    /* vrati string ako zaznam typu:
     * potlacena hrana: (v1, v2)    hodnota psi: x */
    std::string CubicGraph::psiForAllEdges_toString(const char string[13]) {
        std::string psiString;
        for(int i = 0; i < numberOfVertices; i++){
            for(int j = 0; j < adjLists[i].size(); j++){
                if(adjLists[i][j] > i){
                    CubicGraph newGraph = suppressEdge(std::pair<int,int>(i, adjLists[i][j]));
                    int psi = newGraph.findPsiValue();
                    psiString.append("potlacena hrana: ( ");
                    psiString.append(std::to_string(i));
                    psiString.append(", ");
                    psiString.append(std::to_string(adjLists[i][j]));
                    psiString.append(" )    hodnota psi: ");
                    psiString.append(std::to_string(psi));
                    psiString.append("\n");
                }
            }
        }
        return psiString;
    }


    CubicGraph::~CubicGraph()= default;
