//main.c 文件 

void print(char *str);
extern char *global_var;

int main()
{
    print(global_var);
    return 0;
}