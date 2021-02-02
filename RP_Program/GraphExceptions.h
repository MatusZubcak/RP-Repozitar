//
// Created by Zalman on 19. 11. 2020.
//

#ifndef SEMESTRALPROJECT_GRAPHEXCEPTIONS_H
#define SEMESTRALPROJECT_GRAPHEXCEPTIONS_H

#include <exception>


struct WrongNumberOfVerticesException : std::exception {
    const char* what() const noexcept override;
};

struct BadlyDefinedGraphException : std::exception {
    const char *what() const noexcept override;
};

struct EdgeNotExistException : std::exception {
    const char *what() const noexcept override;
};


#endif //SEMESTRALPROJECT_GRAPHEXCEPTIONS_H
