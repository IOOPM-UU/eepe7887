#include <stdbool.h>
#include <stdlib.h>
#include "linked_list.h"

struct link 
{
    link_t *previous;
    int value;
    link_t *next;
};

struct list 
{
    link_t *first;
    link_t *last;
    int size;
};

typedef struct list ioopm_list_t;
link_t *link_create(int value, link_t *previous, link_t *next)
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
    list->first = NULL;
    list->last = NULL;
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

void ioopm_list_append(ioopm_list_t *list, int value)
{
    if (list->first == NULL)
    {
        link_t *link = link_create(value, NULL, NULL);
        list->first = link;
        list->last = link;
        list->size = list->size + 1;

    }
    else 
    {
        link_t *link = link_create(value, list->last, NULL);
        list->last->next = link;
        list->last = link;
        list->size = list->size + 1;

    }
}

void ioopm_list_prepend(ioopm_list_t *list, int value)
{
    if (list->first == NULL)
    {
        link_t *link = link_create(value, NULL, NULL);
        list->first = link;
        list->last = link;
        list->size = list->size + 1;

    }
    else
    {
        link_t *link = link_create(value, NULL, list->first);
        list->first->previous = link;
        list->first = link;
        list->size = list->size + 1;

    }
}

int ioopm_list_head(ioopm_list_t *list)
{
    return list->first->value;
}

int ioopm_list_last(ioopm_list_t *list)
{
    return list->last->value;
}

void ioopm_list_insert(ioopm_list_t *list, int index, int value)
{
    
    link_t *first_link = list->first;

      if (index == list->size)
       {
       ioopm_list_append(list, value);
        }

      else if (index == 0) 
        {
        ioopm_list_prepend(list, value);
        }

        else if(index == list->size - 1)
        {
            link_t *link = link_create(value, list->last->previous, list->last);
            list->last->previous->next = link;
            list->last->previous = link;
            list->size = list->size + 1;
        }
    else {
    int i = 0;
    while(first_link != list->last)
        {
            if(i == index)
            {
                link_t *link = link_create(value, first_link->previous, first_link);
                first_link->next->previous = link;
                first_link->next = link;
                list->size = list->size + 1;

                break;
            }
            first_link = first_link->next;

            i++;

        }    
    }
}


int ioopm_list_remove(ioopm_list_t *list, int index)
{
    link_t *first_link = list->first;
    int i = 0;
  

    if (index == list->size - 1) {
        link_t *last_link = list->last;
        last_link->previous->next = NULL;
        list->last = last_link->previous;
        int tmp = last_link->value;
        list->size = list->size - 1;
        free(last_link);
        return tmp;

    }

      if (index == 0) {
        first_link->next->previous = NULL;
        list->first = first_link->next;
        
        int tmp = first_link->value;
        list->size = list->size - 1;
        free(first_link);
        return tmp;
    }


    while(first_link != list->last)
    {
        if(i == index)

        {   
            link_t *tmp_link_1 = first_link->next;
            link_t *tmp_link_2 = first_link->previous;

            first_link->previous->next = tmp_link_1;
            first_link->next->previous = tmp_link_2;
            int tmp = first_link->value;
            list->size = list->size - 1;
            free(first_link);
            return tmp;
        }
        first_link = first_link->next;
        i++;
    }
    return 0;
}

int ioopm_list_get(ioopm_list_t *list, int index)
{
    link_t *first_link = list->first;


    int i = 0;
    while(first_link != list->last)
    {
        if(i == index)
        {
            return first_link->value;
        }
        first_link = first_link->next;
        i++;
    }

    if(first_link == list->last)
    {
        return first_link->value;
    }
    return 0;
}

int ioopm_list_size(ioopm_list_t *list)
{
    return list->size;
}

bool ioopm_list_is_empty(ioopm_list_t *list)
{
    if(list->first == NULL)
    {
        return true;
    }
    return false;
}



typedef struct list_iterator ioopm_list_iterator_t

struct list_iterator 
{
    ioopm_list_t *list;
    link_t *link;
}

ioopm_list_iterator_t *ioopm_list_iterator_create(ioopm_list_t *l)
{
    ioopm_list_iterator_t *it = calloc(sizeof(ioopm_hash_table_iterator_t));
    it->list = l;
    it->link = l->first;
}

void ioopm_list_iterator_destroy(ioopm_list_iterator_t *iter)
{
    free(iter);
}

bool ioopm_list_iterator_at_end(ioopm_list_iterator_t *iter)
{
    link_t *link = iter->link;
    link_t *last_link = iter->list->last;
    if(link = last)
    {
        return true;
    }
    return false;
}

void ioopm_list_iterator_advance(ioopm_list_iterator_t *iter)
{
    if(iter->link != iter->list->last)¨
    {
    iter->link = iter->link->next;
    }
}

int ioopm_list_iterator_current(ioopm_list_iterator_t *iter)
{
    int value = iter->link->value;
    return value;
}

int ioopm_list_iterator_remove(ioopm_list_iterator_t *iter)
{
    int value = iter->link->value;
    link_destroy(iter->link);
    return value;
}

void ioopm_list_iterator_insert(ioopm_list_iterator_t *iter, int element)
{
    link_t *current_link = iter->link;
    link_t *new_link =link_create(element, current_link->previous, current_link);
    current_link->previous->next = new_link;
    current_link->previous = new_link;


}
