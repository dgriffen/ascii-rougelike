#include <util/list.h>
#include <util/util.h>

#include <stdint.h>

List init_list(size_t elem_size) {
    size_t capacity = 10;
    size_t size = 0;
    void *data = malloc(elem_size * capacity);

    return (List){.capacity = capacity, .size = size, .elem_size = elem_size, .data = data};
}

void destroy_list(List *list) {
    list->size = 0;
    list->capacity = 0;
    free(list->data);
}

void *list_at(List *list, size_t index) {
    uint8_t *byte_data = (uint8_t *)list->data;
    void *elem = (void *) &byte_data[index * list->elem_size];

    return elem;
}

void list_place(List *list, size_t index, void *n) {
    uint8_t *byte_n = (uint8_t *)n;
    uint8_t *byte_data = (uint8_t *)list->data;

    for(size_t i = 0; i < list->elem_size; i++) {
        byte_data[(index * list->elem_size) + i] = byte_n[i];
    }
}

void list_push(List *list, void *n) {
    uint8_t *byte_n = (uint8_t *)n;
    uint8_t *byte_data = (uint8_t *)list->data;

    for(size_t i = 0; i < list->elem_size; i++) {
        byte_data[(list->size * list->elem_size) + i] = byte_n[i];
    }
    list->size++;

    if (list->size >= list->capacity) {
        // reallocate list
        void *new_data = realloc(list->data, list->elem_size * (list->capacity * 2));
        if (!new_data) {
            // error! revert the push
            list->size--;
            return;
        }
        list->data = new_data;
        list->capacity = list->capacity * 2;
    }
}

void* list_pop(List *list) {
    list->size--;
    uint8_t *byte_data = (uint8_t *)list->data;
    return &byte_data[list->size * list->elem_size];
}

void list_shuffle(List *list) {
    for (size_t i = 0; i < list->size; i++) {
        int swap = i + better_rand(list->size - i - 1);
        list_swap(list, swap, i);
    }
}

void list_swap(List *list, size_t first, size_t second) {
    uint8_t *byte_data = list->data;
    uint8_t *tmp = malloc(list->elem_size);
    for(size_t j = 0; j < list->elem_size; j++) {
        tmp[j] = byte_data[(first * list->elem_size) + j];
    }

    for(size_t j = 0; j < list->elem_size; j++) {
        byte_data[(first * list->elem_size) + j] = byte_data[(second * list->elem_size) + j];
    }
    
    for(size_t j = 0; j < list->elem_size; j++) {
        byte_data[(second * list->elem_size) + j] = tmp[j];
    }

    free(tmp);
}
