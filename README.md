# Hopcroft-Tarjan-Planarity-Testing



    CMPUT 403 Project Proposal
    
    The Hopcroft-Tarjan Planarity Algorithm is a Linear-Time planarity testing algorithm designed by John Hopcroft and Robert Tarjan in 1974. The algorithm uses what is called the Path Addition Method.  The algorithm uses a depth-first-search to find two 'low-point arrays' and assigns weights to the edges of G, where the weight is computed from the low-points. The algorithm then sorts incident edges based on weight and performs another DFS called the 'pathfinder' which embeds the graph in the plane.
    
    To understand and implement the algorithm I will follow the original paper which outlines the design [1] and I have a supplementary paper [2] which attempts to outline some intuition behind the algorithm and expose some of the finer details.
    
    For testing I will have a sample file which includes various graphs which are known to be planar or non-planar, I will run the algorithm on such graphs and assert the the output matches the planarity labels for the graphs.
    
    [1] Hopcroft, John; Tarjan, Robert E. (1974), "Efficient planarity testing", Journal of the Association for Computing Machinery 21 (4): 549–568, doi:10.1145/321850.321852.
    
    [2]William Kocay. (1993) “The Hopcroft-Tarjan Planarity Algorithm”, University Of Manitoba http://www.combinatorialmath.ca/G&G/articles/planarity.pdf
    
    Shawn Anderson
