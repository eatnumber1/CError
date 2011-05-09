#import <stdlib.h>
#import <string.h>
#import <errno.h>

#import "cerror.h"

static const char * const CERROR_DOMAIN_LIBC = "CERROR_DOMAIN_LIBC";

cerror_id_t CERROR_ID_LIBC;

static cerror_t *nomem;

static char *get_libc_error_message( int code ) {
	return strdup(strerror(code));
}

bool cerr_library_init() {
	nomem = malloc(sizeof(cerror_t));
	if( nomem == NULL ) return false;

	char *msg = get_libc_error_message(ENOMEM);
	if( msg == NULL ) {
		free(nomem);
		return false;
	}
	nomem->message = msg;

	CERROR_ID_LIBC = cerr_create_id(CERROR_DOMAIN_LIBC);
	nomem->type = CERROR_ID_LIBC;
	nomem->code = CERROR_CODE_NOMEM;

	nomem->cause = NULL;
	return true;
}

void cerr_library_destroy() {
	cerr_error_free(nomem);
}

bool cerr_new_error( cerror_t **err, const cerror_id_t type, const cerror_id_t code, const char *message, cerror_t *cause ) {
	if( err == NULL ) return true;

	cerror_t *nerr = malloc(sizeof(cerror_t));
	if( nerr == NULL ) {
		*err = nomem;
	}

	char *msg = strdup(message);
	if( msg == NULL ) {
		free(nerr);
		return false;
	}

	nerr->message = msg;
	nerr->type = type;
	nerr->code = code;
	nerr->cause = cause;

	*err = nerr;
	return true;
}

bool cerr_libc_error( cerror_t **err, const id_t code ) {
	return cerr_new_error(err, CERROR_ID_LIBC, code, strerror(code), NULL);
}

bool cerr_libc_error_errno( cerror_t **err ) {
	return cerr_libc_error(err, errno);
}

void cerr_error_free( cerror_t *err ) {
	if( err->cause != NULL ) cerr_error_free(err->cause);
	free(err->message);
	free(err);
}
