/*************************************************************************
 * Sample code (binary Predicate)
 *************************************************************************/
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

class Food
{
private:
   string mName;

public:
   Food(string name)
   {
      mName = name;
   }

   string getName() { return mName; }

} f0("eggs"), f1("bacon"), f2("sandwich"), f3("roast"), f4("potatoes");

class Meal
{
private:
   string mName;

public:
   Meal(string name)
   {
      mName = name;
   }

   string getName() { return mName; }

} m0("breakfast"), m1("lunch"), m2("dinner");

template <typename T1, typename T2>
class IsTypicallyAssociatedWith : public Predicate<Food, Meal>
{
public:
   bool isTrue(Food f, Meal m)
   {
      // work some better magic here
      string food = f.getName();
      string meal = m.getName();
      if (meal == "breakfast")
      {
         return (food == "eggs" or
                 food == "bacon");
      }
      else if (meal == "lunch")
      {
         return (food == "sandwich");
      }
      else if (meal == "dinner")
      {
         return (food == "roast" or
                 food == "potatoes");
      }
      else
      {
         return false;
      }
   }

   bool isFalse(Food f, Meal m)
   {
      return ! isTrue(f, m);
   }
};
