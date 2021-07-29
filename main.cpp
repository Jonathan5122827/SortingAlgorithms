#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

class Center	{

	public:

		Center();
		void SetInfo(string info);
		string GetInfo();
		string info;
		int value;
		void SetValue(int value);
		int GetValue();
};

void InsertionSort(Center *E[]);

void Merge(Center *E[], Center *tempArr[], int leftPos, int rightPos, int rightEnd);

void MergeSort(Center *E[], Center *tempArr[], int left, int right);

void PrintArray(Center *E[], ofstream &outx);

int leftChild(int i);

void percDown(Center *E[], int i, int n);

void heapSort(Center *E[]);

Center* median3(Center *E[], int left, int right);

void QuickSort(Center *E[], int left, int right);

void HybridQuickSort(Center *E[], int left, int right);


int main(){

	int lines, place = 0;

	string temp;

	ifstream in ("Child_Care_Centers.csv");

	Center *X [121078];

        Center *Temp [121078];

	while(!in.eof())	{


		getline(in,temp);

		int pos ,posx, cnt = 0;

		pos = temp.find(",",37);

		string temp2 = temp.substr(pos + 1,1);

		char c = temp2[0];

		Center *E = new Center();

		E->SetInfo(temp);

		if(c == '"')	{

			E->SetValue(1000);
		}

		else	{

			E->SetValue(c);
		}

		X[place] = E;

		place++;

		lines++;
	}

	X[0]->SetValue(-100);

	ofstream out("SortedCenters.txt");

	int c = 0;

	cout << endl << "Which sorting algorithim would you like to execute:" << endl;

	cout << endl << "1 - Insertion Sort" << endl << "2 - Merge Sort" << endl << "3 - Quick Sort" << endl << "4 - Hybrid Quick Sort" << endl << "5 - Heapsort" << endl;

	cout << endl << "Enter between 1-5: ";

	cin >> c;

        int startx = clock();

	switch(c)	{

		case 1:

			cout << endl << "This will take up to a few minutes to complete!";

			InsertionSort(X);

			PrintArray(X,out);

			break;

		case 2:

			MergeSort(X,Temp,1,121076);

                        PrintArray(X,out);

			break;

		case 3:

			QuickSort(X,1,121076);

			PrintArray(X,out);


			break;

		case 4:

			HybridQuickSort(X,1,121076);

                        PrintArray(X,out);

			break;

		case 5:

			heapSort(X);

			PrintArray(X,out);

			break;

		default:

			cout << "Not a number option" << endl;
	}

                      int stopx = clock();

        cout << endl << "Completed in " <<  (stopx - startx)/double(CLOCKS_PER_SEC)*1000 << " ms" << endl << endl << "Open SortedCenters.txt in the current directory." << endl << endl;

	return 0;
}

void Center::SetInfo(string info)	{

	this->info = info;
}

string Center::GetInfo()	{

	return  this->info;
}

Center::Center()	{

	this->info = "X";
	this->value = -2;
}

void Center::SetValue(int value)	{

	this->value = value;
}

int Center::GetValue()	{

	return this->value;
}

void InsertionSort(Center *E[])	{

	for(int i = 1; i < 121077; i++)	{

		Center *temp = E[i];

		int j;

		for(j = i; j > 0 && temp->GetValue() < E[j-1]->GetValue(); --j)	{

			E[j] = E[j-1];
		}

		E[j] = temp;
	}
}

void PrintArray(Center *E[], ofstream &outx)	{

        for(int i = 0; i < 121077; i++) {

                outx << E[i]->GetInfo() << endl;
                //outx << E[i]->GetValue() << endl;
        }
}

