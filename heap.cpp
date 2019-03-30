/*
This program realise HEAP 
heap structure:
    KEY: string[5]
    DATA: array of int

Left child < Parent < Right child
03.2019 P.Sh.
*/
#include <iostream>
#include <stdlib.h>

class heap_node
{
private:
    char *key;
    int *arr;
    int amount;

    heap_node *l_child = NULL;     // less
    heap_node *r_child = NULL;     // more 

public:
    heap_node(char *key_str, int *arr_point, int amount_elem)
    {
        key = key_str;
        arr = arr_point;
        amount = amount_elem;
    }

    heap_node(char* key_str)
    {
        key = key_str;
        arr = NULL;
        amount = 0;        
    }

    ~heap_node()
    {
        // delete data in node
		if (arr != NULL)
		{
			delete[] arr;
			arr = NULL;
		}
		delete[] key;
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

	void remove_under(heap_node *pointer)   // recursive delete last item 
	{
		if (pointer != NULL)
		{
			while (1)
			{
				if ((*pointer).get_l_child() != NULL)
				{
					remove_under((*pointer).get_l_child());
					(*pointer).set_l_child(0);
				}
				else
				{
					if ((*pointer).get_r_child() != NULL)
					{
						remove_under((*pointer).get_r_child());
						(*pointer).set_r_child(NULL);
					}
					else
					{
						delete pointer;         //remove last item
						return;
					}
				}
			}
		}
		return;
	}
    
    bool compare(char* a, char* b)
    {
        if (*a < *b)
        {return true;}
        else
        {return false;}
    }

public:
    HEAP()
    {
        heap_node *root = NULL;
    }

    ~HEAP()
    {
        //delete all heap_node
        remove_under(root);
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
       while (1)        // find place for current item
        {
            if( compare( (*tmp).get_key() , (*Pn).get_key()))
            {
                if ((*tmp).get_l_child() == NULL)       // insert to left
                {
                    (*tmp).set_l_child(Pn);
                    return;
                }
                else
                {
                    tmp = (*tmp).get_l_child();         // choise next item
                }
            }
            else
            {
                if ((*tmp).get_r_child() == NULL)       // insert to right
                {
                    (*tmp).set_r_child(Pn);
                    return;
                }
                else
                {
                    tmp = (*tmp).get_r_child();         // choise next item 
                }
            }
        }
    } 

    void clear(void)
    {
        remove_under(root);
        root = NULL;
    };

    int* find(char *key, int &amount)
    {
        heap_node *tmp = root;
        while(1)
        {
            if (tmp == NULL)    // if last item, return 0
            {
                amount = 0;
                return NULL;
            }
            else                
            {
                if (  *(*tmp).get_key() == *key )     // item was found
                {
                    return (*tmp).get_array(amount);
                }
                else
                {
                    if( compare( (*tmp).get_key() , key))   // choice next item
                    {
                        tmp = (*tmp).get_l_child();
                    }
                    else
                    {
                        tmp = (*tmp).get_r_child();
                    }
                }
            }
        }
    }

    char* get_min(int *&array, int &amount)
    {
        heap_node *tmp = root;
        while(1)
        {
            if ((*tmp).get_l_child() == NULL)
            {
                array = (*tmp).get_array(amount);
                return (*tmp).get_key();
            }
            else
            {
                tmp = (*tmp).get_l_child();
            }
            
        }
    }

    char* get_max(int *&array, int &amount)
    {
        heap_node *tmp = root;
        while(1)
        {
            if ((*tmp).get_r_child() == NULL)
            {
                array = (*tmp).get_array(amount);
                return (*tmp).get_key();
            }
            else
            {
                tmp = (*tmp).get_r_child();
            }
            
        }
    }

    int remove_elem(char *key)
    {
        heap_node *tmp = root;
        heap_node *parent = root;
        int state = 2;
        while(tmp != NULL)                      // if tmp is last item -> exit
        {
            if (  *(*tmp).get_key() == *key )   // find element 
            {
                if ((*tmp).get_l_child() != NULL)   // item was found
                {
                    switch (state)
                    {
                        case 0:
                            (*parent).set_l_child((*tmp).get_l_child());
                            break;
                    
                        case 1:
                            (*parent).set_r_child((*tmp).get_l_child());
                            break;
                    
                        case 2:
                            root = (*tmp).get_l_child();
                            break;
                    }
                    if ((*tmp).get_r_child() != NULL)
                    {
                        heap_node *tmp_2 = (*tmp).get_l_child();
                        while((*tmp).get_r_child() != NULL)        // find largest key
                        {
                            tmp_2 = (*tmp_2).get_r_child();
                        }
                        (*tmp_2).set_r_child((*tmp).get_r_child()); // link right subtree to largest in left subtree
                    } 
                    delete tmp;
                    return 0;
                }
                else
                {
                    if ((*tmp).get_r_child() != NULL)
                    {
                        switch (state)      // link right subtree to perent of deleted item
                        {
                            case 0:
                                (*parent).set_l_child((*tmp).get_r_child());
                                break;

                            case 1:
                                (*parent).set_r_child((*tmp).get_r_child());
                                break;

                            case 2:
                                root = (*tmp).get_r_child();
                                break;
                        }
                    }
                    else
                    {
                        switch (state)      // removoble item has no children
                        {
                            case 0:
                                (*parent).set_l_child(NULL);
                                break;

                            case 1:
                                (*parent).set_r_child(NULL);
                                break;

                            case 2:
                                root = (NULL);
                                break;
                        }
                    }
                    delete tmp;
                    return 0;
                }
                
            }
            else        // get next element
            {
                parent = tmp;
                if( compare( (*tmp).get_key() , key))   // choice next elem
                {
                    tmp = (*tmp).get_l_child();
                    state = 0;
                }
                else
                {
                    tmp = (*tmp).get_r_child();
                    state = 1;
                }
            }
        }   
        return 1;
    }
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
    static char *temp;
    temp = new char[5];
    for(int i = 0; i < 5; i++)
    {
        temp[i] = (rand() % 128) + 1;
    }
    return temp;
}

int main()
{
    HEAP heap;
    int amount = 0;
    int *tmp_arr;
    char *tmp_ch;
    char *tmp_ch_2;            
    tmp_ch_2 = new char[5];

    for(int count = 0; count < 20; count++)      // random 30 items to heap
    {
        tmp_ch = random_char();
        tmp_arr = random_arr(amount);
        
        if (count == 6)         // remind key in 23 item
        {
            for (int i = 0;i<5;i++) // copy key
            {
                tmp_ch_2[i] = tmp_ch[i];
            }
        }
        heap.add(tmp_ch,tmp_arr, amount);
    };
    
    std::cout<<std::endl<<" last item :" << std::endl;
    tmp_arr = heap.find(tmp_ch,amount);         // print last added item
    for (int i =0; i < amount;i++)
    {
        std::cout << tmp_arr[i] << "  ";
    }
    std::cout<<std::endl;
    std::cout<<std::endl<<" item 6(1):" << std::endl;
    
    tmp_arr = heap.find(tmp_ch_2,amount);     // find 6 item
    for (int i =0; i < amount;i++)              // print array 
    {
        std::cout << tmp_arr[i] << "  ";
    }
    std::cout<<std::endl;
    
    heap.remove_elem(tmp_ch_2);                 // remove 6 item ( comment this line to check )
        
    std::cout<<std::endl<<" item 6(2):" << std::endl;
    tmp_arr = heap.find(tmp_ch_2,amount);     // find 6 item
    for (int i =0; i < amount;i++)              // print array 
    {
        std::cout << tmp_arr[i] << "  ";
    }
    std::cout<<std::endl;

    tmp_ch = heap.get_max(tmp_arr,amount);      // get max
    std::cout<<" max item: " << std::endl;
    std::cout << tmp_ch << std::endl;
    for (int i =0; i < amount;i++)              // print array 
    {
        std::cout << tmp_arr[i] << "  ";
    }
    heap.clear();
    return 0;
}