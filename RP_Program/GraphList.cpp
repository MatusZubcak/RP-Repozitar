//
// Created by Zalman on 19. 11. 2020.
//

#include "GraphList.h"
#include "GraphExceptions.h"
#include <fstream>
#include <iostream>






    void GraphList::createCubicGraphList(const std::string& Filename, const std::shared_ptr<PsiFunction>& strategy){
        numberOfVertices = -1;
        std::ifstream f;
        f.open( Filename );
        if (!f) {
            std::cerr << "Unable to open file " << Filename;
            exit(1);   // call system to stop
        }

        /* Pokusi sa pomocou txt suboru vytvorit korektny kubicky graf */
        try{
            f >> numberOfVertices;
            if( numberOfVertices < 0 ) throw WrongNumberOfVerticesException();

            std::vector< std::vector <int> > adjLists;
            int i = 0;
            int a,b,c;
            while(f >> a >> b >> c){
                i++;
                std::vector< int > adjList;

                adjList.push_back( a );
                adjList.push_back( b );
                adjList.push_back( c );

                adjLists.push_back(adjList);
                adjList.clear();

                /* Ak je graf korektny, tak ho zapise do Listu.
                 * Ak sa nieco pokazilo pri tvorbe - zly .txt subor,
                 * tak hodi exception a skonci s tvorbou*/
                if( i % numberOfVertices == 0){
                    CubicGraph cg(adjLists, strategy );
                    adjLists.clear();
                    if( cg.isCorrectlyDefined()){
                        cubicGraphsList.push_back(cg);
                    } else{
                        throw BadlyDefinedGraphException();
                    }
                }

            }

            f.close();

        } catch( std::exception& e ){
            f.close();
            std::cout<< "..." << std::endl;
            std::cout << e.what() << std::endl;
        }
    }

    void GraphList::psiForAllEdges_toTxt(const std::string& Filename){
        std::ofstream  f;
        f.open(Filename);
        if (!f) {
            std::cerr << "Unable to open file " << Filename;
            exit(1);   // call system to stop
        }

        for( int i = 0; i < cubicGraphsList.size(); i++){
            std::string graphString = cubicGraphsList[i].toString();
            graphString.erase(0, 3);
            f << graphString;

            //samotne psi
            std::string psiString = cubicGraphsList[i].psiForAllEdges_toString(nullptr);
            f << psiString << std::endl;

        }

        f.close();
    }


    /* vypise grafy, co obsahuje v
    * cubicGraphsList do suboru v tvare
    * podobnom ako bol povodny input txt */
    void GraphList::toTxt(const std::string& Filename){
        std::ofstream f;
        f.open(Filename);
        if (!f) {
            std::cerr << "Unable to open file " << Filename;
            exit(1);   // call system to stop
        }

        f << numberOfVertices << std::endl;

        for( int i = 0; i < cubicGraphsList.size(); i++){
            std::string s = cubicGraphsList[i].toString();
            s.erase(0, 2);
            f << s;
        }

        f.close();
    }