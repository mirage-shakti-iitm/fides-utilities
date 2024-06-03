// Format : <curr_cap:target_cap>
// input_filename: anything
// output_filename: cap_matrix.h

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstddef>   
#include <cstdlib>
#include <cstdint>

using namespace std;
  
// Function to set the kth bit of n 
uint64_t setBit(uint64_t n, uint64_t k) 
{ 
    // printf("k = %lu\n", 1lu<<k);
    // if we use 1 << (k-1), then (k-1) is casted to int leading to underflow. So constant, "1", is suffixed with lu(long unsigned)
    return (n | (1lu << (k - 1)));

} 
  
// Function to clear the kth bit of n 
int clearBit(uint64_t n, uint64_t k) 
{ 
    return (n & (~(1 << (k - 1)))); 
} 
  
// Function to toggle the kth bit of n 
int toggleBit(uint64_t n, uint64_t k) 
{ 
    return (n ^ (1 << (k - 1))); 
} 

int main(int argc, char *argv[]){
  string input_filename;
  string output_filename("cap_matrix.h");
  uint64_t cap_matrix[256*4] = {0};
	    
	if(argc >= 2){
    input_filename = argv[1];
  }
  else{
   	cout<<"cap_matrix_generator <input_filename>\nOutput filename: cap_matrix.h\n";
    return 0;
  }


  cout<<"Generating : "<< output_filename<<"\n";

  ifstream input_file;
  input_file.open(input_filename,ios::in);

  ofstream output_file;
  output_file.open(output_filename,ios::out);
   
  if(input_file.is_open() && output_file.is_open()){
    string str;
    while (getline(input_file, str)){
      size_t index = str.find(":");
      string curr_cap_string = str.substr(0,index);
      string target_cap_string = str.substr(index+1);

      int curr_cap = stoi(curr_cap_string);
      int target_cap = stoi(target_cap_string);

      int cap_matrix_row = -1;
      int cap_matrix_column_bit = -1;
      
      if(target_cap>=0 && target_cap<=63){
        cap_matrix_row = 0;
      }
      else if(target_cap>=64 && target_cap<=127){
        cap_matrix_row = 1;
      }
      else if(target_cap>=128 && target_cap<=191){
        cap_matrix_row = 2;
      }      
      else if(target_cap>=192 && target_cap<=255){
        cap_matrix_row = 3;
      }

      cap_matrix_column_bit = target_cap - cap_matrix_row*64 + 1;
      cap_matrix_row = curr_cap*4 + cap_matrix_row;

      printf("curr_cap = %d, target_cap = %d\n", curr_cap, target_cap);
      printf("cap_matrix_column_bit = %d, cap_matrix_row = %d\n", cap_matrix_column_bit, cap_matrix_row);
      printf("cap_matrix[cap_matrix_row] = %lu\n", cap_matrix[cap_matrix_row]);

      cap_matrix[cap_matrix_row] = setBit(cap_matrix[cap_matrix_row], cap_matrix_column_bit);

      printf("cap_matrix[cap_matrix_row] = %lu\n", cap_matrix[cap_matrix_row]);
      
    }

    output_file<<"#include <stdint.h>\n";
    // output_file<<"uint64_t\n__attribute__((section (\".capability-matrix-reserved\") ))\n __attribute__(( aligned (16) ))\n cap_matrix[256*4] = {\n";
    output_file<<"uint64_t\n__attribute__(( aligned (16) ))\n cap_matrix[256*4] = {\n";
    for(int i=0;i<256*4;i++){
      output_file<<cap_matrix[i];
      if(i==256*4-1){
        output_file<<" };\n";
      }
      else if((i+1)%4==0){
        output_file<<",\n";
      }
      else
        output_file<<", ";       
    }
    input_file.close();
    output_file.close();
  }
}

/*

*/