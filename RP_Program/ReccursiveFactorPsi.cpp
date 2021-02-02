//
// Created by Zalman on 5. 12. 2020.
//

#include <cassert>
#include <algorithm>
#include <iostream>
#include <unordered_set>
#include "ReccursiveFactorPsi.h"
/* normalizuje AdjLists do tvaru bez osamotenych vrcholov
 * a usorti Lists */

ReccursiveFactorPsi::ReccursiveFactorPsi() {
    psiValue = 0;
};

void ReccursiveFactorPsi::normalise (std::vector<std::vector<int>> &adjLists){
    bool loneVertexFound;
    do{
        loneVertexFound = false;
        int i = 0;
        while(i < adjLists.size()){
            if(adjLists[i].empty()){

                loneVertexFound = true;
                for(int j = 0; j < adjLists.size(); j++){
                    for(int k = 0; k < adjLists[j].size(); k++){
                        if(adjLists[j][k] > i) adjLists[j][k]--;
                    }
                }

                for(int j = i+1; j < adjLists.size(); j++){
                    std::swap(adjLists[j], adjLists[j-1]);
                }
                adjLists.pop_back();
                i = 0;
            }
            i++;
        }
    }while(loneVertexFound);

    for(int i = 0; i < adjLists.size(); i++){
        assert(!adjLists[i].empty());
        std::sort(adjLists[i].begin(), adjLists[i].end());
    }

}

/*zisti ci je kruznica parnej dlzky.
 * Ak je, vykona aj reziu potrebnu na "vymazanie" danych hran z grafovej reprezentacie
 * aby sme tu istu kruznicu nepocitali 2-krat*/
bool ReccursiveFactorPsi::cycleIsEven( std::vector< std::pair <int, bool>> &linearGraphRepresentation, int vertex){

    int verticesInCycle = 0;
    int current = vertex;
    do{
        int next;
        for(int i = 0; i < 3; i++){
            if(!linearGraphRepresentation[3 * current + i].second){
                next = linearGraphRepresentation[ 3*current + i].first;
            }
            linearGraphRepresentation[ 3*current + i].second = true;
        }

        bool edgeAdded = false;
        for(int i = 0; i < 3; i++){
            if(!edgeAdded && !linearGraphRepresentation[ 3*next + i].second &&linearGraphRepresentation[ 3*next + i].first == current) {
                linearGraphRepresentation[3 * next + i].second = true;
                edgeAdded = true;
            }
        }

        current = next;
        verticesInCycle++;
    }while(current != vertex);

    if( verticesInCycle%2 == 0) return true;
    return false;
}


/* rekurzivne zgeneruje vsetky mozne 1-faktory a vypocita pre kazdy z nich pocet ofarbeni */
void ReccursiveFactorPsi::reccursivellyCountPsi(std::vector<std::pair<int, bool>> linearGraphRepresentation, int vertex){
    if( 3*vertex >= linearGraphRepresentation.size()){

            int potentialPsiForThis1Factor = 1;
            int lGR_size = linearGraphRepresentation.size();
            for(int i = 0; i < lGR_size; i++){
                if(!linearGraphRepresentation[i].second){
                    if(cycleIsEven(linearGraphRepresentation, i/3)){
                        potentialPsiForThis1Factor = 2*potentialPsiForThis1Factor;
                    } else{
                        return;
                    }
                }
            }
            //delime dvomi, lebo v skutocnosti tymto sposobom generujeme nie kombinacie ale permutacie rozdelenia 2-faktoru do 2 farieb
            psiValue += potentialPsiForThis1Factor/2;
            return;
    }

    //ak uz ma hranu tento vrchol, nema zmysel mu ju pridavat, rovno ideme na dalsi vrchol
    if( linearGraphRepresentation[ 3*vertex ].second ||
        linearGraphRepresentation[ 3*vertex + 1 ].second ||
        linearGraphRepresentation[ 3*vertex + 2 ].second){
        reccursivellyCountPsi(linearGraphRepresentation, vertex+1);
        return;
    }
    else { //ak nema hranu, pokusime sa mu ju pridat
        bool edgeAdded = false;
        for(int i = 0; i < 3; i++){
            if(linearGraphRepresentation[ 3*vertex + i].first > vertex){
                int neighbour = linearGraphRepresentation[ 3*vertex + i].first;
                bool neighbourHasEdge = false;
                for(int j = 0; j < 3; j++){
                    if(linearGraphRepresentation[ 3*neighbour + j].second) neighbourHasEdge = true;
                }

                if(!neighbourHasEdge){
                    linearGraphRepresentation[ 3*vertex + i].second = true;
                    int neighbourAddedEdge = -1;
                    for(int j = 0; j < 3; j++){
                        if(neighbourAddedEdge == -1 && linearGraphRepresentation[ 3*neighbour + j].first == vertex){
                            neighbourAddedEdge = 3*neighbour + j;
                            linearGraphRepresentation[ 3*neighbour + j].second = true;
                        }
                    }

                    edgeAdded = true;
                    reccursivellyCountPsi(linearGraphRepresentation, vertex+1);
                    linearGraphRepresentation[neighbourAddedEdge].second = false;
                    linearGraphRepresentation[ 3*vertex + i].second = false;
                }

            }
        }
        //ak sa nepodarilo hranu pridat, nema zmysel dalej uvazovat rekurziu
        if(!edgeAdded) return;
    }


}

int ReccursiveFactorPsi::getPsiValue(std::vector<std::vector<int>> adjLists) {
    psiValue = 0;
    normalise(adjLists);
    int n = adjLists.size();
    std::vector<std::pair<int, bool>> linearGraphRepresentation( 3*n );


    // adjLists to linear graph representation
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 3; j++){
            linearGraphRepresentation[3*i + j] = std::pair<int,bool>(adjLists[i][j], false);
        }
    }
    //std::cout << "___________________" << std::endl << std::endl;

    //fixne nastavime jednu pevnu hranu v 1-faktore, aby sme negenerovali moznosti navyse
    linearGraphRepresentation[0].second = true;
    int neighbour = linearGraphRepresentation[0].first;
    bool neighbourAdded = false;
    for(int j = 0; j < 3; j++){
        if( !neighbourAdded && linearGraphRepresentation[ 3*neighbour + j].first == 0){
            linearGraphRepresentation[ 3*neighbour + j].second = true;
            neighbourAdded = true;

            //std::cout << "neighbour: " << 3*neighbour + j << std::endl;
        }
    }
    //pre zvysne volame rekurzivnu funkciu na hladanie 1-faktoru
    reccursivellyCountPsi(linearGraphRepresentation, 1);
    return psiValue;
}