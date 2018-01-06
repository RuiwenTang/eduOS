#include <eduos/stddef.h>

#if __SIZEOF_POINTER__ == 4

typedef uint64_t u_quad_t;
u_quad_t __qdivrem(u_quad_t uq, u_quad_t vq, u_quad_t* arq);


/*
 * Return remainder after dividing two unsigned quads.
 */
u_quad_t __udivmoddi4(a, b)
u_quad_t a, b;
{
	u_quad_t r;

	(void)__qdivrem(a, b, &r);
	return (r);
}

#endif