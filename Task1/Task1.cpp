
#include <iostream>

int weight_var1(unsigned int x);
int weight_var2(unsigned int x);
int weight_var3(unsigned int x);
int weight_var4(unsigned int x);

using namespace std;


int main()
{
    unsigned int userNumber;

    cout << "Task 1" << endl << "Enter ZERO to exit" << endl;

    do
    {
        cout << endl << "Input the your number for detecting weight: ";

        cin >> userNumber;

        cout << "Weight is: " << weight_var1(userNumber);

        cout << endl;
        cout << "Weight is: " << weight_var2(userNumber);

        cout << endl;
        cout << "Weight is: " << weight_var3(userNumber);

        cout << endl;
        cout << "Weight is: " << weight_var4(userNumber);
        cout << endl;
    } while (userNumber);
}


/**
 * @brief Calculate count of "1" in input number. Variant 1
 *
 * @param unsigned int x - input number
 *
 * @retval Number of bits equal "1"
 */
int weight_var1(unsigned int x)
{

    /*
    * алгоритма Брайана Кернигана
    *
    */

    int count = 0;

    while (x)
    {
        x &= (x - 1);    // Clear the LSB bits
        count++;
    }

    return count;
}

/**
 * @brief Calculate count of "1" in input number. Variant 2
 *
 * @param unsigned int x - input number
 *
 * @retval Number of bits equal "1"
 */
int weight_var2(unsigned int x)
{

    /*
    * алгоритма Брайана Кернигана
    *
    */

    int count = 0;

    for(;x;count++)
    {
        x &= (x - 1);    // Clear the LSB bits        
    }

    return count;
}

/**
 * @brief Calculate count of "1" in input number. Variant 3
 *
 * @param unsigned int x - input number
 *
 * @retval Number of bits equal "1"
 */
int weight_var3(unsigned int x)
{

    int count = 0;

    for (unsigned char i = 0; i < 32; i++)
    {
        count += (x & 0x01);    // check the last bit
        x >>= 1;                // move to right on 1 bits
    }

    return count;
}

/**
 * @brief Calculate count of "1" in input number. Variant 4
 *
 * @param unsigned int x - input number
 *
 * @retval Number of bits equal "1"
 */
int weight_var4(unsigned int x)
{
    int count = 0;

    for (; x; x >>= 1)
    {
        count += x & 1;
    }

    return count;
}