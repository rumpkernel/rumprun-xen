#ifndef __MINIOS_XMALLOC_H__
#define __MINIOS_XMALLOC_H__


#include <limits.h>

void *	memalloc(size_t, size_t);
void	memfree(void *);
void	free(void *);
int	posix_memalign(void **, size_t, size_t);
void *	realloc(void *, size_t);
void *	calloc(size_t, size_t);

#define DEFAULT_ALIGN (sizeof(unsigned long))

/* compat */
#define _xmalloc(size, align) memalloc(size, align)
#define xfree(ptr) free(ptr)


static inline void *_xmalloc_array(size_t size, size_t align, size_t num)
{
	/* Check for overflow. */
	if (size && num > UINT_MAX / size)
		return NULL;
 	return _xmalloc(size * num, align);
}

/* Allocate space for typed object. */
#define xmalloc(_type) ((_type *)_xmalloc(sizeof(_type), __alignof__(_type)))

/* Allocate space for array of typed objects. */
#define xmalloc_array(_type, _num) ((_type *)_xmalloc_array(sizeof(_type), __alignof__(_type), _num))

#endif /* __MINIOS_XMALLOC_H__ */
