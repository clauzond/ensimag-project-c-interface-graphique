#include "ei_widget.h"
#include "ei_widgetclass.h"



typedef struct ei_widget_t  {
    ei_widgetclass_t* wclass;

    struct ei_widget_t* parent;
    struct ei_widget_t* children_head;
    struct ei_widget_t* children_tail;
} ei_widget_t;

typedef struct ei_frame_t {
    ei_widget_t*	widget;

    ei_relief_t*	relief;
    char**			text;
    ei_font_t*		text_font;
    ei_color_t*		text_color;
    ei_anchor_t*	text_anchor;
    ei_surface_t*	img;
    ei_rect_t**		img_rect;
    ei_anchor_t*	img_anchor;

} ei_frame_t;

void			ei_frame_configure		(ei_widget_t*		widget,
                                           ei_size_t*		requested_size,
                                           const ei_color_t*	color,
                                           int*			border_width,
                                           ei_relief_t*		relief,
                                           char**			text,
                                           ei_font_t*		text_font,
                                           ei_color_t*		text_color,
                                           ei_anchor_t*		text_anchor,
                                           ei_surface_t*		img,
                                           ei_rect_t**		img_rect,
                                           ei_anchor_t*		img_anchor);


ei_widget_t*		ei_widget_create		(ei_widgetclass_name_t	class_name,
                                             ei_widget_t*		parent,
                                             void*			user_data,
                                             ei_widget_destructor_t destructor);
