/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 08:56:36 by efarin            #+#    #+#             */
/*   Updated: 2021/04/28 08:56:39 by efarin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include <stdio.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_struct
{
	int		lenmax;
	int		hmap;
	int		Rx;
	int		Ry;
	int		i;
	int		F_R;
	int		F_G;
	int		F_B;
	int		C_R;
	int		C_G;
	int		C_B;
	char	position;
	int		xplayer;
	int		yplayer;
	char	*pathtoNO;
	char	*pathtoSO;
	char	*pathtoWE;
	char	*pathtoEA;
	char	*pathtoS;
	char	*args[8];
	char	**map;
}	t_struct;

t_list			*ft_lstnew(void *content);
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstclear(t_list **lst, void (*del)(void*));
int				ft_lstsize(t_list *lst);
t_list			*makelst(int fd, t_struct *mstruct);
int				getlenmax(t_list **alst);
char			**fromlsttotab(t_list **alst, t_struct *mstruct);
char			**fillthetabwithspaces(char **tab, t_struct *mstruct);
void			structinit(t_struct *mstruct);
int				checkthenorth(char **tab);
int				checkalltab(char **tab, t_struct *mstruct);
int				checkspaces(char **tab, int i, int j);
int				checkthemap(char **tab, t_struct *mstruct);
t_struct		*ismapvalid(char **arv);
int				ft_atoi(const char *nptr);
size_t			ft_cmpt(char const *s, char c);
char			*ft_free(char **tab, size_t i);
char			**ft_mem(char const *s, char c);
char			**ft_split(char const *s, char c);
char			*ft_substr(char const *s, unsigned int start, size_t len);
void			checkelemR(char *line, t_struct *mstruct);
char			*checktheid(char *line, char a, char b);
void			checkelemF(char *line, t_struct *mstruct);
void			checkelemC(char *line, t_struct *mstruct);
void			sky_color(char **elem, t_struct *mstruct);
void			floor_color(char **elem, t_struct *mstruct);
int				checktheorder(char **tab, t_struct *mstruct);
char			*ft_strcpy(char *dst, const char *src, size_t dstsize);
void			ft_bzero(void *s, size_t n);
size_t			ft_strlen(const char *s);
size_t			ft_check(char c, char const *set);
char			*ft_putzero(size_t i);
char			*ft_strtrim(char const *s1, char const *set);
int				shouldiskip(char *line, t_struct *mstruct);
char			*ft_strdup(const char *s);
int				checkplayerposition(char **tab, t_struct *mstruct);
char			*fromdoubletosimple(char **tab, t_struct *mstruct);
int				ft_strcmp(char *s1, char *s2);
void			maketab(t_struct *mstruct);
int				whatstheid(char *line, t_struct *mstruct);
int				firstpartmap(char *line, t_struct *mstruct, int y);
int				wrfree(void *ptr);
void			*wrmalloc(unsigned long size);
void			wrdestroy(void);
void			ft_lstadd_back(t_list **alst, t_list *new);
t_list			*error_makelst(char **line, t_list *thelist);

#endif
