#include <iostream>
using namespace std;

typedef struct MinMax {
  /* data */
  int min;
  int max;
}MinMax;


void minMax(int start,int end,int *array,MinMax *m)
{


	if (end - start == 1)
	{
    std::cout << "Array of Size 1 detected\nMin and Max will be:"<<array[start] << "\n\n\n";

    m->min = array[start];
		m->max = array[start];
		return;
	}
	else if (end - start == 2)
	{
    std::cout << "Array of Size 2 Detected" << '\n';
		if (array[start] > array[end - 1])
		{
			m->min = array[end - 1];
			m->max = array[start];
		}
		else
		{
			m->min = array[start];
			m->max = array[end - 1];
		}
    std::cout << "Min is:"<<m->min<<"\nMaximum is:"<<m->max << "\n\n\n";
		return;
	}
	MinMax *left = new MinMax;
	MinMax *right = new MinMax;
	int mid = (start + end)/2;
  std::cout << "Finding Min and Max for left Half("<<start<<','<<mid<<')'<< '\n';
	minMax(start, mid+1,array , left);
  std::cout << "Min of left half is:"<<left->min<<"\nMax of right half is:"<<left->max<< "\n\n";
  std::cout << "Finding Min and Max for right Half("<<mid+1<<','<<end -1<<')'<< '\n';
	minMax(mid+1, end,array , right);
  std::cout << "Min of right half is:"<<left->min<<"\nMax of right half is:"<<left->max<< "\n\n";


	m->min = left->min;
	m->max = left->max;
	if (left->min > right -> min)
		m->min = right ->min;
	if (left->max < right -> max)
		m->max = right->max;
  std::cout << "Min for both halves is:"<<m->min<<"Max for both halves is:"<<m->max<< "\nGoing One level Up\n\n\n\n";
}


int main(int argc, char const *argv[]) {
  int *array;
  int n;
  std::cout << "Enter Array Size:";
  cin>>n;
  array = new int(n);
  for (size_t i = 0; i < n; i++) {
    std::cout << "Enter Element [" <<i<< "]:";
    cin >> array[i];
  }
  MinMax *m = new MinMax;
  minMax(0,n,array,m);
  cout<<"Minimum is :"<<m->min<<"\nMaximum is :"<<m->max<<"\n\n";
  return 0;
}
