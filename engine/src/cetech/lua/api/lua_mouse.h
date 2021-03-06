#include "cetech/lua/lua_enviroment.h"
#include "cetech/lua/lua_stack.h"

#include "cetech/input/mouse.h"

namespace cetech {

    static int mouse_button_index(lua_State* L) {
        LuaStack stack(L);

        const char* scancode = stack.to_string(1);
        const uint32_t index = mouse::button_index(scancode);
        stack.push_uint32(index);
        return 1;
    }

    static int mouse_button_name(lua_State* L) {
        LuaStack stack(L);

        uint32_t index = stack.to_int(1);
        stack.push_string(mouse::button_name(index));
        return 1;
    }

    static int mouse_button_state(lua_State* L) {
        LuaStack stack(L);

        uint32_t index = stack.to_int(1);
        stack.push_bool(mouse::button_state(index));
        return 1;
    }

    static int mouse_button_pressed(lua_State* L) {
        LuaStack stack(L);

        uint32_t index = stack.to_int(1);
        stack.push_bool(mouse::button_pressed(index));
        return 1;
    }

    static int mouse_button_released(lua_State* L) {
        LuaStack stack(L);

        uint32_t index = stack.to_int(1);
        stack.push_bool(mouse::button_released(index));
        return 1;
    }

    static int mouse_axis(lua_State* L) {
        LuaStack stack(L);

        //uint32_t index = stack.to_int(1);
        stack.push_vector2(mouse::axis());
        return 1;
    }

    namespace lua_mouse {
        static const char* module_name = "Mouse";

        void load_libs() {
            lua_enviroment::set_module_function(module_name, "button_index", mouse_button_index);
            lua_enviroment::set_module_function(module_name, "button_name", mouse_button_name);
            lua_enviroment::set_module_function(module_name, "button_state", mouse_button_state);
            lua_enviroment::set_module_function(module_name, "pressed", mouse_button_pressed);
            lua_enviroment::set_module_function(module_name, "released", mouse_button_released);
            lua_enviroment::set_module_function(module_name, "axis", mouse_axis);
        }
    }
}
