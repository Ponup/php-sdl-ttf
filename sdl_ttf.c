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

/* {{{ void test1() */
PHP_FUNCTION(test1)
{
	ZEND_PARSE_PARAMETERS_NONE();

	TTF_Init();
	TTF_Font *font = TTF_OpenFont("arial.ttf", 40);
	SDL_Color color = {255, 255, 255};
	SDL_Surface *surface = TTF_RenderText_Solid(font, "Open | Give | Pick up | Use | Walk | Talk", color);
	TTF_CloseFont(font);
	TTF_Quit();

	php_printf("The extension %s is loaded and working!\r\n", "sdl_ttf");

	sdl_surface_to_zval(surface, return_value);
}
/* }}} */

/* {{{ string test2( [ string $var ] ) */
PHP_FUNCTION(test2)
{
	char *var = "World";
	size_t var_len = sizeof("World") - 1;
	zend_string *retval;

	ZEND_PARSE_PARAMETERS_START(0, 1)
	Z_PARAM_OPTIONAL
	Z_PARAM_STRING(var, var_len)
	ZEND_PARSE_PARAMETERS_END();

	retval = strpprintf(0, "Hello %s", var);

	RETURN_STR(retval);
}
/* }}}*/

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
