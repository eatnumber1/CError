#import <stdbool.h>

#import "cerror_codes.h"

extern cerror_id_t CERROR_ID_LIBC;

enum {
	CERROR_CODE_NOMEM
};

typedef struct cerror_t_nest {
	cerror_id_t type;
	cerror_id_t code;
	char *message;
	const struct cerror_t_nest *cause;
} cerror_t;

bool cerr_library_init();
void cerr_library_destroy();
bool cerr_new_error( const cerror_t **err, const cerror_id_t type, const cerror_id_t code, const char *message, const cerror_t *cause );
bool cerr_libc_error( const cerror_t **err, const cerror_id_t code );
bool cerr_libc_error_errno( const cerror_t **err );
