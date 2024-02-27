void	*add_redirect_out(void *redirect, char *content, int type)
{

	if (!redirect)
		return (new_redirect_out(content, type));
	new = NULL;
	new = new_redirect_out(content, type);
	redirect->next = new;
	return (new);
}