void Merge(Center *E[], Center *tempArr[], int leftPos, int rightPos, int rightEnd)	{

	int leftEnd = rightPos - 1;

	int tmpPos = leftPos;

	int numElem = rightEnd - leftPos + 1;

	while(leftPos <= leftEnd && rightPos <= rightEnd)	{

		//Center *temp = E[leftPos];

		if(E[leftPos]->GetValue() <= E[rightPos]->GetValue())	{

			tempArr[tmpPos++] = E[leftPos++];
		}

		else	{

			tempArr[tmpPos++] = E[rightPos++];
		}
	}

	while(leftPos <= leftEnd)	{

		tempArr[tmpPos++] = E[leftPos++];
	}

	while(rightPos <= rightEnd)	{

		tempArr[tmpPos++] = E[rightPos++];
	}

	for(int i = 0; i < numElem; i++, --rightEnd)	{

		E[rightEnd] = tempArr[rightEnd];
	}
}

void MergeSort(Center *E[], Center *tempArr[], int left, int right)	{

	if(left < right)	{

		int center = (left + right) / 2;

		MergeSort(E,tempArr,left,center);

                MergeSort(E,tempArr,center + 1,right);

		Merge(E,tempArr,left,center + 1,right);

	}
}

int leftChild(int i)	{

	return 2 *i + 1;
}

void percDown(Center *E[], int i, int n)	{


	int child;

	Center *temp;

	for(temp = E[i]; leftChild(i) < n; i = child)	{

		child = leftChild(i);

		if(child != n - 1 && E[child]->GetValue() < E[child + 1]->GetValue())	{

			++child;
		}

		if(temp->GetValue() < E[child]->GetValue())	{

			E[i] = E[child];
		}

		else	{

			break;
		}
	}

	E[i] = temp;
}

void heapSort(Center *E[])	{

	for(int i = (121077/2) - 1; i >= 0; --i)	{

		percDown(E,i,121077);
	}

	for(int j = 121077 - 1; j > 0; --j)	{

		Center *tmp = E[0];

		E[0] = E[j];

		E[j] = tmp;

		percDown(E,0,j);
	}
}

Center* median3(Center *E[], int left, int right)	{

	int center = (left + right) / 2;

	if(E[center]->GetValue() < E[left]->GetValue())	{

		Center *temp = E[center];

		E[center] = E[left];

		E[left] = temp;
	}

	if(E[right]->GetValue() < E[left]->GetValue())	{

		Center *temp = E[right];

		E[right] = E[left];

		E[left] = temp;
	}

	if(E[right]->GetValue() < E[center]->GetValue())	{

		Center *temp = E[right];

		E[right] = E[center];

		E[center] = temp;
	}

	Center *temp = E[center];

	E[center] = E[right - 1];

	E[right - 1] = temp;

	return E[right - 1];

}

void QuickSort(Center *E[], int left, int right)	{

	if(left < right)	{

		Center* pivot = median3(E,left,right);

		int i = left;

		int j = right - 1;

		for(;;)	{

			while(E[++i]->GetValue() < pivot->GetValue())	{}

			while(pivot->GetValue() < E[--j]->GetValue())	{}

			if( i < j)	{

				Center *temp = E[i];

				E[i] = E[j];

				E[j] = temp;
			}

			else	{break;}
		}

		Center *temp = E[i];

		E[i] = E[right - 1];

		E[right - 1] = temp;

		QuickSort(E,left, i - 1);

		QuickSort(E,i + 1, right);

	}
}

void HybridQuickSort(Center *E[], int left, int right)        {

        if(left + 20 < right)        {

                Center* pivot = median3(E,left,right);

                int i = left;

                int j = right - 1;

                for(;;) {

                        while(E[++i]->GetValue() < pivot->GetValue())   {}

                        while(pivot->GetValue() < E[--j]->GetValue())   {}

                        if( i < j)      {

                                Center *temp = E[i];

                                E[i] = E[j];

                                E[j] = temp;
                        }

                        else    {break;}
                }

                Center *temp = E[i];

                E[i] = E[right - 1];

                E[right - 1] = temp;

                QuickSort(E,left, i - 1);

                QuickSort(E,i + 1, right);
        }

	else	{InsertionSort(E);}
}







