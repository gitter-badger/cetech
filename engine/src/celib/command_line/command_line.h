#pragma once

/*******************************************************************************
**** Includes
*******************************************************************************/
#include <cstring>

/*******************************************************************************
**** Interface
*******************************************************************************/
namespace cetech {

    /***************************************************************************
    **** Command line parser
    ***************************************************************************/
    namespace command_line {

        /***********************************************************************
        **** Set args
        ***********************************************************************/
        void set_args(int argc,
                      const char** argv);

        /***********************************************************************
        **** Find argument. Return index or argc if not found
        ***********************************************************************/
        int find_argument(const char* longopt,
                          char shortopt = '\0');

        /***********************************************************************
        **** Get parametr or nullptr
        ***********************************************************************/
        const char* get_parameter(const char* longopt,
                                  char shortopt = '\0');

        /***********************************************************************
        **** Has arguments?
        ***********************************************************************/
        bool has_argument(const char* longopt,
                          char shortopt = '\0');
    }
}
