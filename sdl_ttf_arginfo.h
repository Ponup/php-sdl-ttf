/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 0509bf10887c0babd3cda7a4f7931ee606597491 */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_TTF_Init, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_TTF_Quit, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

#define arginfo_test1 arginfo_TTF_Quit

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_test2, 0, 0, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, str, IS_STRING, 0, "\"\"")
ZEND_END_ARG_INFO()


ZEND_FUNCTION(TTF_Init);
ZEND_FUNCTION(TTF_Quit);
ZEND_FUNCTION(test1);
ZEND_FUNCTION(test2);


static const zend_function_entry ext_functions[] = {
	ZEND_FE(TTF_Init, arginfo_TTF_Init)
	ZEND_FE(TTF_Quit, arginfo_TTF_Quit)
	ZEND_FE(test1, arginfo_test1)
	ZEND_FE(test2, arginfo_test2)
	ZEND_FE_END
};
