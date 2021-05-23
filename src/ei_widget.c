#include <stdlib.h>
#include <stdio.h>

#include "ei_widget.h"
#include "ei_widgetclass.h"
#include "ei_types.h"



typedef struct ei_frame_t {
    ei_widget_t*	widget;

    ei_size_t*		requested_size;
    const ei_color_t*	color;
    int*			border_width;
    ei_relief_t*	relief;
    char**			text;
    ei_font_t*		text_font;
    ei_color_t*		text_color;
    ei_anchor_t*	text_anchor;
    ei_surface_t*	img;
    ei_rect_t**		img_rect;
    ei_anchor_t*	img_anchor;

} ei_frame_t;

/**
 * @brief	Configures the attributes of widgets of the class "frame".
 *
 *		Parameters obey the "default" protocol: if a parameter is "NULL" and it has never
 *		been defined before, then a default value should be used (default values are
 *		specified for each parameter). If the parameter is "NULL" but was defined on a
 *		previous call, then its value must not be changed.
 *
 * @param	widget		The widget to configure.
 * @param	requested_size	The size requested for this widget, including the widget's borders.
 *				The geometry manager may override this size due to other constraints.
 *				Defaults to the "natural size" of the widget, ie. big enough to
 *				display the border and the text or the image. This may be (0, 0)
 *				if the widget has border_width=0, and no text and no image.
 * @param	color		The color of the background of the widget. Defaults to
 *				\ref ei_default_background_color.
 * @param	border_width	The width in pixel of the border decoration of the widget. The final
 *				appearance depends on the "relief" parameter. Defaults to 0.
 * @param	relief		Appearance of the border of the widget. Defaults to
 *				\ref ei_relief_none.
 * @param	text		The text to display in the widget, or NULL. Only one of the
 *				parameter "text" and "img" should be used (i.e. non-NULL). Defaults
 *				to NULL.
 * @param	text_font	The font used to display the text. Defaults to \ref ei_default_font.
 * @param	text_color	The color used to display the text. Defaults to
 *				\ref ei_font_default_color.
 * @param	text_anchor	The anchor of the text, i.e. where it is placed within the widget.
 *				Defines both the anchoring point on the parent and on the widget.
 *				Defaults to \ref ei_anc_center.
 * @param	img		The image to display in the widget, or NULL. Any surface can be
 *				used, but usually a surface returned by \ref hw_image_load. Only one
 *				of the parameter "text" and "img" should be used (i.e. non-NULL).
 				Defaults to NULL.
 * @param	img_rect	If not NULL, this rectangle defines a subpart of "img" to use as the
 *				image displayed in the widget. Defaults to NULL.
 * @param	img_anchor	The anchor of the image, i.e. where it is placed within the widget
 *				when the size of the widget is bigger than the size of the image.
 *				Defaults to \ref ei_anc_center.
 */
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
                                           ei_anchor_t*		img_anchor){

}


/**
 * @brief	Creates a new instance of a widget of some particular class, as a descendant of
 *		an existing widget.
 *
 *		The widget is not displayed on screen until it is managed by a geometry manager.
 *		When no more needed, the widget must be released by calling \ref ei_widget_destroy.
 *
 * @param	class_name	The name of the class of the widget that is to be created.
 * @param	parent 		A pointer to the parent widget. Can not be NULL.
 * @param	user_data	A pointer provided by the programmer for private use. May be NULL.
 * @param	destructor	A pointer to a function to call before destroying a widget structure. May be NULL.
 *
 * @return			The newly created widget, or NULL if there was an error.
 */
ei_widget_t*		ei_widget_create		(ei_widgetclass_name_t	class_name,
                                             ei_widget_t*		parent,
                                             void*			user_data,
                                             ei_widget_destructor_t destructor){
        // TODO: Vérification que la classe dont le nom a été passé en paramètre est connue par la bibliothèque

        // TODO: Appel de la fonction d'allocation de widgets de la classe

        // Initialisation des attributs communs à tous les widgets
        ei_widget_t* widget;
        widget->wclass = class_name;
        widget->user_data = user_data;
        widget->destructor = destructor;

        /* Widget Hierachy Management */
        widget->parent = parent;

        if (widget->parent->children_head != NULL){
                widget->next_sibling = widget->parent->children_head->next_sibling;
                widget->parent->children_head->next_sibling = widget;

        } else {
                widget->parent->children_head = widget;
                ei_widget_t* ptr = widget->parent;
                while (ptr != NULL){
                        ptr->children_tail = widget;
                        ptr = ptr->parent;
                }
                widget->next_sibling = NULL;
        }
        widget->children_head = NULL;
        widget->children_tail = NULL;

        // TODO: Appel de la fonction d'initialisation des attributs spécifiques à la classe

        return widget;

}


typedef struct ei_button_t {
        struct ei_widget_t*     widget;

        struct ei_relief_t*     relief;
        ei_font_t*              font;
        char**                  text;
        ei_color_t*             text_color;
        ei_rect_t*              button_rect;
        ei_color_t*             top_color;
        ei_color_t*             bot_color;
        ei_color_t*             inside_color;
        float*                  rayon;
        ei_anchor_t*            button_anchor;
} ei_button_t;

void			ei_button_configure		        (ei_widget_t*		widget,
                                                                ei_size_t*		requested_size,
                                                                const ei_color_t*	color,
                                                                int*			border_width,
                                                                int*			corner_radius,
                                                                ei_relief_t*		relief,
                                                                char**			text,
                                                                ei_font_t*		text_font,
                                                                ei_color_t*		text_color,
                                                                ei_anchor_t*		text_anchor,
                                                                ei_surface_t*		img,
                                                                ei_rect_t**		img_rect,
                                                                ei_anchor_t*		img_anchor,
                                                                ei_callback_t*		callback,
                                                                void**			user_param) {
        /* TODO: requested_size */
        if(color == NULL){
//                widget->wclass-> = ei_default_background_color;
        }
        if(border_width == NULL){
                border_width = k_default_button_border_width;
        }
        if(corner_radius == NULL){
                corner_radius = k_default_button_corner_radius;
        }
        if(relief == NULL){
                relief = ei_relief_none;
        }
        if(text_font == NULL){
                text_font = ei_default_font;
        }
        if(text_color == NULL){
//                text_color = ei_font_default_color;
        }
        if(text_anchor == NULL){
                text_anchor = ei_anc_center;
        }
        if(img_anchor == NULL){
                img_anchor = ei_anc_center;
        }

}
