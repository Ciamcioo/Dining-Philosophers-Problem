#include <iostream>
#include <string>
#include <thread> 


#define STR(X) STR_HELLPER(X)
#define STR_HELLPER(X) #X

#define BASIC_LOG "Philosopher number: %d"

const char philosopher_log[]                       = BASIC_LOG "\n";
const char philosopher_thinking_log[]              = BASIC_LOG " is thinking\n";
const char philosopher_wake_up_log[]               = BASIC_LOG " is waking up\n";
const char philosopher_eating_log[]                = BASIC_LOG " is eating\n";
const char philosopher_is_putting_down_chopstick[] = BASIC_LOG " is puttting down chopstick\n";

void philosopher_action(int id) {
   printf(philosopher_log, id);

   int time_to_think = std::rand() % 120; 
   printf(philosopher_thinking_log, id);
   std::this_thread::sleep_for(std::chrono::seconds(time_to_think));
   printf(philosopher_wake_up_log, id);
   return;
}

int main(int argc, char* args[]) {
   const int PHILOSOPHERS_NUM = std::stoi(args[1]);
   std::cout << "Number of philosophers: " << PHILOSOPHERS_NUM << std::endl; 

   std::srand(std::time(0));

   std::cout << std::endl << std::endl;

   std::thread philosopher[PHILOSOPHERS_NUM];
   for (int i = 0; i < PHILOSOPHERS_NUM; i++) {
      philosopher[i] = std::thread(philosopher_action, i+1);
   }


   for (int i = 0; i < PHILOSOPHERS_NUM; i++) {
      philosopher[i].join();
   } 

   return 0;
}
