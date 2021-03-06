#import <assert.h>
#import <stdlib.h>

#import "libc.h"

int printf_e( cerror_t **err, const char *format, ... ) {
	va_list ap;
	va_start(ap, format);
	int ret = vprintf_e(err, format, ap);
	va_end(ap);
	return ret;
}

int vprintf_e( cerror_t **err, const char *format, va_list ap ) {
	return vfprintf_e(err, stdout, format, ap);
}

int fprintf_e( cerror_t **err, FILE *stream, const char *format, ... ) {
	va_list ap;
	va_start(ap, format);
	int ret = vfprintf_e(err, stream, format, ap);
	va_end(ap);
	return ret;
}

int vfprintf_e( cerror_t **err, FILE *stream, const char *format, va_list ap ) {
	int ret = vfprintf(stream, format, ap);
	if( ret < 0 ) {
		// Behavior not defined by POSIX. Assuming errno is set.
		cerr_libc_error_errno(err);
		return ret;
	}
	return ret;
}

size_t fread_e( cerror_t **err, void *ptr, size_t size, size_t nitems, FILE *stream ) {
	size_t ret = fread(ptr, size, nitems, stream);
	if( ferror(stream) ) {
		cerr_libc_error_errno(err);
		return ret;
	} else if( ret != nitems ) {
		assert(feof(stream));
	}
	return ret;
}

size_t fwrite_e( cerror_t **err, const void *ptr, size_t size, size_t nitems, FILE *stream ) {
	size_t ret = fwrite(ptr, size, nitems, stream);
	if( ret < nitems ) {
		cerr_libc_error_errno(err);
		return ret;
	}
	return ret;
}

bool fclose_e( cerror_t **err, FILE *stream ) {
	if( fclose(stream) == EOF ) {
		cerr_libc_error_errno(err);
		return false;
	}
	return true;
}

bool fflush_e( cerror_t **err, FILE *stream ) {
	if( fflush(stream) == EOF ) {
		cerr_libc_error_errno(err);
		return false;
	}
	return true;
}

void *realloc_e( cerror_t **err, void *ptr, size_t size ) {
	void *ret = realloc(ptr, size);
	if( ret == NULL ) {
		cerr_libc_error_errno(err);
		return NULL;
	}
	return ret;
}

void *malloc_e( cerror_t **err, size_t size ) {
	void *ret = malloc(size);
	if( ret == NULL ) {
		cerr_libc_error_errno(err);
		return NULL;
	}
	return ret;
}
