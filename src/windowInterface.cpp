#include "windowInterface.h"

namespace ROOT_NAMESPACE
{
    std::list<windowInterface &> windowInterface::sm_windowList;

    const td::list<windowInterface &> & windowInterface::getAll()
    {
        return sm_windowList;
    }

    bool windowInterface::init(void)
    {
        if( object::init() )
        {
            return true;
        }

        return false;
    }
}