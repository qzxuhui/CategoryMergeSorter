#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <list>
#include <algorithm>
#include <map>

class Item
{
public:
    explicit Item(std::string &name_, int category_)
        : name(name_), category(category_)
    {
    }
    void print()
    {
        std::cout << std::setw(10) << name;
        std::cout << std::setw(10) << category;
        std::cout << std::endl;
    }

    static void registerCategory(const std::string &item)
    {
    }

private:
    std::string name;
    int category;
    int num_category;
};

class Sorter
{
};

int getSum(std::vector<int> int_vector)
{
    int sum = 0;
    int size = int_vector.size();
    for (int i = 0; i < size; i++)
    {
        sum = sum + int_vector[i];
    }
    return sum;
}

template <typename T>
std::vector<int> sort_indexes(const std::vector<T> &v)
{
    // initialize original index locations
    std::vector<int> idx(v.size());
    for (int i = 0; i != idx.size(); ++i)
        idx[i] = i;

    // sort indexes based on comparing values in v
    std::sort(idx.begin(), idx.end(),
              [&v](int i1, int i2) { return v[i1] < v[i2]; });

    return idx;
}

int main()
{
    std::string input_filename = "input.txt";
    std::ifstream fin;
    fin.open(input_filename);
    int num_data;
    int num_category;
    fin >> num_data;
    fin >> num_category;
    std::cout << "num_data:" << num_data << std::endl;
    std::cout << "num_category:" << num_category << std::endl;
    std::vector<std::list<Item>> item_list_vector(num_category);
    for (int i = 0; i < num_data; i++)
    {
        std::string name;
        int category;
        fin >> name;
        fin >> category;
        Item item(name, category);
        item_list_vector[category].push_back(item);
    }
    fin.close();

    // print
    for (int i = 0; i < num_category; i++)
    {
        std::cout << "this is category " << i << std::endl;
        std::list<Item>::iterator it;
        for (it = item_list_vector[i].begin(); it != item_list_vector[i].end(); it++)
        {
            (*it).print();
        }
    }

    std::vector<double> precent_array(num_category);
    std::vector<int> sum_array(num_category);
    for (int i = 0; i < num_category; i++)
    {
        sum_array[i] = item_list_vector[i].size();
    }

    for (int i = 0; i < num_category; i++)
    {
        precent_array[i] = sum_array[i] * 1.0 / num_data;
    }

    std::vector<std::list<Item>::iterator> iterator_vector(num_category);
    for (int i = 0; i < num_category; i++)
    {
        iterator_vector[i] = item_list_vector[i].begin();
    }

    // first add each first item
    std::list<Item> sorted_items;
    for (int i = 0; i < num_category; i++)
    {
        std::list<Item>::iterator &it = iterator_vector[i];
        Item item = *it;
        sorted_items.push_back(item);
        it++;
    }

    // then add other item into sorted_items by rule
    std::vector<int> count(num_category);
    for (int i = 0; i < num_category; i++)
    {
        count[i] = 1;
    }

    while (1)
    {
        // break if all inserted
        if (getSum(count) == num_data)
        {
            break;
        }

        // find next insert
        std::vector<double> now_percent(num_category);
        for (int i = 0; i < num_category; i++)
        {
            now_percent[i] = count[i] * 1.0 / getSum(count);
        }

        std::vector<double> distance_precent(num_category);
        for (int i = 0; i < num_category; i++)
        {
            distance_precent[i] = now_percent[i] - precent_array[i];
        }

        std::vector<int> index_array = sort_indexes(distance_precent);

        for (int i = 0; i < num_category; i++)
        {
            int min_index = index_array[i];
            if (count[min_index] == sum_array[min_index])
            {
                continue;
            }
            else
            {
                std::list<Item>::iterator &it = iterator_vector[min_index];
                Item item = *it;
                sorted_items.push_back(item);
                it++;
                count[min_index] = count[min_index] + 1;
                break;
            }
        }
    }

    // --------------------------------------------------------
    std::string output_filename = "output.txt";
    std::cout << "sort result:" << std::endl;
    std::list<Item>::iterator sort_it;
    for (sort_it = sorted_items.begin(); sort_it != sorted_items.end(); sort_it++)
    {
        (*sort_it).print();
    }
    return 0;
}