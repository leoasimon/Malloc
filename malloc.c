#include "malloc.h"
t_manager	*manager = NULL;

t_stock		*get_linked(t_stock *curr, size_t chunk_size)
{
	if (!curr)
		return init_stock(chunk_size);
	if (curr->free_bits < chunk_size + MALLOC_STRUCT_SIZE)
		curr->next = get_linked(curr->next, chunk_size);
	return curr;
}

t_malloc	*add_large_node(t_malloc *curr, size_t req_size)
{
	if (!curr)
		return init_large_mmap(req_size);
	curr->next = add_large_node(curr->next, req_size);
	return curr;
}

void		*retrieve_large_tail(t_malloc *curr)
{
	if (!curr->next)
		return curr->ret_ptr;
	return retrieve_large_tail(curr->next);
}

t_malloc	*get_updated_head(t_malloc *curr, size_t req_size, void *pot_addr)
{
	if (!curr)
		return (init_malloc(pot_addr, req_size));
	curr->next = get_updated_head(curr->next, req_size, curr->ret_ptr + req_size);
	return (curr);
}

void	*get_ret_ptr(t_malloc *curr)
{
	if (curr->next)
		return get_ret_ptr(curr->next);
	return curr->ret_ptr;
}

//At this point, our stock has some avalaible space
void	*retrieve_chunk(t_stock *stock, size_t req_size)
{
	//dummy malloc, push new malloc to the end of the heap
	stock->head = get_updated_head(stock->head, req_size, (void *)stock + STOCK_STRUCT_SIZE);
	stock->free_bits -= req_size + MALLOC_STRUCT_SIZE;
	return get_ret_ptr(stock->head);
}

//At this point an available m_mmap should exist, no mmap call would be necessary
t_stock	*retrieve_available_mmap(t_stock *curr, size_t req_size)
{
	if (curr->free_bits >= req_size + MALLOC_STRUCT_SIZE) return curr;
	return retrieve_available_mmap(curr->next, req_size);
}

void	*malloc(size_t	req_size)
{
	static int		debug_count = 0;

	debug_count++;
	//Check if the base manager exists
	if (manager == NULL)
		manager = init_manager();
	// Check size_t to know if we deal with SMALL, SMALL or LARGE, 
	//...go for a nice function pointer array ?...
	if (req_size <= TINY)
	{
		manager->tiny = get_linked(manager->tiny, TINY);
		return (retrieve_chunk(retrieve_available_mmap(manager->tiny, req_size), req_size));
	}
	if (req_size <= SMALL)
	{
		manager->small = get_linked(manager->small, SMALL);
		return (retrieve_chunk(retrieve_available_mmap(manager->small, req_size), req_size));
	}
	if (req_size > SMALL)
	{
		manager->large = add_large_node(manager->large, req_size);// check if we already have list of large mmaps
		// attach address of large to list of larges
		// return head of list
		return (retrieve_large_tail(manager->large));
	}
	return NULL;
}