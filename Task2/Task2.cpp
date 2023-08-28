
#include <iostream>


using namespace std;


int parity_var1(unsigned int x);
int parity_var2(unsigned int x);
int parity_var3(unsigned int x);


int main()
{

    setlocale(LC_ALL, "Russian");

    cout << "Task 2" << endl;

    unsigned int userNumber;
    do
    {

        cout << endl << "Input the your number for detecting parity: ";

        cin >> userNumber;

        if (parity_var1(userNumber))
        {
            cout << "Your number is Even" << endl;
        }
        else
        {
            cout << "Your number is Odd" << endl;
        }

        if (parity_var2(userNumber))
        {
            cout << "Your number is Even" << endl;
        }
        else
        {
            cout << "Your number is Odd" << endl;
        }


        if (parity_var3(userNumber))
        {
            cout << "Your number is Even" << endl;
        }
        else
        {
            cout << "Your number is Odd" << endl;
        }

    } while (userNumber);
}


/**
 * @brief Determines the parity of a input number. Variant 1
 *
 * @param unsigned int x - input number
 *
 * @retval "1" if number is Even, "0" - odd
 */
int parity_var1(unsigned int x)
{
    /*
    * Value mod 2
    */
    if ((x % 2) == 0)
    {
        return 1;
    }

    return 0;
}

/**
 * @brief Determines the parity of a input number. Variant 2
 *
 * @param unsigned int x - input number
 *
 * @retval "1" if number is Even, "0" - odd
 */
int parity_var2(unsigned int x)
{
    /*
    * Value mod 2
    */
    return !(x % 2);
}

/**
 * @brief Determines the parity of a input number. Variant 3
 *
 * @param unsigned int x - input number
 *
 * @retval "1" if number is Even, "0" - odd
 */
int parity_var3(unsigned int x)
{
    /*
    * Check the LSB bit
    */
    return !(x & 0x01);
}

