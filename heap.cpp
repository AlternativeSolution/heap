/*
This program realise HEAP 
max-heap structure:
    KEY: string[5]
    DATA: array of int

Left child ALWAYS less Right child
03.2019 P.Sh.
*/
#include <iostream>
#include <random>
#include <stdlib.h>


class heap_node
{
private:
    char key[];
    int *arr;
    int amount;

    heap_node *l_child = NULL;     // less
    heap_node *r_child = NULL;     // more 

public:
    heap_node(char *key_str, int *arr_point, int amount_elem)
    {
        *key = *key_str;
        arr = arr_point;
        amount = amount_elem;
    }

    heap_node(char key_str[])
    {
        *key = *key_str;
        arr = NULL;
        amount = 0;        
    }

    ~heap_node()
    {
        delete[] arr;
    }

     void set_r_child(heap_node* child)
    {
        r_child = child;
    };

    void set_l_child(heap_node* child)
    {
        l_child = child;
    };

    heap_node* get_r_child(void)
    {
        return r_child;
    };

    heap_node* get_l_child(void)
    {
        return l_child;
    };

    char* get_key()
    {
        return key;
    }

    int* get_array(int &amount_elem)
    {
        amount_elem = amount;
        return arr;
    }

};


class HEAP
{
private:
    heap_node *root = NULL;

    void remove(heap_node *pointer)
    {
        if (pointer != NULL)
        {
            if ((*pointer).get_l_child() != NULL)
            {
                remove((*pointer).get_l_child());
            }
            else
            {
                if ((*pointer).get_r_child() != NULL)
                {
                    remove((*pointer).get_r_child());
                }
                else
                {
                    delete pointer;
                }
                
            }
            
        }
        return;
    }

public:
    HEAP()
    {
        heap_node *root = NULL;
    }

    ~HEAP()
    {
        //delete all heap_node
        remove(root);
        delete root;
    }

    void add(char *key_str, int* arr_point, int amount_elem)
    {
        heap_node *tmp = root;
        heap_node *Pn = new heap_node(key_str, arr_point, amount_elem);
        (*Pn).set_l_child(NULL);
        (*Pn).set_r_child(NULL);
        if (tmp == NULL) 
        {
            root = Pn;
            return;
        }
        while (1)
        {
            if ( (*tmp).get_key() > (*Pn).get_key())
            {
                if ((*tmp).get_l_child() == NULL)
                {
                    (*tmp).set_l_child(Pn);
                    return;
                }
                else
                {
                    tmp = (*tmp).get_l_child();
                }
            }
            else
            {
                if ((*tmp).get_r_child() == NULL)
                {
                    (*tmp).set_r_child(Pn);
                    return;
                }
                else
                {
                    tmp = (*tmp).get_r_child();
                }
            }
            
        }
    }

    void clear(void)
    {
        remove(root);
        root = NULL;
    };
};

int* random_arr(int &amount)
{
    amount = rand() % 100;
    int *array;
    array = new int[amount];
    for(int i = 0; i < amount; i++)
    {
        array[i] = rand() % 10000;
    }
    return array;
}

char* random_char(void)
{
    static char temp[5];
    for(int i = 0; i < 5; i++)
    {
        temp[i] = rand() % 128;
    }
    return temp;
}

int main()
{
    HEAP heap;
    int amount = 0;
    for(int count = 0; count < 30; count++)
    {
        heap.add(random_char(),random_arr(amount), amount);
    };
    heap.clear();
}