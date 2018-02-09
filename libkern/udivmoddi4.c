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
	// update from http://dox.ipxe.org/____udivmoddi4_8c_source.html
	u_quad_t r;

	if (b == 0) {
		return 0;
	}

	u_quad_t quot = 0, qbit = 1;

	// Left justify denominator and count shift
	while((int64_t) b >= 0) {
		b <<= 1;
		quot <<= 1;
	}
	while(qbit) {
		if (b <= a) {
			a -= b;
			quot += qbit;
		}
		b >>= 1;
		qbit >>= 1;
	}
	return quot;

	// (void)__qdivrem(a, b, &r);
	// return (r);
}

#endif