#ifndef JC_VECTOR
#define JC_VECTOR

typedef struct
{
	void *elements;
	size_t used_size;
	size_t available_size;
} jc_vector;

void jc_vector_init(jc_vector *vector);
void jc_vector_add(jc_vector *vector, void *element);
void jc_vector_add(jc_vector *vector, void *element, int position);
void jc_vector_clear(jc_vector *vector);
jc_vector *jc_vector_clone(jc_vector *vector);
void *jc_vector_get(jc_vector *vector, int position);
void jc_vector_remove(jc_vector *vector, int position);
void *jc_vector_replace(jc_vector *vector, int position);
size_t jc_vector_size(jc_vector *vector);


#endif
