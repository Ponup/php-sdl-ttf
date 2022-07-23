/* sdl_ttf extension for PHP */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_sdl_ttf.h"
#include "sdl_ttf_arginfo.h"

#include <SDL2/SDL_ttf.h>

extern zend_bool sdl_surface_to_zval(SDL_Surface *surface, zval *z_val);

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

PHP_FUNCTION(TTF_Quit)
{
	ZEND_PARSE_PARAMETERS_NONE();

	TTF_Quit();
}

PHP_FUNCTION(TTF_RenderText_Solid)
{
	char *text;
	size_t text_len;

	zval *z_color;

	ZEND_PARSE_PARAMETERS_START(2, 2)
	Z_PARAM_STRING(text, text_len)
	Z_PARAM_ZVAL(z_color)
	ZEND_PARSE_PARAMETERS_END();

	TTF_Font *font = TTF_OpenFont("arial.ttf", 40);
	SDL_Color *color = (SDL_Color *)// todo fetch from zval;
	SDL_Surface *surface = TTF_RenderText_Solid(font, text, *color);
	TTF_CloseFont(font);

	sdl_surface_to_zval(surface, return_value);
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
	php_info_print_table_start();
	php_info_print_table_header(2, "sdl_ttf support", "enabled");
	php_info_print_table_end();
}
/* }}} */

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
	NULL,				 /* PHP_MINIT - Module initialization */
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
