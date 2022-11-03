#include <iostream>
using namespace std;
class Hashing
{
private:
    int *HT;    // array->hash table
    int HS;     // hash size
    int count;  // use in rehashing
    float load; // count/HS
public:
    Hashing()
    {
        this->load = 0;
        this->count = 0;
        this->HS = 10;
        this->HT = (int *)malloc(HS * sizeof(int));
        //  HT = new int(HS);
        for (int i = 0; i < HS; i++)
        {
            this->HT[i] = -1;
        }
    }
    Hashing(int HS)
    {
        this->load = 0;
        this->count = 0;
        this->HS = HS;
        this->HT = (int *)malloc(HS * sizeof(int));
        // HT = new int(HS);
        for (int i = 0; i < HS; i++)
        {
            this->HT[i] = -1;
        }
    }
    int givePrime(int n)
    {
        bool is_prime = true;
        if (n == 0 || n == 1)
        {
            is_prime = false;
        }
        // loop to check if n is prime
        for (int i = 2; i <= n / 2; ++i)
        {
            if (n % i == 0)
            {
                is_prime = false;
                break;
            }
        }
        if (is_prime)
        {
            return n;
        }
        else{
            return givePrime(n+1);
        }       
    }
    void insertKey(int x)
    {
        if (load >= 0.5) 
        {
            cout << "Rehashing" << endl;
            int loadArray[count];
            int k = 0;
            for (int j = 0; j < HS; j++)
            {
                if (HT[j] != -1)
                {
                    loadArray[k++] = HT[j];
                }
            }
            int temp_count = count;
            this->load = 0;
            this->count = 0;
            free(HT);
            this->HS = givePrime(HS * 2);
            this->HT = (int *)malloc(HS * sizeof(int));
            for (int i = 0; i < HS; i++)
            {
                this->HT[i] = -1;
            }
            for (int i = 0; i < temp_count; i++)
            {
                insertKey(loadArray[i]);
            }
        }
        int HI = x % HS;
        int i = HI;
        while (HT[i] != -1)
        {
            i = (i + 1) % HS; //linear probing
        }
        HT[i] = x;
        this->count++;
        this->load = float(count) / float(HS);
    }
    void displayHT()
    {

        cout << "The Hash Table is :" << endl;
        for (int i = 0; i < HS; i++)
        {
            cout << i << " - "
                 << "[" << HT[i] << "]" << endl;
        }
    }
    bool searchInHT(int key){
        int HI = key % HS;
        int i = HI;
        while(HT[i]!=-1){
            if(HT[i] == key){
                return true;
            }
            else{
                i = (i+1) % HS;
            }
        }
        return false;
    }
};
int main()
{
    int Hs;
    cout << "Enter the total size of Hash table :";
    cin >> Hs;
    int count;
    Hashing h1(Hs);
    int option, key;
    do
    {
        cout << "What operations do you want to perform?Select Option Number.Enter 0 to exit." << endl;
        cout << "1. insertValue" << endl;
        cout << "2. print Hash Table" << endl;
        cout << "3. search In Hash Table" << endl;
        cout << "4. Clear Screen" << endl;
        cin >> option;
        switch (option)
        {
        case 0:
            cout << "Thanks !!" << endl;
            break;
        case 1:
            cout << "Enter the data you want to insert" << endl;
            cin >> key;
            h1.insertKey(key);
            break;
        case 2:
            h1.displayHT();
            break;
        case 3:
            int s;
            cout<<"Enter the key that you want to search in Hash table :";
            cin>>s;
            cout<<endl;
            bool res;
            res = h1.searchInHT(s);
            if(res == true){
                cout << s << " key has been located in the Hash table!!!" << endl;
                cout<<endl;
            }
            else{
                cout << s << " key is not present in the Hash table!!!" << endl;
                cout<<endl;
            }
            break;
        case 4:
            system("cls");
            break;
        default:
            cout << "Enter proper option Number " << endl;
        }
    } while (option != 0);
    return 0;
}
