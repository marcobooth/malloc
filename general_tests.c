/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_tests.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfleming <tfleming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 22:29:16 by tfleming          #+#    #+#             */
/*   Updated: 2018/01/14 12:50:32 by mbooth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>
#include <string.h>
#include "malloc.h"

intmax_t            ft_abs_large(intmax_t number)
{
    if (number < 0)
        return (-number);
    return (number);
}

void                write_chars(char *first, char *now, size_t number)
{
    while (now >= first)
    {
        *now = number % 10 + '0';
        number /= 10;
        now--;
    }
}

int        ft_count_digits_ularge(uintmax_t number)
{
    int    count;

    if (number == 0)
        return (1);
    count = 0;
    while (number > 0)
    {
        number /= 10;
        count++;
    }
    return (count);
}

void                put_size_t(size_t number)
{
    char    string[128 + 1];
    int        length;

    if (number == 0)
        ft_putstr("0");
    else
    {
        length = ft_count_digits_ularge(ft_abs_large(number));
        write_chars(string, string + length - 1, number);
        string[length] = '\0';
        ft_putstr(string);
    }
}

void        alloc_and_free(size_t repititions, size_t size)
{
    size_t    i;
    char    *malloced[repititions];

    ft_putstr("\nAbout to allocate ");
    put_size_t(size);
    ft_putstr(" bytes ");
    put_size_t(repititions);
    ft_putstr(" times. ");
    show_alloc_mem();
    i = 0;
    while (i < repititions)
    {
        malloced[i] = (char*)malloc(size);
        memset(malloced[i], 'f', size - 1);
        malloced[i][size - 1] = '\0';
        if (strlen(malloced[i]) != size - 1)
            ft_putstr("FAILED before being done!\n");
        i++;
    }
    ft_putstr("Allocated the memory. ");
    show_alloc_mem();
    i = 0;
    while (i < repititions)
    {
        if (strlen(malloced[i]) != size - 1)
            ft_putstr("FAILED!?!\n");
        free(malloced[i]);
        i++;
    }
    ft_putstr("Freed the memory. ");
    show_alloc_mem();
}

void        growing_realloc(size_t max_size, size_t step)
{
    size_t    current_size;
    char    *current;

    ft_putstr("\nGrowing realloc...\n");
    current_size = 8;
    current = NULL;
    while (current_size <= max_size)
    {
        ft_putstr("Allocating: ");
        put_size_t(current_size);
        current = (char*)realloc(current, current_size);
        if (current_size > 0)
        {
            if (current_size != step &&
                  ft_strlen(current) != current_size - step - 1)
                ft_putstr("\nFAILED!\n\n");
            memset(current, 'f', current_size);
            current[current_size - 1] = '\0';
            if (ft_strlen(current) != current_size - 1)
                ft_putstr("FAILED!");
        }
        current_size += step;
        ft_putstr("\t");
        show_alloc_mem();
        ft_putstr("\n");
    }
    free(current);
    ft_putstr("Freed the last allocated memory. ");
    show_alloc_mem();
}

void        try_every_size_up_to(size_t max, size_t step)
{
    size_t    i;
    void    *allocations[max];

    ft_putstr("Starting out. ");
    show_alloc_mem();
    i = 0;
    while (i < max)
    {
        allocations[i] = malloc(i);
        i += step;
    }
    ft_putstr("Mallocced everything. ");
    show_alloc_mem();
    ft_putstr("done with showing you some shit\n");
    i = 0;
    while (i < max)
    {
        free(allocations[i]);
        i += step;
    }
    ft_putstr("Freed everything. ");
    show_alloc_mem();
}

void        free_as_you_go(size_t repititions, size_t size)
{
    size_t    i;
    char    *result;

    ft_putstr("\nAbout to allocate then free ");
    put_size_t(size);
    ft_putstr(" bytes ");
    put_size_t(repititions);
    ft_putstr(" times. ");
    show_alloc_mem();
    i = 0;
    while (i < repititions)
    {
        result = (char*)malloc(size);
        memset(result, 'f', size - 1);
        result[size - 1] = '\0';
        if (strlen(result) != size - 1)
            ft_putstr("FAILED before being done!\n");
        free(result);
        i++;
    }
    ft_putstr("Done. ");
    show_alloc_mem();
}

int            main(void)
{
    ft_putstr("Starting testing program...\n");
    ft_putstr("getpagesize: ");
    put_size_t(getpagesize());
    ft_putstr("\n");
    try_every_size_up_to(3200, 8);
    alloc_and_free(400, 250);
    alloc_and_free(400, 2500);
    alloc_and_free(400, 4096);
    growing_realloc(20, 8);
    free_as_you_go(1024, 1024);

    // TODO: free as you go with 0, all sizes
}
