//
// Created by Zalman on 23. 11. 2020.
//

#ifndef SEMESTRALPROJECT_PSIFUNCTION_H
#define SEMESTRALPROJECT_PSIFUNCTION_H


#include <vector>

class PsiFunction{

public:
    /* Metoda, ktoru dedia a overriduju konkretne strategie
     * tam potom vyhodnocuje hodnotu Psi funkcie */
    virtual int getPsiValue(std::vector< std::vector < int >> AdjLists) = 0;
    virtual ~PsiFunction()= default;;


};

#endif //SEMESTRALPROJECT_PSIFUNCTION_H
