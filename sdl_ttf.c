/* sdl_ttf extension for PHP */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_sdl_ttf.h"
#include "sdl_ttf_arginfo.h"
#include "sdl_ttf_font.h"

#include <SDL2/SDL_ttf.h>

extern zend_class_entry *ttf_font_ce;
extern zend_bool sdl_surface_to_zval(SDL_Surface *surface, zval *z_val);
extern zend_bool zval_to_sdl_color(zval *value, SDL_Color *color);

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE()  \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

PHP_FUNCTION(TTF_Init)
{
	ZEND_PARSE_PARAMETERS_NONE();

	RETURN_LONG(TTF_Init());
}

PHP_FUNCTION(TTF_WasInit)
{
	ZEND_PARSE_PARAMETERS_NONE();

	RETURN_LONG(TTF_WasInit());
}

PHP_FUNCTION(TTF_Quit)
{
	ZEND_PARSE_PARAMETERS_NONE();

	TTF_Quit();
}

PHP_FUNCTION(TTF_OpenFont)
{
	char *name;
	size_t name_len;
	zend_long size;

	ZEND_PARSE_PARAMETERS_START(2, 2)
	Z_PARAM_STRING(name, name_len)
	Z_PARAM_LONG(size)
	ZEND_PARSE_PARAMETERS_END();

	TTF_Font *font = TTF_OpenFont(name, size);

	ttf_font_to_zval(font, return_value);
}

PHP_FUNCTION(TTF_CloseFont)
{
	zval *z_font;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_ZVAL(z_font)
	ZEND_PARSE_PARAMETERS_END();

	TTF_Font *font;
	font = php_ttf_font_from_zval_p(z_font);

	TTF_CloseFont(font);
}

PHP_FUNCTION(TTF_RenderText_Solid)
{
	char *text;
	size_t text_len;

	zval *z_font, *z_color;

	ZEND_PARSE_PARAMETERS_START(3, 3)
	Z_PARAM_OBJECT_OF_CLASS(z_font, ttf_font_ce)
	Z_PARAM_STRING(text, text_len)
	Z_PARAM_ZVAL(z_color)
	ZEND_PARSE_PARAMETERS_END();

	TTF_Font *font;
	font = php_ttf_font_from_zval_p(z_font);
	SDL_Color color;
	zval_to_sdl_color(z_color, &color);
	SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);

	sdl_surface_to_zval(surface, return_value);
}

PHP_FUNCTION(TTF_RenderText_Blended)
{
	char *text;
	size_t text_len;

	zval *z_font, *z_color;

	ZEND_PARSE_PARAMETERS_START(3, 3)
	Z_PARAM_OBJECT_OF_CLASS(z_font, ttf_font_ce)
	Z_PARAM_STRING(text, text_len)
	Z_PARAM_ZVAL(z_color)
	ZEND_PARSE_PARAMETERS_END();

	TTF_Font *font;
	font = php_ttf_font_from_zval_p(z_font);
	SDL_Color color;
	zval_to_sdl_color(z_color, &color);
	SDL_Surface *surface = TTF_RenderText_Blended(font, text, color);

	sdl_surface_to_zval(surface, return_value);
}

PHP_FUNCTION(TTF_RenderText_Shaded)
{
	char *text;
	size_t text_len;

	zval *z_font, *z_color, *z_backgroundColor;

	ZEND_PARSE_PARAMETERS_START(4, 4)
	Z_PARAM_OBJECT_OF_CLASS(z_font, ttf_font_ce)
	Z_PARAM_STRING(text, text_len)
	Z_PARAM_ZVAL(z_color)
	Z_PARAM_ZVAL(z_backgroundColor)
	ZEND_PARSE_PARAMETERS_END();

	TTF_Font *font;
	font = php_ttf_font_from_zval_p(z_font);
	SDL_Color color, backgroundColor;
	zval_to_sdl_color(z_color, &color);
	zval_to_sdl_color(z_backgroundColor, &backgroundColor);
	SDL_Surface *surface = TTF_RenderText_Shaded(font, text, color, backgroundColor);

	sdl_surface_to_zval(surface, return_value);
}

PHP_FUNCTION(TTF_SizeUTF8)
{
    char *text;
 	size_t text_len;
	zval *z_font, *z_width=NULL, *z_height=NULL;

	if( zend_parse_parameters(ZEND_NUM_ARGS(), "zsz/z/", &z_font, &text, &text_len, &z_width, &z_height) == FAILURE ) {
        return;
    }

	TTF_Font *font;
	font = php_ttf_font_from_zval_p(z_font);
	int w, h;

	TTF_SizeUTF8(font, text, &w, &h);

	zval_dtor(z_width);
	ZVAL_LONG(z_width, w);
	zval_dtor(z_height);
	ZVAL_LONG(z_height, h);
}

/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(sdl_ttf)
{
#if defined(ZTS) && defined(COMPILE_DL_SDL_TTF)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(sdl_ttf)
{
	char buffer[128];
	const SDL_version *linked_version = TTF_Linked_Version();

	php_info_print_table_start();
	php_info_print_table_header(2, "SDL_ttf support", "enabled");
	php_info_print_table_row(2, "SDL_ttf PHP extension version", PHP_SDL_TTF_VERSION);
	snprintf(buffer, sizeof(buffer), "%d.%d.%d", linked_version->major, linked_version->minor, linked_version->patch);
	php_info_print_table_row(2, "SDL_ttf linked version", buffer);
	php_info_print_table_end();
}
/* }}} */

PHP_MINIT_FUNCTION(sdl_ttf)
{
	php_ttf_font_minit_helper();

	return SUCCESS;
}

static const zend_module_dep ext_deps[] = {
	ZEND_MOD_REQUIRED("sdl")
		ZEND_MOD_END};

/* {{{ sdl_ttf_module_entry */
zend_module_entry sdl_ttf_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	ext_deps,
	"sdl_ttf",			 /* Extension name */
	ext_functions,		 /* zend_function_entry */
	PHP_MINIT(sdl_ttf),	 /* PHP_MINIT - Module initialization */
	NULL,				 /* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(sdl_ttf),	 /* PHP_RINIT - Request initialization */
	NULL,				 /* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(sdl_ttf),	 /* PHP_MINFO - Module info */
	PHP_SDL_TTF_VERSION, /* Version */
	STANDARD_MODULE_PROPERTIES};
/* }}} */

#ifdef COMPILE_DL_SDL_TTF
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(sdl_ttf)
#endif
