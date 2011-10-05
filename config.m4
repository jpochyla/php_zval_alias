PHP_ARG_ENABLE(zval_alias, whether to enable is_zval_alias support,
	[ --enable-zval_alias   Enable is_zval_alias support])

if test "$PHP_ZVAL_ALIAS" = "yes"; then
	AC_DEFINE(HAVE_ZVAL_ALIAS, 1, [Whether you have is_zval_alias])
	PHP_NEW_EXTENSION(zval_alias, zval_alias.c, $ext_shared)
fi
