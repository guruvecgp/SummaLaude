import multiprocessing
import time

def worker_function(name):
    """A function to be executed by a separate process."""
    print(f"Process {name}: Starting...")
    time.sleep(2)  # Simulate some work
    print(f"Process {name}: Finished.")

if __name__ == "__main__":
    print("Main process: Starting...")

    # Create two Process objects
    process1 = multiprocessing.Process(target=worker_function, args=("One",))
    process2 = multiprocessing.Process(target=worker_function, args=("Two",))

    # Start the processes
    process1.start()
    process2.start()

    # Wait for both processes to complete
    process1.join()
    process2.join()

    print("Main process: All processes finished.")
