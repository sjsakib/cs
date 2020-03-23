#include <stdio.h>
#include <stdlib.h>

struct Vector {
    int size;
    int *elements;
};

struct Vector* new_vector(int size) {
    struct Vector* newVector = malloc(sizeof(struct Vector));
    newVector->size = size;
    newVector->elements = malloc(size *sizeof(int));
    return newVector;
}

int get_element(struct Vector* v, int i) {
    return v->elements[i];
}
void put_element(struct Vector* v, int i, int x) {
    v->elements[i] = x;
}
void push_element(struct Vector* v, int x) {
    // Could allocate 10 at a time and keep another property for allocated size
    v->elements = realloc(v->elements, sizeof(int)*(v->size+1));
    v->elements[v->size] = x;
    v->size+=1;
}
int pop_element(struct Vector* v) {
    int ret = v->elements[v->size-1];
    v->elements = realloc(v->elements, sizeof(int)*(v->size-1));
    v->size-=1;
    return ret;
}

int main(int argc, char **argv) {
    struct Vector* list = new_vector(0);
    for(int  i = 0; i<100; i++) {
        push_element(list, i);
    }
    return 0;
}
