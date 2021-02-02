//
// Created by Zalman on 23. 11. 2020.
//

#ifndef SEMESTRALPROJECT_BACKTRACKPSI_H
#define SEMESTRALPROJECT_BACKTRACKPSI_H


#include "PsiFunction.h"

class BacktrackPsi : public PsiFunction{
private:

    bool nextColoring(std::vector<int> &color);

    /* pairList to adjLists */
    std::vector<std::vector<int>> toAdjLists(std::vector<std::pair<int, int>> pairList);


    /* pairList to adjLists */
    std::vector<std::pair<int,int>> toPairList(std::vector<std::vector<int>> AdjLists);

public:

    /* Konstruktor */
    BacktrackPsi();

    /* Samotna PsiFunkcia */
    int getPsiValue(std::vector< std::vector < int >> adjLists) override;

};


#endif //SEMESTRALPROJECT_BACKTRACKPSI_H
