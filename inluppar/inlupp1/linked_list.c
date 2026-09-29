#include <stdbool.h>
#include <stdlib.h>
#include "linked_list.h"
#include "list_iterator.h"
#include "common.h"
#define int_elem(x)   ((elem_t) { .i = (x) })
#define bool_elem(x)  ((elem_t) { .b = (x) })
#define ptr_elem(x)   ((elem_t) { .p = (x) })
#define string_elem(x) ((elem_t) { .s = (x) })

struct link 
{
    link_t *previous;
    elem_t value;
    link_t *next;
};

struct list 
{
    link_t *first;
    link_t *last;
    size_t size;
};

typedef struct list ioopm_list_t;
link_t *link_create(elem_t value, link_t *previous, link_t *next)
{
    link_t *link = calloc(1, sizeof(link_t));
    link->previous = previous;
    link->value = value;
    link->next = next;
    return link;
}

ioopm_list_t *ioopm_list_create(void)
{
    ioopm_list_t *list = calloc(1, sizeof(ioopm_list_t));

    link_t *head = link_create(int_elem(0), NULL, NULL);
    link_t *tail = link_create(int_elem(0), head, NULL);

    head->next = tail;
    list->first = head;
    list->last = tail;
    list->size = 0;

    return list;
}

link_t *link_destroy(link_t *link)
{   
    link_t *tmp = link->next;
    free(link);
    link = tmp;
    return link;
    
}


void ioopm_list_destroy(ioopm_list_t *list)
{
    link_t *first_link = list->first;
    
    while(first_link != list->last)
    {
        first_link = link_destroy(first_link);
    }

    free(first_link);
    free(list);
}

void ioopm_list_append(ioopm_list_t *list, elem_t value)
{
    link_t *link = link_create(value, list->last->previous, list->last);
    list->last->previous->next = link;
    list->last->previous = link;
    list->size = list->size + 1;

}

void ioopm_list_prepend(ioopm_list_t *list, elem_t value)
{
    link_t *link = link_create(value, list->first, list->first->next);
    list->first->next->previous = link;
    list->first->next = link;
    list->size = list->size + 1;
}


elem_t ioopm_list_head(ioopm_list_t *list)
{
    return list->first->next->value;
}

elem_t ioopm_list_last(ioopm_list_t *list)
{
    return list->last->previous->value;
}

void ioopm_list_insert(ioopm_list_t *list, size_t index, elem_t value)
{
    
    if(index <= list->size)
    {
        link_t *first_link = list->first->next;

        for(size_t i = 0; i < index; i++)
        {
            first_link = first_link->next;
        }
        link_t *link = link_create(value, first_link->previous, first_link);
        first_link->previous->next = link;
        first_link->previous = link;
        list->size = list->size + 1;
    }   
}



elem_t ioopm_list_remove(ioopm_list_t *list, size_t index)
{
    link_t *first_link = list->first->next;
    size_t i = 0;
    elem_t no_elem;


    while(first_link != list->last)
    {
        if(i == index)

        {   
            link_t *tmp_link_1 = first_link->next;
            link_t *tmp_link_2 = first_link->previous;

            first_link->previous->next = tmp_link_1;
            first_link->next->previous = tmp_link_2;
            elem_t tmp = first_link->value;
            list->size = list->size - 1;
            free(first_link);
            return tmp;
        }
        first_link = first_link->next;
        i++;
    }
    return no_elem;
}

elem_t ioopm_list_get(ioopm_list_t *list, size_t index)
{
    link_t *first_link = list->first->next;
    elem_t no_elem;

    size_t i = 0;
    while(first_link != list->last)
    {
        if(i == index)
        {
            return first_link->value;
        }
        first_link = first_link->next;
        i++;
    }

    return no_elem;
}

size_t ioopm_list_size(ioopm_list_t *list)
{
    return list->size;
}

bool ioopm_list_is_empty(ioopm_list_t *list)
{
    return list->first->next == list->last;   
}




struct list_iterator 
{
    ioopm_list_t *list;
    link_t *link;
};

ioopm_list_iterator_t *ioopm_list_iterator_create(ioopm_list_t *l)
{
    ioopm_list_iterator_t *it = calloc(1, sizeof(ioopm_list_iterator_t));
    it->list = l;
    it->link = l->first;
    return it;
}

void ioopm_list_iterator_destroy(ioopm_list_iterator_t *iter)
{
    free(iter);
}

bool ioopm_list_iterator_at_end(ioopm_list_iterator_t *iter)
{
    link_t *link = iter->link;
    link_t *last_link = iter->list->last;

    return link == last_link;
}

bool ioopm_list_iterator_advance(ioopm_list_iterator_t *iter)
{
    if(!ioopm_list_iterator_at_end(iter))
    {
    iter->link = iter->link->next;
    return true;
    }
return false;
}


elem_t ioopm_list_iterator_current(ioopm_list_iterator_t *iter)
{
    elem_t value = iter->link->value;
    return value;
}

elem_t ioopm_list_iterator_remove(ioopm_list_iterator_t *iter)
{
    elem_t value = iter->link->value;

    link_t *tmp = iter->link;
    iter->link->next->previous = tmp->previous;
    iter->link->previous->next = tmp->next;

  

    iter->link = (tmp->next == iter->list->last)
     ? tmp->previous 
     : tmp->next;

    free(tmp);
    iter->list->size = iter->list->size - 1;
    return value;

}

void ioopm_list_iterator_insert(ioopm_list_iterator_t *iter, elem_t element)
{
    link_t *current_link = iter->link;
    link_t *new_link =link_create(element, current_link, current_link->next);

    current_link->next = new_link;
    current_link->next->previous = new_link;

    if(current_link == iter->list->first)
    {
        iter->link = new_link;
    }

    iter->list->size = iter->list->size + 1;

}
