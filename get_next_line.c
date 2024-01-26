#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

char    *get_line(char **static_var)
{
    char    *tmp;
    char    *line;
    int     i;

    i = ft_strchr(*static_var, '\n') - *static_var;
    line = malloc(i + 2);
    if (!line)
    {
        if (*static_var)
            return (free(*static_var), NULL);
        return NULL;
    }
    i = 0;
    while ((*static_var)[i] != '\n')
    {
        line[i] = (*static_var)[i];
        i++;
    }
    line[i] = '\n';
    line[i + 1] = '\0';
    tmp = *static_var;
    i = ft_strchr(*static_var, '\n') - *static_var;
    *static_var = ft_substr(*static_var, i + 1, ft_strlen(*static_var) - i + 1);
    return(free(tmp) , line);
}
int     read_function(int fd, char **static_var)
{
    char *buffer;
    char *tmp;
    ssize_t buffersize;

    buffer = malloc(BUFFER_SIZE + 1);
    if (!buffer)
        return(free(*static_var), 0);
    buffersize = read(fd, buffer, BUFFER_SIZE);
    buffer[buffersize] = '\0';
    tmp = *static_var;
    *static_var = ft_strjoin(*static_var, buffer);
    free(tmp);
    free(buffer);
    return (buffersize);
}
char    *get_next_line(int fd)
{
    static char *static_var;
    char *buffer;
    char *tmp;
    int count;

    count = 0;
    buffer = NULL;
    if (fd < 0 ||  BUFFER_SIZE <= 0 || fd >= OPEN_MAX || read(fd, buffer, 0) < 0)
    {
        if (static_var)
            return(free(static_var), static_var = NULL);
        return NULL;
    }
    if (static_var && ft_strchr(static_var, '\n'))
        return (get_line(&static_var));
    while(read_function(fd, &static_var) && !ft_strchr(static_var, '\n'))
        count++;
    if (static_var && ft_strchr(static_var, '\n'))
        return(get_line(&static_var));
    if (static_var && *static_var)
        return (tmp = ft_strjoin(static_var, ""), free(static_var), static_var = NULL, tmp);
    tmp = static_var;
    static_var = NULL;
    return (free(tmp), static_var);
}

// char *read_line(char *str, int fd)
// {
//     char *buff;
//     int read_b = 1;
//     char *tmp;
//     buff = malloc(BUFFER_SIZE + 1);
//     if (!buff)
//         return (NULL);
//     while (read_b && check_for_newline(str))
//     {
//         read_b = read(fd, buff, BUFFER_SIZE);
//         if (read_b < 0)
//             return (free(str), free(buff), NULL);
//         if (read_b == 0)
//             return (free(buff), str);
//         buff[read_b] = '\0';
//         tmp = str;
//         str = ft_strjoin(tmp, buff);
//         free(tmp);
//     }
//     free(buff);
   
//     buff = NULL;
//     return str;
// }

// char *get_line(char *str)
// {
//     int i = 0;
//     while (str[i] && str[i] != '\n')
//         i++;
//     return (ft_substr(str, 0, i + 1));
// }

// char *restore_line(char *str)
// {
//     int i = 0;
//     char *tmp;
//     while (str[i] && str[i] != '\n')
//         i++;
//     if (!str[i])
//         return (free(str), NULL);
//     return ( tmp = ft_substr(str, i + 1, ft_strlen(str) - i + 1), free(str), tmp);
// }
// // int read_test(int fd)
// // {
// //     char *buffer;
// //     ssize_t bytesread = read(fd, buffer, BUFFER_SIZE);
// //     if (bytesread == 0)
// //         return 1;
// //     return 0;
// // }

// char *get_next_line(int fd)
// {
//     char *line;
//     static char *str;
//     if (fd < 0 || read(fd, str, 0) < 0)
//         return (NULL);
//     if (!str)
//         str = strdup("");
//     str = read_line(str, fd);
//     if (!str)
//         return (free(str), NULL);
//     if (!check_for_newline(str))
//     {
//         line = get_line(str);
//         str = restore_line(str);
//         return line;
//     }
//     if (str && *str && check_for_newline(str))
//     {
//         line = ft_strdup(str);
//         free(str);
//         str = NULL;
//         return(line);
//     }
//     return (NULL);
// }

// void l()
// {
// 	system("leaks a.out");
// }

// int main()
// {
//   atexit(l);
//     int fd;
//     fd = open("file.txt",O_RDONLY, 0700);
//     char *line = get_next_line(fd);
//     while(line)
//     {
//         printf("%s", line);
//         free(line);
//         line = get_next_line(fd);
//     }
//     //  line = get_next_line(3);
//     //  printf("%s",line);
// }
