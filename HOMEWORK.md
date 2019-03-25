Homework for session 6 (2019-04-01):

* finish the hashtable reallocation function

Homework for session 5 (2019-03-18):

* find what the error was with realloc for AoC/2015/03
* make the hashtable more usable by:
  * using more sophisticated hash key to bucket (pick algorithm)
  * making the size (number of buckets) somehow dynamic
    (either auto or have a special call to extend, or at construction time)
  * making it resilient to buffer re-use by caller:
    hash_put(buf, len, val); where "buf" is reused in a loop

Homework for session 3 (2019-02-08):

* Make a user account for `eric` on laptop ✓
* Fix hashtable\_size and test it ✓
* Double check the includes ~~(cpp-clean from google)~~ ✓
* Read and do the exercises of *SICP 1.1 Elements of Programming*  
  1.1 ✓ 1.2 ✓ 1.3 ✓ 1.4 ✓ 1.5 ✓ 1.6 - 1.7 - 1.8 -
