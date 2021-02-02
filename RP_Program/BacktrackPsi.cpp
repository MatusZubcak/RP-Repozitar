//
// Created by Zalman on 23. 11. 2020.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>
#include "BacktrackPsi.h"

BacktrackPsi::BacktrackPsi(){}

/* pairList to adjLists */
std::vector<std::vector<int>> BacktrackPsi::toAdjLists(std::vector<std::pair<int, int>> pairList) {
    int NumberOfVertices = -1;
    for(std::pair<int, int> edge : pairList){
        if(edge.first > NumberOfVertices) NumberOfVertices = edge.first;
        if(edge.second > NumberOfVertices) NumberOfVertices = edge.second;
    }

    std::vector<std::vector<int>> adjLists(NumberOfVertices+1);

    for(std::pair<int, int> edge: pairList){
        adjLists[edge.first].push_back(edge.second);
        adjLists[edge.second].push_back(edge.first);
    }

    for(int i = 0; i < NumberOfVertices; i++){
        std::sort(adjLists[i].begin(), adjLists[i].end());
    }
    return adjLists;
}

std::vector<std::pair<int, int>> BacktrackPsi::toPairList(std::vector<std::vector<int>> adjLists) {
    std::vector<std::pair<int, int>> pairList;
    int NumberOfVertices = adjLists.size();
    for(int i = 0; i < NumberOfVertices; i++){
        for(int j = 0; j < adjLists[i].size(); j++) {
            if (adjLists[i][j] > i) pairList.push_back(std::pair<int, int>(i, adjLists[i][j]));
        }

    }
    return pairList;
}

int BacktrackPsi::getPsiValue(std::vector<std::vector<int>> adjLists){
        int psiValue = 0;
        int numberOfVertices = adjLists.size();
        std::vector<std::pair<int,int>> pairList = toPairList( adjLists );
        std::vector<std::vector<int>> adj = toAdjLists( pairList );
        sort(pairList.begin(), pairList.end());

        /* Pomocna maska colors na farbenie hran. Pouzivame farby
         * 0 - red, 1 - green, 2 - blue */
        std::vector<int> color(pairList.size(), 0);

        do{
            std::vector< std::vector< std::pair <int, int> > > coloredAdjLists(numberOfVertices);
            for(int k = 0; k < pairList.size(); k++){
                int v1 = pairList[k].first;
                int v2 = pairList[k].second;

                coloredAdjLists[v1].push_back( std::pair <int, int>(v2, color[k]));
                coloredAdjLists[v2].push_back( std::pair <int, int>(v1, color[k]));
            }
            bool wellColored = true;
            for(std::vector<std::pair<int,int>> neighbourList : coloredAdjLists) {

                std::vector<int> adjColors;
                for (std::pair<int, int> coloredEdge : neighbourList) {
                    adjColors.push_back(coloredEdge.second);
                }

                std::sort(adjColors.begin(), adjColors.end());
                if (adjColors.size() != 0) {
                    for (int i = 1; i < adjColors.size(); i++) {
                        if (adjColors[i - 1] == adjColors[i]) wellColored = false;
                    }
                }
                adjColors.clear();
            }

            if(wellColored) psiValue++;
            coloredAdjLists.clear();

            /*
            bool isWellColored = true;
            for(int i = 0; i < numberOfVertices; i++){
                std::vector<int> i_Colors;
                for( int neighbour : adjLists[i]){
                    std::vector<std::pair<int,int>> includedPairs;
                    for( int k = 0; k < pairList.size(); k++){
                        if( std::find(includedPairs.begin(), includedPairs.end(), pairList[k]) == includedPairs.end() ) {
                            if (pairList[k] == std::pair<int, int>(i, neighbour) ||
                                pairList[k] == std::pair<int, int>(neighbour, i)) {
                                includedPairs.push_back(pairList[k]);
                                i_Colors.push_back(color[k]);
                            }
                        }
                    }
                    includedPairs.clear();
                }
                sort(i_Colors.begin(), i_Colors.end());

                if(i_Colors.size() != 0){
                    for(int i = 1; i < i_Colors.size(); i++){
                        if(i_Colors[i-1] == i_Colors[i]) {
                            isWellColored = false;
                        }
                    }
                }
                i_Colors.clear();
            }
            if( isWellColored ) psiValue++;*/
        }while(nextColoring(color));

        /* pretoze generujeme permutacie 3 farieb, musime delit 6 ak chceme len kombinacie = mnoziny*/
    return psiValue/6;
    }

    /*dalsie ofarbenie */
    bool BacktrackPsi::nextColoring(std::vector<int> &color){

    for(int i = 0; i < color.size(); i++){
        if(color[i] == 2){
            color[i] = 0;
        }
        else {
            color[i]++;
            return true;
        }
    }
    return false;
    }