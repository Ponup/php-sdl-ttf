/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 233844ee06bb65ba7543a4bda09957a0cabd75f0 */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_TTF_Init, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_TTF_Quit, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_TTF_RenderText_Solid, 0, 2, SDL_Surface, 0)
	ZEND_ARG_TYPE_INFO(0, text, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO(0, color, SDL_Color, 0)
ZEND_END_ARG_INFO()


ZEND_FUNCTION(TTF_Init);
ZEND_FUNCTION(TTF_Quit);
ZEND_FUNCTION(TTF_RenderText_Solid);


static const zend_function_entry ext_functions[] = {
	ZEND_FE(TTF_Init, arginfo_TTF_Init)
	ZEND_FE(TTF_Quit, arginfo_TTF_Quit)
	ZEND_FE(TTF_RenderText_Solid, arginfo_TTF_RenderText_Solid)
	ZEND_FE_END
};
