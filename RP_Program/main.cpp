#include <iostream>
#include <thread>
#include "CubicGraph.h"
#include "GraphList.h"
#include "ReccursiveFactorPsi.h"
#include "BacktrackPsi.h"
#include "GraphLoader.h"

int main() {
    std::shared_ptr<PsiFunction> strategyRec = std::make_shared<ReccursiveFactorPsi>();
    std::shared_ptr<PsiFunction> strategyBc = std::make_shared<BacktrackPsi>();

    CubicGraph cg = GraphLoader::loadHorizontalGraph("J9.txt");
    cg.toTxt("i9OUTRO.txt");
    cg.psiForAllEdges_toTxt("i9PSI.txt");
/*
    GraphList gl1 = GraphLoader::loadVerticalGraphList("s18c4.txt",strategyRec);
    gl1.psiForAllEdges_toTxt("s18c4PSI.txt");
    gl1.toTxt("s18c4OUTPUT.txt");

    GraphList gl2 = GraphLoader::loadVerticalGraphList("s20c4.txt",strategyRec);
    gl2.psiForAllEdges_toTxt("s20c4PSI.txt");
    gl2.toTxt("s20c4OUTPUT.txt");

    GraphList gl3 = GraphLoader::loadVerticalGraphList("s22c4.txt",strategyRec);
    gl3.psiForAllEdges_toTxt("s22c4PSI.txt");
    gl3.toTxt("s22c4OUTPUT.txt");

    GraphList gl4 = GraphLoader::loadVerticalGraphList("s24c4.txt",strategyRec);
    gl4.psiForAllEdges_toTxt("s24c4PSI.txt");
    gl4.toTxt("s24c4OUTPUT.txt");

    GraphList gl5 = GraphLoader::loadVerticalGraphList("s26c4.txt",strategyRec);
    gl5.psiForAllEdges_toTxt("s26c4PSI.txt");
    gl5.toTxt("s26c4OUTPUT.txt");

    GraphList gl6 = GraphLoader::loadVerticalGraphList("s28c4.txt",strategyRec);
    gl6.psiForAllEdges_toTxt("s28c4PSI.txt");
    gl6.toTxt("s28c4OUTPUT.txt");

    GraphList gl7 = GraphLoader::loadVerticalGraphList("s30c4.txt");
    gl7.psiForAllEdges_toTxt("s30c4PSI.txt");
    gl7.toTxt("s30c4OUTPUT.txt");
*/
    //GraphList g12("12g3e.txt", strategyRec);
    //g12.psiForAllEdges_toTxt("12g3ePsiLIST.txt");

    //GraphList g14("14g3e.txt", strategyRec);
    //g14.psiForAllEdges_toTxt("14g3ePsiLIST.txt");
/*
    CubicGraph pg = GraphLoader::loadHorizontalGraph("pg.10",strategyRec);
    pg.psiForAllEdges_toTxt("pgPSI.txt");
    pg.toTxt("pg.txt");

    CubicGraph i3 = GraphLoader::loadHorizontalGraph("i3.12",strategyRec);
    i3.psiForAllEdges_toTxt("i3PSI.txt");
    i3.toTxt("i3.txt");

    CubicGraph i5 = GraphLoader::loadHorizontalGraph("i5.20",strategyRec);
    i5.psiForAllEdges_toTxt("i5PSI.txt");
    i5.toTxt("i5.txt");

    CubicGraph i7 = GraphLoader::loadHorizontalGraph("i7.28",strategyRec);
    i7.psiForAllEdges_toTxt("i7PSI.txt");
    i7.toTxt("i7.txt");
*/

/*
    GraphList gl1 ("4g3e.txt", strategyRec);
    gl1.psiForAllEdges_toTxt("4g3ePsiLIST.txt");

    GraphList glbc1 ("4g3e.txt", strategyBc);
    glbc1.psiForAllEdges_toTxt("4g3ePsiBacktrackLIST.txt");

    GraphList gl2 ("6g3e.txt", strategyRec);
    gl2.psiForAllEdges_toTxt("6g3ePsiLIST.txt");

    GraphList glbc2 ("6g3e.txt", strategyBc);
    glbc2.psiForAllEdges_toTxt("6g3ePsiBacktrackLIST.txt");

    GraphList gl3 ("8g3e.txt", strategyRec);
    gl3.psiForAllEdges_toTxt("8g3ePsiLIST.txt");

    GraphList glbc3 ("8g3e.txt", strategyBc);
    glbc3.psiForAllEdges_toTxt("8g3ePsiBacktrackLIST.txt");

    GraphList gl4 ("10g3e.txt", strategyRec);
    gl4.psiForAllEdges_toTxt("10g3ePsiLIST.txt");

    GraphList glbc4 ("10g3e.txt", strategyBc);
    glbc4.psiForAllEdges_toTxt("10g3ePsiBacktrackLIST.txt");
*/



    /*CubicGraph cg1("10g3e.txt", strategy);
    cg1.psiForAllEdges_toTxt("10g3ePsi.txt");

    CubicGraph cg2("12g3e.txt", strategy);
    cg2.psiForAllEdges_toTxt("12g3ePsi.txt");

    CubicGraph cg3("14g3e.txt", strategy);
    cg3.psiForAllEdges_toTxt("14g3ePsi.txt");

    CubicGraph cg4("16g3e.txt", strategy);
    cg4.psiForAllEdges_toTxt("16g3ePsi.txt");

    CubicGraph cgBacktrack("10g3e.txt");
    cgBacktrack.psiForAllEdges_toTxt("10g3ePsiBacktrack.txt");*/


    /*CubicGraph cg1Backtrack("12g3e.txt");
    cg1Backtrack.psiForAllEdges_toTxt("12g3ePsiBacktrack.txt");

    CubicGraph cg2Backtrack("14g3e.txt");
    cg2Backtrack.psiForAllEdges_toTxt("14g3ePsiBacktrack.txt");

    CubicGraph cg3Backtrack("16g3e.txt");
    cg3Backtrack.psiForAllEdges_toTxt("16g3ePsiBacktrack.txt");*/
    //CubicGraph suppressed = cg.suppressEdge(std::pair<int, int>(5, 0));
    //std::cout << suppressed.toString() << std::endl << std::endl;
    //std::cout << suppressed.findPsiValue();


   /* CubicGraph cg(8, std::vector<std::vector<int>> {
            {5, 6, 7},
            {2, 3, 4},
            {1, 3, 4},
            {1, 2, 5},
            {1, 2, 6},
            {0, 3, 7},
            {0, 4, 7},
            {0, 5, 6}
    }, strategy);
    CubicGraph suppressed = cg.suppressEdge(std::pair<int,int>(0,5));
    std::cout << suppressed.psiForAllEdges_toString();*/


    /*CubicGraph cg(6, std::vector<std::vector<int>> {
            {1,1,5},
            {0,0,2},
            {1,3,4},
            {2,4,5},
            {2,3,5},
            {0,3,4},
    }, strategy);*/

   /* CubicGraph cg(6, std::vector<std::vector<int>> {
            {1,4,5},
            {0,2,5},
            {1,3,3},
            {2,2,4},
            {0,3,5},
            {0,1,4},
    }, strategy);*/
    /*std::cout << suppressed.toString() << std::endl << std::endl;
    std::cout << std::endl << suppressed.findPsiValue() << std::endl;*/

    return 0;
}
