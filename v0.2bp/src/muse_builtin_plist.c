/**
 * @file muse_builtin_plist.c
 * @author Srikumar K. S. (mailto:kumar@muvee.com)
 *
 * Copyright (c) 2006 Jointly owned by Srikumar K. S. and muvee Technologies Pte. Ltd. 
 *
 * All rights reserved. See LICENSE.txt distributed with this source code
 * or http://muvee-symbolic-expressions.googlecode.com/svn/trunk/LICENSE.txt
 * for terms and conditions under which this software is provided to you.
 */

#include "muse_builtins.h"

/**
 * (get symbol property).
 * Looks up the given property for the given symbol.
 * If found, it yields the @code (property . value) @endcode pair,
 * and if not found, it evaluates to ().
 * @see fn_put()
 */
muse_cell fn_get( muse_env *env, void *context, muse_cell args)
{
	muse_cell sym	= muse_evalnext(&args);
	muse_cell prop	= muse_evalnext(&args);
	return muse_get_prop( sym, prop );
}

/**
 * (put symbol property value).
 * Sets the given property of the given symbol to the given value.
 * Subsequently, if you evaluate @code (get symbol property) @endcode,
 * you'll get @code (property . value) @endcode as the result.
 */
muse_cell fn_put( muse_env *env, void *context, muse_cell args)
{
	muse_cell sym	= muse_evalnext(&args);
	muse_cell prop	= muse_evalnext(&args);
	muse_cell value = muse_evalnext(&args);
	return muse_put_prop( sym, prop, value );
}

/**
 * (assoc plist key).
 * @see muse_assoc()
 */
muse_cell fn_assoc( muse_env *env, void *context, muse_cell args)
{
	muse_cell alist = muse_evalnext(&args);
	muse_cell prop = muse_evalnext(&args);
	return muse_assoc(alist,prop);
}

/**
 * (plist symbol).
 * @see muse_symbol_plist()
 */ 
muse_cell fn_plist( muse_env *env, void *context, muse_cell args)
{
	return muse_symbol_plist( muse_evalnext(&args) );
}

/**
 * (symbol "symbol-name").
 * Interns the symbol of the given textual name and returns a unique symbol
 * cell.
 */
muse_cell fn_symbol( muse_env *env, void *context, muse_cell args )
{
	muse_cell name = muse_evalnext(&args);
	int length = 0;
	const muse_char *text = muse_text_contents( name, &length );
	return muse_symbol( text, text + length );
}

/**
 * (name sym).
 * Returns the text name of the given symbol or () if the
 * given thing is not a symbol or doesn't have a name.
 */
muse_cell fn_name( muse_env *env, void *context, muse_cell args )
{
	muse_cell sym = muse_evalnext(&args);
	if ( sym && _cellt(sym) == MUSE_SYMBOL_CELL )
	{
		return _tail(_head(_tail(sym)));
	}
	else
		return MUSE_NIL;
}
