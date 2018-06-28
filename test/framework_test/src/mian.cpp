#include "appaction.h"
#include "stdlib.h"
#include <unistd.h>

int main(int argc, char ** argv)
{
    IMSTACK

    ws::appaction::Create( argc, argv );
} 