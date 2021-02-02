//
// Created by Zalman on 24. 12. 2020.
//

#include "GraphLoader.h"
#include "ReccursiveFactorPsi.h"
#include <sstream>

/* Nacita zo suboru s nazvom Filename kubicky graf reprezentovany vertikalnou maticou susednosti
 * Vzhladom na charakteristiku suboru, ktory poziva takyto zapis predpokladame, ze vrcholy su indexovane od 1
 * Grafu prideli strategiu na pocitanie Psi hodnoty strategy*/
CubicGraph GraphLoader::loadVerticalGraph (const std::string& Filename, std::shared_ptr<PsiFunction> strategy){
    CubicGraph g = CubicGraph();
    g.strategy = std::move(strategy);
    g.numberOfVertices = -1;
    int vertex;
    std::ifstream f;
    f.open(Filename);
    if (!f) {
        std::cerr << "Unable to open file " << Filename;
        exit(1);   // call system to stop
    }
    /*Pokusi sa pomocou txt suboru vytvorit korektny kubicky graf */
    try {
        std::string s;
        std::getline(f,s); //nacitame prvy redundantny riadok, ktory nam nehovori ziadnu informaciu

        std::vector<int> tmpList;
        for (int i = 0; i < 3; i++){
            std::getline(f, s);
            std::istringstream stream(s);

            while ( stream >> vertex){
                tmpList.push_back(vertex-1);
            }
        }

        std::vector<int> adjList;
        g.numberOfVertices = tmpList.size()/3;
        for(int i = 0; i < g.numberOfVertices; i++){
            adjList.push_back(tmpList[i]);
            adjList.push_back(tmpList[i + g.numberOfVertices]);
            adjList.push_back(tmpList[i + 2*g.numberOfVertices]);

            std::sort(adjList.begin(),adjList.end());
            g.adjLists.push_back(adjList);
            adjList.clear();
        }

        if (!g.isCorrectlyDefined()){
            throw BadlyDefinedGraphException();
        }
        f.close();
        return g;

    }  catch (std::exception &e) {
        f.close();
        std::cout<< "..." << std::endl;
        std::cout << e.what() << std::endl;
        return CubicGraph();
    }

}

/* Nacita kubicky graf zo suboru s nazvnom Filename. Graf je reprezentovany ako matica susednosti pre jednotlive vrcholy
 * horizontalne. Vrcholy indexujeme od 0
 * Grafu prideli strategiu na pocitanie Psi hodnoty strategy*/
CubicGraph GraphLoader::loadHorizontalGraph (const std::string& Filename, std::shared_ptr<PsiFunction> strategy){
    CubicGraph g = CubicGraph();
    g.strategy = std::move(strategy);
    g.numberOfVertices = -1;
    int vertex;
    std::ifstream f;
    f.open(Filename);
    if (!f) {
        std::cerr << "Unable to open file " << Filename;
        exit(1);   // call system to stop
    }
    /*Pokusi sa pomocou txt suboru vytvorit korektny kubicky graf */
    try {
        f >> g.numberOfVertices;
        if (g.numberOfVertices < 0) throw WrongNumberOfVerticesException();

        int i = 0;
        std::vector<int> adjList;
        while (f >> vertex && i < 3 * g.numberOfVertices) { //toto zmen ak chces iny ako kubicky graf
            adjList.push_back(vertex);

            if (i % 3 == 2) {  //toto zmen ak chces iny ako kubicky graf
                std::sort(adjList.begin(), adjList.end());
                g.adjLists.push_back(adjList);
                adjList.clear();
            }
            i++;
        }

        if(g.numberOfVertices < 0){
            throw WrongNumberOfVerticesException();
        }
        if (!g.isCorrectlyDefined()){
            throw BadlyDefinedGraphException();
        }
        f.close();
        return g;
    } catch (std::exception &e) {
        f.close();
        std::cout<< "..." << std::endl;
        std::cout << e.what() << std::endl;
        return CubicGraph();
    }
}

/* Nacita zo suboru s nazvom Filename List kubickych grafov reprezentovany vertikalnou maticou susednosti
* Vzhladom na charakteristiku suboru, ktory poziva takyto zapis predpokladame, ze vrcholy su indexovane od 1
* Grafom  prideli strategiu na pocitanie Psi hodnoty strategy*/
GraphList GraphLoader::loadVerticalGraphList (const std::string& Filename, const std::shared_ptr<PsiFunction>& strategy){
    GraphList gl = GraphList();
    gl.numberOfVertices = -1;
    std::ifstream  f;
    f.open( Filename );
    if (!f) {
        std::cerr << "Unable to open file " << Filename;
        exit(1);   // call system to stop
    }

    try{
        std::string s;
        while( std::getline(f,s) ){ //mozeme si dovolit, lebo prvy riadok nenesie ziadnu informaciu

            CubicGraph g = CubicGraph();
            g.strategy = strategy;
            std::vector<int> tmpList;
            int vertex;

            for (int i = 0; i < 3; i++){
                std::getline(f, s);
                std::istringstream stream(s);

                while ( stream >> vertex){
                    tmpList.push_back(vertex-1);
                }
            }

            std::vector<int> adjList;
            g.numberOfVertices = tmpList.size()/3;
            for(int i = 0; i < g.numberOfVertices; i++){
                adjList.push_back(tmpList[i]);
                adjList.push_back(tmpList[i + g.numberOfVertices]);
                adjList.push_back(tmpList[i + 2*g.numberOfVertices]);

                std::sort(adjList.begin(),adjList.end());
                g.adjLists.push_back(adjList);
                adjList.clear();
            }

            if(gl.numberOfVertices == -1) gl.numberOfVertices = g.numberOfVertices;
            if(gl.numberOfVertices != g.numberOfVertices) throw WrongNumberOfVerticesException();
            if (!g.isCorrectlyDefined()) throw BadlyDefinedGraphException();

            gl.cubicGraphsList.push_back(g);
        }

        f.close();
        return gl;
    } catch( std::exception& e ){
        f.close();
        std::cout<< "..." << std::endl;
        std::cout << e.what() << std::endl;
        return GraphList();
    }
}


