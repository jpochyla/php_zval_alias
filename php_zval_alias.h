#ifndef PHP_ZVAL_ALIAS_H
#define PHP_ZVAL_ALIAS_H 1

#ifdef ZTS
#include "TSRM.h"
#endif

#define PHP_ZVAL_ALIAS_VERSION "1.0"
#define PHP_ZVAL_ALIAS_EXTNAME "zval_alias"

ZEND_BEGIN_MODULE_GLOBALS(zval_alias)
	HashTable *active_symbol_table;
	zend_op_array *active_op_array;
ZEND_END_MODULE_GLOBALS(zval_alias)

#ifdef ZTS
#define ZVA_G(v) TSRMG(zval_alias_globals_id, zend_zval_alias_globals *, v)
#else
#define ZVA_G(v) (zval_alias_globals.v)
#endif

PHP_RINIT_FUNCTION(zval_alias);

PHP_FUNCTION(is_zval_alias);

extern zend_module_entry zval_alias_module_entry;
#define phpext_hello_ptr &zval_alias_module_entry

#endif
