#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct tree {
    int info;
    int number;
    struct tree *next_left;
    struct tree *next_right;
} tree;
void enter_number(char *str,int *n){
    while(1){
        gets(str);
        *n = atoi(str);
        if(!*n) { puts("enter correct number");}
        else {break;}
    }
}
tree *create_tree(tree * first_elem)
{
    char *str;
    str = (char *) calloc(10, sizeof(char));
    if (first_elem) {
        puts("Tree already created");
        return (first_elem);
    }
    if (!(first_elem = (tree *) calloc(1, sizeof(tree)))) {
        puts("No free memory");
        return (NULL);
    }
    puts("Enter info in first element");
    enter_number(str,&first_elem -> info);
    first_elem->number = 1;
    first_elem->next_left = NULL;
    first_elem->next_right = NULL;
    return (first_elem);
}

void add_elem(tree * first_elem)
{
    tree *current1, *current2;
    char *str;
    int current_number;
    int out_cycle;
    if (!first_elem) {
        puts("No tree");
        return;
    }

    do {
        puts("Enter info (0 - out)");
        str = (char *) calloc(10, sizeof(char));
        while(1){
			gets(str);
			if (!strcmp(str, "0")){
				return;}
			current_number = atoi(str);
			if(!current_number) { puts("enter correct number");}
			else {break;}
		}
        current1 = first_elem;
        out_cycle = 0;

        do {
            if (current_number == current1->info) {
                current1->number++;
                out_cycle = 1;
            }

            else {
                if (current_number < current1->info) {
                    if (current1->next_left != NULL) {
                        current1 = current1->next_left;
                    }

                    else {
                        out_cycle = 1;
                    }
                }

                else {
                    if (current1->next_right != NULL) {
                        current1 = current1->next_right;
                    }

                    else {
                        out_cycle = 1;
                    }
                }
            }
        } while (out_cycle == 0);
        if (current_number != current1->info) {
            if ((current2 = (tree *) malloc(sizeof(tree))) == NULL) {
                puts("No free memory");
                return;
            }
            if (current_number < current1->info) {
                current1->next_left = current2;
            }

            else {
                current1->next_right = current2;
            }
            current2->info = current_number;
            current2->number = 1;
            current2->next_right = NULL;
            current2->next_left = NULL;
        }
        free(str);
    } while (1);
}

int calculate_number_of_nod(tree * current, int n)
{
    static int level = -1, number;
    if (current->next_left == NULL && current->next_right == NULL) {
        return 0;
    }
    level += 1;
    if (level == n) {
        number += 1;
    }
    calculate_number_of_nod(current->next_left, n);
    calculate_number_of_nod(current->next_right, n);
    level -= 1;
    if (level == -1) {
        return number;
    }
    
    else {
        return 0;
    }
}

int main(int argc, char **argv)
{
    tree *first_elem;
    char *str;
    int n;
    str = (char *) calloc(10, sizeof(char));
    first_elem = NULL;
    if (argc == 2) {
        if ((strcmp(argv[1], "-h")) == 0) {
            puts("Instructions for use:");
            puts("1.Launch file:");
            puts(" gcc-Wall-Wextra-o lab4.exe lab4.c");
            puts(" ./lab4.exe");
            puts("2.In the screen prompts you to enter the first element of a tree (root).");
            puts("    Enter it. Next, you are prompted to enter ocheredenoy the tree.");
            puts("    Enter it. Proposals will be displayed as long as you do not enter '0'.");
            puts("    Next, you are prompted to enter the level for which you want to calculate the number of nodes.");
            puts("    Enter it.");
            puts("3.The displayed the number of nodes at a given level or '0' if the current level");
            puts("    does not exist or at no nodes.");
            return 0;
        }
    }
    first_elem = create_tree(first_elem);
    add_elem(first_elem);
    puts("Enter level");
    enter_number(str,&n);
    printf("number of nod on level %d: %d", n,
           calculate_number_of_nod(first_elem, n));
    return 0;
}
