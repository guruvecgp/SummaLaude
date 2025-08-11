#!/usr/bin/perl
use strict;
use warnings;
use threads;
use threads::shared; # Required for shared variables

# Declare a shared variable
my $counter :shared = 0;

sub worker_thread {
    my ($thread_id) = @_;
    print "Thread $thread_id: Starting...\n";

    # Increment shared counter with a lock to prevent race conditions
    {
        lock($counter);
        $counter++;
    }

    sleep(2); # Simulate some work

    print "Thread $thread_id: Finished. Counter: $counter\n";
    return "Thread $thread_id completed";
}

print "Main process: Starting threads...\n";

my @threads;
for my $i (1..3) {
    # Create a new thread and pass an argument
    push @threads, threads->create(\&worker_thread, $i);
}

# Wait for all threads to complete and retrieve their return values
foreach my $thr (@threads) {
    my $result = $thr->join();
    print "Main process: Received result from thread: $result\n";
}

print "Main process: All threads finished. Final counter value: $counter\n";
