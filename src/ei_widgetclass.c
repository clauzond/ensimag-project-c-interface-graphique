#include "ei_widget.h"
#include "ei_widgetclass.h"



typedef struct ei_widgetclass_t {
    ei_widgetclass_name_t               name;
    ei_widgetclass_allocfunc_t          allocfunc;
    ei_widgetclass_releasefunc_t        releasefunc;
    ei_widgetclass_drawfunc_t           drawfunc;
    ei_widgetclass_setdefaultsfunc_t    setdefaultsfunc;
    ei_widgetclass_geomnotifyfunc_t     geomnotifyfunc;
    ei_widgetclass_handlefunc_t         handlefunc;
    struct ei_widgetclass_t*            next;
} ei_widgetclass_t;