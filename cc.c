#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

char    *get(char **op)
{
    char *line;
    char *tmp;
    int i;
    int j = ft_strlen(*op);

    i = ft_strchr(*op, '\n') - *op;
    line = malloc(i + 2);
    if (!line)
    {
        if (*op)
            return (free(op), NULL);
        return NULL;
    }
    i = 0;
    while ((*op)[i] != '\n')
    {
        line[i] = (*op)[i];
        i++;
    }
    line[i] = '\n';
    line[i + 1] = '\0';
    tmp = *op;
    i = ft_strchr(*op, '\n') - *op;
    *op = ft_substr(*op, i + 1, j - i + 1);
    free(tmp);
    return (line);
}
char    *geti_n(int fd)
{
    char *buffer;
    static char *op;
    ssize_t read1;
    char *tmp;

    if ( op && ft_strchr(op, '\n'))
        return(get(&op));
    buffer = malloc(BUFFER_SIZE + 1);
    if (!buffer)
        return(free(op), NULL);
    read1 = read(fd, buffer, BUFFER_SIZE);
    tmp = op;
    op = ft_strjoin(buffer, "");
    free(tmp);
    free(buffer);
    if (op && ft_strchr(op, '\n'))
        return(get(&op));
    if (op && *op)
        return (tmp = ft_strjoin(op, ""), free(op), op = NULL, tmp);
    tmp = op;
    op = NULL;
    return (free(tmp), op);
}
void l()
{
	system("leaks a.out");
}
int main()
{
    int fd;
    fd = open("file.txt", O_CREAT | O_RDONLY, 0700);
    char *line = geti_n(fd);
    while(line)
    {
        printf("%s", line);
        free(line);
        line = geti_n(fd);
    }
    //  line = get_next_line(3);
    //  printf("%s",line);
  atexit(l);
}