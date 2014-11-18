
#include "fb.h"

#if defined(__cplusplus)
extern "C"
#endif
void kmain()
{
  fb_init();
  fb_writestr("Hello, World.\n");
}
