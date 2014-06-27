Scheduler simulation
=====

The binary reads from 2 pre-defined input files
  * jobs.txt
  * resources.txt


Since we're simulating real we need a way to represent time in the input files. We've broken the time continuum into discrete time ticks and assume that nothing happens between these ticks. Each tick is represented by a line in each input file. If nothing happens during a tick, there should be an empty line. This is necessary because we need to have some relative ordering of resource available events vs job request events, and using file (input stream) line numbers as time counters seems pretty natural. 

Here's an example of resources.txt

'''
(1 4) (2 5) (3 5) (1 2)

(2 1) (3 1)
(1 5) (2 10)
'''

Here there were 4 events during T=0, no events during T=1, 2 events during T=2 and 2 events during T=3
jobs.txt file should follow the same pattern and then our simulator iterates over the input streams in parallel, one tick at a time.


the format for the resources.txt and jobs.txt is according to the spec: 
resources.txt: (1 4) means node 1 has 4 units available.
jobs.txt: (4 6) (3 6) means that jobId=1 needs 4 units for 6 time units and jobId=2 needs 3 units for 6 seconds.

We've provided two scheduler implementations:
  * First come first served scheduler
  * Shortest time first scheduler



