#ifndef __VRB_H__
#define __VRB_H__

/* C library */
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>

struct vrb {
	char *lower_ptr;
	char *upper_ptr;
	char *first_ptr;
	char *last_ptr;
	char *mem_ptr;
	size_t buf_size;
	int flags;
};
typedef struct vrb *vrb_p;


vrb_p vrb_init_opt(vrb_p vrb, size_t size, const char *name, int options);

#define vrb_capacity(b) ((b)->buf_size)
#define vrb_data_len(b) (((b)->last_ptr)-((b)->first_ptr))
#define vrb_data_ptr(b) ((b)->first_ptr)
#define vrb_data_end(b) ((b)->last_ptr)
#define vrb_space_len(b) (((b)->first_ptr)+((b)->buf_size)-((b)->last_ptr))
#define vrb_space_ptr(b) ((b)->last_ptr)
#define vrb_space_end(b) (((b)->first_ptr)+((b)->buf_size))
#define vrb_is_empty(b) (((b)->last_ptr)==((b)->first_ptr))
#define vrb_is_full(b) (vrb_space_len((b))==0)
#define vrb_is_not_empty(b) (!(vrb_is_empty((b))))
#define vrb_is_not_full(b) (!(vrb_is_full((b))))
#define vrb_new(s,n) (vrb_init_opt(((vrb_p)(NULL)),(s),(n),0))
#define vrb_new_opt(s,n,o) (vrb_init_opt(((vrb_p)(NULL)),(s),(n),(o)))
#define vrb_init(v,s,n) (vrb_init_opt((v),(s),(n),0))

/**
 *
 */
#define vrb_space_len(b) (((b)->first_ptr)+((b)->buf_size)-((b)->last_ptr))

#endif /* __VRB_H__ */
