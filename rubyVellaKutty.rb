# Create an array to hold the thread objects
threads = []

# Create three threads, each performing a simple task
3.times do |i|
  threads << Thread.new do
    puts "Thread #{i + 1} starting..."
    sleep(rand(0.5..2.0)) # Simulate some work with a random delay
    puts "Thread #{i + 1} finished."
  end
end

puts "Main thread continuing while others run..."

# Wait for all threads to complete before the main thread exits
threads.each(&:join)

puts "All threads have completed, main thread exiting."
