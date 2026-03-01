#define UNIQ(id, name, func, type, waxed, returned_type, type_func)                                               \
    static type_func wrapper_##func(void* data) {                                                                 \
        if (waxed == 0) {                                                                                         \
            __builtin_choose_expr(                                                                                \
                __builtin_types_compatible_p(type_func, void),                                                    \
                (void)((void(*)(void))func)(),                                                                    \
                return (type_func)((returned_type(*)(void))func)()                                                \
            );                                                                                                    \
        } else {                                                                                                  \
            __builtin_choose_expr(                                                                                \
                __builtin_types_compatible_p(type_func, void),                                                    \
                (void)__builtin_choose_expr(                                                                      \
                    (__builtin_types_compatible_p(type, char*) || __builtin_types_compatible_p(type, void*)),     \
                    ((void(*)(type))func)((type)data),                                                            \
                    ((void(*)(type))func)(*(type*)data)),                                                         \
                return (type_func)__builtin_choose_expr(                                                          \
                    (__builtin_types_compatible_p(type, char*) || __builtin_types_compatible_p(type, void*)),     \
                    func((type)data),                                                                             \
                    func(*(type*)data))                                                                           \
            );                                                                                                    \
        }                                                                                                         \
        /* Финальный возврат для не-void функций, чтобы компилятор не ругался */                                  \
        __builtin_choose_expr(                                                                                    \   
            __builtin_types_compatible_p(type_func, void),                                                        \
            (void)0,                                                                                              \
            return (type_func)0                                                                                   \
        );                                                                                                        \
    }                                                                                                               
VGA_LIST
#undef UNIQ
