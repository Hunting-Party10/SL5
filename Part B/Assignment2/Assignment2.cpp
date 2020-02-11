#include <iostream>
#include <vector>
class OptimalStorage {
private:
  std::vector<int> tapes; //tape Sizes
  std::vector<int> progs; //Prog Sizes
  typedef struct optimal{
    std::vector<int> tape_contents;
  }optimal;
  std::vector<optimal> storage;
public:
  OptimalStorage (int num_tapes,int *tape_sizes,int num_progs,int *progs);
  void Optimize();
  void Mergesort();
  void Sort(std::vector<int> &,int,int);
  void Combine(std::vector<int> &,int,int,int,int);
  void displayOptimal();
};

void OptimalStorage::Mergesort(){
  std::vector<int> array;
  array = progs;
  progs.clear();
  Sort(array,0,array.size()-1);
  progs = array;
}

void OptimalStorage::Sort(std::vector<int> &array,int start,int end) {
  if (start == end)
    return;
  int mid = (start + end)/2;
  Sort(array,start,mid);
  Sort(array,mid+1,end);
  Combine(array,start,mid,mid+1,end);
}

void OptimalStorage::Combine(std::vector<int> &array,int start1,int end1,int start2,int end2){
  std::vector<int> temp;
  int i=start1,j=start2;
  while(i<=end1 && j<=end2)
  {
    if (array[i] > array[j])
      temp.push_back(array[j++]);
    else
      temp.push_back(array[i++]);
  }
  while(i <= end1)
    temp.push_back(array[i++]);
  while(j <= end2)
    temp.push_back(array[j++]);
  array.erase(array.begin()+start1,array.begin()+end2 +1);
  for (size_t i = 0; i < temp.size(); i++)
    array.insert(array.begin()+start1+i,temp[i]);
}

OptimalStorage::OptimalStorage(int num_tapes,int *tape_sizes,int num_progs,int *prog){
  optimal O;
  for (size_t i = 0; i < num_tapes; i++){
    tapes.push_back(tape_sizes[i]);
    storage.push_back(O);
  }
  for (size_t i = 0; i < num_progs; i++)
    progs.push_back(prog[i]);

    std::cout << "Initial Tape status" << '\n';
    for (size_t i = 0; i < tapes.size(); i++) {
      std::cout << tapes[i] << '-';
    }
}

void OptimalStorage::Optimize() {
  Mergesort();
  int j = 0;
  int count=0;
  for (size_t i = 0; i < progs.size() -1; i++) {
    if(j == tapes.size()){
      if(j == count)
        break;
      j = 0;
    }
    if(tapes[j] == 0)
        count++;
    if(progs[i] <= tapes[j]){
      storage[j].tape_contents.push_back(progs[i]);
      tapes[j] -= progs[i];
      count= 0;
    }
    j++;
  }
  if (progs.size() != 0)
    std::cout << "Number of programs exceeds disk space" << '\n';

}

void OptimalStorage::displayOptimal()
{
  std::vector<int>:: iterator tape = tapes.begin();
  for (std::vector<optimal>:: iterator i = storage.begin(); i != storage.end(); i++) {
    optimal o = *i;
    int sum = 0;
    std::cout << "For tape of size:"<<*tape<< " Storage is\n";
    for (std::vector<int>::iterator p = o.tape_contents.begin(); p != o.tape_contents.end(); p++){
      std::cout << *p << ' ';
      sum = 2 * sum + *p;
    }
    std::cout << "With Response Time = "<< sum/o.tape_contents.size() << "\n\n\n";
    tape ++;
  }
}

int main(int argc, char const *argv[]) {
  int num_tapes,num_progs;
  std::cout << "Enter Number of Tapes:";
  std::cin >> num_tapes;
  std::cout << "Enter Their Sizes:" << '\n';
  int tapes[num_tapes];
  for (int i = 0; i < num_tapes; i++)
    std::cin >> tapes[i];
  std::cout << "Enter Number of Programs:";
  std::cin >> num_progs;
  std::cout << "Enter Their Sizes:" << '\n';
  int progs[num_progs];
  for (int i = 0; i < num_progs; i++)
    std::cin >> progs[i];
  OptimalStorage os(num_tapes,tapes,num_progs,progs);
  os.Optimize();
  os.displayOptimal();

  return 0;
}
