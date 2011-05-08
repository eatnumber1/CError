#import <string.h>
#import <assert.h>

#import "cerror_codes.h"

// Simple hash algorithm
cerror_id_t cerr_create_id( const char *unique ) {
	assert(unique != NULL);
	cerror_id_t id = 1;
	for( size_t i = 0; i < strlen(unique); i++ ) {
		id += unique[i];
	}
	return id;
}
