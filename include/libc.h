#import <stdbool.h>
#import <stdio.h>
#import <stdarg.h>

#import "cerror.h"

int printf_e( const cerror_t **err, const char *format, ... );
int vprintf_e( const cerror_t **err, const char *format, va_list ap );
int fprintf_e( const cerror_t **err, FILE *stream, const char *format, ... );
int vfprintf_e( const cerror_t **err, FILE *stream, const char *format, va_list ap );
size_t fread_e( const cerror_t **err, void *ptr, size_t size, size_t nitems, FILE *stream );
size_t fwrite_e( const cerror_t **err, const void *ptr, size_t size, size_t nitems, FILE *stream );