/* Nacita list kubickych grafov zo suboru s nazvnom Filename. Graf je reprezentovany ako matica susednosti
* pre jednotlive vrcholy horizontalne. Vrcholy indexujeme od 0
* Grafom prideli strategiu na pocitanie Psi hodnoty strategy*/
GraphList GraphLoader::loadHorizontalGraphList (const std::string& Filename, const std::shared_ptr<PsiFunction>& strategy) {
    GraphList gl = GraphList();
    gl.numberOfVertices = -1;
    std::ifstream f;
    f.open(Filename);
    if (!f) {
        std::cerr << "Unable to open file " << Filename;
        exit(1);   // call system to stop
    }

    /* Pokusi sa pomocou txt suboru vytvorit korektny kubicky graf */
    try {
        f >> gl.numberOfVertices;
        if (gl.numberOfVertices < 0) throw WrongNumberOfVerticesException();

        std::vector<std::vector<int> > adjLists;
        int i = 0;
        int a, b, c;
        while (f >> a >> b >> c) {
            i++;
            std::vector<int> adjList;

            adjList.push_back(a);
            adjList.push_back(b);
            adjList.push_back(c);

            adjLists.push_back(adjList);
            adjList.clear();

            /* Ak je graf korektny, tak ho zapise do Listu.
             * Ak sa nieco pokazilo pri tvorbe - zly .txt subor,
             * tak hodi exception a skonci s tvorbou*/
            if (i % gl.numberOfVertices == 0) {
                CubicGraph cg(adjLists, strategy);
                adjLists.clear();
                if (cg.isCorrectlyDefined()) {
                    gl.cubicGraphsList.push_back(cg);
                } else {
                    throw BadlyDefinedGraphException();
                }
            }

        }

        f.close();
        return gl;

    } catch (std::exception &e) {
        f.close();
        std::cout << "..." << std::endl;
        std::cout << e.what() << std::endl;
        return GraphList();
    }
}

    /* Nacita zo suboru s nazvom Filename kubicky graf reprezentovany vertikalnou maticou susednosti
    * Vzhladom na charakteristiku suboru, ktory poziva takyto zapis predpokladame, ze vrcholy su indexovane od 1
    * Grafu prideli najrychlejsiu strategiu na pocitanie hodnoty Psi - strategiu ReccursiveFactorPsi */
    CubicGraph GraphLoader::loadVerticalGraph (const std::string& Filename){
        std::shared_ptr<PsiFunction> ReccursiveFactorPsiStrategy = std::make_shared<ReccursiveFactorPsi>();
        return GraphLoader::loadVerticalGraph(Filename, ReccursiveFactorPsiStrategy);
    }


    /* Nacita kubicky graf zo suboru s nazvnom Filename. Graf je reprezentovany ako matica susednosti pre jednotlive vrcholy
    * horizontalne. Vrcholy indexujeme od 0
    * Grafu prideli najrychlejsiu strategiu na pocitanie hodnoty Psi - strategiu ReccursiveFactorPsi */
    CubicGraph GraphLoader::loadHorizontalGraph (const std::string& Filename){
        std::shared_ptr<PsiFunction> ReccursiveFactorPsiStrategy = std::make_shared<ReccursiveFactorPsi>();
        return GraphLoader::loadHorizontalGraph(Filename, ReccursiveFactorPsiStrategy);
    }


    /* Nacita zo suboru s nazvom Filename List kubickych grafov reprezentovany vertikalnou maticou susednosti
    * Vzhladom na charakteristiku suboru, ktory poziva takyto zapis predpokladame, ze vrcholy su indexovane od 1
    * Grafu prideli najrychlejsiu strategiu na pocitanie hodnoty Psi - strategiu ReccursiveFactorPsi */
    GraphList GraphLoader::loadVerticalGraphList (const std::string& Filename){
        std::shared_ptr<PsiFunction> ReccursiveFactorPsiStrategy = std::make_shared<ReccursiveFactorPsi>();
        return GraphLoader::loadVerticalGraphList(Filename, ReccursiveFactorPsiStrategy);

    }


    /* Nacita list kubickych grafov zo suboru s nazvnom Filename. Graf je reprezentovany ako matica susednosti
    * pre jednotlive vrcholy horizontalne. Vrcholy indexujeme od 0
    * Grafu prideli najrychlejsiu strategiu na pocitanie hodnoty Psi - strategiu ReccursiveFactorPsi */
    GraphList GraphLoader::loadHorizontalGraphList (const std::string& Filename){
        std::shared_ptr<PsiFunction> ReccursiveFactorPsiStrategy = std::make_shared<ReccursiveFactorPsi>();
        return GraphLoader::loadHorizontalGraphList(Filename, ReccursiveFactorPsiStrategy);
    }




