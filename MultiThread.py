import threading
import time

def task(name, delay):
    """
    A function to be executed by each thread.
    Simulates a task with a delay.
    """
    print(f"Thread '{name}': Starting task...")
    for i in range(3):
        print(f"Thread '{name}': Step {i+1}")
        time.sleep(delay)  # Simulate work
    print(f"Thread '{name}': Task finished.")

if __name__ == "__main__":
    print("Main thread: Starting program.")

    # Create two threads
    thread1 = threading.Thread(target=task, args=("Thread 1", 1))
    thread2 = threading.Thread(target=task, args=("Thread 2", 0.5))

    # Start the threads
    thread1.start()
    thread2.start()

    # Wait for both threads to complete
    thread1.join()
    thread2.join()

    print("Main thread: All threads have finished. Exiting program.")
