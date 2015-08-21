Public-code
===========

I feel that these pieces of code are small and don't deserve their own repositories. Code is added at the end of the year from the private git repository that I use for Uni.

###Bits and pieces of code written at Uni, available for public access

**automata.c** - Buids a deterministic automata and checks if given words are accepted or not

**BFS.cpp, DFS.cpp** - BFS and DFS implementation in C++

**BFS_DFS.java** - BFS and DFS implementation in Java

**DiceThrows.java** - If you throw a n-sided dice X times, how many times will each possible combination of sums appear?

**doubly_linked_list.c** - a doubly-linked list implementation

**hangman.c** - A Hangman game implementation. Has as input files domains that have 10 words each. Player can chose the domain for the word that has to be guessed

**linked_list.c** - a linked list implementation

**min_max_vector.c** - gets the minimum and maximum value from a vector, using minimal number of comparisons

**poli.c** - calculates the sum of two polynomials

**queue.c** - a queue implementation

**stack.c** - a stack implementation

**list_files.c** - an implementation of `tree /f` from DOS. Recursively lists all directories and files from a parent directory given as a command line argument

***tic-tac-toe.pl*** - Tic-Tac-Toe game with AI implemented in Prolog.

**EmailServer.java** and **EmailClient.java**:
Your task is to code a simplified email server and client. Then run the server program in one command window and the client program consecutively in each of two further command
windows. For the first client, log in with one of the names specified below (i.e., 'Dave' or 'Karen') and send a few emails (fewer than 10) to the other user. Then quit and run the
client program again, this time logging in as the other user and selecting reading of his/her emails. The full details of this simplified client–server application are given below.

- The server recognizes only two users, called 'Dave' and 'Karen'.
- Each of the above users has a message box on the server that can accept a maximum of 10 messages.
- Each user may either send a one-line message to the other or read his/her own messages.
- A count is kept of the number of messages in each mailbox. As another message is received, the appropriate count is incremented (if the maximum has not been reached). When messages are read, the appropriate count is reduced to zero.
- When sending a message, the client sends three things: the user's name, the word 'send' and the message itself.
- When requesting reading of mail, the client sends two things: the user's name and the word 'read'.
- As each message is received by the server, it is added to the appropriate mailbox (if there is room). If the mailbox is full, the message is ignored.
- When a read request is received, the server fi rst sends an integer indicating the number of messages (possibly 0) that will be sent and then transmits the messages
themselves (after which it reduces the appropriate message count to 0).
- Each user is to be allowed to 'send' and/or 'read' as many times as he/she wishes, until he/she decides to quit.
- When the user selects the 'quit' option, the client sends two things: the user's name and then the word 'quit'.
