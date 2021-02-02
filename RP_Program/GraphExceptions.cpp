//
// Created by Zalman on 19. 11. 2020.
//

#include "GraphExceptions.h"

    const char* WrongNumberOfVerticesException::what() const noexcept
    {
        return "Bad number of vertices exception";
    }


    const char* BadlyDefinedGraphException::what() const noexcept
    {
        return "Badly defined Graph exception";
    }

    const char* EdgeNotExistException::what() const noexcept
    {
        return "You tried to suppress Edge that does not exist";
    }
