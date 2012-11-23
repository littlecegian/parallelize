
PARALLELIZATION RESULTS  :

APPROACH :

1) The "list of words to be tested" ie. "input.txt" is split.
2) Each node then performs same "LevDist operation" on the words allocated to it. 


ANALYSIS :

1) In this case the amount of time is improved a lot by parallelisation.
2) 
                Time Sequential ~=   286000   microsec
                Time Parallel     ~=     94300   microsec       ( for 16 nodes)                   
       
                Speedup     = T-Seq/T-Pal  ~= 3.03


   Thus, it saturates to a speedup of 2 or 3 depending on number of threads used
 in the parallel case.

neo@neo:~/Desktop/Now$ mpirun -np 1 a.out 1 

////////////////////////////////////////////////////////////////////////////////

Process Time of word         absence  :  15
Process Time of word       ocidental  :  7079
Process Time of word         acuraci  :  8751
Process Time of word        advanced  :  188
Process Time of word        iffeting  :  5568
Process Time of word       algorithm  :  327
Process Time of word    announcement  :  601
Process Time of word      drrangemet  :  12544
Process Time of word      bradcustin  :  12584
Process Time of word          heapes  :  3257
Process Time of word         commant  :  1399
Process Time of word       compleint  :  1856
Process Time of word     connections  :  2413
Process Time of word        dedicion  :  2964
Process Time of word     differecelt  :  13652
Process Time of word    embarrassing  :  4495
Process Time of word        execusst  :  10036
Process Time of word        dormatty  :  10087
Process Time of word      exeneraton  :  12625
Process Time of word       guarownth  :  11350
Process Time of word         husband  :  3816
Process Time of word       cimposted  :  1946
Process Time of word   inconvenience  :  3247
Process Time of word          leaven  :  3877
Process Time of word       marknater  :  6167
Process Time of word         membory  :  8762
Process Time of word       necessary  :  6641
Process Time of word          lomite  :  7576
Process Time of word    permfissance  :  15011
Process Time of word     procuctmmer  :  9449
Process Time of word         releave  :  6478
Process Time of word          server  :  6056
Process Time of word   stadistioncal  :  15025
Process Time of word         thourgh  :  7983
Process Time of word trainsferlation  :  17545
Process Time of word       upserdate  :  10988
Process Time of word          vision  :  7335
Process Time of word      wherebsver  :  12518
Process Time of word           brite  :  4359
Process Time of word            zero  :  5210


neo@neo:~/Desktop/Now$ mpirun -np 16 a.out 16 

/////////////////////////////////////////////////////////////////////////////////////////////////////

Process Time of word       cimposted  :  1928
Process Time of word   inconvenience  :  3218
Process Time of word          leaven  :  3852
Process Time of word           brite  :  4384
Process Time of word            zero  :  5199
Process Time of word          heapes  :  7306
Process Time of word         commant  :  68871
Process Time of word       compleint  :  1846
Process Time of word        advanced  :  431
Process Time of word        iffeting  :  113218
Process Time of word       algorithm  :  328
Process Time of word         releave  :  6473
Process Time of word          server  :  62081
Process Time of word    permfissance  :  53263
Process Time of word     procuctmmer  :  37436
Process Time of word       marknater  :  6147
Process Time of word         membory  :  92369
Process Time of word trainsferlation  :  52800
Process Time of word       upserdate  :  24163
Process Time of word      exeneraton  :  80751
Process Time of word       guarownth  :  24521
Process Time of word         husband  :  19142
Process Time of word   stadistioncal  :  90075
Process Time of word         thourgh  :  8016
Process Time of word          vision  :  7263
Process Time of word      wherebsver  :  86818
Process Time of word       necessary  :  6593
Process Time of word          lomite  :  121306
Process Time of word     connections  :  5444
Process Time of word        dedicion  :  72264
Process Time of word     differecelt  :  76356
Process Time of word    embarrassing  :  4488
Process Time of word        execusst  :  90060
Process Time of word        dormatty  :  54497
Process Time of word         absence  :  14
Process Time of word       ocidental  :  66990
Process Time of word         acuraci  :  8756
Process Time of word    announcement  :  1331
Process Time of word      drrangemet  :  133659
Process Time of word      bradcustin  :  57747

///////////////////////////////////////////////////////////////////////////////////////////////////////

FULL OUTPUT :  (for 16 threads)

