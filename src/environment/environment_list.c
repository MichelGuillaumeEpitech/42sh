/*
** EPITECH PROJECT, 2023
** src
** File description:
** list_environment
*/

#include "environment.h"

static environment_node_t *new(void)
{
    environment_node_t *node = malloc(sizeof(*node));

    if (!node)
        return (NULL);

    *node = (environment_node_t){0};

    return (node);
}

static void pop(environment_list_t *list, environment_node_t *node)
{
    if (!list || !node)
        return;
    if (--list->size <= 0) {
        list->size = 0;
        list->first = NULL;
        list->last = NULL;
        free (node);
        return;
    }
    if (node == list->first) {
        list->first = node->next;
        list->first->prev = NULL;
    } else if (node == list->last) {
        list->last = node->prev;
        list->last->next = NULL;
    } else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    free(node);
}

static void add(environment_list_t *list, environment_node_t *node)
{
    if (!list || !node)
        return;

    if (list->size == 0) {
        list->first = node;
        list->last = node;
    } else {
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
    }
    ++list->size;
}

environment_list_t *new_environment_list(void)
{
    environment_list_t *list = malloc(sizeof(*list));

    list->last = NULL;
    list->first = NULL;
    list->size = 0;
    list->add = add;
    list->new = new;
    list->pop = pop;

    return (list);
}
