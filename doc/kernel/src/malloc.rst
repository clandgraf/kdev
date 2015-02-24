Memory Allocation
=================

The memory allocator implemented in the kernel is inspired by Doug Lea's malloc, see http://g.oswego.edu/dl/html/malloc.html.

Binning
-------

Free chunks of memory are kept in fast bins or normal bins. Fast bins contain chunks of a fixed size and are provided from size 16 to 512 bytes in 8 byte steps. Normal bins store chunks of up to their size. Each bin contains a linked list of all free chunks of its size. The bin itself is implemented as a pointer to the first free chunk. 

Chunk Layout
------------

The minimum chunk size is 16 byte. Each chunk of memory has a header and a footer containing the size of the chunk. The header additionally stores the `used` flag in its least significant bit (since chunk sizes are multiples of 8 bytes this bit can be used, but must be masked out to use the size of the chunk).

When a chunk is not used, the second and third 32 bit are used to store the nodes next and previous pointer of the linked list in the bin.

.. code::

   0                   sizeof(chunk)  | used-bit
   4                   next free chunk
   8                   previous free chunk
   . . .               user memory
   sizeof(chunk) - 4   sizeof(chunk)
