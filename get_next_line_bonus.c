#include "get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>

char    *ft_get_line(char **Var)
{
    char    *tmp;
    char    *line;
    int     i;

    i = ft_strchr(*Var, '\n') - *Var;
    line = malloc(i + 2);
    if (!line)
    {
        if (*Var)
            return (free(*Var), NULL);
        return NULL;
    }
    i = 0;
    while ((*Var)[i] != '\n')
    {
        line[i] = (*Var)[i];
        i++;
    }
    line[i] = '\n';
    line[i + 1] = '\0';
    tmp = *Var;
    i = ft_strchr(*Var, '\n') - *Var;
    *Var = ft_substr(*Var, i + 1, ft_strlen(*Var) - i + 1);
    return (free(tmp) , line);
}
int     read_function(int fd, char **Var)
{
    char *buffer;
    char *tmp;
    ssize_t buffersize;

    buffersize = 1;
    buffer = malloc(BUFFER_SIZE + 1);
    if (!buffer)
        return 0;
    while (buffersize > 0  && !ft_strchr(Var[fd], '\n'))
    {
        buffersize = read(fd, buffer, BUFFER_SIZE);
        if (buffersize > 0)
        {
            buffer[buffersize] = '\0';
            tmp = *Var;
            *Var = ft_strjoin(*Var, buffer);
            free(tmp);
        }
    }
    free(buffer);
    return (buffersize);
}

char    *get_next_line(int fd)
{
    static char *Var[OPEN_MAX];
    char *buffer;
    char *tmp;

    buffer = NULL;
    if (fd < 0)
        return NULL;
    if (BUFFER_SIZE <= 0 || fd >= OPEN_MAX || read(fd, buffer, 0) < 0 )
    {
        if (Var[fd])
            return(free(Var[fd]), Var[fd] = NULL);
        return NULL;
    }
    if (Var[fd] && ft_strchr(Var[fd], '\n'))
        return (ft_get_line(&Var[fd]));
    if(!ft_strchr(Var[fd], '\n'))
        read_function(fd, &Var[fd]);
    if (Var[fd] && ft_strchr(Var[fd], '\n'))
        return(ft_get_line(&Var[fd]));
    if  (Var[fd] && *(Var[fd]))
        return (tmp = ft_strjoin(Var[fd], ""), free(Var[fd]), Var[fd] = NULL, tmp);
    tmp = Var[fd];
    Var[fd] = NULL;
    return (free(tmp), Var[fd]);
}
// // // // // void l()
// // // // // {
// // // // // 	system("leaks a.out");
// // // // // }
// int main()
// {
//     char c = 0; 
//     int fd = open("42_with_nl", O_CREAT | O_RDONLY, 0700);
//     read(fd, &c, 1); 
// if (BUFFER_SIZE == 42) {
// 		char c = 0; read(fd, &c, 1); check(c == '1'); ++iTest;
// 	    get_next_line(fd, NULL);}
// 	else {
// 		 /* 2 */ gnl(fd, "1");
// 		 /* 3 */ gnl(fd, NULL);})
//     // char *line= get_next_line(fd);
//     // while(line)
//     // {
//     //     // i++;
//     //     // if (i == 3)
//     //     //     close(3);
//     //     printf("%s", line);
//     //     free(line);
//     //     line = get_next_line(3);
//     // }
//     //  line = get_next_line(3);
//     //  printf("%s",line);
// //   atexit(l);
// }
