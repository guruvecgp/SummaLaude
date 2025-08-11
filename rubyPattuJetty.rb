# Example of using Threads for concurrent execution
puts "Starting concurrent tasks with Threads..."

threads = []

# Create multiple threads
threads << Thread.new do
  puts "Thread 1 started."
  sleep(2) # Simulate a time-consuming operation
  puts "Thread 1 finished."
end

threads << Thread.new do
  puts "Thread 2 started."
  sleep(1) # Simulate a time-consuming operation
  puts "Thread 2 finished."
end

# Wait for all threads to complete
threads.each(&:join)

puts "All threads completed."
