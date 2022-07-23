#include "sdl_ttf_font.h"
#include "sdl_ttf_arginfo.h"

zend_class_entry *ttf_font_ce = NULL;
zend_object_handlers php_ttf_font_object_handlers;

php_ttf_font_object *php_ttf_font_object_from_zend_object(zend_object *zobj)
{
    return ((php_ttf_font_object *)(zobj + 1)) - 1;
}

zend_object *php_ttf_font_object_to_zend_object(php_ttf_font_object *obj)
{
    return ((zend_object *)(obj + 1)) - 1;
}

TTF_Font *php_ttf_font_from_zval_p(zval *zp)
{
    return php_ttf_font_object_from_zend_object(Z_OBJ_P(zp))->internal;
}

inline void ttf_font_to_zval(TTF_Font *ttf_font, zval *zp)
{
    object_init_ex(zp, ttf_font_ce);
    php_ttf_font_object *php_ttf_font = php_ttf_font_object_from_zend_object(Z_OBJ_P(zp));
    php_ttf_font->internal = ttf_font;
}

zend_object *php_ttf_font_object_create(zend_class_entry *ce)
{
    php_ttf_font_object *obj = zend_object_alloc(sizeof(php_ttf_font_object), ce);
    zend_object *zobj = php_ttf_font_object_to_zend_object(obj);

    obj->internal = NULL;
    zend_object_std_init(zobj, ce);
    object_properties_init(zobj, ce);
    zobj->handlers = &php_ttf_font_object_handlers;

    return zobj;
}

void php_ttf_font_object_free(zend_object *zobj)
{
    php_ttf_font_object *obj = php_ttf_font_object_from_zend_object(zobj);

    if (obj->internal)
    {
        // TTF_CloseFont(obj->internal);
        obj->internal = NULL;
    }

    zend_object_std_dtor(zobj);
}

zend_function *php_ttf_font_object_get_constructor(zend_object *object)
{
    zend_throw_error(NULL, "You cannot initialize a TTF_Font object except through helper functions");
    return NULL;
}

void php_ttf_font_minit_helper(void)
{
    ttf_font_ce = register_class_TTF_Font();
    ttf_font_ce->create_object = php_ttf_font_object_create;

    memcpy(&php_ttf_font_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));
    php_ttf_font_object_handlers.clone_obj = NULL;
    php_ttf_font_object_handlers.free_obj = php_ttf_font_object_free;
    php_ttf_font_object_handlers.get_constructor = php_ttf_font_object_get_constructor;
    php_ttf_font_object_handlers.offset = XtOffsetOf(php_ttf_font_object, std);
}
