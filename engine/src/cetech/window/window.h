#pragma once

/*******************************************************************************
**** Includes
*******************************************************************************/

#include "celib/defines.h"

#include "celib/container_types.h"
#include "celib/math_types.h"

#if defined(CETECH_SDL2)
    #include "SDL2/SDL.h"
#endif

/*******************************************************************************
**** Interface
*******************************************************************************/
namespace cetech {

    /***************************************************************************
    **** Window struct
    ***************************************************************************/
#if defined(CETECH_SDL2)
    struct Window {
        SDL_Window* wnd;
    };
#endif


    /***************************************************************************
    **** Window manager
    ***************************************************************************/
    namespace window {

        /***********************************************************************
        **** Window flag
        ***********************************************************************/
        enum WindowFlags {
            WINDOW_NOFLAG = 0,
            WINDOW_FULLSCREEN = 1,

        };

        /***********************************************************************
        **** Window create position
        ***********************************************************************/
        enum WindowPos {
            WINDOWPOS_CENTERED = 1,
            WINDOWPOS_UNDEFINED = 2
        };

        /***********************************************************************
        **** Make new window
        ***********************************************************************/
        Window make_window(const char* title,
                           const int32_t x,
                           const int32_t y,
                           const int32_t width,
                           const int32_t height,
                           WindowFlags flags);

        /***********************************************************************
        **** Make new window from Native handler
        ***********************************************************************/
        Window make_from(void* hndl);

        /***********************************************************************
        **** Destroy window
        ***********************************************************************/
        void destroy_window(const Window& w);

        /***********************************************************************
        **** Set window title
        ***********************************************************************/
        void set_title(const Window& w,
                       const char* title);

        /***********************************************************************
        **** Set window title
        ***********************************************************************/
        const char* get_title(const Window& w);

        /***********************************************************************
        **** Update window
        ***********************************************************************/
        void update(const Window& w);

        /***********************************************************************
        **** Resize window
        ***********************************************************************/
        void resize(const Window& w,
                    uint32_t width,
                    uint32_t height);
    }
}
