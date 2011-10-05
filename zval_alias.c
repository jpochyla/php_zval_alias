#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_zval_alias.h"

ZEND_DECLARE_MODULE_GLOBALS(zval_alias)

static function_entry zval_alias_functions[] =
{
	PHP_FE(is_zval_alias, NULL)
	{NULL, NULL, NULL}
};

zend_module_entry zval_alias_module_entry =
{
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	PHP_ZVAL_ALIAS_EXTNAME,
	zval_alias_functions,
	NULL,
	NULL,
	PHP_RINIT(zval_alias),
	NULL,
	NULL,
#if ZEND_MODULE_API_NO >= 20010901
	PHP_ZVAL_ALIAS_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_ZVAL_ALIAS
ZEND_GET_MODULE(zval_alias)
#endif

PHP_RINIT_FUNCTION(zval_alias)
{
	ZVA_G(active_symbol_table) = NULL;

	return SUCCESS;
}

zval* xdebug_get_php_symbol(char* name, int name_length)
{
	HashTable           *st = NULL;
	zval               **retval;
	TSRMLS_FETCH();

	st = ZVA_G(active_symbol_table);
	if (st && st->nNumOfElements && zend_hash_find(st, name, name_length, (void **) &retval) == SUCCESS) {
		return *retval;
	}

	st = EG(active_op_array)->static_variables;
	if (st) {
		if (zend_hash_find(st, name, name_length, (void **) &retval) == SUCCESS) {
			return *retval;
		}
	}
	
	st = &EG(symbol_table);
	if (zend_hash_find(st, name, name_length, (void **) &retval) == SUCCESS) {
		return *retval;
	}
	return NULL;
}

PHP_FUNCTION(is_zval_alias)
{
	zval **args[2], *vars[2];
	int i;

	if (ZEND_NUM_ARGS() != 2 || zend_get_parameters_array_ex(2, args) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

#if PHP_VERSION_ID >= 50300
	if (!EG(active_symbol_table)) {
		zend_rebuild_symbol_table(TSRMLS_C);
	}
#endif

	for (i = 0; i < 2; i++) {
		if (Z_TYPE_PP(args[i]) == IS_STRING) {
			ZVA_G(active_symbol_table) = EG(active_symbol_table);
			vars[i] = xdebug_get_php_symbol(Z_STRVAL_PP(args[i]), Z_STRLEN_PP(args[i]) + 1);
		}
	}

	RETURN_BOOL(vars[0] && vars[1] && vars[0] == vars[1]);
}
