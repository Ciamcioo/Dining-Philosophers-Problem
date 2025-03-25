# Dining Philosophers Problem

This is a C++ implementation of the classical "Dining Philosophers" problem, which demonstrates synchronization issues in concurrent programming. The philosophers alternate between thinking and eating, requiring two chopsticks to eat.

## Prerequisites

- A C++ compiler (GCC, Clang, or MSVC)
- C++11 or newer

## Compilation

To compile the program, use the following command:

```sh
 g++ -std=c++11 -o dining_philosophers dining_philosophers.cpp -pthread
```

## Usage

Run the compiled program with the number of philosophers as a command-line argument:

```sh
 ./dining_philosophers <number_of_philosophers>
```

For example, to run with 5 philosophers:

```sh
 ./dining_philosophers 5
```

## Explanation

1. Each philosopher starts in a thinking state.
2. They attempt to pick up two chopsticks (left and right).
3. If successful, they eat for a random duration and then put the chopsticks down.
4. If unsuccessful, they keep trying.
5. The process continues until all philosophers have eaten.

## Synchronization Mechanism

- A global mutex (`chopstick_lock`) ensures that chopsticks are picked up and put down safely.
- Boolean array `chopsticks[]` keeps track of chopstick availability.

## Example Output

```
Number of philosophers: 5

[LOG] Philosopher number: 1 has been created
[LOG] Philosopher number: 2 has been created
[LOG] Philosopher number: 3 has been created
...
```

## Notes

- The execution is non-deterministic due to the use of `std::rand()`.
- The solution avoids deadlocks by ensuring mutual exclusion when accessing chopsticks.

## License

This project is licensed under the MIT License.


