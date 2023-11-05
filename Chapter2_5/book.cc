#include <iostream>
#include "Sales_data.h"

int main(int argc, char const *argv[]){
    Sales_data data1, data2;
    double price = 0;
    //input data1
    std::cout << "input data1, formate:ISBN units_sold price" << std::endl;
    std::cin >> data1.bookNo >> data1.units_sold >> price;
    data1.revenue = data1.units_sold * price;
    //input data2
    std::cout << "input data2, formate:ISBN units_sold price" << std::endl;
    std::cin >> data2.bookNo >> data2.units_sold >> price;
    data2.revenue = data2.units_sold * price;
    //calculate average revenue and output
    std::cout << "output, formate:ISBN units_sold total_revenue average revenue" << std::endl;
    if(data1.bookNo == data2.bookNo){
        unsigned totalCnt = data1.units_sold + data2.units_sold;
        double totalRevenue = data1.revenue + data2.revenue;
        std::cout << data1.bookNo << " " << totalCnt << " " << totalRevenue << " ";
        if(totalCnt != 0){
            std::cout << totalRevenue/totalCnt << std::endl;
        } 
        else{
            std::cout << "no sales" << std::endl;
        }
        return 0;
    } 
    else{
        std::cerr << "Data must refer to the same ISBN" << std::endl;
        return -1;
    }
}
