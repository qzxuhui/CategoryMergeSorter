#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <list>
#include <sstream>
#include <algorithm>
#include <map>

class Item
{
public:
    explicit Item(std::string &name_, std::string category_name)
        : name(name_)
    {
        category = map_category_name_to_index[category_name];
    }

    void print()
    {
        std::cout << std::setw(10) << name;
        std::cout << std::setw(10) << category;
        std::cout << "     " << map_category_index_to_name[category];
        std::cout << std::endl;
    }

    void printResults(std::ofstream &fout)
    {
        fout << std::setw(10) << name;
        fout << "     " << map_category_index_to_name[category];
        fout << std::endl;
    }

    int getCategoryIndex()
    {
        return category;
    }

    static void registerCategory(std::string category_name)
    {
        auto pos = map_category_name_to_index.find(category_name);
        bool flag = (pos == map_category_name_to_index.end()) ? false : true;
        if (flag == false)
        {
            max_category_index++;
            map_category_name_to_index.insert(
                std::make_pair(category_name, max_category_index));

            map_category_index_to_name.insert(
                std::make_pair(max_category_index, category_name));
        }
    }

    static int getNumCategory()
    {
        return max_category_index + 1;
    }

private:
    std::string name;
    int category;

    static int max_category_index;
    static std::map<std::string, int> map_category_name_to_index;
    static std::map<int, std::string> map_category_index_to_name;
};

int Item::max_category_index = -1;
std::map<std::string, int> Item::map_category_name_to_index;
std::map<int, std::string> Item::map_category_index_to_name;

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

std::string parseFileContent(std::ifstream &fin)
{
    std::stringstream sstr;
    sstr << fin.rdbuf();
    return sstr.str();
}

std::list<Item> getSortItem(std::list<Item> &origin_list)
{
    int num_data = origin_list.size();
    int num_category = Item::getNumCategory();
    std::list<Item>::iterator origin_it;
    std::vector<std::list<Item>> item_list_vector(num_category);
    for (origin_it = origin_list.begin(); origin_it != origin_list.end(); origin_it++)
    {
        Item item = (*origin_it);
        int category_index = item.getCategoryIndex();
        item_list_vector[category_index].push_back(item);
    }

    std::vector<double> expect_precent_in_each_category(num_category);
    std::vector<int> num_item_in_each_category(num_category);
    for (int i = 0; i < num_category; i++)
    {
        num_item_in_each_category[i] = item_list_vector[i].size();
    }

    for (int i = 0; i < num_category; i++)
    {
        expect_precent_in_each_category[i] = num_item_in_each_category[i] * 1.0 / num_data;
    }

    std::vector<std::list<Item>::iterator> iterator_vector(num_category);
    for (int i = 0; i < num_category; i++)
    {
        iterator_vector[i] = item_list_vector[i].begin();
    }

    std::list<Item> sorted_items;
    std::vector<int> count(num_category);
    for (int i = 0; i < num_category; i++)
    {
        count[i] = 0;
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
            distance_precent[i] = now_percent[i] - expect_precent_in_each_category[i];
        }

        std::vector<int> index_array = sort_indexes(distance_precent);

        // choose item add into sort list
        for (int i = 0; i < num_category; i++)
        {
            int min_index = index_array[i];
            if (count[min_index] == num_item_in_each_category[min_index])
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
    return sorted_items;
}

std::list<Item> parseItemListFromFile(std::string input_filename)
{
    std::ifstream fin;
    fin.open(input_filename);
    std::string file_content = parseFileContent(fin);
    std::istringstream file_content_stream(file_content);
    fin.close();

    // parse file content
    std::list<Item> origin_list;
    std::string name;
    std::string category_name;
    while (file_content_stream >> name)
    {
        file_content_stream >> category_name;
        Item::registerCategory(category_name);
        Item item(name, category_name);
        origin_list.push_back(item);
    }
    return origin_list;
}

void exportResult(std::string output_filename, std::list<Item> &sorted_items)
{
    std::cout << "sort result:" << std::endl;
    std::ofstream fout;
    fout.open(output_filename);
    std::list<Item>::iterator sort_it;
    for (sort_it = sorted_items.begin(); sort_it != sorted_items.end(); sort_it++)
    {
        (*sort_it).print();
        (*sort_it).printResults(fout);
    }
    fout.close();
}

int main()
{
    std::string input_filename = "input.txt";
    std::string output_filename = "output.txt";
    std::list<Item> origin_list = parseItemListFromFile(input_filename);
    std::list<Item> sorted_items = getSortItem(origin_list);
    exportResult(output_filename, sorted_items);
    return 0;
}