#include <iostream>

#include "interruptible_thread.h"

using namespace iret;

void func()
{
  condition_variable_any cnd;
  mutex mtx;

  interruption_point();
  cout << 1 << endl;
  interruption_point();

  unique_lock<mutex> lck(mtx);
  interruptible_wait(cnd, lck, [] { return false; });
}

int main()
{
  interruptible_thread th(func);

  th.interrupt();
  th.join();

  return 0;
}