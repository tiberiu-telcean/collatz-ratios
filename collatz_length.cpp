#include <cstdio>
#include <cmath>
#include <vector>
#include <unistd.h>
#include <cstdint>

int64_t last_to_check = 10000;
std::vector<int64_t> numbers_checked;
std::vector<double> ratios;
std::vector<int64_t> list_of_lengths;
std::vector<int64_t> lowest_ratios;

void collatz(int64_t input){
    int64_t lenght = 0;
    int64_t number = input;
    while(number != 1){
	if(number%2 == 0){
            number = number/2;
	    lenght++;
	}else{
            number = 3 * number + 1;
	    lenght++;
	}
    }
    list_of_lengths.push_back(lenght);
    ratios.push_back(log2(input)/lenght);
    numbers_checked.push_back(input);
}

int main(int argc, char** argv){
    double current_lowest_ratio = 1;
    if(argc>1){
	last_to_check=atoi(argv[1]);
    }
    for(int64_t i=2; i<(int)last_to_check; i++){
        collatz(i);
        if(ratios[i-2] < current_lowest_ratio){
            current_lowest_ratio = ratios[i-2];
    	    printf("%f: %d\n", current_lowest_ratio, numbers_checked[i-2]);
	    lowest_ratios.push_back(numbers_checked[i-2]);
	}
    }
    FILE* csv = fopen("collatz_lengths.csv", "w");
    for(int64_t i=0; i<numbers_checked.size(); i++){
	if(i){
	    fprintf(csv, ",%d", numbers_checked[i]);
	}else{
	    fprintf(csv, "%d", numbers_checked[i]);
	}
    }
    fprintf(csv, "\n");
    for(int64_t i=0; i<list_of_lengths.size(); i++){
	if(i){
	    fprintf(csv, ",%d", list_of_lengths[i]);
	}else{
	    fprintf(csv, "%d", list_of_lengths[i]);
	}
    }
    fprintf(csv, "\n");
    for(int64_t i=0; i<ratios.size(); i++){
	if(i){
	    fprintf(csv, ",%f", ratios[i]);
	}else{
	    fprintf(csv, "%f", ratios[i]);
	}
    }
    fprintf(csv, "\n");
}
