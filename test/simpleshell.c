#include "main.h"
#include "holberton.h"

/**
 *main - super simple shell
 *that can run commands with their full path, without any argument.
 *@argc: number of command line arguments
 *@argv: array of command line arguments
 *Return: Always 0
 */
int main(int argc, char **argv)
{
int i;
int w;
int j;
char *lineptr;
char **args;
arg_list *head;
if (argc != 1)
{
write(STDERR_FILENO, "usage: ./hsh\n", 13);
exit(97);
}
for (i = 0; ; i++)
{
lineptr = doinitials(lineptr);
if (checksignal(lineptr) == 0 || *lineptr == '\n')
{
free(lineptr);
continue;
}
head = linktoken(lineptr, " \n");
args = linktolist(head);
j = 0;
if (fork() == 0)
{
if (execve(args[0], args, NULL) == -1)
{
while(args[j] != NULL)
{
free(args[j]);
j++;
}
perror(argv[0]);
exit(99);
}
}
else
{
while(args[j] != NULL)
{
free(args[j]);
j++;
}
wait(&w);
continue;
}
}
return (0);
}

/**
 *linktoken - links the strings got from strtok
 *using a singly linked list
 *@str: initial string
 *@del: delimeter
 *Return: pointer to the head of the list
 */
arg_list *linktoken(char *str, char *del)
{
int j;
char *token;
arg_list *head;
arg_list *el;
head = NULL;
el = NULL;
for (j = 0; ; j++, str = NULL)
{
token = strtok(str, del);
if (token == NULL)
break;
el = malloc(sizeof(*el) * 1);
el->token = token;
if (j == 0)
{
el->next = NULL;
head = el;
}
else
{
el->next = head;
head = el;
}
}
return (head);
}

/**
 *linktolist - stores the token elements of
 *a singly linked list in an array of char*
 *with a null pointer as the last element of the array
 *@head: pointer to head of linked list
 *Return: array of char * containing values of
 *elements of the linked list
 */
char **linktolist(arg_list *head)
{
int i;
arg_list *tmp;
char **buf;
tmp = head;
for (i = 0; tmp != NULL; i++, tmp = tmp->next)
continue;
buf = malloc(sizeof(char *) * (i + 1));
if (buf == NULL)
exit(98);
tmp = head;
buf[i] = NULL; 
for (i = i - 1; i >= 0; i--, tmp = tmp->next)
buf[i] = strdup(tmp->token);
return (buf);
}

/**
 *doinitials - do the initial sequence of things
 *for the loop in question. This function is only here
 *to keep in line with betty 40 line code requirement
 *Return: void
 */
char *doinitials(char *lineptr)
{
size_t n;
n = 1;
lineptr = malloc(sizeof(*lineptr) * n);
if (isatty(STDIN_FILENO))
prompt();
n = getline(&lineptr, &n, stdin);
if (n == (size_t)-1)
{
free(lineptr);
exit(0);
}
return (lineptr);
}

/**
 *checksignal - exits the shell
 *@str: command
 *Return: 0 on success
 */
int checksignal(char *str)
{
if (str[0] == 'e' && str[1] == 'n' && str[2] == 'v')
{
print_env();
return (0);
}
else if (str[0] == 'e' && str[1] == 'x' && str[2] == 'i'
&& str[3] == 't')
{
free(str);
exit(99);
}
return (-1);
}
