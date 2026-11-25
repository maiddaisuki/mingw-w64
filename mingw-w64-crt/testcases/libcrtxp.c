static int *all_callbacks_called_ptr;

__declspec(dllexport)
void __cdecl setvar(int *var_all_callbacks_called_ptr)
{
  all_callbacks_called_ptr = var_all_callbacks_called_ptr;
}

#define DLL_BUILD
#include "t_crtxp_callback_order.c"