Matching word  3 by rank 1 : advanced
Spelling is correct.
Matching word  4 by rank 1 : iffeting
Spelling is incorrect.
Suggestions :
1 : affecting
2 : deleting
3 : different
4 : effective
5 : feeding
6 : feeling
7 : fitting
8 : inserting
9 : inventing
10 : inviting
Matching word  5 by rank 1 : algorithm
Spelling is correct.
Process Time of word        advanced  :  428
Process Time of word        iffeting  :  45748
Process Time of word       algorithm  :  732
Matching word  38 by rank 15 : brite
Spelling is incorrect.
Suggestions :
1 : arise
2 : bit
3 : bite
4 : bites
5 : bits
6 : brief
7 : bring
8 : broke
9 : byte
10 : drive
Matching word  39 by rank 15 : zero
Spelling is correct.
Process Time of word           brite  :  4334
Process Time of word            zero  :  5168
Matching word  9 by rank 3 : heapes
Spelling is incorrect.
Suggestions :
1 : cheaper
2 : cheapest
3 : head's
4 : headed
5 : header
6 : heads
7 : hears
8 : heat's
9 : helped
10 : helps
Matching word  10 by rank 3 : commant
Spelling is incorrect.
Suggestions :
1 : combine
2 : coming
3 : command
4 : commands
5 : comment
6 : comment's
7 : commented
8 : commenting
9 : comments
10 : committee
Matching word  11 by rank 3 : compleint
Spelling is incorrect.
Suggestions :
1 : collect
2 : combine
3 : combining
4 : coming
5 : comment
6 : comments
7 : company
8 : comparing
9 : compiler
10 : compiler's
Process Time of word          heapes  :  7352
Process Time of word         commant  :  97038
Process Time of word       compleint  :  1859
Matching word  26 by rank 9 : necessary
Spelling is correct.
Matching word  27 by rank 9 : lomite
Spelling is incorrect.
Suggestions :
1 : limit
2 : limit's
3 : limited
4 : limits
5 : omit
6 : omits
7 : omitted
Process Time of word       necessary  :  25426
Process Time of word          lomite  :  7662
Matching word  21 by rank 7 : cimposted
Spelling is incorrect.
Suggestions :
1 : closed
2 : commented
3 : compared
4 : complete
5 : completed
6 : completes
7 : compose
8 : composed
9 : composes
10 : composing
Matching word  22 by rank 7 : inconvenience
Spelling is incorrect.
Suggestions :
1 : conference
2 : consequence
3 : consequences
4 : convenient
5 : convention
6 : convention's
7 : conventional
8 : conventions
9 : convince
10 : convinced
Matching word  23 by rank 7 : leaven
Spelling is incorrect.
Suggestions :
1 : cleared
2 : clearer
3 : eaten
4 : even
5 : leaded
6 : leader
7 : leading
8 : learn
9 : leave
10 : leaved
Process Time of word       cimposted  :  95643
Process Time of word   inconvenience  :  79512
Process Time of word          leaven  :  3863
Matching word  24 by rank 8 : marknater
Spelling is incorrect.
Suggestions :
1 : greater
2 : manage
3 : managed
4 : manager
5 : manages
6 : manner
7 : marked
8 : market
9 : market's
10 : marriage
Matching word  25 by rank 8 : membory
Spelling is incorrect.
Suggestions :
1 : member
2 : member's
3 : members
4 : memory
5 : memory's
Process Time of word       marknater  :  84992
Process Time of word         membory  :  8709
Matching word  30 by rank 11 : releave
Spelling is incorrect.
Suggestions :
1 : behave
2 : believe
3 : delete
4 : leave
5 : leaved
6 : leaves
7 : please
8 : receive
9 : received
10 : receives
Matching word  31 by rank 11 : server
Spelling is correct.
Process Time of word         releave  :  6442
Process Time of word          server  :  64356
Matching word  28 by rank 10 : permfissance
Spelling is incorrect.
Suggestions :
1 : performance
2 : performance's
3 : permission
4 : permission's
Matching word  29 by rank 10 : procuctmmer
Spelling is incorrect.
Suggestions :
1 : customer
2 : produce
3 : produced
4 : produces
5 : product
6 : product's
7 : production
8 : products
9 : programmer
10 : programmers
Process Time of word    permfissance  :  43996
Process Time of word     procuctmmer  :  30401
Matching word  34 by rank 13 : trainsferlation
Spelling is incorrect.
Suggestions :
1 : administration
2 : consideration
3 : conversation
4 : demonstration
5 : generation
6 : information
7 : instruction
8 : manipulation
9 : observation
10 : relation
Matching word  35 by rank 13 : upserdate
Spelling is incorrect.
Suggestions :
1 : alternate
2 : desperate
3 : generate
4 : operate
5 : operated
6 : operates
7 : update
8 : updated
9 : updates
10 : upset
Process Time of word trainsferlation  :  5425
Process Time of word       upserdate  :  18240
Matching word  6 by rank 2 : announcement
Spelling is correct.
Matching word  7 by rank 2 : drrangemet
Spelling is incorrect.
Suggestions :
1 : arrange
2 : arranged
3 : arrangement
4 : arrangement's
5 : arrangements
6 : arranges
Matching word  8 by rank 2 : bradcustin
Spelling is incorrect.
Suggestions :
1 : broadcast
2 : broadcasting
3 : broadcasts
Process Time of word    announcement  :  1367
Process Time of word      drrangemet  :  19013
Process Time of word      bradcustin  :  12528
Matching word  36 by rank 14 : vision
Spelling is correct.
Matching word  37 by rank 14 : wherebsver
Spelling is incorrect.
Suggestions :
1 : whatever
2 : whenever
3 : whereas
4 : whereby
5 : wherever
6 : whoever
Process Time of word          vision  :  11123
Process Time of word      wherebsver  :  122076
Matching word  12 by rank 4 : connections
Spelling is incorrect.
Suggestions :
1 : actions
2 : collecting
3 : collection
4 : collection's
5 : collects
6 : commenting
7 : competition
8 : competition's
9 : concept's
10 : concerning
Matching word  13 by rank 4 : dedicion
Spelling is incorrect.
Suggestions :
1 : addition
2 : decision
3 : decision's
4 : decisions
5 : dedicate
6 : dedicated
7 : dedicates
8 : dedicating
9 : division
10 : edition
Matching word  14 by rank 4 : differecelt
Spelling is incorrect.
Suggestions :
1 : differ
2 : difference
3 : difference's
4 : differences
5 : different
6 : differently
7 : difficult
8 : difficulty
9 : direct
10 : directly
Process Time of word     connections  :  5431
Process Time of word        dedicion  :  -877390
Process Time of word     differecelt  :  71770
Matching word  32 by rank 12 : stadistioncal
Spelling is incorrect.
Suggestions :
1 : additional
2 : distinct
3 : distinctly
4 : national
5 : station
6 : station's
7 : stations
8 : statistic
9 : statistical
10 : statistics
Matching word  33 by rank 12 : thourgh
Spelling is incorrect.
Suggestions :
1 : church
2 : enough
3 : fourth
4 : hour
5 : hour's
6 : hours
7 : rough
8 : though
9 : thought
10 : thoughts
Process Time of word   stadistioncal  :  81248
Process Time of word         thourgh  :  92111
Matching word  18 by rank 6 : exeneraton
Spelling is incorrect.
Suggestions :
1 : generate
2 : generated
3 : generates
4 : generating
5 : generation
6 : generation's
Matching word  19 by rank 6 : guarownth
Spelling is incorrect.
Suggestions :
1 : grown
2 : growth
3 : guarantee
Matching word  20 by rank 6 : husband
Spelling is correct.
Process Time of word      exeneraton  :  3884
Process Time of word       guarownth  :  105389
Process Time of word         husband  :  22122
Matching word  0 by rank 0 : absence
Spelling is correct.
Matching word  1 by rank 0 : ocidental
Spelling is incorrect.
Suggestions :
1 : accident
2 : accident's
3 : accidental
4 : accidentally
5 : central
6 : ideal
7 : identical
8 : incident
9 : incident's
10 : incidentally
Matching word  2 by rank 0 : acuraci
Spelling is incorrect.
Suggestions :
1 : accuracy
2 : accuracy's
3 : accurate
4 : attract
Process Time of word         absence  :  14
Process Time of word       ocidental  :  55098
Process Time of word         acuraci  :  8763
Matching word  15 by rank 5 : embarrassing
Spelling is correct.
Matching word  16 by rank 5 : execusst
Spelling is incorrect.
Suggestions :
1 : excess
2 : excuse
3 : execute
4 : executed
5 : executes
6 : executing
Matching word  17 by rank 5 : dormatty
Spelling is incorrect.
Suggestions :
1 : format
2 : format's
3 : normally
Process Time of word    embarrassing  :  10082
Process Time of word        execusst  :  87301
Process Time of word        dormatty  :  73800
