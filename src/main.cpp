#include <iostream>
#include <string>
#include <thread> 
#include <mutex>

#define STR(X) STR_HELLPER(X)
#define STR_HELLPER(X) #X

#define BASIC_LOG "[LOG] Philosopher number: %d"

const char philosopher_log[]                       = BASIC_LOG "\n";
const char philosopher_create_log[]                = BASIC_LOG " has been created\n";
const char philosopher_thinking_log[]              = BASIC_LOG " is thinking\n";
const char philosopher_stop_thinking[]             = BASIC_LOG " stops thinking\n";
const char philosopher_picked_chopstick[]          = BASIC_LOG " picked the %s chopstick\n";
const char philosopher_try_to_eat[]                = BASIC_LOG " tries to eat\n";
const char philosopher_start_eating_log[]          = BASIC_LOG " starts eating\n";
const char philosopher_finish_eating_log[]         = BASIC_LOG " finish eating\n";
const char philosopher_put_down_chopstick[]        = BASIC_LOG " put down the %s chopstick\n";

std::mutex chopstick_lock;
bool* chopsticks;
int philosophers_number = 0;

void put_down_chopstick(int index) {
   index = index % philosophers_number;
   chopsticks[index]=true;
   return;
}

void put_down_chopsticks(int philosopher_index) {
   int left_chopstick = philosopher_index-1;
   int right_chopstick = philosopher_index;

   put_down_chopstick(left_chopstick);
   printf(philosopher_put_down_chopstick, philosopher_index, "left");

   put_down_chopstick(right_chopstick);
   printf(philosopher_put_down_chopstick, philosopher_index, "right");

   return;
}


bool try_to_pick_chopstick(int index) {
   index = index % philosophers_number;

   if (chopsticks[index]) {
      chopsticks[index] = false;
      return true;
   }

   return false;
}

bool try_to_pick_chopsticks(int philosopher_index) {
   int left_chopstick = philosopher_index-1;
   int right_chopstick = philosopher_index;

   if (try_to_pick_chopstick(left_chopstick)) {
      printf(philosopher_picked_chopstick, philosopher_index, "left"); 

      if (try_to_pick_chopstick(right_chopstick)) {
         printf(philosopher_picked_chopstick, philosopher_index, "right");
         return true;
      }
      else {
         put_down_chopstick(left_chopstick);
         printf(philosopher_put_down_chopstick, philosopher_index, "left");
      }
   }

   return false;
}

bool try_to_eat(int philosopher_index) {
   bool isEating = false;

   chopstick_lock.lock();
   
   isEating =  try_to_pick_chopsticks(philosopher_index); 

   chopstick_lock.unlock();

   if (isEating) {
      printf(philosopher_start_eating_log, philosopher_index); 

      int time_to_eat = std::rand() % 15;
      std::this_thread::sleep_for(std::chrono::seconds(time_to_eat));
      printf(philosopher_finish_eating_log, philosopher_index);

      chopstick_lock.lock();

      put_down_chopsticks(philosopher_index);
      
      chopstick_lock.unlock();

      return true;
   }

   return false;
   

}

void philosopher_action(int philosopher_index) {
   printf(philosopher_create_log, philosopher_index);

   printf(philosopher_thinking_log, philosopher_index);

   int time_to_think = std::rand() % 30; 
   std::this_thread::sleep_for(std::chrono::seconds(time_to_think));

   printf(philosopher_stop_thinking, philosopher_index);

   bool hasEatten = false;
   do {
      printf(philosopher_try_to_eat, philosopher_index);
      hasEatten = try_to_eat(philosopher_index);
   } while(!hasEatten);

   return;
}

int main(int argc, char* args[]) {
   std::srand(std::time(0));
   philosophers_number = std::stoi(args[1]);
   std::cout << "Number of philosophers: " << philosophers_number << std::endl; 

   chopsticks = new bool[philosophers_number];
   for (int i = 0 ; i < philosophers_number; i++) {
      chopsticks[i] = true;
   }

   std::cout << std::endl << std::endl;

   std::thread philosopher[philosophers_number];
   for (int i = 0; i < philosophers_number; i++) {
      philosopher[i] = std::thread(philosopher_action, i+1);
   }

   for (int i = 0; i < philosophers_number; i++) {
      philosopher[i].join();
   } 

   return 0;
}
